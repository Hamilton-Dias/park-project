#include "TransformComponent.h"

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {

	this->position = glm::vec2(posX, posY);
	this->velocity = glm::vec2(velX, velY);
	this->width = w;
	this->height = h;
	this->scale = s;
}

void TransformComponent::initialize() {

}

void TransformComponent::update(float deltaTime) {
	
	this->position.x += this->velocity.x * deltaTime;
	this->position.y += this->velocity.y * deltaTime;
}