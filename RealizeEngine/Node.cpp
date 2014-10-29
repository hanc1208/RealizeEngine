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
		if (_onUpdateListener)
			_onUpdateListener(eventArgument);

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onUpdate(eventArgument);
		}
	}

	void Node::onRender(RenderEventArgument eventArgument) const {
		eventArgument.setOrigin(eventArgument.getOrigin() + this->getPosition());

		if (_onRenderListener)
			_onRenderListener(eventArgument);

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onRender(eventArgument);
		}
	}

	bool Node::onMouseDown(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			if ((*child)->onMouseDown(eventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseDownListener)
				_onMouseDownListener(eventArgument);

			return true;
		} else {
			return false;
		}
	}

	bool Node::onMouseMove(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			if ((*child)->onMouseMove(eventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseMoveListener)
				_onMouseMoveListener(eventArgument);

			return true;
		} else {
			return false;
		}
	}

	bool Node::onMouseUp(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			if ((*child)->onMouseUp(eventArgument)) {
				return true;
			}
		}

		if (eventArgument.getLocation().isInRect(this->getRect())) {
			if (_onMouseUpListener)
				_onMouseUpListener(eventArgument);

			return true;
		} else {
			return false;
		}
	}

}