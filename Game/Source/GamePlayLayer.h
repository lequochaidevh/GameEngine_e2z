#pragma once

/*11.1.5_Add NEW: Layer*/

#include "Core/Layer/LayerStack.h"
#include "Core/Logger/Logger.h"
#include "Core/Memory/MemoryAllocator.h"

#define STACK_MEMORY_ALLOCATOR

void testCaseMemoryAllocator(VIEngine::MemoryAllocator* mAllocator);
class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("GameplayLayer is attached");
		testCaseMemoryAllocator(mAllocator);
	}
	virtual void onDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}
	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		return false;
	}
	virtual void onUpdate(VIEngine::Time time) {
		LOG_TRACE("{0} Delta Time", time.getDeltaTime());
	}
	

private:
	VIEngine::MemoryAllocator* mAllocator;
};

void testCaseMemoryAllocator(VIEngine::MemoryAllocator* mAllocator) {
	size_t size = 128 * 1024 * 1024;
	void* address = malloc(size);
#ifdef LINEAR_MEMORY_ALLOCATOR 
	mAllocator = new VIEngine::LinearAllocator(size, address);
#elif defined(STACK_MEMORY_ALLOCATOR)
	mAllocator = new VIEngine::StackAllocator(size, address);
#endif // LINEAR_MEMORY_ALLOCATOR 

	struct GameObject {
		size_t ID = 0;
		std::string Name = "GameObject";
	};

	std::vector<GameObject*> gameObjects;

	for (int i = 0; i < 10000; i++) {
		void* memory = mAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		go->Name = "GameObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

#ifdef LINEAR_MEMORY_ALLOCATOR 
	mAllocator->memClear();
#elif defined(STACK_MEMORY_ALLOCATOR)
	/*Clear Memory 1 stack*/
	for (auto iter = gameObjects.rbegin(); iter != gameObjects.rend(); ++iter) {
		mAllocator->memFree(*iter);
	}
#endif // LINEAR_MEMORY_ALLOCATOR 
	
	gameObjects.clear();

	for (int i = 0; i < 10000; i++) {
		void* memory = mAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i + 10000;
		go->Name = "GameObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}
	mAllocator->memClear();
	gameObjects.clear();
}