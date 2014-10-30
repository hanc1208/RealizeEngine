#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	enum MouseEventButtonType {
		Left,
		Middle,
		Right,
		None
	};

	struct MouseEventArgument : public EventArgument {
		Vector location;
		MouseEventButtonType buttonType;

		MouseEventArgument();
		MouseEventArgument(Node* sender);
		MouseEventArgument(Node* sender, Vector location);
		MouseEventArgument(Node* sender, Vector location, MouseEventButtonType buttonType);
	};

	inline MouseEventArgument::MouseEventArgument() {
		MouseEventArgument(nullptr);
	}

	inline MouseEventArgument::MouseEventArgument(Node* sender) {
		MouseEventArgument(sender, Vector());
	}

	inline MouseEventArgument::MouseEventArgument(Node* sender, Vector location) {
		MouseEventArgument(sender, location, MouseEventButtonType::Left);
	}

	inline MouseEventArgument::MouseEventArgument(Node* sender, Vector location, MouseEventButtonType buttonType) : EventArgument(sender), location(location), buttonType(buttonType) {
	
	}

}