#include "engine.hpp"
#include "scene_base.hpp"
#include "scene_main.hpp"

// Engine
Engine::Engine() {
    iScreenWidth = 480;
    iScreenHeight = 320;
    windowTitle = "BroGamer";
    current_scene = NULL;
    main_scene = NULL;
}
Engine::~Engine() {}

int Engine::init()
{
    this->_init_opengl();
    main_scene = new MainScene(this);
    current_scene = main_scene;
    current_scene->init();
    return 0;
}

int Engine::_init_opengl()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback(glfw_error_callback);

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(iScreenWidth, iScreenHeight, windowTitle.c_str(), NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 要应用透明纹理，首先我们启用2D纹理
    glEnable(GL_TEXTURE_2D);
    // 然后关闭深度测试
    glDepthMask(GL_FALSE);                             // 关掉深度测试
    glEnable(GL_BLEND);                                // 开混合模式贴图
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // 指定混合模式算法

    return 0;
}

int Engine::loop()
{

    while (!glfwWindowShouldClose(this->window))
    {
        // deal input
        // ----------
        this->processInput();
        this->update();
        this->render();

        // glfw: swap buffers
        // ------------------
        glfwSwapBuffers(window);
        // glfw: poll events
        // -----------------
        glfwPollEvents();
    }
    return 0;
}

void Engine::uninit()
{
    if (main_scene) {
        delete main_scene;
        main_scene = NULL;
    }
    // opengl uninit
    glfwTerminate();
}

void Engine::processInput()
{
    // 按ESC按键退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    else {
        current_scene->deal_event();
    }
}

void Engine::update()
{
    current_scene->update();
    // std::cout<<1; std::cout.flush();
}

void Engine::render()
{
    // draw background
    // ---------------
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    current_scene->render();

}


// TimeMamager
// TimeManager::TimeManager() 
// {
//     currentFrame = 0.0f;
//     lastFrame = 0.0f;
//     targetFps = 60.0f;        // 目标fps
// }

// void TimeManager::start()
// {
//     lastFrame = 0.0f;
//     currentFrame = 0.0f;
//     glfwSetTime(0.0f);
// }

// void TimeManager::loop_update()
// {
//     currentFrame = glfwGetTime();
//     lastFrame = currentFrame;
// }

// SpriteRenderer


// for glfw callback func
void framebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// glfw error callback func
void glfw_error_callback(int code, const char *desc)
{
    std::cout << "---- glfw error ----" << std::endl;
    std::cout << " error code: " << code << std::endl;
    std::cout << desc << std::endl;
    std::cout << "--------------------" << std::endl;
}
