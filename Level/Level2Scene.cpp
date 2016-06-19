#include "Level2Scene.h"
#include "cocos2d.h"

USING_NS_CC;

cocos2d::Scene *Level2::createScene() {
	auto scene = Scene::create();
	auto layer = Level2::create();
	scene->addChild(layer);

	return scene;
}

bool Level2::init() {
	if (!Level::init()) {
		return false;
	}

	levelNumber = 2;

	//Title
	this->addLevelTitle();

	//Light source
	lightSource = this->addLightSource(Vec2(250.0, 220.0), BLUE);

	//Receiver
	receiver = this->addReceiver(Vec2(180.0, 80.0));

	//Mirror1
	mirror1 = this->addLense<Mirror>(FILE_MIRROR, Vec2(320.0, 550.0), -15.0);

	//Mirror2
	mirror2 = this->addLense<Mirror>(FILE_MIRROR, Vec2(850.0, 500.0), 45.0);

	//Mirror3
	mirror3 = this->addLense<Mirror>(FILE_MIRROR_R, Vec2(680.0, 260.0));

	//Set rotatable lense
	rotatableLenses.push_back(mirror3);

	this->schedule(schedule_selector(Level2::update), 1.0 / 500);
	this->schedule(schedule_selector(Level2::shoot), 1.0 / 3);

	return true;
}

void Level2::update(float dt) {
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

		//Change the position of photons
		V = photon->getVelocity();
		photon->setPosition(photon->getPosition() + V);
	}

	//Meet the receiver
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 P = photon->getPosition();
		if (P.distance(receiver->getPosition()) <= receiver->getContentSize().width / 2.0) {
			receiver->setColor(BLUE);
			break;
		}
		else {
			receiver->setColor(DARK);
		}
	}

	//Enable or disable next level Button
	if (receiver->getColor() == BLUE) {
		this->nextLevelButtonOnUse(true);
	}
	else {
		this->nextLevelButtonOnUse(false);
	}

	return;
}

void Level2::shoot(float dt) {
	Photon* newPhoton = Photon::create();
	newPhoton->setPosition(Vec2(250.0, 220.0));
	newPhoton->setVelocity(Vec2(2.0 / 5, 1.0 / 5));
	newPhoton->setColor(BLUE);
	this->addChild(newPhoton);
	photons.push_back(newPhoton);

	return;
}
