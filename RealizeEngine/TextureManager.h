#pragma once
#include "Texture.h"
#include <cassert>
#include <map>
#include <string>

using std::map;
using std::string;
using std::wstring;

namespace RE_NAMESPACE {

	class Game;

	class TextureManager {
	private:
		static TextureManager _instance;

		map<string, Texture*> _textures;
	public:
		static TextureManager* getInstance();

		~TextureManager();

		const Texture* loadImage(const string& path, const string& name = "");
		const Texture* getImage(const string& name) const;
	};

	inline TextureManager* TextureManager::getInstance() {
		return &_instance;
	}

	inline const Texture* TextureManager::getImage(const string& name) const {
		assert(_textures.find(name) != _textures.end());
		return _textures.find(name)->second;
	}
}