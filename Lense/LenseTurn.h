#ifndef _LENSETURN_H_
#define _LENSETURN_H_

#include "Lense.h"
#include "cocos2d.h"

class LenseTurn : public Lense {
	bool change(std::vector<Photon*>::iterator &target, std::vector<Photon*> &photons);
public:
	void setTurnColor(cocos2d::Color3B color);
private:
	cocos2d::Color3B turnColor;
};

#endif // _LENSETURN_H_
