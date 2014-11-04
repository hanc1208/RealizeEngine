#include "FontManager.h"

namespace RE_NAMESPACE {

	FontManager FontManager::_instance = FontManager();

	FontManager::~FontManager() {
		for (auto it = _fonts.begin(); it != _fonts.end(); it++) {
			if (it->second._fontHandle) {
				DeleteObject(it->second._fontHandle);
			}
		}
	}

	void FontManager::loadFont(const Font& font, const string& name) {
		_fonts[name] = font;
		_fonts[name]._fontHandle = CreateFontIndirect(&font);
	}

	void FontManager::selectFont(const string& name) {
		SelectObject(OpenGL::_hdc, _fonts[name]._fontHandle);
	}

}