#include "LevelSelectScene.h"
#include "Level1Scene.h"
#include <vector>
#include <string>

USING_NS_CC;
USING_NS_CC_DEN;


Scene *LevelSelect::createScene() {
    auto scene = Scene::create();
    auto layer = LevelSelect::create();
    scene->addChild(layer);

    return scene;
}

bool LevelSelect::init() {
    if (!Layer::init()) {

        return false;
    }
    

    auto rootNode = CSLoader::createNode("Csbs/LevelSelect.csb");
    rootNode->setPosition(Vec2::ZERO);
    this->addChild(rootNode);

    std::string levelPrefix = "Level";
    std::vector<ui::Button *> levelButtons(15); 

    for (int i = 0; i < 4; i++) {
        auto levelNum = __String::createWithFormat("Level%d", i + 1);
        levelButtons[i] = dynamic_cast<ui::Button *>(rootNode->getChildByName(levelNum->_string));
        levelButtons[i]->addTouchEventListener(
			[i](Ref* pSender, ui::Widget::TouchEventType type) {
			if (type == ui::Widget::TouchEventType::ENDED) {
				Scene *scr = Level::createLevel(i + 1);
				auto reScr = TransitionFade::create(0.5f, scr);
				Director::getInstance()->replaceScene(reScr);
				if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
					SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
				}
			}
		});
    }
    
    auto mainMenuButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("MainMenuButton"));
    mainMenuButton->addTouchEventListener([](Ref* pSender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //auto scr = Level::createScene();
            //auto reScr = TransitionProgressInOut::create(0.6f, scr);
            Director::getInstance()->popToRootScene();
            if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
            }
        }
    });


    return true;
}


void LevelSelect::onEnterTransitionDidFinish() {
    Layer::onEnterTransitionDidFinish();
    if (UserDefault::getInstance()->getBoolForKey(MUSIC_KEY)) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }
}

//void LevelSelect::levelSelectMenuItemCallback(Ref *pSender, ui::Widget::TouchEventType type) {
//    auto item = (MenuItem *)pSender;
//    log("Touch Level%d ", item->getZOrder());
//    //To be continue...
//}

