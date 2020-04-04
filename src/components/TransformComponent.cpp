#include "TransformComponent.h"

TransformComponent::TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {

	this->position.x = posX;
	this->position.y = posY;
	this->velocity.x = velX;
	this->velocity.y = velY;
	this->width = w;
	this->height = h;
	this->scale = s;
}

void TransformComponent::initialize(){
	
}

void TransformComponent::update(float deltaTime) {
	this->position.x = this->velocity.x * deltaTime;
	this->position.y = this->velocity.y * deltaTime;
}

void TransformComponent::render(){

	SDL_Rect transformRectangle = {
		(int)this->position.x,
		(int)this->position.y,
		this->width,
		this->height
	};
	SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(Game::renderer, &transformRectangle);

}