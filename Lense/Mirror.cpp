#include "Mirror.h"
#include "PhotonGame.h"
#include "cocos2d.h"

USING_NS_CC;

bool Mirror::change(std::vector<Photon*>::iterator &target, std::vector<Photon*>& photons) {
	double k = tan((360 - this->getRotation())*PI / 180.0);
	Photon* photon = *target;
	Vec2 V = photon->getVelocity();
	if (photon->meetLense(this)) {
		photon->setVelocity(V = 2.0 * V.project(Vec2(1.0, k)) - V);
		while (photon->meetLense(this)) {
			photon->setPosition(photon->getPosition() + V);
		}
		return true;
	}

	return false;
}
