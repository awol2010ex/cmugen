#pragma once
#include "cocos2d.h"
class StartupScene : public cocos2d::CCScene
{
public:
	StartupScene(void);
	~StartupScene(void);

	virtual bool init();
	CREATE_FUNC(StartupScene);
};
