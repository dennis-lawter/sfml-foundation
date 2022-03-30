#include "GameObjectFactory.hh"

namespace GameObjectFactory {
	GameObject* create(std::string objectName) {
		if (objectName == "player") {
			return new Player(objectName);
		} else {
			return new GameObject(objectName);
		}
	}

	void destroy(GameObject* objPtr) {
		delete objPtr;
	}
}
