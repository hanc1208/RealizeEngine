#pragma once
#include "Type.h"
#include "Reference.h"
#include "TextureManager.h"
#include "UpdateEventArgument.h"
#include "RenderEventArgument.h"
#include "MouseEventArgument.h"
#include <vector>
#include <functional>

using std::vector;
using std::function;

namespace RE_NAMESPACE {

	class Node : Reference {
		friend class Game;
	protected:
		Rect _rect;
	private:
		vector<Node*> _children;

		function<void(UpdateEventArgument eventArgument)> _onUpdateListener;
		function<void(RenderEventArgument eventArgument)> _onRenderListener;
		function<void(MouseEventArgument eventArgument)> _onMouseDownListener;
		function<void(MouseEventArgument eventArgument)> _onMouseMoveListener;
		function<void(MouseEventArgument eventArgument)> _onMouseUpListener;
		function<void(MouseEventArgument eventArgument)> _onClickListener;
	public:
		virtual ~Node();

		Rect getRect() const;
		void setRect(Rect rect);
		Vector getPosition() const;
		void setPosition(Vector position);
		Size getSize() const;
		void setSize(Size size);
		float getX() const;
		void setX(const float x);
		float getY() const;
		void setY(const float y);
		float getWidth() const;
		void setWidth(const float width);
		float getHeight() const;
		void setHeight(const float height);

		const vector<Node*>& getChildren() const;
		int getChildrenCount() const;
		const Node* getChild(const int index) const;
		void addChild(const Node* child);
		void removeAllChild();
		void removeChild(const int index);
		void removeChild(const Node* child);

		void setOnUpdateListener(const function<void(UpdateEventArgument eventArgument)> onUpdateListener);
		void setOnRenderListener(const function<void(RenderEventArgument eventArgument)> onRenderListener);
		void setOnMouseDownListener(const function<void(MouseEventArgument eventArgument)> onMouseDownListener);
		void setOnMouseMoveListener(const function<void(MouseEventArgument eventArgument)> onMouseMoveListener);
		void setOnMouseUpListener(const function<void(MouseEventArgument eventArgument)> onMouseUpListener);
		void setOnClickListener(const function<void(MouseEventArgument eventArgument)> onClickListener);
	protected:
		virtual void onUpdate(UpdateEventArgument eventArgument);
		virtual void onRender(RenderEventArgument eventArgument) const;
		bool onMouseDown(MouseEventArgument eventArgument);
		bool onMouseMove(MouseEventArgument eventArgument);
		bool onMouseUp(MouseEventArgument eventArgument);
	};

	inline Node::~Node() {
		this->removeAllChild();
	}

	inline Rect Node::getRect() const {
		return _rect;
	}

	inline void Node::setRect(Rect rect) {
		_rect = rect;
	}

	inline Vector Node::getPosition() const {
		return _rect.getOrigin();
	}

	inline void Node::setPosition(Vector position) {
		_rect.setOrigin(position);
	}

	inline Size Node::getSize() const {
		return _rect.getSize();
	}

	inline void Node::setSize(Size size) {
		_rect.setSize(size);
	}

	inline float Node::getX() const {
		return _rect.getX();
	}

	inline void Node::setX(const float x) {
		_rect.setX(x);
	}

	inline float Node::getY() const {
		return _rect.getY();
	}

	inline void Node::setY(const float y) {
		_rect.setY(y);
	}

	inline float Node::getWidth() const {
		return _rect.getWidth();
	}

	inline void Node::setWidth(const float width) {
		_rect.setWidth(width);
	}
	
	inline float Node::getHeight() const {
		return _rect.getHeight();
	}

	inline void Node::setHeight(const float height) {
		_rect.setHeight(height);
	}

	inline const vector<Node*>& Node::getChildren() const {
		return _children;
	}

	inline int Node::getChildrenCount() const {
		return _children.size();
	}

	inline const Node* Node::getChild(const int index) const {
		return _children[index];
	}

	inline void Node::addChild(const Node* child) {
		const_cast<Node*>(child)->retain();
		_children.push_back(const_cast<Node*>(child));
	}

	inline void Node::removeAllChild() {
		int count = _children.size();
		for (int i = 0; i < count; i++) {
			this->removeChild(0);
		}
	}

	inline void Node::setOnUpdateListener(const function<void(UpdateEventArgument eventArgument)> onUpdateListener) {
		_onUpdateListener = onUpdateListener;
	}

	inline void Node::setOnRenderListener(const function<void(RenderEventArgument eventArgument)> onRenderListener) {
		_onRenderListener = onRenderListener;
	}

	inline void Node::setOnMouseDownListener(const function<void(MouseEventArgument eventArgument)> onMouseDownListener) {
		_onMouseDownListener = onMouseDownListener;
	}

	inline void Node::setOnMouseMoveListener(const function<void(MouseEventArgument eventArgument)> onMouseMoveListener) {
		_onMouseMoveListener = onMouseMoveListener;
	}

	inline void Node::setOnMouseUpListener(const function<void(MouseEventArgument eventArgument)> onMouseUpListener) {
		_onMouseUpListener = onMouseUpListener;
	}

	inline void Node::setOnClickListener(const function<void(MouseEventArgument eventArgument)> onClickListener) {
		_onClickListener = onClickListener;
	}

}