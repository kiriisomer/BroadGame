#ifndef SCENE_BASE_HPP
#define SCENE_BASE_HPP

#include <glad/glad.h>
// game scene class
// a game includes multiple scenes, like title scene, 
// game scene, menu scene, ranking scene, etc.
class Engine;

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

	virtual int processInput() = 0;
	virtual int update(GLfloat dt) = 0;
	virtual int render() = 0;

	// private:
	Engine* engine;

	// engine function
	virtual int getKeyStatus(int key);
};


#endif
