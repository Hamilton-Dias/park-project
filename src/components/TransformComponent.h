#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include "../../lib/SDL2/include/SDL.h"
#include "../../lib/glm/glm.hpp"
#include "../entities/EntityManager.h"
#include "../game.h"

class TransformComponent: public Component{

public:
	glm::vec2 position;
	glm::vec2 velocity;
	int height, width, scale;

	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s);
	void initialize();
	void update(float deltaTime) override;
	void render() override;

};

#endif // !TRANSFORMCOMPONENT_H
