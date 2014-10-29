#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	class RenderEventArgument : public EventArgument {
	public:
		Vector _origin;

		RenderEventArgument();
		RenderEventArgument(Node* sender);
		RenderEventArgument(Node* sender, Vector origin);

		Vector getOrigin() const;
		void setOrigin(Vector origin);
		float getX() const;
		void setX(float x);
		float getY() const;
		void setY(float y);
	};

	inline RenderEventArgument::RenderEventArgument() {
		RenderEventArgument(nullptr);
	}

	inline RenderEventArgument::RenderEventArgument(Node* sender) {
		RenderEventArgument(sender, Vector());
	}

	inline RenderEventArgument::RenderEventArgument(Node* sender, Vector origin) : EventArgument(sender) {
		_origin = origin;
	}

	inline Vector RenderEventArgument::getOrigin() const {
		return _origin;
	}

	inline void RenderEventArgument::setOrigin(Vector origin) {
		_origin = origin;
	}

	inline float RenderEventArgument::getX() const {
		return _origin.getX();
	}

	inline void RenderEventArgument::setX(float x) {
		_origin.setX(x);
	}

	inline float RenderEventArgument::getY() const {
		return _origin.getY();
	}

	inline void RenderEventArgument::setY(float y) {
		_origin.setY(y);
	}
}