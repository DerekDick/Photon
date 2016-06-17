#include "SettingLayer.h"

USING_NS_CC;
USING_NS_CC_DEN;

Scene *Setting::createScene() {
    auto scene = Scene::create();
    auto layer = Setting::create();
    scene->addChild(layer);
    
    return scene;
}

bool Setting::init() {
    if (!Layer::init()) {
        return false;
    }

    auto rootNode = CSLoader::createNode("Csbs/Setting.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode);

    auto soundCheckBox = dynamic_cast<ui::CheckBox *>(rootNode->getChildByName("SoundCheckBox"));
    if (!UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
        soundCheckBox->setSelectedState(false);
    }
    soundCheckBox->addEventListener(CC_CALLBACK_2(Setting::soundCheckBoxCallBack, this));


    auto musicCheckBox = dynamic_cast<ui::CheckBox *>(rootNode->getChildByName("MusicCheckBox"));
    if (!UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        musicCheckBox->setSelectedState(false);
    }
    musicCheckBox->addEventListener(CC_CALLBACK_2(Setting::musicCheckBoxCallBack, this));

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

void Setting::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}

void Setting::soundCheckBoxCallBack(cocos2d::Ref * pSender, cocos2d::ui::CheckBox::EventType type) {
    auto item = (ui::CheckBox *)pSender;
    if (type == ui::CheckBox::EventType::UNSELECTED) {
        UserDefault::getInstance()->setBoolForKey(SOUND_KEY, false);
    }
    else {
        SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
        UserDefault::getInstance()->setBoolForKey(SOUND_KEY, true);
    }
}

void Setting::musicCheckBoxCallBack(cocos2d::Ref * pSender, cocos2d::ui::CheckBox::EventType type) {
    auto item = (ui::CheckBox *)pSender;
    if (type == ui::CheckBox::EventType::UNSELECTED) {
        UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, false);
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    }
    else {
        UserDefault::getInstance()->setBoolForKey(MUSIC_KEY, true);
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
    if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
        SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
    }
}
