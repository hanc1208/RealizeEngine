#pragma once
#include "Reference.h"
#include <functional>

using std::function;

namespace RE_NAMESPACE {

	class TimerManager;

	class Timer : public Reference {
		friend class TimerManager;
	private:
		float _interval;
		float _currentTime;
		int _loop;
		int _currentLoop;
		function<void(const Timer* timer)> _listener;
	public:
		const static int Infinity = -1;

		Timer(float interval, int loop = Infinity, function<void(const Timer* timer)> listener = function<void(const Timer* timer)>());

		float getInterval() const;
		void setInterval(float interval);
		int getLoop() const;
		void setLoop(int loop);
		void setListener(function<void(const Timer* timer)> listener);
	};

	inline Timer::Timer(float interval, int loop, function<void(const Timer* timer)> listener) {
		_interval = interval;
		_loop = loop;
		_listener = listener;
	}

	inline float Timer::getInterval() const {
		return _interval;
	}

	inline void Timer::setInterval(float interval) {
		_interval = interval;
	}

	inline int Timer::getLoop() const {
		return _loop;
	}

	inline void Timer::setLoop(int loop) {
		_loop = loop;
	}

	inline void Timer::setListener(function<void(const Timer* timer)> listener) {
		_listener = listener;
	}

}