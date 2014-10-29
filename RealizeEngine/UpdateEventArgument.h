#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	class Node;

	class UpdateEventArgument : public EventArgument {
	private:
		float _deltaTime;
	public:
		UpdateEventArgument();
		UpdateEventArgument(Node* sender);
		UpdateEventArgument(Node* sender, float deltaTime);

		float getDeltaTime();
		void setDeltaTime(float deltaTime);
	};

	inline UpdateEventArgument::UpdateEventArgument()  {
		UpdateEventArgument(nullptr);
	}

	inline UpdateEventArgument::UpdateEventArgument(Node* sender) {
		UpdateEventArgument(sender, 0.0f);
	}

	inline UpdateEventArgument::UpdateEventArgument(Node* sender, float deltaTime) : EventArgument(sender) {
		_deltaTime = deltaTime;
	}

	inline float UpdateEventArgument::getDeltaTime() {
		return _deltaTime;
	}

	inline void UpdateEventArgument::setDeltaTime(float deltaTime) {
		_deltaTime = deltaTime;
	}

}