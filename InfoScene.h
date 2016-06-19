#ifndef _INFO_SCENE_H_
#define _INFO_SCENE_H_

#include"PhotonGame.h"

class Info : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void onEnterTransitionDidFinish();

    CREATE_FUNC(Info);
};

#endif // _INFO_SCENE_H_
