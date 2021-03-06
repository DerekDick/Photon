#ifndef _LEVEL2_SCENE_H_
#define _LEVEL2_SCENE_H_

#include "LevelScene.h"
#include "Mirror.h"

class Level2 : public Level {
public:
	static cocos2d::Scene *createScene();
	bool init();
	CREATE_FUNC(Level2);

	void update(float dt);
	void shoot(float dt);

private:
	cocos2d::Sprite* lightSource;
	cocos2d::Sprite* receiver;
	Lense* mirror1;
	Lense* mirror2;
	Lense* mirror3;
};

#endif // _LEVEL2_SCENE_H_
