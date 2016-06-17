#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "PhotonGame.h"

class HelloWorld : public cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void onEnterTransitionDidFinish();
    void cleanup();

    CREATE_FUNC(HelloWorld);
};

#endif