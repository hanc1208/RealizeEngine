#include "Sprite.h"

namespace RE_NAMESPACE {

	void Sprite::onRender(RenderEventArgument eventArgument) {
		Node::onRender(eventArgument);

		if (_texture) {
			_texture->drawTexture(Rect(eventArgument.origin.x, eventArgument.origin.y, this->getWidth(), this->getHeight()));
		}
	}

}