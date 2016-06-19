#include "LenseRGB.h"
#include "Photon.h"
#include "cocos2d.h"
#include "PhotonGame.h"

USING_NS_CC;

bool LenseRGB::change(std::vector<Photon*>::iterator & target, std::vector<Photon*>& photons) {
	Photon* photon = *target;
	Vec2 V = photon->getVelocity();
	Vec2 P = photon->getPosition();
	if (photon->meetLense(this)) {
		Vec2 initialV = V;
		if (photon->getColor() == WHITE) {
			Vec2 newV = V.rotateByAngle(Vec2(0.0, 0.0), -PI / 6.0);
			photon->setVelocity(newV);
			//Make sure that this photon go through this lense(really important when photons need go through lenses)
			while (photon->meetLense(this)) {
				photon->setPosition(photon->getPosition() + V);
				P = photon->getPosition();
			}
			photon->setColor(BLUE); //Turn blue
			Photon* newPhoton1 = Photon::create();
			target = photons.insert(target, newPhoton1);
			Photon* newPhoton2 = Photon::create();
			target = photons.insert(target, newPhoton2);
			target += 2;
			newPhoton1->setPosition(P);
			newPhoton1->setColor(GREEN); //Green
			newPhoton1->setVelocity(initialV);
			newPhoton2->setPosition(P);
			newPhoton2->setColor(RED); //Red
			newPhoton2->setVelocity(2.0 * newV.project(initialV) - newV);
			auto currentLevel = photon->getParent();
			currentLevel->addChild(newPhoton1);
			currentLevel->addChild(newPhoton2);
		}
		else if (photon->getColor() == BLUE) {
			Vec2 newV = V.rotateByAngle(Vec2(0.0, 0.0), -PI / 6.0);
			photon->setVelocity(newV);
			//Make sure that this photon go through this lense(really important when photons need go through lenses)
			while (photon->meetLense(this)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}
		else if (photon->getColor() == RED) {
			Vec2 newV = V.rotateByAngle(Vec2(0.0, 0.0), PI / 6.0);
			photon->setVelocity(newV);
			//Make sure that this photon go through this lense(really important when photons need go through lenses)
			while (photon->meetLense(this)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}
		else { //Green photon
			while (photon->meetLense(this)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}

		return true;
	}

	return false;
}
