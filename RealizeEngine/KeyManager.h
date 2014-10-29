#pragma once
#include "Constant.h"
#include "KeyEventArgument.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

namespace RE_NAMESPACE {

	class Game;

	class KeyManager {
		friend class Game;
	private:
		static KeyManager _instance;
		map<KeyCode, bool> _keyDowned;
	protected:
		void onKeyDown(KeyEventArgument eventArgument);
		void onKeyUp(KeyEventArgument eventArgument);
	public:
		static KeyManager* getInstance();

		bool isKeyPressed(KeyCode keyCode) const;
		vector<KeyCode> getPressedKeys() const;
	};

	inline KeyManager* KeyManager::getInstance() {
		return &_instance;
	}
}