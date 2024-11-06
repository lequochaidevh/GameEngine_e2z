#pragma once
#include"MemoryManager.h"
#include"Core/Logger/Logger.h"
namespace VIEngine {
	template<typename T, std::size_t MAX_OBJECT_PER_CHUNK>
	class MemoryChunkManager : public MemoryManager {
		static constexpr size_t MEMORY_CHUNK_MAX_SIZE = sizeof(T) * MAX_OBJECT_PER_CHUNK;
		using ObjectList = std::list<T*>;
		class MemoryChunk {
		public:
			MemoryChunk(PoolAllocator* allocator) : mAllocator(allocator) {
			}
			void* allocate() {
				void* memory = mAllocator->allocate();
				VI_ASSERT(memory && "Failed to allocate memory");
				mObjectList.emplace_back((T*)memory);
				return memory;
			}
			//TODO:work not found case
			void free(void* memory) {				
				auto iter = std::find(mObjectList.begin(), mObjectList.end(), memory);
				if (iter != mObjectList.end()) {
					mAllocator->free(memory); //
					mObjectList.erase(iter);
				}
			}
			bool hasSlot() {
				return mObjectList.size() < MAX_OBJECT_PER_CHUNK;
			}
			bool contains(void* memory) {
				return mAllocator->contains(memory);
			}
			const ObjectList& getObjects() const { return mObjectList; }

			void clear() {
				mAllocator->clear();
				mObjectList.clear();
			}
			void close() {
				clear();
				VI_FREE_MEMORY(mAllocator);
			}
			void* getStartAddress() const { return mAllocator->getStartAddress(); }
		private:
			PoolAllocator* mAllocator;
			ObjectList mObjectList;
		};
		using MemoryChunkList = std::list<MemoryChunk*>;
		class Iterator {
		public:
			Iterator(typename MemoryChunkList::iterator begin, typename MemoryChunkList::iterator end) : mCurrentChunk(begin), mEndChunk(end) {
				if (begin != end) {
					VI_ASSERT(*mCurrentChunk && "Invalid memory chunk");
					mCurrentObject = (*mCurrentChunk)->getObjects().begin();
				}
				else {
					mCurrentObject = (*std::prev(mEndChunk))->getObjects().end();
				}
			}
			Iterator& operator++() {
				mCurrentObject++;
				if (mCurrentObject == (*mCurrentChunk)->getObjects().end()) {
					mCurrentChunk++;
					if (mCurrentChunk != mEndChunk) {
						VI_ASSERT(*mCurrentChunk != nullptr && "Invalid memory chunk");
						mCurrentObject = (*mCurrentChunk)->getObjects().begin();
					}
				}
				return *this;
			}
			VI_FORCE_INLINE T* operator*() const { return *mCurrentObject; }
			VI_FORCE_INLINE T* operator->() const { return *mCurrentObject; }
			bool operator==(const Iterator& other) const {
				return mCurrentChunk == other.mCurrentChunk && mCurrentObject == other.mCurrentObject;
			}

			bool operator!=(const Iterator& other) const {
				return !(*this == other);
			}
		private:
			typename MemoryChunkList::iterator mCurrentChunk;
			typename MemoryChunkList::iterator mEndChunk;
			typename ObjectList::const_iterator mCurrentObject;
		};
	public:
		MemoryChunkManager(const char* usage, const MemoryConfiguration& config) : mUsage(usage), MemoryManager(config) {
		}
		~MemoryChunkManager() {
		}
		void* allocate() {
			void* memory = nullptr;

			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (!memoryChunk->hasSlot()) {
					continue;
				}
				return memoryChunk->allocate();
			}
			if (memory == nullptr) {
				PoolAllocator* allocator = new PoolAllocator(
					MEMORY_CHUNK_MAX_SIZE,
					allocateOnStack(mUsage, MEMORY_CHUNK_MAX_SIZE, alignof(T)),
					sizeof(T), alignof(T)
				);
				MemoryChunk* memoryChunk = new MemoryChunk(allocator);
				memory = memoryChunk->allocate();
				mMemoryChunkList.emplace_back(memoryChunk);
			}
			VI_ASSERT(memory && "Failed to allocate new memory");
			return memory;
		}
		template<typename... Args>
		T* newObject(Args&&... args) {
			void* address = allocate();
			return new (address)T(std::forward<Args>(args)...);
		}
		void freeObject(void* memory) {
			for (MemoryChunk* memoryChunk : mMemoryChunkList) {
				if (memoryChunk->contains(memory)) {
					memoryChunk->free(memory);
					return;
				}
			}
			CORE_LOG_WARN("Failed to free memory {0}, possible memory corruption");
		}
		void reset() {
			for (auto iter = mMemoryChunkList.rbegin(); iter != mMemoryChunkList.rend(); ++iter) {
				freeOnStack((*iter)->getStartAddress());
				(*iter)->close();
				VI_FREE_MEMORY(*iter);
			}
			mMemoryChunkList.clear();
		}

		VI_FORCE_INLINE Iterator begin() { return Iterator(mMemoryChunkList.begin(), mMemoryChunkList.end()); }
		VI_FORCE_INLINE Iterator end() { return Iterator(mMemoryChunkList.end(), mMemoryChunkList.end()); }
	private:
		MemoryChunkList mMemoryChunkList;
		const char* mUsage;
	};
}