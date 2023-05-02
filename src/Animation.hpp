#include <SDL2/SDL.h>
#include <iostream>

class Animation
{
public:
    Animation(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t n_frames, uint32_t duration, bool is_loop);
    ~Animation();
    bool update(uint32_t deltaTime);
    void reset();
public:
    bool is_loop;
    SDL_Rect* clip_rect;
private:
    bool is_playing;
    uint32_t clock, duration, n_frames, index, offset_x;
};

Animation::Animation(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t n_frames, uint32_t duration, bool is_loop) {
    this->clip_rect = new SDL_Rect();
    this->offset_x = x;
    this->clip_rect->x = x;
    this->clip_rect->y = y;
    this->clip_rect->w = w;
    this->clip_rect->h = h;
    this->duration = duration;
    this->n_frames = n_frames;
    this->is_loop = is_loop;
    this->is_playing = true;
    index = 0;
}

Animation::~Animation() {
    delete this->clip_rect;
}

bool Animation::update(uint32_t deltaTime) {
    clock += deltaTime;
    if (clock > duration) {
        index++;
        clock = 0;
        if (!is_loop && index == n_frames) {
            return true;
        }
        index%=n_frames;
        clip_rect->x = offset_x  + (clip_rect->x + clip_rect->w)%(clip_rect->w*n_frames);
    }
    return false;
}

void Animation::reset() {
    clip_rect->x = offset_x;
    index = 0;
    clock = 0;
}