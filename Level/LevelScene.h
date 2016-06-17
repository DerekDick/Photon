#pragma once

#include "PhotonGame.h"
#include <vector>

class Level : public cocos2d::Layer {
protected:
    int levelNumber;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::TTFConfig levelTTFConfig;
    cocos2d::ui::Button *pauseButton;
    cocos2d::ui::Button *nextLevelButton;

public:
    static cocos2d::Scene *createScene();
    static cocos2d::Scene *createLevel(int levelNum);

    virtual bool init();
    
    cocos2d::Label *createLabelWithTTF(cocos2d::TTFConfig &ttfConfig,
                                       const std::string &text, cocos2d::Vec2 &position,
                                       cocos2d::Vec2 &anchorPoint = cocos2d::Vec2(0.5,0.5),
                                       cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
                                       int maxLineWidth = 0);
    cocos2d::Sprite *createdAnotherLightSource();
    cocos2d::Sprite *createdAnotherReciever();


    virtual void onEnterTransitionDidFinish();

    CREATE_FUNC(Level);
};