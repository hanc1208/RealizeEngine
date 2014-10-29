#pragma once
#include "Node.h"
#include <thread>

using std::thread;

namespace RE_NAMESPACE {

	enum GameScaleMode {
		NoScale,
		FixedRatio,
		Stretch
	};

	class Game {
	private:
		static Game* _instance;
		HWND _windowHandle;
		HINSTANCE _instanceHandle;

		int _framePerSecond;
		LARGE_INTEGER _queryPerformanceFrequency, _queryPerformanceLast;
		int _framePerSecondCounter;
		LARGE_INTEGER _queryPerformanceFramePerSecondCounterLast;

		Size _resolution;
		Size _size;
		Rect _scaledRect;
		GameScaleMode _gameScaleMode;

		Node* _scene;
	public:
		Game();
		Game(HINSTANCE instanceHandle);
		~Game();

		static Game* getInstance();

		HWND getWindowHandle() const;
		HINSTANCE getInstanceHandle() const;

		int getFramePerSecond() const;
		void setFramePerSecond(int framePerSecond);

		Size getResolution() const;
		void setResolution(const Size& resolution);
		Size getSize() const;
		void setSize(const Size& size);
		Rect getScaledRect() const;
		GameScaleMode getGameScaleMode() const;
		void setGameScaleMode(const GameScaleMode gameScaleMode);

		Node* getScene() const;
		void setScene(const Node* scene);

		void start();
		void destroy();
	protected:
		void registerWindowClass() const;
		HWND createWindow() const;
	private:
		static LRESULT CALLBACK wndProc(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
	};

	inline Game* Game::getInstance() {
		return _instance;
	}

	inline HWND Game::getWindowHandle() const {
		return _windowHandle;
	}

	inline HINSTANCE Game::getInstanceHandle() const {
		return _instanceHandle;
	}

	inline int Game::getFramePerSecond() const {
		return _framePerSecond;
	}

	inline void Game::setFramePerSecond(int framePerSecond) {
		assert(framePerSecond > 0);
		_framePerSecond = framePerSecond;
	}

	inline Size Game::getResolution() const {
		return _resolution;
	}

	inline void Game::setResolution(const Size& resolution) {
		_resolution = resolution;
	}

	inline Size Game::getSize() const {
		return _size;
	}

	inline Rect Game::getScaledRect() const {
		return _scaledRect;
	}

	inline GameScaleMode Game::getGameScaleMode() const {
		return _gameScaleMode;
	}

	inline void Game::setGameScaleMode(const GameScaleMode gameScaleMode) {
		_gameScaleMode = gameScaleMode;
		this->setSize(_size);
	}

	inline Node* Game::getScene() const {
		return _scene;
	}
}