#ifndef _LENSETHROUGH_H_
#define _LENSETHROUGH_H_

#include "Lense.h"
#include "cocos2d.h"
#include "PhotonGame.h"

class LenseThrough : public Lense {
	bool change(std::vector<Photon*>::iterator &target, std::vector<Photon*> &photons);
public:
	void setThroughColor(cocos2d::Color3B color);
private:
	cocos2d::Color3B throughColor = WHITE;
};

#endif _LENSETHROUGH_H_
