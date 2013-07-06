#pragma once
#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"
class GameScene : public cocos2d::CCScene
{
public:
	GameScene(void);
	~GameScene(void);

	virtual bool init();
	CREATE_FUNC(GameScene);

	//游戏层
	CC_SYNTHESIZE(GameLayer*, _gameLayer, GameLayer);
	//操作层
	CC_SYNTHESIZE(HudLayer*, _hudLayer, HudLayer);

	void broadcastInput(float dt);
};
