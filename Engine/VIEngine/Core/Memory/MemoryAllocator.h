#pragma once
#include"pch.h"
namespace VIEngine {
	const uint8_t INVALID_MEMORY_SIZE = 0;
	const uint8_t MAX_ALLOWED_ALIGNMENT = 128;
	class VI_API MemoryAllocator {
	public:
		MemoryAllocator(size_t memorySize, void* address);
		virtual ~MemoryAllocator() = default;
		virtual void* memAllocate(size_t memorySize, uint8_t alignment) { return nullptr; }
		virtual void memFree(void* memory) {}
		virtual void memClear() {}
	protected:
		uint8_t getAddressAdjustment(const void* address, uint8_t alignment);
		uint8_t getAddressAdjustment(const void* address, uint8_t alignment, uint8_t extraMemory);
		bool isPowerOfTwo(uint8_t alignment);
	protected:
		void* mStartAddress;
		size_t mMemorySize;
		size_t mUsedMemory;
		size_t mAllocationCount;
	};

	class VI_API LinearAllocator : public MemoryAllocator {
	public:
		LinearAllocator(size_t memorySize, void* address);
		~LinearAllocator();
		virtual void* memAllocate(size_t memorySize, uint8_t alignment) override;
		virtual void memFree(void* memory) override;
		virtual void memClear() override;
	};

	class VI_API StackAllocator : public MemoryAllocator {
		struct Header {
			uint8_t Padding;
		};
	public:
		StackAllocator(size_t memorySize, void* address);
		~StackAllocator();
		virtual void* memAllocate(size_t memorySize, uint8_t alignment) override;
		virtual void memFree(void* memory) override;
		virtual void memClear() override;
	};
}