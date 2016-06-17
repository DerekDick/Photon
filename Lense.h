#ifndef _LENSE_H_
#define _LENSE_H_

#include "cocos2d.h"

class Lense : public cocos2d::Sprite
{
public:
	virtual bool init();
	void setFileName(std::string fName);
	//CREATE_FUNC(Lense);
private:
	//double k;
	bool isRotatable;
	bool isMovable;
	std::string fileName;
};

#endif // _LENSE_H_
