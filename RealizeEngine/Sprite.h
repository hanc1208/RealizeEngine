#pragma once
#include "Node.h"

namespace RE_NAMESPACE {

	class Sprite : public Node {
	private:
		Texture* _texture;
	public:
		Sprite();
		Sprite(const string& name);
		Sprite(const Texture* texture);
		
		const Texture* getTexture() const;
		void setImage(const Texture* texture);

		void onRender(RenderEventArgument eventArgument) const override;
	};

	inline Sprite::Sprite() {
		_texture = nullptr;
	}

	inline Sprite::Sprite(const string& name) {
		this->setImage(TextureManager::getInstance()->getImage(name));
	}

	inline Sprite::Sprite(const Texture* texture) {
		this->setImage(texture);
	}

	inline const Texture* Sprite::getTexture() const {
		return _texture;
	}

	inline void Sprite::setImage(const Texture* texture) {
		_texture = const_cast<Texture*>(texture);
		this->setSize(Size((float) _texture->getWidth(), (float) _texture->getHeight()));
	}

}