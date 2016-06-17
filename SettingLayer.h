#pragma once

#include "PhotonGame.h"

class Setting : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onEnterTransitionDidFinish();


    void soundCheckBoxCallBack(cocos2d::Ref *pSender, cocos2d::ui::CheckBox::EventType type);
    void musicCheckBoxCallBack(cocos2d::Ref *pSender, cocos2d::ui::CheckBox::EventType type);
    CREATE_FUNC(Setting);
};

