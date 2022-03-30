#ifndef GAMEOBJECTFACTORY_HH_
#define GAMEOBJECTFACTORY_HH_
#include "AllGameObjects.hh"

namespace GameObjectFactory {
	GameObject* create(std::string objectName);
	void destroy(GameObject* objPtr);
}

#endif
