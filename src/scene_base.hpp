#ifndef SCENE_BASE_HPP
#define SCENE_BASE_HPP

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

	virtual int deal_event() = 0;
	virtual int update() = 0;
	virtual int render() = 0;

	// private:
	Engine* engine;

};


#endif
