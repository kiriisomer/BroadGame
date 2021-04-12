#include "scene_base.hpp"
#include "engine.hpp"
// SceneBase
SceneBase::SceneBase(Engine* game_engine_obj) :engine(game_engine_obj) {}

SceneBase::~SceneBase() {}

int SceneBase::getKeyStatus(int key)
{
    return this->engine->getKeyStatus(key);
}