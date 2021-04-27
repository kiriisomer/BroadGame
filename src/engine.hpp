#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
// #include <functional> // std::bind

class SceneBase;
class MainScene;

// game engine: holding everything.
class Engine
{
public:
    unsigned int iScreenWidth;
    unsigned int iScreenHeight;
    int iFrameWidth;
    int iFrameHeight;
    std::string windowTitle;
    GLFWwindow* window;

    // scenes
    SceneBase* current_scene;
    MainScene* main_scene;

public:
    Engine();
    ~Engine();

    int init();
    int _init_opengl();
    void uninit();
    int loop();

    // in main loop process input
    void processInput();
    // in main loop update sprites
    void update(GLfloat dt);
    void render();

    // 
    int getKeyStatus(int key);
};


// time manager, deal time, stabilize the deltatime
// class TimeManager
// {
// public:
//     GLdouble currentFrame;
//     GLdouble lastFrame;
//     GLfloat targetFps;
// public:
//     TimeManager();
//     ~TimeManager();

//     void start();
//     void loop_update();
// };


// for glfw callback func
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

// glfw error callback func
void glfw_error_callback(int code, const char *desc);

#endif
