#include "LoginScene.h"

LoginScene::LoginScene() {
	TextureManager::getInstance()->loadImage("Splash.jpg", "login-logo");

	Sprite* sprite_logo = new Sprite("login-logo");
	sprite_logo->setAnchor(Vector(0.5f, 0.0f));
	sprite_logo->setPosition(Vector(this->getWidth() / 2, 75.0f));
	this->addChild(sprite_logo);
}