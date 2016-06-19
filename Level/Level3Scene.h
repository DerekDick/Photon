#ifndef _LEVEL3_SCENE_H_
#define _LEVEL3_SCENE_H_

#include "LevelScene.h"

class Level3 : public Level {
public:
	static cocos2d::Scene *createScene();
	bool init();
	CREATE_FUNC(Level3);

	void update(float dt);
	void shoot(float dt);

private:
	cocos2d::Sprite* lightSource;
	cocos2d::Sprite* receiver;
	Lense* mirror1;
	Lense* mirror2;
	Lense* mirror3;
	Lense* mirror4;
	Lense* lenseThroughG1;
	Lense* lenseThroughG2;
	Lense* lenseThroughR1;
	Lense* lenseThroughR2;
	Lense* lenseTurnG;
	Lense* lenseTurnR;
};

#endif // _LEVEL3_SCENE_H_
