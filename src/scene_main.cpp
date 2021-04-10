
#include "engine.hpp"
#include "scene_main.hpp"
#include "game_level.hpp"

MainScene::MainScene(Engine* game_engine_obj) : SceneBase(game_engine_obj) {
    Renderer = NULL;
    this->Level = 0;
}

int MainScene::init()
{
    Width = engine->iScreenWidth;
    Height = engine->iScreenHeight;
    // Load shaders
    ResourceManager::LoadShader("shader/sprite.vs", "shader/sprite.frag", nullptr, "sprite");
    
    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -10.0f, 10.0f);
    // glm::mat4 projection = glm::ortho(0.0f, 8.0f, 6.0f, 0.0f, -10.0f, 10.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("texture/face.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("texture/block.png", GL_TRUE, "block");
    ResourceManager::LoadTexture("texture/block_solid.png", GL_TRUE, "block_solid");
    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    // load Levels
    GameLevel one;
    one.Load("res/level/level1.txt", this->Width, this->Height * 0.5);
    this->Levels.push_back(one);
    GameLevel two;
    two.Load("res/level/level2.txt", this->Width, this->Height * 0.5);
    this->Levels.push_back(two);
    GameLevel three;
    three.Load("res/level/level3.txt", this->Width, this->Height * 0.5);
    this->Levels.push_back(three);
    GameLevel four;
    four.Load("res/level/level4.txt", this->Width, this->Height * 0.5);
    this->Levels.push_back(four);

    return 0;
}

void MainScene::destory()
{
    if(Renderer)
    {
        delete Renderer;
        Renderer = NULL;
    }
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
    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
        glm::vec2(350.0f, 250.0f), glm::vec2(100.0f, 100.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->Levels[this->Level].Draw(*Renderer);
    return 0;
}
