#include "SplashScene.h"
#include "Game.h"



namespace RE_NAMESPACE {

	struct bullet : public Sprite {
		float move_x;
		float move_y;
		bullet() : Sprite("Enemy") {
			this->setSize(Size(this->getWidth() * 0.2, this->getHeight() * 0.2));
			int rwidth = rand() % int(Game::getInstance()->getResolution().width);
			int rheight = rand() % int(Game::getInstance()->getResolution().height);
			int width = int(Game::getInstance()->getResolution().width);
			int height = int(Game::getInstance()->getResolution().height);

			int x;
			int y;

			int random = rand() % 4;
			switch (random) {
			case 0:
				x = rwidth;
				y = 0;
				this->move_x = rand() % 600 - 300;
				this->move_y = rand() % 300;
				break;
			case 1:
				x = width;
				y = rheight;
				this->move_x = -rand() % 300;
				this->move_y = rand() % 600 - 300;
				break;
			case 2:
				x = rwidth;
				y = height;
				this->move_x = rand() % 600 - 300;
				this->move_y = -rand() % 300;
				break;
			case 3:
				x = 0;
				y = rheight;
				this->move_x = rand() % 300;
				this->move_y = rand() % 600 - 300;
				break;
			}
			this->move_x /= 100.0f;
			this->move_y /= 100.0f;
			this->setPosition(Vector(x, y));
		}
	};

	SplashScene::SplashScene() {
		srand(time(NULL));
		static int sec = 0;
		TextureManager::getInstance()->loadImage("Splash.jpg", "Splash");
		TextureManager::getInstance()->loadImage("enemy.png", "Enemy");
		TextureManager::getInstance()->loadImage("player.png", "Player");

		this->setSize(Game::getInstance()->getResolution());

		Sprite* player = new Sprite("Player");

		static vector<bullet*> bullet_node;

		Sprite* sprite = new Sprite("Splash");
		sprite->setSize(Game::getInstance()->getResolution());
		this->addChild(sprite);

		static int score = 0;
		for (int i = 0; i<20; i++) {
			bullet* node = new bullet();

			this->addChild(node);
			bullet_node.push_back(node); score++;
		}

		static float time = 0.0f;
		this->setOnUpdateListener([=] (UpdateEventArgument eventArgument) {
			time += eventArgument.deltaTime;

			for (auto it = bullet_node.begin(); it != bullet_node.end();) {
				auto curr = (*it);
				float x = curr->getX() + curr->move_x * 1.5;
				float y = curr->getY() + curr->move_y * 1.5;

				curr->setX(x);
				curr->setY(y);

				if (x > this->getWidth() || y > this->getHeight() || x<0 || y<0) {
					this->removeChild(curr);
					it = bullet_node.erase(it);
					continue;
				} else {
					it++;
				}

				if (player->getRect().doesIntersect(curr->getRect())) {
					TCHAR str[100];
					wsprintf(str, L"Game Over!\n\nScore : %d", score);
					MessageBox(Game::getInstance()->getWindowHandle(), str, L"Dodge", MB_OK);
					Game::getInstance()->destroy();
				}

			}
			if (time >= 0.2f) {
				bullet* node = new bullet();

				this->addChild(node);
				bullet_node.push_back(node);
				time -= 0.2f;
				score++;
			}
		});

		player->setPosition(Vector(this->getWidth() / 2 - player->getWidth(), this->getHeight() / 2 - player->getHeight()));
		player->setSize(Size(player->getWidth() / 2, player->getHeight() / 2));
		player->setOnUpdateListener([=] (UpdateEventArgument eventArgument) {
			int speed = 10;
			if (KeyManager::getInstance()->isKeyPressed((KeyCode) VK_UP)) {
				player->setY(player->getY() - speed);
			} else if (KeyManager::getInstance()->isKeyPressed((KeyCode) VK_LEFT)) {
				player->setX(player->getX() - speed);
			} else if (KeyManager::getInstance()->isKeyPressed((KeyCode) VK_DOWN)) {
				player->setY(player->getY() + speed);
			} else if (KeyManager::getInstance()->isKeyPressed((KeyCode) VK_RIGHT)) {
				player->setX(player->getX() + speed);
			}
		});
		this->addChild(player);
	}
}