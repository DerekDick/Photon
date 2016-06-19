#include "Level3Scene.h"
#include "cocos2d.h"
#include "Mirror.h"
#include "LenseThrough.h"
#include "LenseTurn.h"

USING_NS_CC;

cocos2d::Scene *Level3::createScene() {
	auto scene = Scene::create();
	auto layer = Level3::create();
	scene->addChild(layer);

	return scene;
}

bool Level3::init() {
	if (!Level::init()) {
		return false;
	}

	levelNumber = 3;

	//Title
	this->addLevelTitle();

	//Light source
	lightSource = this->addLightSource(Vec2(230.0, 200.0), RED);

	//Receiver
	receiver = this->addReceiver(Vec2(50.0, 250.0));
	receiver->setColor(DARK_GREEN);

	//Mirror1
	mirror1 = this->addLense<Mirror>(FILE_MIRROR, Vec2(560.0, 580.0));

	//Mirror2
	mirror2 = this->addLense<Mirror>(FILE_MIRROR, Vec2(230.0, 500.0), -75.0);

	//Mirror3
	mirror3 = this->addLense<Mirror>(FILE_MIRROR, Vec2(850.0, 520.0), 80.0);

	//Mirror4
	mirror4 = this->addLense<Mirror>(FILE_MIRROR, Vec2(830.0, 120.0), -48.0);

	//LenseThroughG1
	lenseThroughG1 = this->addLense<LenseThrough>(FILE_LENSE_THROUGH, Vec2(560.0, 550.0));
	((LenseThrough*)lenseThroughG1)->setThroughColor(GREEN);

	//LenseThroughG2
	lenseThroughG2 = this->addLense<LenseThrough>(FILE_LENSE_THROUGH, Vec2(840.0, 160.0), -48.0);
	((LenseThrough*)lenseThroughG2)->setThroughColor(GREEN);

	//LenseThroughR1
	lenseThroughR1 = this->addLense<LenseThrough>(FILE_LENSE_THROUGH, Vec2(250.0, 480.0), -75.0);
	((LenseThrough*)lenseThroughR1)->setThroughColor(RED);

	//LenseThroughR2
	lenseThroughR2 = this->addLense<LenseThrough>(FILE_LENSE_THROUGH, Vec2(830.0, 520.0), 80.0);
	((LenseThrough*)lenseThroughR2)->setThroughColor(RED);

	//LenseTurnG
	lenseTurnG = this->addLense<LenseTurn>(FILE_LENSE_TURN_R, Vec2(500.0, 420.0));
	((LenseTurn*)lenseTurnG)->setTurnColor(GREEN);

	//LenseTurnR
	lenseTurnR = this->addLense<LenseTurn>(FILE_LENSE_TURN_R, Vec2(420.0, 340.0), -60.0);
	((LenseTurn*)lenseTurnR)->setTurnColor(RED);

	//Add rotatable lenses
	rotatableLenses.push_back(lenseTurnG);
	rotatableLenses.push_back(lenseTurnR);

	this->schedule(schedule_selector(Level3::update), 1.0 / 200);
	this->schedule(schedule_selector(Level3::shoot), 1.0 / 3);

	return true;
}

void Level3::update(float dt) {
	//Move the photons
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 V = photon->getVelocity();
		Vec2 P = photon->getPosition();

		//Move the photons
		V = photon->getVelocity();
		photon->setPosition(photon->getPosition() + V);

		//If outside the screen, remove the photon
		if (P.x <= 0.0 || P.x >= visibleSize.width || P.y <= 0.0 || P.y >= visibleSize.height) {
			photon->removeFromParent();
			photons.erase(iter);
			continue;
		}

		//Meet the lenses
		for (std::vector<Lense*>::iterator target = lenses.begin(); target != lenses.end(); target++) {
			Lense* lense = *target;
			if (lense->change(iter, photons)) {
				break;
			}
		}
	}

	//Meet the receiver
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 P = photon->getPosition();
		if (P.distance(receiver->getPosition()) <= receiver->getContentSize().width / 2.0) {
			receiver->setColor(photon->getColor());
			break;
		}
		else {
			receiver->setColor(DARK_GREEN);
		}
	}

	//Enable or disable next level Button
	if (receiver->getColor() == GREEN) {
		this->nextLevelButtonOnUse(true);
	}
	else {
		this->nextLevelButtonOnUse(false);
	}

	return;
}

void Level3::shoot(float dt) {
	Photon* newPhoton = Photon::create();
	newPhoton->setPosition(Vec2(230.0, 200.0));
	newPhoton->setVelocity(Vec2(2.5 / 5, 3.3 / 5));
	newPhoton->setColor(RED);
	this->addChild(newPhoton);
	photons.push_back(newPhoton);

	return;
}
