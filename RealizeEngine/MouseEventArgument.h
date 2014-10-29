#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	enum MouseEventButtonType {
		Left,
		Middle,
		Right
	};

	class MouseEventArgument : public EventArgument {
	private:
		Vector _location;
		MouseEventButtonType _buttonType;
	public:
		MouseEventArgument();
		MouseEventArgument(Node* sender);
		MouseEventArgument(Node* sender, Vector location);
		MouseEventArgument(Node* sender, Vector location, MouseEventButtonType buttonType);

		Vector getLocation() const;
		void setLocation(Vector location);
		float getX() const;
		void setX(float x);
		float getY() const;
		void setY(float y);
		MouseEventButtonType getButtonType() const;
		void setButtonType(MouseEventButtonType buttonType);
	};

	inline MouseEventArgument::MouseEventArgument() : MouseEventArgument(nullptr) {

	}

	inline MouseEventArgument::MouseEventArgument(Node* sender) : MouseEventArgument(sender, Vector()) {

	}

	inline MouseEventArgument::MouseEventArgument(Node* sender, Vector location) : MouseEventArgument(sender, location, MouseEventButtonType::Left) {

	}

	inline MouseEventArgument::MouseEventArgument(Node* sender, Vector location, MouseEventButtonType buttonType) : EventArgument(sender) {
		_location = location;
		_buttonType = buttonType;
	}

	inline Vector MouseEventArgument::getLocation() const {
		return _location;
	}

	inline void MouseEventArgument::setLocation(Vector location) {
		_location = location;
	}

	inline float MouseEventArgument::getX() const {
		return _location.getX();
	}

	inline void MouseEventArgument::setX(float x) {
		_location.setX(x);
	}

	inline float MouseEventArgument::getY() const {
		return _location.getY();
	}

	inline void MouseEventArgument::setY(float y) {
		_location.setY(y);
	}

	inline MouseEventButtonType MouseEventArgument::getButtonType() const {
		return _buttonType;
	}

	inline void MouseEventArgument::setButtonType(MouseEventButtonType buttonType) {
		_buttonType = buttonType;
	}


}