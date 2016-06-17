#include "PauseLayer.h"

USING_NS_CC;
USING_NS_CC_DEN;

Scene * Pause::createScene() {
    auto scene = Scene::create();
    auto layer = Pause::create();
    scene->addChild(layer);

    return scene;
}

bool Pause::init() {
    if (!Setting::init()) {
        return false;
    }

    auto resumeButton = ui::Button::create("Pics/OptionNormal.png", "Pics/OptionSelected.png");
    resumeButton->setTitleFontName("Fonts/Amplify.ttf");
    resumeButton->setTitleFontSize(36);    
    resumeButton->setTitleText("RESUME");
    resumeButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->popScene();
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });
    resumeButton->setPosition(Vec2(480, 200));

    this->addChild(resumeButton);
    return true;
}
