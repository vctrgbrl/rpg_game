#include "Animation.hpp"
#include <unordered_map>
#include <stack>
#include <SDL2/SDL.h>
#include <iostream>

class AnimatedComponent {
public:
    AnimatedComponent(SDL_Texture* texture, std::unordered_map<std::string, Animation*> animations, std::string init);
    ~AnimatedComponent();
    const SDL_Rect* getRect();
    void pushAnimation(std::string name);
    void update(uint32_t deltaTime);
public:
    SDL_Texture* texture;
private:
    std::unordered_map<std::string, Animation*> animations;
    SDL_RendererFlip flip;
    std::stack<Animation*> animation_stack;
};

AnimatedComponent::AnimatedComponent(SDL_Texture* texture, std::unordered_map<std::string, Animation*> animations, std::string init) {
    this->texture = texture;
    this->animations = animations;
    this->animation_stack = std::stack<Animation*>();
    this->flip = SDL_FLIP_NONE;
    animation_stack.push(animations.at(init));
}

AnimatedComponent::~AnimatedComponent() {
}

const SDL_Rect* AnimatedComponent::getRect() {
    return animation_stack.top()->clip_rect;
}

void AnimatedComponent::pushAnimation(std::string name) {
    Animation* desiredAnimation = animations.at(name);
    Animation* runningAnimation = animation_stack.top();
    desiredAnimation->reset();
    
    if (desiredAnimation == animation_stack.top()) return;
    if (!runningAnimation->is_loop) animation_stack.pop();
    
    animation_stack.push(desiredAnimation);
}

void AnimatedComponent::update(uint32_t deltaTime) {
    if (animation_stack.top()->update(deltaTime)) {
        animation_stack.pop();
    }
}