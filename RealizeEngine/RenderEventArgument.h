#pragma once
#include "EventArgument.h"

namespace RE_NAMESPACE {

	struct RenderEventArgument : public EventArgument {
		Vector origin;

		RenderEventArgument();
		RenderEventArgument(Node* sender);
		RenderEventArgument(Node* sender, Vector origin);
	};

	inline RenderEventArgument::RenderEventArgument() {
		RenderEventArgument(nullptr);
	}

	inline RenderEventArgument::RenderEventArgument(Node* sender) {
		RenderEventArgument(sender, Vector());
	}

	inline RenderEventArgument::RenderEventArgument(Node* sender, Vector origin) : EventArgument(sender), origin(origin) {

	}
}