#pragma once 

#include "EventAction.h"

/*8.3_Create EventDispatcher for 2 respone :
	i.Register or add eventCallback to List respective somthing of event
	ii.Excute all of eventCallback when event active */
namespace VIEngine {
	/*8.3.1_Create EventActionList (vector)*/
	using EventActionList = std::vector<IEventAction*>;
	using EventID = UUID;
	class VI_API EventDispatcher {
		friend class Application; // Spec only Application class which can create it
	public:
		~EventDispatcher();
		/*8.3.1.1_Add EventListener to unorder_map[1][2]
			[1]->[typeid().name]
			[2]->[new EventAction<T>(eventCallback)]*/
		template<typename T>
		void addEventListener(const eventCallback<T>& callback) { // callback : eventcontext
			VI_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "add invalid EventContext");
			EventID eventID = getTypeUUID<T>();
			//const char* evenType = typeid(T).name();
			IEventAction* eventAction = new EventAction<T>(callback);
			mEventActionMap[eventID].emplace_back(eventAction);
		}

		template<typename T>
		void dispatchEventListener(const T& evenContext) {
			VI_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "dispatch invalid EventContext");
			EventID eventID = getTypeUUID<T>();
			//const char* eventType = typeid(T).name();
			if (mEventActionMap.find(eventID) == mEventActionMap.end()) {
				return;
			}
			for (auto eventAction : mEventActionMap.at(eventID)) {
				if (eventAction->execute(&evenContext)) {
					break;
				}
			}
		}

	private:
		EventDispatcher();
		std::unordered_map<EventID, EventActionList> mEventActionMap; 
	};
}