#include "EntityManager.h"

void EntityManager::clearData() {

	for (auto& entity : entities) {
		entity->destroy();
	}
}

bool EntityManager::hasNoEntities() {

	return entities.size() == 0;
}

void EntityManager::update(float deltaTime) {

	for (auto& entity : entities) {
		entity->update(deltaTime);
	}
}

void EntityManager::render()
{
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
	{
		for (auto& entity:getEntitiesByLayer(static_cast<LayerType>(layerNumber)))
		{
			entity->render();
		}
	}

	/*for (auto& entity : entities) {
		entity->render();
	}*/
}

Entity& EntityManager::addEntity(std::string name, LayerType layer)
{
	Entity* entity = new Entity(*this, name, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::getEntitiesByLayer(LayerType layer) const
{
	std::vector<Entity*> selectedEntities;

	for (auto& entity : entities)
	{
		if (entity->layer == layer)
			selectedEntities.emplace_back(entity);
	}

	return selectedEntities;
}

std::vector<Entity*> EntityManager::getEntityList() const {

	return entities;
}

unsigned int EntityManager::getEntityCount() {

	return entities.size();
}