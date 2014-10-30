#pragma once
#include "Constant.h"

namespace RE_NAMESPACE {

	class Node;

	struct EventArgument {
		Node* sender;

		EventArgument();
		EventArgument(Node* sender);
	};

	inline EventArgument::EventArgument() {
		EventArgument(nullptr);
	}

	inline EventArgument::EventArgument(Node* sender) : sender(sender) {

	}

}