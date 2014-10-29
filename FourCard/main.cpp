#include <windows.h>
#include "SplashScene.h"

using namespace RE_NAMESPACE;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Game game(hInstance);
	game.setGameScaleMode(GameScaleMode::FixedRatio);
	game.setResolution(Size(1600, 900));
	game.setSize(Size(1800, 900));
	game.setScene(new SplashScene());
	game.start();
}