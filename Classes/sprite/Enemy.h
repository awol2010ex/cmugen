#pragma once
#include "sprite/ActionSprite.h"
using namespace cocos2d;
class Enemy : public ActionSprite
{
public:
    //下一次思考时间
	CC_SYNTHESIZE(long, _nextDecisionTime, NextDecisionTime);


};
