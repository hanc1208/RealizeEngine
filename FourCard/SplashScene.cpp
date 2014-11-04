#include "SplashScene.h"

SplashScene::SplashScene() {
	TextureManager::getInstance()->loadImage("splash.jpg", "splash");

	Font font;
	font.lfHeight = 30;
	strcpy(font.lfFaceName, "¸¼Àº °íµñ");

	FontManager::getInstance()->loadFont(font, "");

	Sprite* sprite = new Sprite("splash");
	sprite->setAnchor(Vector(0.5f, 0.5f));
	sprite->setPosition(Vector(this->getWidth() / 2, this->getHeight() / 2));
	this->addChild(sprite);

	Timer* timer = new Timer(2.0f, 1, [=] (const Timer* timer) {
		Game::getInstance()->setScene(new LoginScene());
	});
	TimerManager::getInstance()->start(timer);
}