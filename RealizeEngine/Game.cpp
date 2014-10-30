#pragma once
#include "Game.h"

namespace RE_NAMESPACE {

	Game* Game::_instance = nullptr;

	Game::Game() {
		_windowHandle = NULL;
	}

	Game::Game(HINSTANCE instanceHandle) {
		_instance = this;
		_instanceHandle = instanceHandle;
		_consoleHandle = NULL;

		this->setFramePerSecond(60);
		this->setResolution(Size(RE_DEFAULT_WIDTH, RE_DEFAULT_HEIGHT));
		this->setSize(_resolution);
		this->setGameScaleMode(GameScaleMode::NoScale);
		this->setScene(nullptr);

		registerWindowClass();
		_windowHandle = createWindow();
		OpenGL::initialize();
		SetProp(_windowHandle, "Game", this);
	}

	Game::~Game() {
		OpenGL::destroy();
		if (_consoleHandle) {
			this->destroyConsole();
		}
		this->setScene(nullptr);
	}

	void Game::setSize(const Size& size) {
		_size = size;

		RECT rect = {0, 0, (LONG) size.width, (LONG) size.height};
		AdjustWindowRect(&rect, GetWindowLong(_windowHandle, GWL_STYLE), FALSE);
		SetWindowPos(_windowHandle, NULL, 0, 0, (int) rect.right - rect.left, (int) rect.bottom - rect.top, SWP_NOZORDER | SWP_NOMOVE);

		_scaledRect = Rect();

		switch (_gameScaleMode) {
		case GameScaleMode::NoScale:
			break;
		case GameScaleMode::FixedRatio: {
			float resolution_ratio = _resolution.width / _resolution.height;
			float size_ratio = _size.width / _size.height;

			if (size_ratio > resolution_ratio) {
				_scaledRect.size.width = _resolution.width * (_size.height / _resolution.height);
				_scaledRect.size.height = _size.height;
				_scaledRect.origin.x = (_size.width - _scaledRect.size.width) / 2;
			} else {
				_scaledRect.size.width = _size.width;
				_scaledRect.size.height = _resolution.height * (_size.width / _resolution.width);
				_scaledRect.origin.y = (_size.height - _scaledRect.size.height) / 2;
			}
			break;
		}
		case GameScaleMode::Stretch:
			_scaledRect.size = _size;
			break;
		}

		OpenGL::onSize(_resolution, _scaledRect);
	}

	void Game::setScene(const Node* scene) {
		if (_scene) {
			_scene->release();
		}

		if (scene) {
			_scene = const_cast<Node*>(scene);
			_scene->retain();
		}
	}

	void Game::start() {
		assert(_scene);
		assert(_windowHandle);
		ShowWindow(_windowHandle, SW_SHOW);

		QueryPerformanceFrequency(&_queryPerformanceFrequency);
		QueryPerformanceCounter(&_queryPerformanceLast);
		QueryPerformanceCounter(&_queryPerformanceFramePerSecondCounterLast);

		_framePerSecondCounter = 0;

		MSG message = { NULL, };
		while (message.message != WM_QUIT) {
			if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE)) {
				GetMessage(&message, NULL, 0, 0);
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			else {
				LARGE_INTEGER queryPerformanceCurrent;
				QueryPerformanceCounter(&queryPerformanceCurrent);
				float time = (float) (queryPerformanceCurrent.QuadPart - _queryPerformanceLast.QuadPart) / _queryPerformanceFrequency.QuadPart;
				float framePerSecondCounterTime = (float) (queryPerformanceCurrent.QuadPart - _queryPerformanceFramePerSecondCounterLast.QuadPart) / _queryPerformanceFrequency.QuadPart;

				if (time >= 1.0 / _framePerSecond) {
					_queryPerformanceLast = queryPerformanceCurrent;

					_framePerSecondCounter++;
					glClearColor(0.0f, 0.5f, 1.0f, 1.0f);
					glClear(GL_COLOR_BUFFER_BIT);

					_scene->onUpdate(UpdateEventArgument(_scene, time));
					_scene->onRender(RenderEventArgument(_scene));

					SwapBuffers(OpenGL::_hdc);
				}

				if (framePerSecondCounterTime >= 1.0) {
					_queryPerformanceFramePerSecondCounterLast = queryPerformanceCurrent;

					printf("Frame Per Second : %d\n", _framePerSecondCounter);

					_framePerSecondCounter = 0;
				}
			}
		}
	}

	void Game::destroy() {
		PostMessage(_windowHandle, WM_QUIT, 0, 0);
	}

	void Game::registerWindowClass() const {
		WNDCLASS wndClass = { NULL, };
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hInstance = _instanceHandle;
		wndClass.lpszClassName = RE_CLASSNAME;
		wndClass.lpfnWndProc = wndProc;
		wndClass.style = CS_OWNDC;
		RegisterClass(&wndClass);
	}

	HWND Game::createWindow() const {
		HWND windowHandle = CreateWindow(RE_CLASSNAME, RE_CLASSNAME, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, CW_USEDEFAULT, CW_USEDEFAULT, (int) RE_DEFAULT_WIDTH, (int) RE_DEFAULT_HEIGHT, NULL, NULL, _instanceHandle, NULL);
		return windowHandle;
	}
	
	LRESULT CALLBACK Game::wndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam) {
		Game* game = static_cast<Game*>(GetProp(windowHandle, "Game"));

		switch (message) {
		case WM_CREATE:
			return 0;
		case WM_SIZE:
			game->setSize(Size(LOWORD(lParam), HIWORD(lParam)));
			return 0;
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MOUSEMOVE:
		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP: {
			MouseEventArgument eventArgument(game->getScene());
			eventArgument.location.x = (LOWORD(lParam) - game->getScaledRect().origin.x) * (game->getResolution().width / game->getScaledRect().size.width);
			eventArgument.location.y = (HIWORD(lParam) - game->getScaledRect().origin.y) * (game->getResolution().height / game->getScaledRect().size.height);
			if (message == WM_LBUTTONDOWN || (message == WM_MOUSEMOVE && wParam | MK_LBUTTON) || message == WM_LBUTTONUP) {
				eventArgument.buttonType = MouseEventButtonType::Left;
			} else if (message == WM_MBUTTONDOWN || (message == WM_MOUSEMOVE && wParam | MK_MBUTTON) || message == WM_MBUTTONUP) {
				eventArgument.buttonType = MouseEventButtonType::Middle;
			} else if (message == WM_RBUTTONDOWN || (message == WM_MOUSEMOVE && wParam | MK_RBUTTON) || message == WM_RBUTTONUP) {
				eventArgument.buttonType = MouseEventButtonType::Right;
			}
			if (message == WM_LBUTTONDOWN || message == WM_MBUTTONDOWN || message == WM_RBUTTONDOWN) {
				game->getScene()->onMouseDown(eventArgument);
			} else if (message == WM_MOUSEMOVE) {
				game->getScene()->onMouseMove(eventArgument);
			} else if (message == WM_LBUTTONUP || message == WM_MBUTTONUP || message == WM_RBUTTONUP) {
				game->getScene()->onMouseUp(eventArgument);
			}
			return 0;
		}
		case WM_KEYDOWN:
			KeyManager::getInstance()->onKeyDown(KeyEventArgument(game->getScene(), (KeyCode) wParam));
			return 0;
		case WM_KEYUP:
			KeyManager::getInstance()->onKeyUp(KeyEventArgument(game->getScene(), (KeyCode) wParam));
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		}

		return DefWindowProc(windowHandle, message, wParam, lParam);
	}
}