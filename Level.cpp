#include "Level.h"
#include "PauseLayer.h"

USING_NS_CC;
USING_NS_CC_DEN;

Scene *Level::createScene() {
    auto scene = Scene::create();
    auto layer = Level::create();
    scene->addChild(layer);

    log("Level created");
    return scene;
}

bool Level::init() {
    if (!Layer::init()) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    auto rootNode = CSLoader::createNode("Csbs/Level.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode);
    
    //pause button
    auto pauseButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("PauseButton"));
    pauseButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto scr = Pause::createScene();
            auto reScr = TransitionMoveInB::create(0.4f, scr);
            Director::getInstance()->pushScene(reScr);
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });

    //level name
    levelTTFConfig = TTFConfig("Fonts/Foglihten.ttf", 40);
    Label* title = Label::createWithTTF(levelTTFConfig, "Aphoton W level B");
    title->setTextColor(Color4B(255, 255, 255, 255));
    title->setAnchorPoint(Vec2(0.5, 1.0));
    title->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height));
    this->addChild(title, 1, "title");

    //level pass


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
