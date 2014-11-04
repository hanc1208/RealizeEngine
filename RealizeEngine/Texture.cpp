#include "Texture.h"
#include "TextureManager.h"

namespace RE_NAMESPACE {

	Texture::Texture(const string& path) {
		int Multiplier2[] = {
			1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096
		};

		wstring wpath;
		wpath.assign(path.begin(), path.end());

		Gdiplus::Bitmap* image = Gdiplus::Bitmap::FromFile(wpath.c_str());
		Gdiplus::Rect rect(0, 0, image->GetWidth(), image->GetHeight());
		Gdiplus::BitmapData bitmapData;

		image->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &bitmapData);

		DWORD* bitmapDataScan0 = (DWORD*) bitmapData.Scan0;

		_size = Size((float) image->GetWidth(), (float) image->GetHeight());

		for (float width = 1.0f;; width *= 2.0f) {
			if (width >= _size.width) {
				_glSize.width = width;
				break;
			}
		}

		for (float height = 1.0f;; height *= 2.0f) {
			if (height >= _size.height) {
				_glSize.height = height;
				break;
			}
		}

		DWORD* glImage = (DWORD*) malloc(sizeof(DWORD) * (int) _glSize.width * (int) _glSize.height);

		for (int y = 0; y < (int) _glSize.height; y++) {
			if (y < _size.height) {
				memcpy(&glImage[(int) (y * _glSize.width)], &bitmapDataScan0[(int) (y * _size.width)], sizeof(DWORD) * (int) _size.width);
				memset(&glImage[(int) (y * _glSize.width + _size.width)], 0, sizeof(DWORD) * (int) (_glSize.width - _size.width));
			} else {
				memset(&glImage[(int) (y * _glSize.width)], 0, sizeof(DWORD) * (int) _glSize.width);
			}
		}

		image->UnlockBits(&bitmapData);

		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
		glGenTextures(1, &_textureID);

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glBindTexture(GL_TEXTURE_2D, _textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei) _glSize.width, (GLsizei) _glSize.height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, glImage);

		glPopAttrib();

		free(glImage);
		delete image;
	}

	Texture::~Texture() {
		glDeleteTextures(1, &_textureID);
	}

	void Texture::drawTexture(const Rect& rect) const {
		float x = rect.origin.x, y = rect.origin.y;
		float width = _glSize.width * rect.size.width / _size.width, height = _glSize.height * rect.size.height / _size.height;

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glBindTexture(GL_TEXTURE_2D, _textureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2f(x, y);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2f(x + width, y);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2f(x + width, y + height);
		glTexCoord2f(0.0f, 1.0f);
		glVertex2f(x, y + height);
		glEnd();

		glPopAttrib();
	}

}
