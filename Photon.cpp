#include "Photon.h"

USING_NS_CC;

#define PI 3.141592

void Photon::setVelocity(Vec2 v) {
	velocity = v;
	return;
}

Vec2 Photon::getVelocity() {
	return velocity;
}

void Photon::setAccl(Vec2 a) {
	accl = a;
	return;
}

Vec2 Photon::getAccl() {
	return accl;
}

bool Photon::init() {
	if (!Sprite::init()) {
		return false;
	}
	initWithFile("Pics/object/photon.png");

	return true;
}

bool Photon::meetLense(Sprite* lense) {
	Vec2 P = this->getPosition();
	Vec2 localP = lense->convertToNodeSpaceAR(P);
	Rect zone(-lense->getContentSize().width / 2.0, -1.0, lense->getContentSize().width, 1.0);
	if (zone.containsPoint(localP)) {
		return true;
	}
	return false;
}
