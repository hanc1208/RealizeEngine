#include "Node.h"

namespace RE_NAMESPACE {

	void Node::removeChild(const int index) {
		assert(index < (int) _children.size());
		auto it = _children.begin();
		for (int i = 0; i < index; i++) {
			it++;
		}
		(*it)->release();
		_children.erase(it);
	}

	void Node::removeChild(const Node* child) {
		auto it = _children.begin();
		for (; it != _children.end(); it++) {
			if (*it == child) {
				(*it)->release();
				it = _children.erase(it);
			}
		}
		assert(it != _children.end());
	}

	void Node::onUpdate(UpdateEventArgument eventArgument) {
		if (_onUpdateListener) {
			eventArgument.setSender(this);
			_onUpdateListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onUpdate(eventArgument);
		}
	}

	void Node::onRender(RenderEventArgument eventArgument) const {
		eventArgument.setOrigin(eventArgument.getOrigin() + this->getPosition());

		if (_onRenderListener) {
			eventArgument.setSender(this);
			_onRenderListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onRender(eventArgument);
		}
	}

	bool Node::onMouseDown(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			MouseEventArgument newEventArgument = eventArgument;
			newEventArgument.setLocation(eventArgument.getLocation() - this->getPosition());
			if ((*child)->onMouseDown(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseDownListener) {
				eventArgument.setSender(this);
				_onMouseDownListener(eventArgument);
			}

			_mouseDowned = true;

			return true;
		} else {
			return false;
		}
	}

	bool Node::onMouseMove(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			MouseEventArgument newEventArgument = eventArgument;
			newEventArgument.setLocation(eventArgument.getLocation() - this->getPosition());
			if ((*child)->onMouseMove(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseMoveListener) {
				eventArgument.setSender(this);
				_onMouseMoveListener(eventArgument);
			}
			
			return true;
		} else {
			return false;
		}
	}

	bool Node::onMouseUp(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			MouseEventArgument newEventArgument = eventArgument;
			newEventArgument.setLocation(eventArgument.getLocation() - this->getPosition());
			if ((*child)->onMouseUp(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseUpListener) {
				eventArgument.setSender(this);
				_onMouseUpListener(eventArgument);
			}

			if (_mouseDowned && _onClickListener) {
				_onClickListener(eventArgument);
				_mouseDowned = false;
			}

			return true;
		} else {
			_mouseDowned = false;
			return false;
		}

	}

	void Node::onKeyDown(KeyEventArgument eventArgument) {
		if (_onKeyDownListener) {
			eventArgument.setSender(this);
			_onKeyDownListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onKeyDown(eventArgument);
		}
	}

}