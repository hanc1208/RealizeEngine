#include "KeyManager.h"
#include "Game.h"

namespace RE_NAMESPACE {
	
	KeyManager KeyManager::_instance;

	void KeyManager::onKeyDown(KeyEventArgument eventArgument) {
		if (_keyDowned.find(eventArgument.getKeyCode()) == _keyDowned.end() || _keyDowned[eventArgument.getKeyCode()] == false) {
			Game::getInstance()->getScene()->onKeyDown(eventArgument);
		}

		_keyDowned[eventArgument.getKeyCode()] = true;
	}

	void KeyManager::onKeyUp(KeyEventArgument eventArgument) {
		_keyDowned[eventArgument.getKeyCode()] = false;
	}

	bool KeyManager::isKeyPressed(KeyCode keyCode) const {
		auto it = _keyDowned.find(keyCode);

		if (it == _keyDowned.end()) {
			return false;
		} else {
			return it->second;
		}
	}

	vector<KeyCode> KeyManager::getPressedKeys() const {
		vector<KeyCode> result;

		if (_keyDowned.size() == 0) {
			return result;
		}

		for (auto key = _keyDowned.begin(); key != _keyDowned.end(); key++) {
			if (key->second) {
				result.push_back(key->first);
			}
		}

		return result;
	}
}