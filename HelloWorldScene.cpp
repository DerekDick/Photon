#include "PhotonGame.h"
#include "HelloWorldScene.h"
#include "LevelSelectScene.h"
#include "InfoScene.h"
#include "SettingScene.h"

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

    auto rootNode = CSLoader::createNode("Csbs/MainMenu.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode, 0);

    auto loadingCircle = CSLoader::createNode("Pics/loading/LoadingCircle.csb");
    loadingCircle->setPosition(WINDOW_CENTER);
    auto loadingWord = CSLoader::createNode("Pics/loading/LoadingWord.csb");
    loadingWord->setPosition(WINDOW_CENTER);

    auto loadingCircleAnimation = CSLoader::createTimeline("Pics/loading/LoadingCircle.csb");
    auto loadingWordAnimation = CSLoader::createTimeline("Pics/loading/LoadingWord.csb");

    loadingCircleAnimation->gotoFrameAndPlay(0, 42, true);
    loadingWordAnimation->gotoFrameAndPlay(0, 80, true);

    loadingCircle->runAction(loadingCircleAnimation);
    loadingWord->runAction(loadingWordAnimation);

    auto first = Sprite::create("Pics/loading/first.jpg");
    first->setAnchorPoint(Point::ZERO);
    first->setPosition(Point::ZERO);

    this->addChild(first);
    this->addChild(loadingCircle);
    this->addChild(loadingWord);

    first->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(1), NULL));
    loadingCircle->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(1), NULL));
    loadingWord->runAction(Sequence::create(DelayTime::create(3), FadeOut::create(1), NULL));

    auto startButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("StartButton"));
    auto startButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = LevelSelect::createScene();
            auto reScr = TransitionProgressInOut::create(0.5f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    };
    startButton->addTouchEventListener(startButtonListener);
    
    auto optionButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("OptionButton"));
    auto optionButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = Setting::createScene();
            auto reScr = TransitionFadeTR::create(0.4f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    };
    optionButton->addTouchEventListener(optionButtonListener);

    auto infoButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("InfoButton"));
    auto infoButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = Info::createScene();
            auto reScr = TransitionFadeBL::create(0.4f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    };
    infoButton->addTouchEventListener(infoButtonListener);

    auto exitButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("ExitButton"));
    auto exitButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            SimpleAudioEngine::getInstance()->stopAllEffects();
            Director::getInstance()->end();
        }
    };
    exitButton->addTouchEventListener(exitButtonListener);

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