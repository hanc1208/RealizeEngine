#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	enum KeyCode {
		Null
	};

	class KeyEventArgument : public EventArgument {
	private:
		KeyCode _keyCode;
	public:
		KeyEventArgument();
		KeyEventArgument(Node* sender);
		KeyEventArgument(Node* sender, KeyCode keyCode);

		KeyCode getKeyCode() const;
		void setKeyCode(KeyCode keyCode);
	};

	inline KeyEventArgument::KeyEventArgument() {
		KeyEventArgument(nullptr);
	}

	inline KeyEventArgument::KeyEventArgument(Node* sender) {
		KeyEventArgument(sender, KeyCode::Null);
	}

	inline KeyEventArgument::KeyEventArgument(Node* sender, KeyCode keyCode) : EventArgument(sender), _keyCode(keyCode) {
	}

	inline KeyCode KeyEventArgument::getKeyCode() const {
		return _keyCode;
	}

	inline void KeyEventArgument::setKeyCode(KeyCode keyCode) {
		_keyCode = keyCode;
	}


}