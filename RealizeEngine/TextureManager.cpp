#include "TextureManager.h"
#include "Game.h"

namespace RE_NAMESPACE {

	TextureManager TextureManager::_instance = TextureManager();

	TextureManager::~TextureManager() {
		for (auto texture = _textures.begin(); texture != _textures.end(); texture++) {
			delete texture->second;
		}
	}

	const Texture* TextureManager::loadImage(const string& path, const string& name) {
		Texture* texture = new Texture(path);

		if (name == "") {
			_textures[path] = texture;
		}
		else {
			_textures[name] = texture;
		}

		return texture;
	}
}