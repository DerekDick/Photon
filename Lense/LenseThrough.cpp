#include "LenseThrough.h"
#include "Photon.h"
#include "cocos2d.h"

USING_NS_CC;

bool LenseThrough::change(std::vector<Photon*>::iterator & target, std::vector<Photon*>& photons) {
	Photon* photon = *target;
	if (photon->meetLense(this)) {
		if (photon->getColor() != this->throughColor) {
			photon->removeFromParent();
			photons.erase(target);
		}

		return true;
	}

	return false;
}

void LenseThrough::setThroughColor(cocos2d::Color3B color) {
	throughColor = color;
	this->setColor(color);
	return;
}
