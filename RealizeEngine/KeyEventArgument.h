#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	enum KeyCode {
		Null
	};

	struct KeyEventArgument : public EventArgument {
		KeyCode keyCode;

		KeyEventArgument();
		KeyEventArgument(Node* sender);
		KeyEventArgument(Node* sender, KeyCode keyCode);
	};

	inline KeyEventArgument::KeyEventArgument() {
		KeyEventArgument(nullptr);
	}

	inline KeyEventArgument::KeyEventArgument(Node* sender) {
		KeyEventArgument(sender, KeyCode::Null);
	}

	inline KeyEventArgument::KeyEventArgument(Node* sender, KeyCode keyCode) : EventArgument(sender), keyCode(keyCode) {
	}

}