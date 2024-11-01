#pragma once

/*11.1.5_Add NEW: Layer*/

#include "Core/Layer/LayerStack.h"
#include "Core/Logger/Logger.h"
#include "Core/Memory/MemoryAllocator.h"
#include<chrono>

#define POOL_MEMORY_ALLOCATOR

#ifndef POOL_MEMORY_ALLOCATOR
	#ifndef STACK_MEMORY_ALLOCATOR
		#define LINEAR_MEMORY_ALLOCATOR
	#endif
#endif // POOL_ALLOCATOR

void testCaseMemoryAllocator(VIEngine::MemoryAllocator* mAllocator);
void testCaseMemoryPoolAllocator(VIEngine::PoolAllocator* mAllocator);
void testPerformanceMemoryAllocator();

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() {}
	~GameplayLayer() {}
	virtual void onAttach() override {
		LOG_TRACE("GameplayLayer is attached");
		testPerformanceMemoryAllocator();
		//#ifdef POOL_MEMORY_ALLOCATOR
		//	testCaseMemoryPoolAllocator(mAllocator);
		//#elif defined(LINEAR_MEMORY_ALLOCATOR) || defined(STACK_MEMORY_ALLOCATOR)
		//	testCaseMemoryAllocator(mAllocator);
		//#endif // POOL_ALLOCATOR
		
	}
	virtual void onDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}
	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		//LOG_TRACE("Key {0} is pressed", (char)eventContext.getKey());
		return false;
	}
	virtual void onUpdate(VIEngine::Time time) {
		//LOG_TRACE("{0} Delta Time", time.getDeltaTime());
	}
	

private:
#ifdef POOL_MEMORY_ALLOCATOR
	VIEngine::PoolAllocator* mAllocator;
#elif defined(LINEAR_MEMORY_ALLOCATOR) || defined(STACK_MEMORY_ALLOCATOR)
	VIEngine::MemoryAllocator* mAllocator;	
#endif // POOL_ALLOCATOR

	
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

	for (int i = 0; i < 10; i++) {
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
	#endif 
	
	gameObjects.clear();

	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i + 10;
		go->Name = "GameObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}
	mAllocator->memClear();
	gameObjects.clear();
}

void testCaseMemoryPoolAllocator(VIEngine::PoolAllocator* mAllocator) {
	size_t size = 128 * 1024 * 1024;
	void* address = malloc(size);

	struct GameObject {
		size_t ID = 0;
		std::string Name = "GameObject";
	};

	mAllocator = new VIEngine::PoolAllocator(size, address, sizeof(GameObject), alignof(GameObject));



	std::vector<GameObject*> gameObjects;
	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocateChunk();
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		go->Name = "GameObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

	mAllocator->memFree(gameObjects[1]);
	mAllocator->memFree(gameObjects[2]);

	void* memory = mAllocator->allocateChunk();
	GameObject* go = new (memory)GameObject();
	go->ID = 11;
	go->Name = "GameObject: " + std::to_string(11);
	gameObjects.emplace_back(go);

	memory = mAllocator->allocateChunk();
	go = new (memory)GameObject();
	go->ID = 12;
	go->Name = "GameObject: " + std::to_string(12);
	gameObjects.emplace_back(go);

	mAllocator->memClear();
	gameObjects.clear();

	for (int i = 0; i < 10; i++) {
		void* memory = mAllocator->allocateChunk();
		GameObject* go = new (memory)GameObject();
		go->ID = i + 10;
		go->Name = "GameObject: " + std::to_string(i);
		gameObjects.emplace_back(go);
	}

	mAllocator->memClear();
	gameObjects.clear();
}

void testPerformanceMemoryAllocator() {
	VIEngine::LinearAllocator* mLinearAllocator;
	VIEngine::StackAllocator* mStackAllocator;
	VIEngine::PoolAllocator* mPoolAllocator;
	size_t size = 128 * 1024 * 1024;

	struct GameObject {
		size_t ID = 0;
		std::string Name = "GameObject";
	};

	mLinearAllocator = new VIEngine::LinearAllocator(size, malloc(size));
	mStackAllocator = new VIEngine::StackAllocator(size, malloc(size));
	mPoolAllocator = new VIEngine::PoolAllocator(size, malloc(size), sizeof(GameObject), alignof(GameObject));

	int numOfObjects = 2000000;
	std::vector<GameObject*> objects;

	// NEW and DELETE operator
	auto startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		GameObject* go = new GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	for (GameObject* object : objects) {
		VI_FREE_MEMORY(object);
	}

	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		GameObject* go = new GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	for (GameObject* object : objects) {
		VI_FREE_MEMORY(object);
	}

	objects.clear();

	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration = endTime - startTime;
	CORE_LOG_INFO("Delete operator takes: {0} seconds", duration.count() / 1000.0f);

	// LINEAR ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mLinearAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mLinearAllocator->memClear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mLinearAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mLinearAllocator->memClear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("LinearAllocator takes: {0} seconds", duration.count() / 1000.0f);

	// STACK ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mStackAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mStackAllocator->memClear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mStackAllocator->memAllocate(sizeof(GameObject), alignof(GameObject));
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mStackAllocator->memClear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("StackAllocator takes: {0} seconds", duration.count() / 1000.0f);

	// Pool ALLOCATOR
	startTime = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mPoolAllocator->allocateChunk();
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mPoolAllocator->memClear();
	objects.clear();

	for (int i = 0; i < numOfObjects; i++) {
		void* memory = mPoolAllocator->allocateChunk();
		GameObject* go = new (memory)GameObject();
		go->ID = i;
		objects.emplace_back(go);
	}

	mPoolAllocator->memClear();
	objects.clear();

	endTime = std::chrono::high_resolution_clock::now();
	duration = endTime - startTime;
	CORE_LOG_INFO("PoolAllocator takes: {0} seconds", duration.count() / 1000.0f);

	CORE_LOG_TRACE("DONE TESTING MEMROY ALLOCATOR");
}