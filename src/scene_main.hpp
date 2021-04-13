#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

#include <vector>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "engine.hpp"
#include "scene_base.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

#include "game_level.hpp"

class Engine;
class SpriteRenderer;
// class GameLevel;
class GameObject;


// initial panel size
const glm::vec2 PLAYER_SIZE(100, 20);
// initial panel move speed
const GLfloat PLAYER_VELOCITY(500.0f);
// initial ball speed(x, y)
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
// initial ball radius
const GLfloat BALL_RADIUS = 12.5f;


class MainScene: public SceneBase
{
public:
    MainScene(Engine* game_engine_obj);
    ~MainScene(){
        this->destory();
    }

    int init();
    int start();
    int pause();
    int restart();
    void destory();

    int processInput();
    int update(GLfloat dt);
    int render();

    GLuint Width;
    GLuint Height;
    SpriteRenderer* Renderer;

    std::map<int, int> KeyStatus;

    std::vector<GameLevel> Levels;
    GLuint Level;

    GameObject *Player;
    BallObject *Ball;
};

#endif
