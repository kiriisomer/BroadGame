#include "game_object.hpp"


GameObject::GameObject(): Position(0, 0), Size(1, 1), Velocity(0.0f), 
        Color(1.0f), Rotation(0.0f), Sprite(), 
        IsSolid(false), Destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, 
    glm::vec3 color, glm::vec2 velocity): 
        Position(pos), Size(size), Velocity(velocity), 
        Color(color), Rotation(0.0f), Sprite(sprite), 
        IsSolid(false), Destroyed(false) { }

void GameObject::Draw(SpriteRenderer &renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Rotation, this->Color);
}


BallObject::BallObject() 
    : GameObject(), Radius(12.5f), isStuck(true) { }

BallObject::BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, 
      glm::vec3(1.0f), velocity), Radius(radius), isStuck(true) { }

glm::vec2 BallObject::Move(GLfloat dt, GLuint window_width)
{
    // if not stuck to player board
    if (!this->isStuck)
    { 
        // move the ball
        this->Position += this->Velocity * dt;
        // check if outside window bounds; if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
      
    }
    return this->Position;

}


// resets the ball to initial Stuck Position (if ball is outside window bounds)
void BallObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->isStuck = true;
}