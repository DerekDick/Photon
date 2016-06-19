#ifndef _LEVELSELECT_SCENE_H_
#define _LEVELSELECT_SCENE_H_

#include "PhotonGame.h"
#include "LevelScene.h"

class LevelSelect : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onEnterTransitionDidFinish();
   
    CREATE_FUNC(LevelSelect);
};


#endif // _LEVELSELECT_SCENE_H_
