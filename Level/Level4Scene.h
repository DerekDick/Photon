#ifndef _LEVEL4_SCENE_H_
#define _LEVEL4_SCENE_H_

#include "LevelScene.h"
#include "cocos2d.h"
#include "Lense.h"

class Level4 : public Level {
public:
	static cocos2d::Scene *createScene();
	bool init();
	CREATE_FUNC(Level4);

	void update(float dt);
	void shoot(float dt);

	void setFactor(double f);

	void onEnter();
	void onExit();

	bool changeBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void changeEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
	bool recieverTag[2];
	cocos2d::Sprite* lightSource;
	cocos2d::Sprite* receiverB;
	cocos2d::Sprite* receiverR;
	Lense* lense;
	cocos2d::Vec2 blackholeCenter = cocos2d::Vec2(400.0, 300.0);
	double factor = 1.0;
	double radius = 90.0;
};

#endif // _LEVEL4_SCENE_H_
