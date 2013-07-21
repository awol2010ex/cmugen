#pragma once
#include "sprite/ActionSprite.h"
using namespace cocos2d;
class Saber : public ActionSprite
{
public:
	Saber(void);
	~Saber(void);


	CREATE_FUNC(Saber);
	bool init();
	void knockout();


};
