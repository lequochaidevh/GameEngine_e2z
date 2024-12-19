#include "EventDispatcher.h"

namespace VIEngine {
	EventDispatcher::EventDispatcher() : mEventActionMap() {

	}
	/*8.3.2_Define ~EventDispatcher() free memory*/
	EventDispatcher::~EventDispatcher() {
		for (auto& pair : mEventActionMap) {
			for (auto evenAction : pair.second) {
				VI_FREE_MEMORY(evenAction);
			}
			pair.second.clear();
		}
		mEventActionMap.clear();
	}
}