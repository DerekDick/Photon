#include "Level4Scene.h"
#include "cocos2d.h"
#include "LenseRGB.h"
#include "PhotonGame.h"
#include <cmath>

USING_NS_CC;

cocos2d::Scene *Level4::createScene() {
	auto scene = Scene::create();
	auto layer = Level4::create();
	scene->addChild(layer);

	return scene;
}

bool Level4::init() {
	if (!Level::init()) {
		return false;
	}

	levelNumber = 4;

	//Title
	this->addLevelTitle();

	//Light source
	lightSource = this->addLightSource(Vec2(200.0, 100.0));

	//ReceiverB
	receiverB = this->addReceiver(Vec2(400.0, 480.0));

	//ReceiverR
	receiverR = this->addReceiver(Vec2(600.0, 230.0));

	//Lense
	lense = this->addLense<LenseRGB>(FILE_LENSE, Vec2(290.0, 190.0), 45.0);

	//Blackhole
	Sprite* blackhole = Sprite::create(FILE_BLACKHOLE);
	blackhole->setPosition(blackholeCenter);
	blackhole->setScale(radius / 50.0);
	this->addChild(blackhole);

	this->schedule(schedule_selector(Level4::update), 1.0 / 200);
	this->schedule(schedule_selector(Level4::shoot), 1.0 / 3);

	return true;
}

void Level4::update(float dt) {
	//Move the photons
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 V = photon->getVelocity();
		Vec2 P = photon->getPosition();

		//Move the photons
		photon->setPosition(P + V);

		//Blackhole
		if (double distance = P.distance(blackholeCenter) <= radius) {
			Vec2 accl = photon->getAccl();
			accl = factor * (blackholeCenter - P) * 0.005 / pow(distance, 3.0);
			photon->setVelocity(V += accl);
		}

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
	recieverTag[0] = recieverTag[1] = false;
	for (std::vector<Photon*>::iterator iter = photons.begin(); iter != photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 P = photon->getPosition();

		if (P.distance(receiverB->getPosition()) <= receiverB->getContentSize().width / 2.0) {
			receiverB->setColor(photon->getColor());
			recieverTag[0] = true;
		}
		if (!recieverTag[0]) {
			receiverB->setColor(DARK);
		}
		
		if (P.distance(receiverR->getPosition()) <= receiverR->getContentSize().width / 2.0) {
			receiverR->setColor(photon->getColor());
			recieverTag[1] = true;
		}		
		if (!recieverTag[1]) {
			receiverR->setColor(DARK);
		}
	}

	//Enable or disable next level Button
	if (recieverTag[0] && recieverTag[1]) {
		this->nextLevelButtonOnUse(true);
	}
	else {
		this->nextLevelButtonOnUse(false);
	}

	return;
}

void Level4::shoot(float dt) {
	Photon* newPhoton = Photon::create();
	newPhoton->setPosition(Vec2(200.0, 100.0));
	newPhoton->setVelocity(Vec2(2.5 / 5, 2.5 / 5));
	this->addChild(newPhoton);
	photons.push_back(newPhoton);

	return;
}

void Level4::setFactor(double f) {
	factor = f;
	return;
}

void Level4::onEnter() {
	Layer::onEnter();
	auto clickListener = EventListenerTouchOneByOne::create();
	clickListener->setSwallowTouches(false);
	clickListener->onTouchBegan = CC_CALLBACK_2(Level4::changeBegan, this);
	clickListener->onTouchEnded = CC_CALLBACK_2(Level4::changeEnded, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(clickListener, this->getChildByName("title"));

	return;
}

void Level4::onExit() {
	Level::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this->getChildByName("title"));
}


bool Level4::changeBegan(cocos2d::Touch *touch, cocos2d::Event * event) {
	Vec2 touchPosition = touch->getLocation();
	if (touchPosition.distance(this->blackholeCenter) <= 15.0) {
		return true;
	}

	return false;
}

void Level4::changeEnded(cocos2d::Touch * touch, cocos2d::Event * event) {
	if (factor < 1.0) {
		factor += 0.2;
	}
	else {
		factor = 0.2;
	}

	return;
}

