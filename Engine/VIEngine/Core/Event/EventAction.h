#pragma once

#include "EventContext.h"
/*8.2_Create interface EventAction*/

namespace VIEngine {
	/*8.2.1_Define EventCallback function*/
	template<typename T> using eventCallback = std::function<bool(const T&)>;

	class VI_API IEventAction {
	public:
		virtual ~IEventAction() = default;
		virtual bool execute(const EventContext*) = 0;
	};

	template <typename T>
	class VI_API EventAction : public IEventAction {
	public:
		//() add -mCallback: eventCallback<T>
		EventAction(const eventCallback<T>& callback) : mCallback(callback){}
		virtual bool execute(const EventContext* eventContext) override {

			//check type value of eventContext
			VI_STATIC_ASSERT(std::is_base_of<EventContext, T>::value && "Invalid EventContext");

			//get value of casting pointer
			return mCallback(*(T*)eventContext);
		}

	private:
		eventCallback<T> mCallback;
	};
}