#ifndef _HELLOWORLD_SCENE_H_
#define _HELLOWORLD_SCENE_H_

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