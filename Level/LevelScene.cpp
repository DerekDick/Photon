#include "LevelScene.h"
#include "PauseLayerScene.h"

USING_NS_CC;
USING_NS_CC_DEN;

cocos2d::Scene *Level::createScene() {
    auto scene = Scene::create();
    auto layer = Level::create();
    scene->addChild(layer);

    return scene;
}

Scene *Level::createLevel(int levelNum) {
    Scene *scene = nullptr;
  /*switch (levelNum) {
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
    }*/
    return scene;
}

bool Level::init() {
    if (!Layer::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    levelNumber = 0;

    auto rootNode = CSLoader::createNode("Csbs/Level.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode);
    
    //level name
    levelTTFConfig = TTFConfig("Fonts/Foglihten.ttf", 40);
    Label* title = Label::createWithTTF(levelTTFConfig, "Aphoton W level B");
    title->setTextColor(Color4B(255, 255, 255, 255));
    title->setAnchorPoint(Vec2(0.5, 1.0));
    title->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height));
    this->addChild(title, 1, "title");

    //pause button
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

    //nextlevel button
    nextLevelButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("NextLevelButton"));
    auto nextLevelButtonListener = [](Ref* pSender, ui::Widget::TouchEventType type, int levelNumber) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scene = Level::createLevel(++levelNumber);
            auto reScr = TransitionTurnOffTiles::create(0.8f, scene);
            Director::getInstance()->replaceScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    };

    return true;
}

Label * Level::createLabelWithTTF(TTFConfig & ttfConfig, const std::string & text,
                                  Vec2 & position, Vec2 & anchorPoint,
                                  TextHAlignment hAlignment, int maxLineWidth) {
    auto myLabel = Label::createWithTTF(ttfConfig, text, hAlignment, maxLineWidth);
    myLabel->setAnchorPoint(anchorPoint);
    myLabel->setPosition(position);

    return myLabel;
}

Sprite *Level::createdAnotherReciever() {
    Sprite* reciever = Sprite::create("Pics/reciever.png");
    reciever->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    reciever->setColor(Color3B(100, 100, 100));
    return reciever;
}

void Level::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
