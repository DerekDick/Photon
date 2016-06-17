#include "PhotonGame.h"
#include "HelloWorldScene.h"
#include "LevelSelectlayer.h"
#include "InfoLayer.h"
#include "SettingLayer.h"


USING_NS_CC;
USING_NS_CC_DEN;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init() {
    if (!Layer::init()) {
        return false;
    }

    //auto pic = Sprite::create("menu/LoadAni/01.png");
    //pic->setPosition(Vec2(100, 100));
    //this->addChild(pic);
    //auto circle = CSLoader::createNode("LoadAni/Node1.csb");
    //circle->setPosition(Vec2::ZERO);
    //auto circleAni = CSLoader::createTimeline("LoadAni/RotateCircle.csb");
    //circleAni->gotoFrameAndPlay(0, 66, true);
    //this->addChild(circle);
    //circle->runAction(circleAni);

    auto rootNode = CSLoader::createNode("Csbs/MainMenu.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode, 0);

    auto startButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("StartButton"));
    startButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = LevelSelect::createScene();
            auto reScr = TransitionProgressInOut::create(0.5f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });
    
    auto optionButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("OptionButton"));
    optionButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = Setting::createScene();
            auto reScr = TransitionFadeTR::create(0.4f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });

    auto infoButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("InfoButton"));
    infoButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = Info::createScene();
            auto reScr = TransitionFadeBL::create(0.4f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });


    auto exitButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("ExitButton"));
    exitButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            SimpleAudioEngine::getInstance()->stopAllEffects();
            Director::getInstance()->end();
        }

    });
    //circle->stopAction(circleAni);

    return true;
}

void HelloWorld::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        if (!UserDefault::getInstance()->getBoolForKey(MUSIC_PLAYED_KEY)) {
            SimpleAudioEngine::getInstance()->playBackgroundMusic(FILE_BGM, true);
            UserDefault::getInstance()->setBoolForKey(MUSIC_PLAYED_KEY, true);
        }
        else {
            SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        }
    }
}

void HelloWorld::cleanup() {
    Layer::cleanup();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}