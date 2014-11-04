#pragma once
#include "OpenGL.h"
#include <map>
#include <string>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using std::map;
using std::string;

namespace RE_NAMESPACE {

	class FontManager;

	class Font : public LOGFONT {
		friend class FontManager;
	private:
		HFONT _fontHandle;
	public:
		Font() : _fontHandle(nullptr) {

		}

		Font(const Font& font) {
			memcpy(this, &font, sizeof(Font));
		}
	};

	class FontManager {
	private:
		static FontManager _instance;

		map<string, Font> _fonts;
	public:
		static FontManager* getInstance();

		~FontManager();

		void loadFont(const Font& font, const string& name);
		void selectFont(const string& name);
	};

	inline FontManager* FontManager::getInstance() {
		return &_instance;
	}

}