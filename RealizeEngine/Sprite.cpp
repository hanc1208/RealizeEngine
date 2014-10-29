#include "Sprite.h"

namespace RE_NAMESPACE {

	void Sprite::onRender(RenderEventArgument eventArgument) const {
		Node::onRender(eventArgument);

		if (_texture) {
			_texture->drawTexture(Rect(eventArgument.getX(), eventArgument.getY(), this->getWidth(), this->getHeight()));
		}
	}

}