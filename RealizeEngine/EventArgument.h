#pragma once
#include "Constant.h"

namespace RE_NAMESPACE {

	class Node;

	class EventArgument {
	private:
		Node* _sender;
	public:
		EventArgument();
		EventArgument(Node* sender);

		Node* getSender() const;
		void setSender(const Node* sender);
	};

	inline EventArgument::EventArgument() : EventArgument(nullptr) {

	}

	inline EventArgument::EventArgument(Node* sender) : _sender(sender) {

	}

	inline Node* EventArgument::getSender() const {
		return _sender;
	}

	inline void EventArgument::setSender(const Node* sender) {
		_sender = const_cast<Node*>(sender);
	}

}