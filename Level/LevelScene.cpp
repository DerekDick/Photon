#include "LevelScene.h"
#include "PauseScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Level4Scene.h"
#include "Level5Scene.h"
#include "Level6Scene.h"
#include "Level7Scene.h"
#include "Level8Scene.h"
#include "Level9Scene.h"
#include "Level10Scene.h"
#include "Level11Scene.h"
#include "Level12Scene.h"
#include "Level13Scene.h"
#include "Level14Scene.h"
#include "Level15Scene.h"

USING_NS_CC;
USING_NS_CC_DEN;

cocos2d::Scene *Level::createScene() {
	Scene* scene = Scene::create();
	Level* layer = Level::create();
	scene->addChild(layer);

	return scene;
}

Scene *Level::createLevel(int levelNum) {
	Scene *scene = nullptr;
	switch (levelNum) {
	case 1:
	scene = Level1::createScene();
	break;
	case 2:
	scene = Level2::createScene();
	break;
	case 3:
	scene = Level3::createScene();
	break;
	case 4:
	scene = Level4::createScene();
	break;
	case 5:
	scene = Level5::createScene();
	break;
	case 6:
	scene = Level6::createScene();
	break;
	case 7:
	scene = Level7::createScene();
	break;
	case 8:
	scene = Level8::createScene();
	break;
	case 9:
	scene = Level9::createScene();
	break;
	case 10:
	scene = Level10::createScene();
	break;
	case 11:
	scene = Level11::createScene();
	break;
	case 12:
	scene = Level12::createScene();
	break;
	case 13:
	scene = Level13::createScene();
	break;
	case 14:
	scene = Level14::createScene();
	break;
	case 15:
	scene = Level15::createScene();
	break;
	default:
	scene = Level::createScene();
	break;
	}
	//scene = Level1::createScene();
	return scene;
}

bool Level::init() {
	if (!Layer::init()) {
		return false;
	}

	levelNumber = 0;

	auto rootNode = CSLoader::createNode("Csbs/Level.csb");
	rootNode->setPosition(Vec2::ZERO);
	this->addChild(rootNode);

	//Pause button
	pauseButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("PauseButton"));
	auto pauseButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			auto scene = Pause::createScene();
			auto reScr = TransitionMoveInB::create(0.4f, scene);
			Director::getInstance()->pushScene(reScr);
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
			}
		}
	};
	pauseButton->addTouchEventListener(pauseButtonListener);

	//Next level button
	nextLevelButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("NextLevelButton"));

	//Usage of intNextLevelButton
	this->initNextLevelButton();

	//When level passed
	this->nextLevelButtonOnUse(true);

	return true;
}

Label * Level::addLevelTitle() {
	auto text = __String::createWithFormat("Aphoton W level%dB", levelNumber);
	Label* title = Label::createWithTTF(levelTTFConfig, text->_string);
	title->setAnchorPoint(Vec2(0.5, 1.0));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	title->setTextColor(Color4B(255, 255, 255, 200));
	this->addChild(title);

	return title;
}

Sprite* Level::addLense(std::string fileName, Vec2 pos, double angle) {
	Sprite* newLense = Sprite::create(fileName);
	newLense->setPosition(pos);
	newLense->setRotation(angle);
	this->addChild(newLense);

	return newLense;
}

cocos2d::Sprite * Level::addReceiver(std::string fileName, cocos2d::Vec2 pos, cocos2d::Color3B color) {
	Sprite* newReceiver = Sprite::create(fileName);
	newReceiver->setPosition(pos);
	newReceiver->setColor(DARK);
	this->addChild(newReceiver);

	return newReceiver;
}

void Level::initNextLevelButton() {
	auto nextLevelButtonListener = [this](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			int levelNum = this->getLevelNumber();
			auto scene = Level::createLevel(levelNum + 1);
			auto reScr = TransitionMoveInL::create(0.8f, scene);
			Director::getInstance()->replaceScene(reScr);
			if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
				SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
			}
		}
	};
	nextLevelButton->addTouchEventListener(nextLevelButtonListener);
	this->nextLevelButtonOnUse(false);
}

void Level::nextLevelButtonOnUse(bool statu) {
	nextLevelButton->setEnabled(statu);
	nextLevelButton->setVisible(statu);
}

void Level::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
}
