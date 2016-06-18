#ifndef _LEVEL_SCENE_H_
#define _LEVEL_SCENE_H_

#include "PhotonGame.h"
#include <vector>

class Level : public cocos2d::Layer {
protected:
	int levelNumber;
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::ui::Button *pauseButton;
	cocos2d::ui::Button *nextLevelButton;

public:
	static cocos2d::Scene* Level::createScene();
	static cocos2d::Scene* createLevel(int levelNum);

	virtual bool init();

	cocos2d::Label* addLevelTitle();
	cocos2d::Sprite* addLense(std::string fileName, cocos2d::Vec2 pos, double angle = 0.0);
	cocos2d::Sprite* addReceiver(std::string fileName, cocos2d::Vec2 pos, cocos2d::Color3B color = DARK);

	void initNextLevelButton();
	void nextLevelButtonOnUse(bool statu);
	int getLevelNumber() const { return levelNumber; }

	virtual void onEnterTransitionDidFinish();

	CREATE_FUNC(Level);

private:
	cocos2d::TTFConfig levelTTFConfig = cocos2d::TTFConfig("Fonts/FoglihtenFr02.ttf", 40);
};

#endif //_LEVEL_SCENE_H_
