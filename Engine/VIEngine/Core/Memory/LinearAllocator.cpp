#include"MemoryAllocator.h"
#include"Core/Logger/Logger.h"
namespace VIEngine {
	LinearAllocator::LinearAllocator(size_t memorySize, void* address) : MemoryAllocator(memorySize, address) {
	}
	LinearAllocator::~LinearAllocator() {
	}
	void* LinearAllocator::allocate(size_t memorySize, uint8_t alignment) {
		VI_ASSERT(memorySize > INVALID_MEMORY_SIZE && "Allocate invalid memory size");
		VI_ASSERT(alignment < MAX_ALLOWED_ALIGNMENT && "Invalid alignment");
		union {
			void* asVoidPtrAddress;
			uintptr_t asUintPtrAddress;
		};
		asVoidPtrAddress = mStartAddress;
		asUintPtrAddress += mUsedMemory;
		uintptr_t adjustment = getAddressAdjustment(asVoidPtrAddress, alignment);
		if (mUsedMemory + memorySize + adjustment > mMemorySize) {
			CORE_LOG_WARN("LinearAllocator is full, can not allocate for new data with size {0}", memorySize);
			return nullptr;
		}
		asUintPtrAddress += adjustment;
		mUsedMemory += memorySize + adjustment;
		mAllocationCount += 1;
		return asVoidPtrAddress;
	}
	void LinearAllocator::free(void* memory) {
		VI_ASSERT(false && "LinearAllocator does not support for free address");
	}
	void LinearAllocator::clear() {
		mUsedMemory = 0;
		mAllocationCount = 0;
	}
}