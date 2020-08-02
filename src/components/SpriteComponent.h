#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include <map>  
#include "../../lib/SDL2/include/SDL.h"
#include "../graphics/TextureManager.h"
#include "../graphics/AssetManager.h"
#include "../graphics/Animation.h"

class SpriteComponent: public Component {
private:
    TransformComponent* transform;
    SDL_Texture* texture;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    bool isAnimated;
    int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char* filePath) {

        isAnimated = false;
        isFixed = false;
        setTexture(filePath);
    };

    SpriteComponent(const char* filePath, int numFrames, int animationSpeed, bool hasDirections, bool isFixed) {

        isAnimated = true;
        this->numFrames = numFrames;
        this->animationSpeed = animationSpeed;
        this->isFixed = isFixed;
        
        if (hasDirections) {

            Animation downAnimation = Animation(0, numFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numFrames, animationSpeed);
            Animation upAnimation = Animation(3, numFrames, animationSpeed);

            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);

            this->animationIndex = 0;
            this-> currentAnimationName = "DownAnimation";
        }
        else {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }

        play(this->currentAnimationName);
        setTexture(filePath);
    };

    void play(std::string animationName) {

        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }

    void setTexture(std::string assetTextureId) {
        texture = Game::assetManager->getTexture(assetTextureId);
    };

    void initialize() override {
        transform = owner->getComponent<TransformComponent>();
        sourceRectangle.x = 0;
        sourceRectangle.y = 0;
        sourceRectangle.w = transform->width;
        sourceRectangle.h = transform->height;
    };

    void update(float deltaTime) override {

        if (isAnimated) {
            sourceRectangle.x = sourceRectangle.w * static_cast<int>((SDL_GetTicks()/animationSpeed) % numFrames);
        }
        sourceRectangle.y = animationIndex * transform->height;

        destinationRectangle.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);
        destinationRectangle.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
        destinationRectangle.w = transform->width * transform->scale;
        destinationRectangle.h = transform->height * transform->scale;
    };

    void render() override {
        TextureManager::draw(texture, sourceRectangle, destinationRectangle, spriteFlip);
    };
};

#endif // !SPRITECOMPONENT_H
