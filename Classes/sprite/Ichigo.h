#pragma once
#include "sprite/ActionSprite.h"
using namespace cocos2d;
class Ichigo : public ActionSprite
{
public:
	Ichigo(void);
	~Ichigo(void);


	CREATE_FUNC(Ichigo);
	bool init();
	void knockout();
	
	//生成站立动作
	static CCAction*  createIdleAction();
};
