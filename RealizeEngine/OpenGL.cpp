#include "OpenGL.h"
#include "Game.h"

namespace RE_NAMESPACE {

	Gdiplus::GdiplusStartupInput OpenGL::_gdiplusStartupInput;
	ULONG_PTR OpenGL::_gdiplusToken;

	HDC OpenGL::_hdc = NULL;
	HGLRC OpenGL::_hGLRC = NULL;
	
	void OpenGL::initialize() {
		Gdiplus::GdiplusStartup(&_gdiplusToken, &_gdiplusStartupInput, NULL);
		_hdc = GetDC(Game::getInstance()->getWindowHandle());

		int _a = GetLastError();

		PIXELFORMATDESCRIPTOR pfd;

		ZeroMemory(&pfd, sizeof(pfd));
		pfd.nSize = sizeof(pfd);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_SUPPORT_GDI | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 16;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int nPixelFormat = ChoosePixelFormat(_hdc, &pfd);
		SetPixelFormat(_hdc, nPixelFormat, &pfd);

		_hGLRC = wglCreateContext(_hdc);
		wglMakeCurrent(_hdc, _hGLRC);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_TEXTURE_2D);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glDisable(GL_DEPTH_TEST); glDisable(GL_LIGHTING);

		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
		if (wglSwapIntervalEXT != NULL)
			wglSwapIntervalEXT(1);
		else {
			if (MessageBox(Game::getInstance()->getWindowHandle(), "WGL_EXT_swap_control �Ӽ��� ����Ͻô� �׷��� ī�忡�� �������� �ʽ��ϴ�.\n\n�� ��� ���� ����ȭ�� �������� �ʾ� CPU, GPU ��뷮�� �ſ� �����մϴ�.\n\nȮ�ι�ư�� �����ø� ��� �����ϸ�, ��� ��ư�� �����ø� ���α׷��� �����մϴ�.)", "����", MB_ICONEXCLAMATION | MB_OKCANCEL) == IDCANCEL) {
				Game::getInstance()->destroy();
				return;
			}
		}
	}

	void OpenGL::destroy() {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(_hGLRC);
		ReleaseDC(Game::getInstance()->getWindowHandle(), _hdc);
		Gdiplus::GdiplusShutdown(_gdiplusToken);
	}

	void OpenGL::onSize(Size resolution, Rect rect) {
		if (rect.getHeight() == 0) {
			rect.setHeight(1);
		}

		glViewport((int) rect.getX(), (int) rect.getY(), (int) rect.getWidth(), (int) rect.getHeight());
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0, resolution.getWidth(), resolution.getHeight(), 0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
}