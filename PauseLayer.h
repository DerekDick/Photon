#pragma once

#include "PhotonGame.h"
#include "SettingLayer.h" 

class Pause : public Setting {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();

    CREATE_FUNC(Pause);
};