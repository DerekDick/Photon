#include "LenseTurn.h"

bool LenseTurn::change(std::vector<Photon*>::iterator & target, std::vector<Photon*>& photons) {
	Photon* photon = *target;
	if (photon->meetLense(this)) {
		photon->setColor(turnColor);

		return true;
	}

	return false;
}

void LenseTurn::setTurnColor(cocos2d::Color3B color) {
	turnColor = color;
	this->setColor(color);
	return;
}
