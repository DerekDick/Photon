#include "Level1Scene.h"
#include "Photon.h"
#include "PhotonGame.h"
#include "Mirror.h"
#include "LenseRGB.h"

USING_NS_CC;

cocos2d::Scene *Level1::createScene() {
	Scene* scene = Scene::create();
	Layer* layer = Level1::create();
	scene->addChild(layer);

	return scene;
}

bool Level1::init() {
	if (!Level::init()) {
		return false;
	}

	levelNumber = 1;

	//Title
	this->addLevelTitle();

	//Light source
	lightSource = this->addLightSource(Vec2(420.0, 560.0), WHITE);

	//Receiver
	receiver = this->addReceiver(Vec2(150.0, 300.0));

	//Colorful lense
	lense = this->addLense<LenseRGB>(FILE_LENSE, Vec2(490.0, 420.0), -27);

	//Mirror1
	mirror1 = this->addLense<Mirror>(FILE_MIRROR_R, Vec2(450.0, 90.0));

	//Mirror2
	mirror2 = this->addLense<Mirror>(FILE_MIRROR_R, Vec2(600.0, 165.0));

	//Mirror3
	mirror3 = this->addLense<Mirror>(FILE_MIRROR_R, Vec2(700.0, 280.0));

	//Set rotatable lenses
	rotatableLenses.push_back(mirror1);
	rotatableLenses.push_back(mirror2);
	rotatableLenses.push_back(mirror3);

	this->schedule(schedule_selector(Level1::update), 1.0 / 1500);
	this->schedule(schedule_selector(Level1::shoot), 1.0 / 2);

	return true;
}

void Level1::update(float dt) {
	double k0 = tan((360 - lense->getRotation())*PI / 180.0);
	double k1 = tan((360 - mirror1->getRotation())*PI / 180.0);
	double k2 = tan((360 - mirror2->getRotation())*PI / 180.0);
	double k3 = tan((360 - mirror3->getRotation())*PI / 180.0);

	//Move the photons
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 V = photon->getVelocity();
		Vec2 P = photon->getPosition();

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

		V = photon->getVelocity();
		photon->setPosition(photon->getPosition() + V);
	}

	//Meet the receiver
	receiverTag[0] = false;
	receiverTag[1] = false;
	receiverTag[2] = false;
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 P = photon->getPosition();
		Color3B currentColor = photon->getColor();
		if (P.distance(receiver->getPosition()) <= receiver->getContentSize().width / 2.0) {
			if (currentColor == RED) {
				receiverTag[0] = true;
			}
			else if (currentColor == GREEN) {
				receiverTag[1] = true;
			}
			else if (currentColor == BLUE) {
				receiverTag[2] = true;
			}
		}
	}
	//Change the color of the receiver
	if (receiverTag[0] && receiverTag[1] && receiverTag[2]) {
		receiver->setColor(WHITE);
	}
	else if (receiverTag[0] && receiverTag[1]) {
		receiver->setColor(RED_GREEN);
	}
	else if (receiverTag[0] && receiverTag[2]) {
		receiver->setColor(RED_BLUE);
	}
	else if (receiverTag[1] && receiverTag[2]) {
		receiver->setColor(GREEN_BLUE);
	}
	else if (receiverTag[0]) {
		receiver->setColor(RED);
	}
	else if (receiverTag[1]) {
		receiver->setColor(GREEN);
	}
	else if (receiverTag[2]) {
		receiver->setColor(BLUE);
	}
	else {
		receiver->setColor(DARK);
	}

	//Enable or disable next level Button
	if (receiver->getColor() == WHITE) {
		this->nextLevelButtonOnUse(true);
	}
	else {
		this->nextLevelButtonOnUse(false);
	}

	return;
}

void Level1::shoot(float dt) {
	Photon* newPhoton = Photon::create();
	newPhoton->setPosition(Vec2(420.0, 560.0));
	newPhoton->setVelocity(Vec2(0.04, -0.08));
	this->addChild(newPhoton);
	photons.push_back(newPhoton);

	return;
}
