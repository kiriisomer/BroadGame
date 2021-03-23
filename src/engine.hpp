#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
// #include <functional> // std::bind

// game engine: holding everything.
class Engine
{
public:
    unsigned int iScreenWidth;
    unsigned int iScreenHeight;
    std::string windowTitle;
    GLFWwindow* window;

public:
    Engine();
    ~Engine();

    int init();
    void uninit();
    int loop();

    // in main loop process input
    void processInput();
    // in main loop update sprites
    void update();
    void render();
};


// time manager, deal time, stabilize the deltatime
class TimeManager
{
public:
    GLdouble currentFrame;
    GLdouble lastFrame;
    GLfloat targetFps;
public:
    TimeManager();
    ~TimeManager();

    void start();
    void loop_update();
};

// game scene class
// a game includes multiple scenes, like title scene, 
// game scene, menu scene, ranking scene, etc.
class SceneBase
{
public:
	SceneBase(Engine* game_engine_obj);
	virtual ~SceneBase();

	virtual int init() = 0;
	virtual int start() = 0;
	virtual int pause() = 0;
	virtual int restart() = 0;
	virtual void destory() = 0;

	virtual int deal_event() = 0;
	virtual int update() = 0;
	virtual int render() = 0;

	// private:
	Engine* engine;

};

class SpriteRenderer
{
    public:
        SpriteRenderer();
        ~SpriteRenderer();

};


// for glfw callback func
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

// glfw error callback func
void glfw_error_callback(int code, const char *desc);

#endif
