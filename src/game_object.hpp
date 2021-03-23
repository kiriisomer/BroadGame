#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "texture.hpp"
#include "sprite_renderer.hpp"

class GameObject
{
public:
    glm::vec2 Position, Size, Velocity;
    glm::vec3 Color;
    GLfloat Rotation;
    GLboolean IsSolid;
    GLboolean Destroyed;

    Texture2D Sprite;

public:
    GameObject();
    GameObject(
        glm::vec2 pos, glm::vec2 size, Texture2D sprite, 
        glm::vec3 color = glm::vec3(1.0f), 
        glm::vec2 velocity = glm::vec2(0.0f, 0.0f)
    );
    // Draw sprite
    virtual void Draw(SpriteRenderer &renderer);
};

#endif
