#include "Photon.h"
#include "Lense.h"
#include <cmath>

USING_NS_CC;

#define PI 3.141592

std::vector<Photon*> Photon::photons;

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
	initWithFile("photon.png");

	return true;
}

bool Photon::meetLense(Lense* lense) {
	Vec2 P = this->getPosition(); //Current position of this photon in this frame
	////Angle no more than 45 degree
	//if (double alpha = 360 - lense->getRotation() != 90) {
	//	if (abs(P.x - lense->getPosition().x) <= lense->getContentSize().width*cos(alpha * PI / 180) / 2.0) {
	//		double diff = P.y - tan(alpha * PI / 180)*(P.x - lense->getPosition().x) - lense->getPosition().y;
	//		if (abs(diff) <= 1.0) {
	//			return true;
	//		}
	//		else {
	//			return false;
	//		}
	//	}
	//	else {
	//		return false;
	//	}
	//}
	////Angle more than 45 degree
	//else if (abs(P.y - lense->getPosition().y) <= lense->getContentSize().width*sin(alpha * PI / 180) / 2.0) {
	//	double diff = P.x - (cos(alpha * PI / 180) / sin(alpha * PI / 180))*(P.y - lense->getPosition().y) - lense->getPosition().x;
	//	if (abs(diff) <= 1.0) {
	//		return true;
	//	}
	//	else {
	//		return false;
	//	}
	//}
	//else {
	//	return false;
	//}

	double k = tan((360 - lense->getRotation())*PI / 180.0);
	if (abs(P.x - lense->getPosition().x) <= lense->getContentSize().width * 0.5 * (1.0 / sqrt(1 + k*k))) {
		if (abs(P.y - k*(P.x - lense->getPosition().x) - lense->getPosition().y) <= 1.0) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (((abs(lense->getRotation() - 90) <= 2.0) || (abs(lense->getRotation() + 90) <= 2.0) || (abs(lense->getRotation() - 270) <= 2.0) || (abs(lense->getRotation() + 270) <= 2.0)) && (abs(P.x - lense->getPosition().x) <= 2.0) && (abs(P.y - lense->getPosition().y) <= lense->getContentSize().width / 2.0)) {
		return true;
	}
	else {
		return false;
	}
}
