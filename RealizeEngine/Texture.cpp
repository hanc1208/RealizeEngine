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
			if (width >= _size.getWidth()) {
				_glSize.setWidth(width);
				break;
			}
		}

		for (float height = 1.0f;; height *= 2.0f) {
			if (height >= _size.getHeight()) {
				_glSize.setHeight(height);
				break;
			}
		}

		DWORD* glImage = (DWORD*) malloc(sizeof(DWORD) * (int) _glSize.getWidth() * (int) _glSize.getHeight());

		for (int y = 0; y < (int) _glSize.getHeight(); y++) {
			if (y < _size.getHeight()) {
				memcpy(&glImage[(int) (y * _glSize.getWidth())], &bitmapDataScan0[(int) (y * _size.getWidth())], sizeof(DWORD) * (int) _size.getWidth());
				memset(&glImage[(int) (y * _glSize.getWidth() + _size.getWidth())], 0, sizeof(DWORD) * (int) (_glSize.getWidth() - _size.getWidth()));
			} else {
				memset(&glImage[(int) (y * _glSize.getWidth())], 0, sizeof(DWORD) * (int) _glSize.getWidth());
			}
		}

		image->UnlockBits(&bitmapData);

		glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_TRUE);
		glGenTextures(1, &_textureID);

		glPushAttrib(GL_ALL_ATTRIB_BITS);

		glBindTexture(GL_TEXTURE_2D, _textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei) _glSize.getWidth(), (GLsizei) _glSize.getHeight(), 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, glImage);

		glPopAttrib();

		free(glImage);
		delete image;
	}

	Texture::~Texture() {
		glDeleteTextures(1, &_textureID);
	}

	void Texture::drawTexture(const Rect& rect) const {
		float x = rect.getX(), y = rect.getY();
		float width = _glSize.getWidth() * rect.getWidth() / _size.getWidth(), height = _glSize.getHeight() * rect.getHeight() / _size.getHeight();

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
