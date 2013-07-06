#pragma once
#include "actionsprite.h"
using namespace cocos2d;
class Pokemon : public ActionSprite
{
public:
	Pokemon(void);
	~Pokemon(void);


	CREATE_FUNC(Pokemon);
	bool init();
	void knockout();


};
