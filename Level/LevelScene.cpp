#include "LevelScene.h"
#include "PauseScene.h"
#include "Level1Scene.h"
#include "Level2Scene.h"
#include "Level3Scene.h"
#include "Level4Scene.h"
#include "Lense.h"
#include "Mirror.h"
#include "PhotonGame.h"

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
	}
	return scene;
}

bool Level::init() {
	if (!Layer::init()) {
		return false;
	}

	levelNumber = 0;

	auto rootNode = CSLoader::createNode("Csbs/Level.csb");
	rootNode->setPosition(Vec2::ZERO);
	this->addChild(rootNode, 0, "rootChild");

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
	nextLevelButton = dynamic_cast<ui::Button*>(rootNode->getChildByName("NextLevelButton"));

	//Usage of intNextLevelButton
	this->initNextLevelButton();

	return true;
}

Label* Level::addLevelTitle() {
	auto text = __String::createWithFormat("Aphoton W level%dB", levelNumber);
	Label* title = Label::createWithTTF(levelTTFConfig, text->_string);
	title->setAnchorPoint(Vec2(0.5, 1.0));
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height));
	title->setTextColor(Color4B(255, 255, 255, 200));
	this->addChild(title, 1, "title");

	return title;
}

Sprite* Level::addLightSource(cocos2d::Vec2 pos, cocos2d::Color3B color) {
	Sprite* lightSource = Sprite::create(FILE_LIGHT_SOURCE);
	lightSource->setPosition(pos);
	lightSource->setColor(color);
	this->addChild(lightSource);
	return lightSource;
}

cocos2d::Sprite* Level::addReceiver(cocos2d::Vec2 pos, cocos2d::Color3B color) {
	Sprite* newReceiver = Sprite::create(FILE_RECEIVER);
	newReceiver->setPosition(pos);
	newReceiver->setColor(DARK);
	this->addChild(newReceiver);

	return newReceiver;
}

void Level::initNextLevelButton() {
	auto nextLevelButtonListener = [this](Ref* pSender, ui::Widget::TouchEventType type) {
		if (type == ui::Widget::TouchEventType::ENDED) {
			int levelNum = this->getLevelNumber();
			if (levelNum != 4) {
				auto scene = Level::createLevel(levelNum + 1);
				auto reScr = TransitionMoveInL::create(0.8f, scene);
				Director::getInstance()->replaceScene(reScr);
			}
			else {
				Director::getInstance()->popToRootScene();
			}
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

void Level::onEnter() {
	Layer::onEnter();
	auto myTouchListener = EventListenerTouchOneByOne::create();
	myTouchListener->setSwallowTouches(false);
	myTouchListener->onTouchBegan = CC_CALLBACK_2(Level::touchBegan, this);
	myTouchListener->onTouchMoved = CC_CALLBACK_2(Level::touchMoved, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(myTouchListener, this->getChildByName("rootChild"));

	return;
}
bool Level::touchBegan(Touch* touch, Event* event) {
	Vec2 touchPosition = touch->getLocation();
	// move event should be responded first
	for (std::vector<Sprite*>::iterator iter = movableLenses.begin(); iter != movableLenses.end(); iter++) {
		Sprite* lense = *iter;
		if (touchPosition.distance(lense->getPosition()) <= lense->getContentSize().height / 2.0) {
			movingLense = lense;
			return true;
		}
	}
	// if no lense is movable, respond to the rotate event
	for (std::vector<Sprite*>::iterator iter = rotatableLenses.begin(); iter != rotatableLenses.end(); iter++) {
		Sprite* lense = *iter;
		Vec2 localPosition = lense->convertToNodeSpaceAR(touchPosition);
		if ( (abs(localPosition.x) <= lense->getContentSize().width / 2.0) && (abs(localPosition.y) <= lense->getContentSize().height / 2.0)/*touchPosition.distance(lense->getPosition()) <= lense->getContentSize().width / 2.0*/) {
			rotatingLense = lense;
			return true;
		}
	}

	movingLense = nullptr;
	rotatingLense = nullptr;

	return false;
}

void Level::touchMoved(cocos2d::Touch * touch, cocos2d::Event* event) {
	Vec2 touchPosition = touch->getLocation();
	if (movingLense) {
		movingLense->setPosition(touchPosition);
		return;
	}
	else if (rotatingLense) {
		Vec2 lensePosition = rotatingLense->getPosition();
		double angle = 0.0;
		if (touchPosition.x != lensePosition.x) {
			angle = atan((touchPosition.y - lensePosition.y) / (touchPosition.x - lensePosition.x)) * 180 / PI;
		}
		else {
			angle = 90;
		}
		rotatingLense->setRotation(360 - angle);
		return;
	}
}

void Level::onExit() {
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this->getChildByName("rootChild"));
	return;
}
