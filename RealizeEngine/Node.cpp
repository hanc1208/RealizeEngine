#include "Node.h"
#include "Game.h"

namespace RE_NAMESPACE {

	Node::Node() : _parent(nullptr), _mouseDowned(false) {
		this->setSize(Game::getInstance()->getResolution());
	}

	void Node::addChild(const Node* child) {
		const_cast<Node*>(child)->_parent = this;
		const_cast<Node*>(child)->retain();
		_children.push_back(const_cast<Node*>(child));
	}

	void Node::removeAllChild() {
		int count = _children.size();
		for (int i = 0; i < count; i++) {
			this->removeChild(0);
		}
	}

	void Node::removeChild(const int index) {
		assert(index < (int) _children.size());
		auto it = _children.begin();
		for (int i = 0; i < index; i++) {
			it++;
		}
		(*it)->_parent = nullptr;
		(*it)->release();
		_children.erase(it);
	}

	void Node::removeChild(const Node* child) {
		auto it = _children.begin();
		for (; it != _children.end();) {
			if (*it == child) {
				(*it)->_parent = nullptr;
				(*it)->release();
				it = _children.erase(it);
			} else {
				it++;
			}
		}
	}

	void Node::onUpdate(UpdateEventArgument eventArgument) {
		if (_onUpdateListener) {
			eventArgument.sender = this;
			_onUpdateListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onUpdate(eventArgument);
		}
	}

	void Node::onRender(RenderEventArgument eventArgument) {
		if (_onRenderListener) {
			eventArgument.sender = this;
			_onRenderListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			RenderEventArgument newEventArgument = eventArgument;
			newEventArgument.origin += (*child)->getPosition();
			newEventArgument.origin.x -= (*child)->getWidth() * (*child)->getAnchor().x;
			newEventArgument.origin.y -= (*child)->getHeight() * (*child)->getAnchor().y;
			(*child)->onRender(newEventArgument);
		}
	}

	bool Node::onMouseDown(MouseEventArgument eventArgument) {
		for (auto child = _children.rbegin(); child != _children.rend(); child++) {
			MouseEventArgument newEventArgument = eventArgument;
			newEventArgument.location -= this->getPosition();
			if ((*child)->onMouseDown(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.location.isInRect(this->getRect())) {
			if (_onMouseDownListener) {
				eventArgument.sender = this;
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
			newEventArgument.location -= this->getPosition();
			if ((*child)->onMouseMove(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.location.isInRect(this->getRect())) {
			if (_onMouseMoveListener) {
				eventArgument.sender = this;
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
			newEventArgument.location -= this->getPosition();
			if ((*child)->onMouseUp(newEventArgument)) {
				return true;
			}
		}

		if (eventArgument.location.isInRect(this->getRect())) {
			if (_onMouseUpListener) {
				eventArgument.sender = this;
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
			eventArgument.sender = this;
			_onKeyDownListener(eventArgument);
		}

		for (auto child = _children.begin(); child != _children.end(); child++) {
			(*child)->onKeyDown(eventArgument);
		}
	}

}