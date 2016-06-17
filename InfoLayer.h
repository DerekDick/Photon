#pragma once

#include"PhotonGame.h"

class Info : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onEnterTransitionDidFinish();

    CREATE_FUNC(Info);
};