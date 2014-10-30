#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	class Node;

	struct UpdateEventArgument : public EventArgument {
		float deltaTime;

		UpdateEventArgument();
		UpdateEventArgument(Node* sender);
		UpdateEventArgument(Node* sender, float deltaTime);
	};

	inline UpdateEventArgument::UpdateEventArgument()  {
		UpdateEventArgument(nullptr);
	}

	inline UpdateEventArgument::UpdateEventArgument(Node* sender) {
		UpdateEventArgument(sender, 0.0f);
	}

	inline UpdateEventArgument::UpdateEventArgument(Node* sender, float deltaTime) : EventArgument(sender), deltaTime(deltaTime) {

	}

}