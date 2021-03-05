#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
// #include <functional> // std::bind

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

// for glfw callback func
void framebufferSizeCallback(GLFWwindow *window, int width, int height);

// glfw error callback func
void glfw_error_callback(int code, const char *desc);

#endif
