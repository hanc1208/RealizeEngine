#include "LoginScene.h"

LoginScene::LoginScene() {
	TextureManager::getInstance()->loadImage("Splash.jpg", "login-logo");

	Sprite* sprite_logo = new Sprite("login-logo");
	sprite_logo->setAnchor(Vector(0.5f, 0.0f));
	sprite_logo->setPosition(Vector(this->getWidth() / 2, 75.0f));
	this->addChild(sprite_logo);

	Node* textBox_id = new Node();
	textBox_id->setAnchor(Vector(0.5f, 0.0f));
	textBox_id->setPosition(Vector(this->getWidth() / 2, 405.0f));
	textBox_id->setSize(Size(320.0f, 45.0f));
	textBox_id->setBackgroundColor(Color(209, 202, 186));
	this->addChild(textBox_id);

	Node* textBox_password = new Node();
	textBox_password->setAnchor(Vector(0.5f, 0.0f));
	textBox_password->setPosition(Vector(this->getWidth() / 2, 475.0f));
	textBox_password->setSize(Size(320.0f, 45.0f));
	textBox_password->setBackgroundColor(Color(209, 202, 186));
	this->addChild(textBox_password);

	Label* button_login = new Label("로그인", "");
	button_login->setAnchor(Vector(0.5f, 0.0f));
	button_login->setPosition(Vector(this->getWidth() / 2, 580.0f));
	button_login->setSize(Size(190.0f, 45.0f));
	button_login->setBackgroundColor(Color(196, 211, 208));
	button_login->setTextHAlignment(TextHAlignment::CENTER);
	button_login->setTextVAlignment(TextVAlignment::CENTER);
	button_login->setOnClickListener([] (MouseEventArgument eventArgument) {
		printf("로그인!!!");
	});
	this->addChild(button_login);
}