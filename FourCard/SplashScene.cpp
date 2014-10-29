#include "SplashScene.h"
#include "Game.h"

namespace RE_NAMESPACE {

	SplashScene::SplashScene() {
		TextureManager::getInstance()->loadImage("Splash.jpg", "Splash");

		Sprite* sprite = new Sprite("Splash");
		sprite->setSize(Game::getInstance()->getResolution());
		this->addChild(sprite);

		Node* node = new Node();
		node->setRect(Rect(400, 150, 800, 600));
		node->setOnRenderListener([=] (RenderEventArgument eventArgument) {
			glColor4f(1.0, 1.0, 1.0, 1.0);
			glRectf(eventArgument.getX(), eventArgument.getY(), eventArgument.getX() + node->getWidth(), eventArgument.getY() + node->getHeight());
		});
		node->setOnClickListener([=] (MouseEventArgument eventArgument) {
			printf("Node  400, 150, 800, 600 Click\n");
		});
		this->addChild(node);
		Node* node2 = new Node();
		node2->setRect(Rect(250, 150, 300, 300));
		node2->setOnRenderListener([=] (RenderEventArgument eventArgument) {
			glColor4f(0.8, 0.8, 0.8, 1.0);
			glRectf(eventArgument.getX(), eventArgument.getY(), eventArgument.getX() + node2->getWidth(), eventArgument.getY() + node2->getHeight());
		});
		node2->setOnClickListener([=] (MouseEventArgument eventArgument) {
			printf("Node2 250, 150, 300, 300 Click\n");
		});
		node->addChild(node2);
		Node* node3 = new Node();
		node3->setRect(Rect(700, 400, 800, 400));
		node3->setOnRenderListener([=] (RenderEventArgument eventArgument) {
			glColor4f(0.6, 0.6, 0.6, 1.0);
			glRectf(eventArgument.getX(), eventArgument.getY(), eventArgument.getX() + node3->getWidth(), eventArgument.getY() + node3->getHeight());
		});
		node3->setOnClickListener([=] (MouseEventArgument eventArgument) {
			printf("Node3 700, 400, 800, 400 Click\n");
		});
		this->addChild(node3);
		Node* node4 = new Node();
		node4->setRect(Rect(100, 100, 250, 250));
		node4->setOnRenderListener([=] (RenderEventArgument eventArgument) {
			glColor4f(0.4, 0.4, 0.4, 1.0);
			glRectf(eventArgument.getX(), eventArgument.getY(), eventArgument.getX() + node4->getWidth(), eventArgument.getY() + node4->getHeight());
		});
		node4->setOnClickListener([=] (MouseEventArgument eventArgument) {
			printf("Node4 100, 100, 250, 250 Click\n");
		});
		node3->addChild(node4);

		this->setOnKeyDownListener([] (KeyEventArgument eventArgument) {
			printf("KeyDown %d\n", eventArgument.getKeyCode());
		});

		this->setOnUpdateListener([] (UpdateEventArgument eventArgument) {
			vector<KeyCode> result = KeyManager::getInstance()->getPressedKeys();

			for (auto it = result.begin(); it != result.end(); it++) {
				printf("KeyPressed %d\n", *it);
			}
		});
	}
}