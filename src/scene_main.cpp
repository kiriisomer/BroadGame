
#include "engine.hpp"
#include "scene_main.hpp"

MainScene::MainScene(Engine* game_engine_obj) : SceneBase(game_engine_obj) {}

int MainScene::init()
{
    Width = engine->iScreenWidth;
    Height = engine->iScreenHeight;
    // Load shaders
    ResourceManager::LoadShader("shader/sprite.vs", "shader/sprite.frag", nullptr, "sprite");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -10.0f, 10.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("texture/face.png", GL_TRUE, "face");
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    return 0;
}

int MainScene::start()
{
    return 0;
}

int MainScene::pause()
{
    return 0;
}

int MainScene::restart()
{
    return 0;
}

void MainScene::destory()
{
    delete Renderer;
}

int MainScene::deal_event()
{
    return 0;
}

int MainScene::update()
{
    return 0;
}

int MainScene::render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(300, 300), glm::vec2(400, 400), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    return 0;
}
