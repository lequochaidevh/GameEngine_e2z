#include"MemoryAllocator.h"
namespace VIEngine {
	PoolAllocator::PoolAllocator(size_t memorySize, void* address, size_t chunkSize, uint8_t chunkAlignment) :
		MemoryAllocator(memorySize, address), mChunkSize(chunkSize), mChunkAlignment(chunkAlignment)
	{
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		size_t adjustedAddress = alignForward(asUintPtrAddress, mChunkAlignment);
		mAddressOffset = adjustedAddress - asUintPtrAddress;
		mMemorySize -= mAddressOffset;
		mChunkSize = alignForward(mChunkSize, mChunkAlignment);
		VI_ASSERT(mChunkSize >= sizeof(FreeNode) && "Invalid chunk size");
		VI_ASSERT(mMemorySize >= mChunkSize && "Invalid memory size");
		mFreeListHead = nullptr;
		this->clear();
	}
	PoolAllocator::~PoolAllocator() {
	}
	void* PoolAllocator::allocate() {
		FreeNode* node = mFreeListHead;
		VI_ASSERT(node != nullptr && "PoolAllocator is full, no more chunk to allocate");
		mFreeListHead = node->Next;
		mUsedMemory += mChunkSize;
		mAllocationCount++;
		return node;
	}
	void PoolAllocator::free(void* memory) {
		VI_ASSERT(memory != nullptr && "Free invalid memory address");
		VI_ASSERT(contains(memory) && "Free out of bound memory address");
		FreeNode* node = reinterpret_cast<FreeNode*>(memory);
		node->Next = mFreeListHead;//Its make value in vector change
		mFreeListHead = node;
		mUsedMemory -= mChunkSize;
		mAllocationCount--;
	}
	void PoolAllocator::clear() {
		size_t numberOfChunks = mMemorySize / mChunkSize;
		union {
			void* asVoidPtrAddress;
			char* asCharPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		for (size_t idx = 0; idx < numberOfChunks; idx++) {
			FreeNode* node = reinterpret_cast<FreeNode*>(asCharPtrAddress + mAddressOffset + idx * mChunkSize);
			node->Next = mFreeListHead;
			mFreeListHead = node;
		}
		mUsedMemory = 0;
		mAllocationCount = 0;
	}
	bool PoolAllocator::contains(void* memory) {
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		uintptr_t numberOfChunks = mMemorySize / mChunkSize;
		uintptr_t uintPtrMemory = reinterpret_cast<uintptr_t>(memory);
		return uintPtrMemory >= asUintPtrAddress && uintPtrMemory <= asUintPtrAddress + mAddressOffset + (numberOfChunks - 1) * mChunkSize;
	}
}
