#include "SplashScene.h"

SplashScene::SplashScene() {
	TextureManager::getInstance()->loadImage("splash.jpg", "splash");
	Sprite* sprite = new Sprite("splash");
	sprite->setSize(this->getSize());
	this->addChild(sprite);

	Font font;
	memset(&font, 0, sizeof(Font));

	font.lfHeight = 200;
	strcpy(font.lfFaceName, "���� ���");

	FontManager::getInstance()->loadFont(font, "���� ���");

	Label* label = new Label("�ȳ� ����", "���� ���");
	label->setPosition(Vector(100.0f, 100.0f));

	this->addChild(label);

	Timer* timer = new Timer(1.0f, 1, [=] (const Timer* timer) {
		Game::getInstance()->setScene(new LoginScene());
	});
	TimerManager::getInstance()->start(timer);
}