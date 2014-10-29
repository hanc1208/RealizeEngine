#pragma once
#include "Type.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "OpenGL/gl.h"
#include "OpenGL/glu.h"
#include "OpenGL/wglext.h"
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

namespace RE_NAMESPACE {
	
	class Game;

	class OpenGL {
	private:
		static Gdiplus::GdiplusStartupInput _gdiplusStartupInput;
		static ULONG_PTR _gdiplusToken;
	public:
		static HDC _hdc;
		static HGLRC _hGLRC;
	public:
		static void initialize();
		static void destroy();
		static void onSize(Size resolution, Rect rect);
	};

}