#pragma once
#include "sprite/Enemy.h"
using namespace cocos2d;
class HollowInvasionOne : public Enemy
{
public:
    HollowInvasionOne(void);
	~HollowInvasionOne(void);


	CREATE_FUNC(HollowInvasionOne);
	bool init();
	void knockout();


};