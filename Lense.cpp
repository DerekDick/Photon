#include "Lense.h"

USING_NS_CC;

bool Lense::init() {
	if (!Sprite::init()) {
		return false;
	}
	//initWithFile(fileName);

	return true;
}

void Lense::setFileName(std::string fName) {
	fileName = fName;
	return;
}
