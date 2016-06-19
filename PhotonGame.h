#ifndef _PHOTONGAME_H_
#define _PHOTONGAME_H_

//header files include
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "cocostudio\CocoStudio.h"
#include "ui\CocosGUI.h"

//Macros defination
//namespace
#define USING_NS_CC_DEN using namespace CocosDenshion

//constants
#define PI 3.14159265
#define RED cocos2d::Color3B(248, 68, 98)
#define GREEN cocos2d::Color3B(168, 255, 100)
#define BLUE cocos2d::Color3B(40, 180, 255)
#define WHITE cocos2d::Color3B(255, 255, 255)
#define DARK cocos2d::Color3B(50, 50, 50)
#define RED_GREEN cocos2d::Color3B(255, 255, 0)
#define RED_BLUE cocos2d::Color3B(255, 0, 255)
#define GREEN_BLUE cocos2d::Color3B(0, 255, 255)
#define WINDOW_SIZE 960, 640
#define WINDOW_CENTER cocos2d::Vec2(480, 320)
#define MUSIC_KEY "music_key"
#define SOUND_KEY "sound_key"
#define MUSIC_PLAYED_KEY "music_played_key"

//file path
#define FILE_BGM "Sound/Bgm_MoscowOutskirtsNight.mp3"
#define FILE_SOUND_1 "Sound/Click.wav"
#define FILE_RECEIVER "Pics/object/receiver.png"
#define FILE_LENSE "Pics/object/lense.png"
#define FILE_MIRROR "Pics/object/mirror.png"
#define FILE_MIRROR_R "Pics/object/mirror_r.png"

#endif // _PHOTONGAME_H_
