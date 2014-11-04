#include "TimerManager.h"

namespace RE_NAMESPACE {

	TimerManager TimerManager::_instance = TimerManager();

	void TimerManager::start(const Timer* timer) {
		for (auto it = _timers.begin(); it != _timers.end(); it++) {
			if (*it == timer) {
				(*it)->_currentTime = 0.0f;
				(*it)->_currentLoop = 0;
				return;
			}
		}
		const_cast<Timer*>(timer)->retain();
		_timers.push_back(const_cast<Timer*>(timer));
	}

	void TimerManager::stop(const Timer* timer) {
		for (auto it = _timers.begin(); it != _timers.end(); it++) {
			if (*it == timer) {
				(*it)->release();
				_timers.erase(it);
				return;
			}
		}
	}

	void TimerManager::onUpdate(UpdateEventArgument eventArgument) {
		for (auto it = _timers.begin(); it != _timers.end();) {
			if ((*it)->_loop != Timer::Infinity && (*it)->_currentLoop >= (*it)->_loop) {
				it = _timers.erase(it);
				continue;
			}

			(*it)->_currentTime += eventArgument.deltaTime;

			if ((*it)->_currentTime >= (*it)->_interval) {
				(*it)->_currentTime -= (*it)->_interval;
				
				(*it)->_currentLoop += 1;

				if ((*it)->_listener) {
					(*it)->_listener(*it);
				}
			}

			it++;
		}
	}
}