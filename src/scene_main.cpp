
#include "engine.hpp"
#include "scene_main.hpp"
#include "game_object.hpp"

MainScene::MainScene(Engine *game_engine_obj) : SceneBase(game_engine_obj)
{
    Renderer = NULL;
    this->Level = 0;
}

int MainScene::init()
{
    Width = engine->iScreenWidth;
    Height = engine->iScreenHeight;
    // Load shaders
    ResourceManager::LoadShader("shader/sprite.vs", "shader/sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("shader/particle.vs", "shader/particle.frag", nullptr, "particle");
    ResourceManager::LoadShader("shader/post_processing.vs", "shader/post_processing.frag", nullptr, "postprocessing");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), 
        static_cast<GLfloat>(this->Height), 0.0f, -10.0f, 10.0f);
    // glm::mat4 projection = glm::ortho(0.0f, 8.0f, 6.0f, 0.0f, -10.0f, 10.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
    ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
    // Load textures
    ResourceManager::LoadTexture("res/texture/face.png", GL_TRUE, "face");
    ResourceManager::LoadTexture("res/texture/block.png", GL_TRUE, "block");
    ResourceManager::LoadTexture("res/texture/block_solid.png", GL_TRUE, "block_solid");
    ResourceManager::LoadTexture("res/texture/paddle.png", GL_TRUE, "paddle");
    ResourceManager::LoadTexture("res/texture/particle.png", GL_TRUE, "particle");


    // Set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    // particle
    Particles = new ParticleGenerator(
        ResourceManager::GetShader("particle"), 
        ResourceManager::GetTexture("face"), 
        5000
    );
    Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), 
        this->Width, this->Height);
    
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
        this->Height - PLAYER_SIZE.y);
    glm::vec2 ballPos = playerPos + glm::vec2(
                                        PLAYER_SIZE.x / 2 - BALL_RADIUS,
                                        -BALL_RADIUS * 2);
    Player = new GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("paddle")
                            );
    Ball = new BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY,
                          ResourceManager::GetTexture("face"));

    // key press info
    KeyStatus[GLFW_KEY_A] = GLFW_RELEASE;
    KeyStatus[GLFW_KEY_D] = GLFW_RELEASE;

    return 0;
}

void MainScene::destory()
{
    if (Renderer)
    {
        delete Renderer;
        Renderer = NULL;
    }
    if (Player)
    {
        delete Player;
        Player = NULL;
    }
    if (Ball)
    {
        delete Ball;
        Ball = NULL;
    }
    if (Particles)
    {
        delete Particles;
        Particles = NULL;
    }
    if (Effects)
    {
        delete Effects;
        Effects = NULL;
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
    KeyStatus[GLFW_KEY_SPACE] = this->getKeyStatus(GLFW_KEY_SPACE);
    KeyStatus[GLFW_KEY_A] = this->getKeyStatus(GLFW_KEY_A);
    KeyStatus[GLFW_KEY_D] = this->getKeyStatus(GLFW_KEY_D);
    KeyStatus[GLFW_KEY_U] = this->getKeyStatus(GLFW_KEY_U);
    KeyStatus[GLFW_KEY_I] = this->getKeyStatus(GLFW_KEY_I);
    KeyStatus[GLFW_KEY_O] = this->getKeyStatus(GLFW_KEY_O);
    return 0;
}

int MainScene::update(GLfloat dt)
{
    GLfloat velocity = PLAYER_VELOCITY * dt;
    Ball->Move(dt, this->Width);
    this->DoCollisions();
    // move the panel
    if (this->KeyStatus[GLFW_KEY_A] == GLFW_PRESS &&
        this->KeyStatus[GLFW_KEY_D] == GLFW_RELEASE)
    {
        if (Player->Position.x >= 0)
        {
            Player->Position.x -= velocity;
            if (Ball->isStuck)
                Ball->Position.x -= velocity;
        }
    }
    else if (this->KeyStatus[GLFW_KEY_D] == GLFW_PRESS &&
             this->KeyStatus[GLFW_KEY_A] == GLFW_RELEASE)
    {
        if (Player->Position.x <= this->Width - Player->Size.x)
        {
            Player->Position.x += velocity;
            if (Ball->isStuck)
                Ball->Position.x += velocity;
        }
    }

    if (this->KeyStatus[GLFW_KEY_SPACE])
        Ball->isStuck = false;

    // effect switch
    if (this->KeyStatus[GLFW_KEY_U])
    {    
        Effects->Chaos = true;
        Effects->Confuse = false;
    }
    else if (this->KeyStatus[GLFW_KEY_I])
    {
        Effects->Chaos = false;
        Effects->Confuse = true;
    }
    else if (this->KeyStatus[GLFW_KEY_O])
    {
        Effects->Chaos = false;
        Effects->Confuse = false;
    }


    if (Ball->Position.y >= this->Height +20.0f)
    {
        // this->ResetLevel();
        this->ResetPlayerAndBall();
    }

    // Update particles
    Particles->Update(dt, *Ball, 1, glm::vec2(Ball->Radius / 2));
    // reduce shake time
    if (ShakeTime > 0.0f)
    {
        ShakeTime -= dt;
        if (ShakeTime <= 0.0f)
            Effects->Shake = GL_FALSE;
    }

    return 0;
}

int MainScene::render()
{

    Effects->BeginRender();
        // Renderer->DrawSprite(ResourceManager::GetTexture("face"),
        //                      glm::vec2(350.0f, 250.0f), glm::vec2(100.0f, 100.0f), 
        //                      45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        this->Levels[this->Level].Draw(*Renderer);
        Player->Draw(*Renderer);
        Particles->Draw();
        Ball->Draw(*Renderer);
    Effects->EndRender();
    Effects->Render(glfwGetTime());
    return 0;
}

void MainScene::DoCollisions()
{
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        if (!box.Destroyed)
        {
            Collision collision = CheckBallCollision(*Ball, box);
            if (std::get<0>(collision)) // If collision is true
            {
                // Destroy block if not solid
                if (!box.IsSolid)
                    box.Destroyed = GL_TRUE;
                else
                {
                    ShakeTime = 0.05f;
                    Effects->Shake = GL_TRUE;
                }
                // Collision resolution
                Direction dir = std::get<1>(collision);
                glm::vec2 diff_vector = std::get<2>(collision);
                if (dir == LEFT || dir == RIGHT) // Horizontal collision
                {
                    Ball->Velocity.x = -Ball->Velocity.x; // Reverse horizontal velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.x);
                    if (dir == LEFT)
                        Ball->Position.x += penetration; // Move ball to right
                    else
                        Ball->Position.x -= penetration; // Move ball to left;
                }
                else // Vertical collision
                {
                    Ball->Velocity.y = -Ball->Velocity.y; // Reverse vertical velocity
                    // Relocate
                    GLfloat penetration = Ball->Radius - std::abs(diff_vector.y);
                    if (dir == UP)
                        Ball->Position.y -= penetration; // Move ball bback up
                    else
                        Ball->Position.y += penetration; // Move ball back down
                }
            }
        }    
    }
    // Also check collisions for player pad (unless stuck)
    Collision result = CheckBallCollision(*Ball, *Player);
    if (!Ball->isStuck && std::get<0>(result))
    {
        // Check where it hit the board, and change velocity based on where it hit the board
        GLfloat centerBoard = Player->Position.x + Player->Size.x / 2;
        GLfloat distance = (Ball->Position.x + Ball->Radius) - centerBoard;
        GLfloat percentage = distance / (Player->Size.x / 2);
        // Then move accordingly
        GLfloat strength = 2.0f;
        glm::vec2 oldVelocity = Ball->Velocity;
        Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength; 
        //Ball->Velocity.y = -Ball->Velocity.y;
        Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
        // Fix sticky paddle
        Ball->Velocity.y = -1 * abs(Ball->Velocity.y);
    }
}

void MainScene::ResetLevel()
{
    if (this->Level == 0)
        this->Levels[0].Load("res/level/level1.txt", this->Width, this->Height * 0.5f);
    else if (this->Level == 1)
        this->Levels[1].Load("res/level/level2.txt", this->Width, this->Height * 0.5f);
    else if (this->Level == 2)
        this->Levels[2].Load("res/level/level3.txt", this->Width, this->Height * 0.5f);
    else if (this->Level == 3)
        this->Levels[3].Load("res/level/level4.txt", this->Width, this->Height * 0.5f);
}

void MainScene::ResetPlayerAndBall()
{
    // Reset player/ball stats
    Player->Size = PLAYER_SIZE;
    Player->Position = glm::vec2(this->Width / 2 - PLAYER_SIZE.x / 2, this->Height - PLAYER_SIZE.y);
    Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2 - BALL_RADIUS, -(BALL_RADIUS * 2)), INITIAL_BALL_VELOCITY);
}