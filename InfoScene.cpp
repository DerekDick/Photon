#include "InfoScene.h"

USING_NS_CC;
USING_NS_CC_DEN;

cocos2d::Scene * Info::createScene() {
    auto scene = Scene::create();
    auto layer = Info::create();
    scene->addChild(layer);

    return scene;
}

bool Info::init() {
    if (!Layer::init()) {
        return false;
    }

    auto rootNode = CSLoader::createNode("Csbs/Info.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode);

    auto mainMenuButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("MainMenuButton"));
    mainMenuButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->popToRootScene();
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });

    return true;
}

void Info::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}
