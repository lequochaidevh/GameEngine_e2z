#include"GameplayLayer.h"
#include<VIEngine/Base.h>

using namespace VIEngine;

GameplayLayer::GameplayLayer() {

}

GameplayLayer::~GameplayLayer() {

}

void GameplayLayer::onAttach() {
	LOG_TRACE("GameplayLayer is attached");

	MemoryManager memoryManager;
	Actor* actor = memoryManager.newOnStack<Actor>("ActorManager");
	Object* obj = actor;

	LOG_TRACE(actor->runTimeType.getTypeName()); // Actor
	LOG_TRACE(actor->getRunTimeTypeInfo().getTypeName()); // Actor

	LOG_TRACE(obj->runTimeType.getTypeName()); // Object
	LOG_TRACE(obj->getRunTimeTypeInfo().getTypeName()); // Actor

	LOG_TRACE(actor->isTypeOf(obj->runTimeType)); // false
	LOG_TRACE(actor->isDerivedFrom(obj->runTimeType)); // true
	LOG_TRACE(actor->isExactlyTypeOf(obj)); // true
	LOG_TRACE(actor->isExactlyDerivedFrom(obj)); // true

	// Casting
	{
		int count = 100000;
		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < count; i++) {
				auto obj = downCast<Object>(actor);
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = endTime - startTime;
			LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
		}

		{
			auto startTime = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < count; i++) {
				//III-> Turn off RTTI of C++ Compiler
				//auto actor = dynamic_cast<Actor*>(obj);
				auto obj = dynamic_cast<Object*>(actor); //->UpCast NOT Have runTimeCheck, need use static_cast have faster
			}
			auto endTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> duration = endTime - startTime;
			LOG_INFO("RTTI takes {0} seconds", duration.count() / 1000.0f);
		}
	}

	memoryManager.freeOnStack(actor);
}

void GameplayLayer::onDetach() {
	LOG_TRACE("GameplayLayer is detached");
}

void GameplayLayer::onUpdate(Time time) {

}

bool GameplayLayer::onKeyPressedEvent(const KeyPressedEvent& eventContext) {
	return false;
}