#ifndef _LEVEL_SCENE_H_
#define _LEVEL_SCENE_H_

#include "PhotonGame.h"
#include "Photon.h"
#include "Lense.h"
#include <vector>

class Level : public cocos2d::Layer {
protected:
	int levelNumber;
	cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	cocos2d::ui::Button *pauseButton;
	cocos2d::ui::Button *nextLevelButton;

public:
	std::vector<Photon*> photons;
	std::vector<Lense*> lenses;
	std::vector<cocos2d::Sprite*> movableLenses;
	std::vector<cocos2d::Sprite*> rotatableLenses;
	cocos2d::Sprite* rotatingLense = nullptr;
	cocos2d::Sprite* movingLense = nullptr;

	static cocos2d::Scene* Level::createScene();
	static cocos2d::Scene* createLevel(int levelNum);

	virtual bool init();

	cocos2d::Label* addLevelTitle();
	cocos2d::Sprite* addLightSource(cocos2d::Vec2 pos, cocos2d::Color3B color = WHITE);
	cocos2d::Sprite* addReceiver(cocos2d::Vec2 pos, cocos2d::Color3B color = DARK);
	
	template<typename T>
	T* addLense(const std::string &fileName, cocos2d::Vec2 pos, double angle = 0.0) {
		T* newLense = Lense::create<T>(fileName, pos, angle);
		this->addChild(newLense);
		lenses.push_back(newLense);

		return newLense;
	}

	void initNextLevelButton();
	void nextLevelButtonOnUse(bool statu);
	int getLevelNumber() const { return levelNumber; }

	bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void touchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual void onEnter();
	virtual void onExit();

	virtual void onEnterTransitionDidFinish();

	CREATE_FUNC(Level);

private:
	cocos2d::TTFConfig levelTTFConfig = cocos2d::TTFConfig("Fonts/FoglihtenFr02.ttf", 40);
};

#endif //_LEVEL_SCENE_H_
