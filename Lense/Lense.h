#ifndef _LENSE_H_
#define _LENSE_H_

#include "cocos2d.h"
#include "Photon.h"
#include <vector>

class Lense : public cocos2d::Sprite {
public:
	std::string fileName;
	virtual bool change(std::vector<Photon*>::iterator &target, std::vector<Photon*> &photons) = 0;
	
	template<typename T>
	static T *create(const std::string &fileName, cocos2d::Vec2 pos, double angle = 0.0) {
		auto lense = new T;
		if (lense) {
			lense->initWithFile(fileName);
			lense->autorelease();
			lense->setPosition(pos);
			lense->setRotation(angle);

			return lense;
		}
		else {
			delete lense;
			lense = nullptr;
			return nullptr;
		}
	}
};

#endif // _LENSE_H_
