#include "GameObjectFactory.hh"

namespace GameObjectFactory {
	GameObject* create(std::string objectName) {
		if (objectName == "player") {
			// return new ParticleObject();
			return new Player(objectName);
		} else {
			return new GameObject(objectName);
		}
	}

	void destroy(GameObject* objPtr) {
		if (objPtr->name == "player") {
			delete (Player*)objPtr;
		} else {
			delete objPtr;
		}
	}
}
