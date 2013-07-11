#include "scene/GameScene.h"
using namespace cocos2d;

GameScene::GameScene(void) {
	_gameLayer = NULL;//游戏层
	_hudLayer = NULL;//操作层
}

GameScene::~GameScene(void) {//析构

	if(_hudLayer !=NULL){
	   _hudLayer =NULL;
	}
	if(_gameLayer !=NULL)
	{
	   _gameLayer =NULL;
	}
}

bool GameScene::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCScene::init());

		//精灵图
		CCSpriteFrameCache* cache =
					CCSpriteFrameCache::sharedSpriteFrameCache();
		cache->addSpriteFramesWithFile("sprite/cnf.plist", "sprite/cnf.pvr.ccz");
		//UI图
		cache->addSpriteFramesWithFile("UI.plist", "UI.png");


		//游戏层
		_gameLayer = GameLayer::create();
		this->addChild(_gameLayer, 0);

		//操作层
		_hudLayer = HudLayer::create();
		this->addChild(_hudLayer, 1);
		_hudLayer->getJoystick()->setDelegate(_gameLayer);//摇杆
		_gameLayer->setHud(_hudLayer);


		//定时同步按钮状态
		this->schedule(schedule_selector(GameScene::broadcastInput));
		bRet = true;
	} while (0);

	return bRet;
}

//同步操作层与游戏层信息
void GameScene::broadcastInput(float dt)
{
	//A按钮
	_gameLayer->setInBtnState(_hudLayer->getInBtnState());
}
