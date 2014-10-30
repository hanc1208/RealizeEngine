#pragma once
#include "OpenGL.h"
#include "Type.h"
#include <string>

using std::string;

namespace RE_NAMESPACE {

	class TextureManager;

	class Texture {
	private:
		Size _size;
		Size _glSize;
		GLuint _textureID;
	public:
		Texture(const string& path);
		~Texture();

		Size getSize() const;
		float getWidth() const;
		float getHeight() const;
		Size getGLSize() const;

		void drawTexture(const Rect& rect) const;
	};

	inline Size Texture::getSize() const {
		return _size;
	}

	inline float Texture::getWidth() const {
		return _size.width;
	}

	inline float Texture::getHeight() const {
		return _size.height;
	}

	inline Size Texture::getGLSize() const {
		return _glSize;
	}
}