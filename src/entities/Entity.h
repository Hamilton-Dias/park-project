#ifndef ENTITY_H
#define ENTITY_H

#include <vector>;
#include <string>;
#include "EntityManager.h"
#include "../components/Component.h"

class EntityManager;

class Entity {

private:
	//EntityManager& manager;
	bool isActive;
	std::vector<Component*> components;

public:
	std::string name;
	Entity(EntityManager& manager, std::string name);
	void update(float deltaTime);
	void render();
	void destroy();
	bool getIsActive() { return this->isActive; };

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... args) {
		T* newComponent(new T(std::forward<TArgs>(args)...));
		newComponent->owner = this;
		components.emplace_back(newComponent);
		newComponent->initialize();
		return *newComponent;
	}

};

#endif // !ENTITY_H
