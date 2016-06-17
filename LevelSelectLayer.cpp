#include "LevelSelectlayer.h"
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
    std::vector<std::string> levelNames(15);
    std::vector<ui::Button *> levelButtons(15);

    for (int i = 0; i < 15; i++) {
        //Get the buttons' names
        if (i < 9) {
            levelPrefix.push_back(i + '1');
        }
        else if (i == 9) {
            levelPrefix += "10";
        }
        else {
            levelPrefix.push_back(i - 9 + '0');
        }
        levelNames[i] = levelPrefix;
        levelPrefix.pop_back();

        levelButtons[i] = dynamic_cast<ui::Button *>(rootNode->getChildByName(levelNames[i]));
        levelButtons[i]->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
            if (type == ui::Widget::TouchEventType::ENDED) {
                Scene *scr = Level::createScene();
                /*Scene *scr = nullptr;*/
                /*switch (i + 1) {
                case 1:
                    scr = Level1::createScene();
                case 2:
                    scr = Level2::createScene();
                case 3:
                    scr = Level3::createScene();
                case 4:
                    scr = Level4::createScene();
                case 5:
                    scr = Level5::createScene();
                case 6:
                    scr = Level6::createScene();
                case 7:
                    scr = Level7::createScene();
                case 8:
                    scr = Level8::createScene();
                case 9:
                    scr = Level9::createScene();
                case 10:
                    scr = Level10::createScene();
                case 11:
                    scr = Level11::createScene();
                case 12:
                    scr = Level12::createScene();
                case 13:
                    scr = Level13::createScene();
                case 14:
                    scr = Level14::createScene();
                case 15:
                    scr = Level15::createScene();
                default:
                    break;
                }*/
                auto reScr = TransitionFade::create(0.5f, scr);
                Director::getInstance()->replaceScene(reScr);
                if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
                    SimpleAudioEngine::getInstance()->playEffect(FILE_SOUND_1);
                }
            }
        });
    }
    
    auto mainMenuButton = dynamic_cast<ui::Button *>(rootNode->getChildByName("MainMenuButton"));
    mainMenuButton->addTouchEventListener([&](Ref* pSender, ui::Widget::TouchEventType type) {
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

