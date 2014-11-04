#include "SplashScene.h"
#include "Game.h"



namespace RE_NAMESPACE {

	SplashScene::SplashScene() {
		TextureManager::getInstance()->loadImage("splash.jpg", "splash");
		Sprite* sprite = new Sprite("splash");
		sprite->setSize(this->getSize());
		this->addChild(sprite);

		Font font;
		memset(&font, 0, sizeof(Font));

		font.lfHeight = 20;
		strcpy(font.lfFaceName, "¸¼Àº °íµñ");

		FontManager::getInstance()->loadFont(font, "¸¼Àº °íµñ");

		Label* label = new Label("¾È³ç ¤¾¤¾", "¸¼Àº °íµñ");
		label->setPosition(Vector(100.0f, 100.0f));

		this->addChild(label);

		Timer* timer = new Timer(3.0f, 1, [=] (const Timer* timer) {
			this->removeChild(sprite);
		});
		TimerManager::getInstance()->start(timer);
	}

}