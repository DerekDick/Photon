#ifndef _PHOTON_H_
#define _PHOTON_H_

#include "cocos2d.h"
#include "Lense.h"
#include <vector>

class Photon : public cocos2d::Sprite
{
public:
	static std::vector<Photon*> photons;
	virtual bool init();
	void setVelocity(cocos2d::Vec2 v);
	cocos2d::Vec2 getVelocity();
	void setAccl(cocos2d::Vec2 a);
	cocos2d::Vec2 getAccl();
	bool meetLense(Lense* lense);
	CREATE_FUNC(Photon);
private:
	cocos2d::Vec2 velocity;
	cocos2d::Vec2 accl;
};

#endif // _PHOTON_H_
