#include <SDL2/SDL.h>
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(/* args */);
    ~Camera();
public:
    glm::vec2 position;
    float zoom;
};

Camera::Camera(/* args */)
{
}

Camera::~Camera()
{
}
