#include "Entity.h"

Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name) {

	//this->manager = manager;
	//this->name = name;
	this->isActive = true;
}

void Entity::update(float deltaTime) {

	for (auto& component: components) {
		component->update(deltaTime);
	}
}

void Entity::render() {

	for (auto& component : components) {
		component->render();
	}
}

void Entity::destroy() {
	this->isActive = false;
}