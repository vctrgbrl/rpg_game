#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "AnimatedComponent.hpp"
#include "glad/glad.h"
#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexArrayObject.hpp"

int main(int argc, char* argv[]) {
    uint32_t flag;
    flag = SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    // Also request a depth buffer
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    // IMG_LoadPNG_RW("");

    if (flag) {
        std::cout << "Error initializing SDL2 Init everything: main.cpp 6" << std::endl;
        std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
        return -1;
    }

    flag = IMG_Init(IMG_INIT_PNG);
    if (!flag) {
        std::cout << "Error initializing IMG_Init everything: main.cpp 14" << std::endl;
        std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
        return -1;
    }
    
    SDL_Window* window = SDL_CreateWindow(
        "Hello, World!", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        800, 600, 
        SDL_WINDOW_OPENGL);

    SDL_GLContext maincontext = SDL_GL_CreateContext(window);

    // Check OpenGL properties
    printf("OpenGL loaded\n");
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    printf("Vendor:   %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version:  %s\n", glGetString(GL_VERSION));


    glViewport(0, 0, 800, 400);

    if (!window) {
        std::cout << "Error initializing SDL_CreateWindow: main.cpp 13" << std::endl;
        std::cout << "SDL2 Error: " << SDL_GetError() << std::endl;
    }

    bool window_opened = true;

    SDL_Surface* window_surface = SDL_GetWindowSurface(window);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* image = IMG_LoadTexture(renderer, "container.jpg");

    if (!image) {
        std::cout << "Error initializing image " << std::endl;
        std::cout << "SDL2 Error:" << SDL_GetError() << std::endl;
    }

    SDL_Rect pos = {400, 300, 15 * 10, 16 * 10};

    uint32_t last_tick = 0;
    uint32_t delta_time = 0;
    AnimatedComponent ac(image, 
    std::unordered_map<std::string, Animation*>(
        {
            std::pair("fly", new Animation(0, 0,15,16,2,200, true )),
            std::pair("atk", new Animation(30,0,15,16,2,200, false)),
            std::pair("die", new Animation(60,0,15,16,3,200, false)),
        }
    ), "fly");

    int32_t length;
    const uint8_t* keystate = SDL_GetKeyboardState(&length);
    std::cout << length << std::endl;

    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };
    std::vector<Lone::VertexArrayObject::Attribute> attributes = {
        {GL_FLOAT, 3, sizeof(float)},
        {GL_FLOAT, 3, sizeof(float)},
        {GL_FLOAT, 2, sizeof(float)},
    };

    uint32_t indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Lone::VertexArrayObject vao(sizeof(vertices), vertices, attributes, sizeof(indices), indices);
    Lone::Shader shader = Lone::Shader("shader.glsl");
    Lone::Texture texture(argv[1]);
    // Lone::Texture texture("container.jpg");

    while (window_opened) {

        uint32_t tick = SDL_GetTicks();
        delta_time = tick - last_tick;
        last_tick = tick;
        
        glClearColor(0.4f, 0.5f, 1.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        texture.Bind();
        vao.Bind();
        shader.Bind();
        shader.setUniform("texture_1", texture.id);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_QUIT:
                window_opened = false;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.scancode)
                {
                case SDL_SCANCODE_SPACE:
                    ac.pushAnimation("die");
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        if (keystate[SDL_Scancode::SDL_SCANCODE_A]) {
            pos.x -= delta_time;
        } if (keystate[SDL_Scancode::SDL_SCANCODE_D]) {
            pos.x += delta_time;
        } if (keystate[SDL_Scancode::SDL_SCANCODE_W]) {
            pos.y += delta_time;
        } if (keystate[SDL_Scancode::SDL_SCANCODE_S]) {
            pos.y -= delta_time;
        }
        // ac.update(delta_time);

        // SDL_RenderClear(renderer);
        // SDL_RenderCopyEx(renderer, image, ac.getRect(), &pos, 0, nullptr, SDL_FLIP_HORIZONTAL);
        // SDL_RenderPresent(renderer);
    }
    return 0;
}
