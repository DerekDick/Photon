#ifndef _LEVEL1SCENE_H_
#define _LEVEL1SCENE_H_

#include "PhotonGame.h"

class Level1 : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt);
	void shoot(float dt);

	virtual void onEnter();
	virtual void onExit();

	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	CREATE_FUNC(Level1);
};

#endif // _LEVEL1SCENE_H_
