
#include "engine.hpp"
#include "scene_main.hpp"
#include "game_object.hpp"

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
    ResourceManager::LoadTexture("texture/paddle.png", GL_TRUE, "paddle");
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

    // player paddle info
    glm::vec2 playerPos = glm::vec2(
        this->Width / 2 - PLAYER_SIZE.x / 2, 
        this->Height - PLAYER_SIZE.y
    );
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

    return 0;
}

void MainScene::destory()
{
    if(Renderer)
    {
        delete Renderer;
        Renderer = NULL;
    }
    if(Player)
    {
        delete Player;
        Player = NULL;
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

int MainScene::processInput()
{
    return 0;
}

int MainScene::update(GLfloat dt)
{
    GLfloat velocity = PLAYER_VELOCITY * dt;
    // // 移动挡板
    // if (this->Keys[GLFW_KEY_A])
    // {
    //     if (Player->Position.x >= 0)
    //         Player->Position.x -= velocity;
    // }
    // if (this->Keys[GLFW_KEY_D])
    // {
    //     if (Player->Position.x <= this->Width - Player->Size.x)
    //         Player->Position.x += velocity;
    // }
    return 0;
}

int MainScene::render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"),
        glm::vec2(350.0f, 250.0f), glm::vec2(100.0f, 100.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    this->Levels[this->Level].Draw(*Renderer);
    Player->Draw(*Renderer);
    return 0;
}
