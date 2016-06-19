#ifndef _PAUSE_SCENE_H_
#define _PAUSE_SCENE_H_

#include "PhotonGame.h"
#include "SettingScene.h" 

class Pause : public Setting {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();

    CREATE_FUNC(Pause);
};

#endif // _PAUSE_SCENE_H_
