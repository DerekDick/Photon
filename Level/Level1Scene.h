#ifndef _LEVEL1_SCENE_H_
#define _LEVEL1_SCENE_H_

#include "LevelScene.h"

class Level1 : public Level {
public:
	static cocos2d::Scene *createScene();
	bool init();
	CREATE_FUNC(Level1);

	void update(float dt);
	void shoot(float dt);

private:
	cocos2d::Sprite* lightSource;
	cocos2d::Sprite* lense;
	cocos2d::Sprite* mirror1;
	cocos2d::Sprite* mirror2;
	cocos2d::Sprite* mirror3;
	cocos2d::Sprite* receiver;
	bool receiverTag[3]; //Tag whether the red green blue photons has reached the receiver

};

#endif // _LEVEL1_SCENE_H_
