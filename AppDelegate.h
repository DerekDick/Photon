#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "PhotonGame.h"
#include <thread>

class  AppDelegate : private cocos2d::Application {
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
private:
    static void loadingAudio();
};

#endif