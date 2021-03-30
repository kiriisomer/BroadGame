#ifndef SCENE_MAIN_HPP
#define SCENE_MAIN_HPP

// #include "engine.hpp"
#include "scene_base.hpp"
class Engine;
// class SceneBase;


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

};

#endif
