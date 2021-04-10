#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "engine.hpp"
#include "scene_base.hpp"
#include "resource_manager.hpp"
#include "sprite_renderer.hpp"

class Engine;
class SpriteRenderer;
class GameLevel;

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

    int deal_event();
    int update();
    int render();

    GLuint Width;
    GLuint Height;
    SpriteRenderer* Renderer;

    std::vector<GameLevel> Levels;
    GLuint Level;
};

#endif
