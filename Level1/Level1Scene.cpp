#include "Level1Scene.h"
#include "Photon.h"
#include <cmath>
#include <vector>

USING_NS_CC;

bool rotateTag[4] = { false }; //Tag whether rotate the mirror or lense when cursor moved
bool receiverTag[3] = { false }; //Tag whether the red green blue photons has reached the receiver

Scene* Level1::createScene() {
	Scene* scene = Scene::create();
	Level1* layer = Level1::create();
	scene->addChild(layer);

	return scene;
}

bool Level1::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Title
	TTFConfig ttfconfig = TTFConfig("fonts/FoglihtenFr02.ttf", 40);
	Label* title = Label::createWithTTF(ttfconfig, "Aphoton W level 1B");
	title->setTextColor(Color4B(255, 255, 255, 255));
	title->setAnchorPoint(Vec2(0.5, 1.0));
	title->setPosition(Vec2(visibleSize.width / 2.0, visibleSize.height));
	this->addChild(title, 0, "title");

	//Lense
	Sprite* lense = Sprite::create("mirror.png");
	lense->setPosition(Vec2(490.0, 420.0));
	lense->setRotation(360 - 27);
	lense->setColor(Color3B(150, 150, 150));
	this->addChild(lense, 0, "lense");

	//Mirror1
	Lense* mirror1 = (Lense*)Lense::create("mirror_r.png");
	mirror1->setPosition(Vec2(450.0, 90.0));
	this->addChild(mirror1, 0, "mirror1");

	//Mirror2
	Lense* mirror2 = (Lense*)Lense::create("mirror_r.png");
	mirror2->setPosition(Vec2(600.0, 165.0));
	this->addChild(mirror2, 0, "mirror2");

	//Mirror3
	Lense* mirror3 = (Lense*)Lense::create("mirror_r.png");
	mirror3->setPosition(Vec2(700.0, 280.0));
	this->addChild(mirror3, 0, "mirror3");

	//receiver
	Sprite* receiver = Sprite::create("receiver.png");
	receiver->setPosition(Vec2(150.0, 300.0));
	receiver->setColor(Color3B(100, 100, 100));
	this->addChild(receiver, 0, "receiver");

	//End Button
	Sprite* endButton = Sprite::create("end_button_normal.png");
	endButton->setAnchorPoint(Vec2(1.0, 0.0));
	endButton->setPosition(Vec2(visibleSize.width, 0.0));
	endButton->setColor(Color3B(100, 100, 100));
	endButton->setScale(0.3, 0.3);
	this->addChild(endButton, 0, "endButton");

	this->schedule(schedule_selector(Level1::update), 1.0 / 5000);
	this->schedule(schedule_selector(Level1::shoot), 1.0 / 3);

	return true;
}

void Level1::update(float dt) {
	static Size visibleSize = Director::getInstance()->getVisibleSize();
	static Vec2 origin = Director::getInstance()->getVisibleOrigin();

	static auto lense = (Sprite*)this->getChildByName("lense");
	double k0 = tan((360 - lense->getRotation())*PI / 180.0);
	static auto mirror1 = (Lense*)this->getChildByName("mirror1");
	double k1 = tan((360 - mirror1->getRotation())*PI / 180.0);
	static auto mirror2 = (Lense*)this->getChildByName("mirror2");
	double k2 = tan((360 - mirror2->getRotation())*PI / 180.0);
	static auto mirror3 = (Lense*)this->getChildByName("mirror3");
	double k3 = tan((360 - mirror3->getRotation())*PI / 180.0);
	static auto receiver = (Sprite*)this->getChildByName("receiver");

	for (std::vector<Photon*>::iterator iter = Photon::photons.begin(); iter != Photon::photons.end(); iter++) {
		Photon* photon = *iter;
		Vec2 V = photon->getVelocity();
		Vec2 P = photon->getPosition();

		//If outside the screen, remove the photon
		if (P.x <= 0.0 || P.x >= visibleSize.width || P.y <= 0.0 || P.y >= visibleSize.height) {
			photon->removeFromParent();
			Photon::photons.erase(iter);
			continue;
		}

		//Through the lense
		P = photon->getPosition();
		if (abs(P.x - lense->getPosition().x) <= lense->getContentSize().width * 0.5 * (1.0 / sqrt(1 + k0*k0))) {
			if (abs(P.y - k0*(P.x - lense->getPosition().x) - lense->getPosition().y) <= 1.0) {
				Vec2 initialV = V;
				Vec2 newV = V.rotateByAngle(Vec2(0.0, 0.0), -PI / 6.0);
				photon->setVelocity(newV);
				Photon* newPhoton1 = Photon::create();
				iter = Photon::photons.insert(iter, newPhoton1);
				Photon* newPhoton2 = Photon::create();
				iter = Photon::photons.insert(iter, newPhoton2);
				//Make sure that this photon go through this lense(really important when photons need go through lenses)
				while ((abs(P.x - lense->getPosition().x) <= lense->getContentSize().width * 0.5 * (1.0 / sqrt(1 + k0*k0))
					&& abs(P.y - k0*(P.x - lense->getPosition().x) - lense->getPosition().y) <= 1.0))
				{
					photon->setPosition(photon->getPosition() + V);
					P = photon->getPosition();
				}
				newPhoton1->setPosition(P);
				newPhoton1->setColor(GREEN); //Green
				newPhoton1->setVelocity(initialV);
				newPhoton2->setPosition(P);
				newPhoton2->setColor(RED); //Red
				newPhoton2->setVelocity(2.0 * newV.project(initialV) - newV);
				this->addChild(newPhoton1);
				this->addChild(newPhoton2);
				photon->setColor(BLUE); //Turn blue
			}
		}

		////Meet mirror1
		if (photon->meetLense(mirror1)) {
			photon->setVelocity(V = 2.0 * V.project(Vec2(1.0, k1)) - V);
			while (photon->meetLense(mirror1)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}

		//Meet mirror2
		if (photon->meetLense(mirror2)) {
			photon->setVelocity(V = 2.0 * V.project(Vec2(1.0, k2)) - V);
			while (photon->meetLense(mirror2)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}

		//Meet mirror3
		if (photon->meetLense(mirror3)) {
			photon->setVelocity(V = 2.0 * V.project(Vec2(1.0, k3)) - V);
			while (photon->meetLense(mirror3)) {
				photon->setPosition(photon->getPosition() + V);
			}
		}

		photon->setPosition(photon->getPosition() + V);
	}

	//Meet the receiver
	receiverTag[0] = false;
	receiverTag[1] = false;
	receiverTag[2] = false;
	for (std::vector<Photon*>::iterator iter = Photon::photons.begin(); iter != Photon::photons.end(); iter++) {
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
		receiver->setColor(Color3B(255, 255, 255));
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

	return;
}

void Level1::shoot(float dt) {
	Photon* newPhoton = Photon::create();
	newPhoton->setPosition(Vec2(420.0, 560.0));
	newPhoton->setVelocity(Vec2(0.1/5, -0.2/5));
	this->addChild(newPhoton);
	Photon::photons.push_back(newPhoton);

	return;
}

void Level1::onEnter() {
	Layer::onEnter();
	EventListenerTouchOneByOne* myTouchListener = EventListenerTouchOneByOne::create();

	myTouchListener->setSwallowTouches(true);
	myTouchListener->onTouchBegan = CC_CALLBACK_2(Level1::touchBegan, this);
	myTouchListener->onTouchMoved = CC_CALLBACK_2(Level1::touchMoved, this);
	myTouchListener->onTouchEnded = CC_CALLBACK_2(Level1::touchEnded, this);

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(myTouchListener, getChildByName("mirror1"));
	
	return;
}

bool Level1::touchBegan(Touch* touch, Event* event) {
	static Sprite* target = (Sprite*)(event->getCurrentTarget());
	static Sprite* lense = (Sprite*)this->getChildByName("lense");
	static Sprite* mirror2 = (Sprite*)this->getChildByName("mirror2");
	static Sprite* mirror3 = (Sprite*)this->getChildByName("mirror3");
	Vec2 P_mirror2 = mirror2->getPosition();
	Vec2 P_mirror3 = mirror3->getPosition();
	Vec2 P_lense = lense->getPosition();
	Vec2 P = touch->getLocation();
	Vec2 P0 = target->getPosition();
	//Rotate mirror1
	double distance = P.distance(P0);
	if (distance <= target->getContentSize().width / 2.0) {
		double angle = atan((P.y - P0.y) / (P.x - P0.x)) * 180 / PI;
		target->setRotation(360 - angle);
		rotateTag[1] = true;
	}
	else {
		rotateTag[1] = false;
	}

	//Rotate mirror2
	if (P.distance(P_mirror2) <= lense->getContentSize().width / 2.0) {
		double angle = atan((P.y - P_mirror2.y) / (P.x - P_mirror2.x)) * 180 / PI;
		mirror2->setRotation(360 - angle);
		rotateTag[2] = true;
	}
	else {
		rotateTag[2] = false;
	}

	//Rotate mirror3
	if (P.distance(P_mirror3) <= lense->getContentSize().width / 2.0) {
		double angle = atan((P.y - P_mirror3.y) / (P.x - P_mirror3.x)) * 180 / PI;
		mirror3->setRotation(360 - angle);
		rotateTag[3] = true;
	}
	else {
		rotateTag[3] = false;
	}

	return true;
}

void Level1::touchMoved(Touch* touch, Event* event) {
	static Sprite* target = (Sprite*)(event->getCurrentTarget());
	static Sprite* endButton = (Sprite*)(this->getChildByName("endButton"));
	static Sprite* lense = (Sprite*)this->getChildByName("lense");
	static Sprite* mirror2 = (Sprite*)this->getChildByName("mirror2");
	static Sprite* mirror3 = (Sprite*)this->getChildByName("mirror3");
	Vec2 P_mirror2 = mirror2->getPosition();
	Vec2 P_mirror3 = mirror3->getPosition();
	Vec2 P_lense = lense->getPosition();
	Vec2 P = touch->getLocation();
	Vec2 P0 = target->getPosition();
	//Rotate mirror1
	if (rotateTag[1]) {
		double angle = atan((P.y - P0.y) / (P.x - P0.x)) * 180 / PI;
		target->setRotation(360 - angle);
	}

	//Rotate mirror2
	if (rotateTag[2]) {
		double angle = atan((P.y - P_mirror2.y) / (P.x - P_mirror2.x)) * 180 / PI;
		mirror2->setRotation(360 - angle);
	}

	//Rotate mirror3
	if (rotateTag[3]) {
		double angle = atan((P.y - P_mirror3.y) / (P.x - P_mirror3.x)) * 180 / PI;
		mirror3->setRotation(360 - angle);
	}

	//End Button
	static Vec2 endButtonCenter = endButton->getPosition() + (Vec2(-endButton->getContentSize().width, endButton->getContentSize().height) / 2.0) * 0.3;
	if (P.distance(endButtonCenter) <= (endButton->getContentSize().width / 2.0) * 0.3) {
		endButton->setColor(Color3B(255, 255, 255));
	}
	else {
		endButton->setColor(Color3B(100, 100, 100));
	}

	return;
}

void Level1::touchEnded(Touch* touch, Event* event) {
	static Sprite* target = (Sprite*)(event->getCurrentTarget());
	static Sprite* endButton = (Sprite*)(this->getChildByName("endButton"));

	Vec2 P = touch->getLocation();

	//End Button
	static Vec2 endButtonCenter = endButton->getPosition() + (Vec2(-endButton->getContentSize().width, endButton->getContentSize().height) / 2.0) * 0.3;
	if (P.distance(endButtonCenter) <= (endButton->getContentSize().width / 2.0) * 0.3) {
		exit(0);
	}

	return;
}

void Level1::onExit() {
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
	return;
}
