#pragma once
#include "Timer.h"
#include "UpdateEventArgument.h"
#include <vector>

using std::vector;
using std::function;

namespace RE_NAMESPACE {

	class TimerManager {
	private:
		static TimerManager _instance;

		vector<Timer*> _timers;
	public:
		static TimerManager* getInstance();

		~TimerManager();

		void start(const Timer* timer);
		void stop(const Timer* timer);
		void onUpdate(UpdateEventArgument eventArgument);
	};

	inline TimerManager* TimerManager::getInstance() {
		return &_instance;
	}

}