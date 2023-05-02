#include <SDL2/SDL.h>
#include "AnimatedComponent.hpp"
// #include "Camera.hpp"

class Renderer
{
public:
    Renderer();
    ~Renderer();
    void render( AnimatedComponent& animatedComponent);
private:
    SDL_Renderer* renderer;
};

Renderer::Renderer() {

}

Renderer::~Renderer() {
}

void Renderer::render(AnimatedComponent& animatedComponent) {
    int cam_x, cam_y;
    SDL_Rect pos = {0,0,0,0};
    SDL_RenderCopyEx(
        renderer,
        animatedComponent.texture,
        &pos,
        animatedComponent.getRect(),
        0,
        nullptr,
        SDL_FLIP_NONE
    );
}

// Fazer Exercício Aval Desempenho
// Fazer relatório Trabalho Redes