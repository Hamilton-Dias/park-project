#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <vector>
#include "Entity.h"
#include "../components/Component.h"

class EntityManager {

private:
	std::vector<Entity*> entities;

public:
	void clearData();
	void update(float deltaTime);
	void render();
	bool hasNoEntities();
	Entity& addEntity(std::string name, LayerType layer);
	std::vector<Entity*> getEntityList() const;
	std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
	unsigned int getEntityCount();

};

#endif // !ENTITYMANAGER_H
