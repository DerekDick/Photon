#ifndef _PHOTON_H_
#define _PHOTON_H_

#include "cocos2d.h"
#include <vector>

class Photon : public cocos2d::Sprite
{
public:
	virtual bool init();
	void setVelocity(cocos2d::Vec2 v);
	cocos2d::Vec2 getVelocity();
	void setAccl(cocos2d::Vec2 a);
	cocos2d::Vec2 getAccl();
	bool meetLense(cocos2d::Sprite* lense);
	CREATE_FUNC(Photon);
private:
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 accl;
};

#endif // _PHOTON_H_
