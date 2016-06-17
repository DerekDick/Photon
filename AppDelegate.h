#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "PhotonGame.h"

USING_NS_CC;

class  AppDelegate : private cocos2d::Application {
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
private:
    virtual void initSoundAndMusic();
};

#endif