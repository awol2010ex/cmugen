#pragma once
#include "cocos2d.h"
#include "sprite/Ichigo.h"
#include "sprite/Enemy.h"
#include "Sneaky/SneakyJoystickExt.h"
#include "layer/HudLayer.h"
class GameLayer: public cocos2d::CCLayer,
		public SneakyJoystickDelegate {
public:
	GameLayer(void);
	~GameLayer(void);

	CREATE_FUNC (GameLayer);
	bool init();
	//初始化地图
	void initTileMap();
	//精灵初始化
	void initHero();
	//摇杆代理
	virtual void didChangeDirectionTo(SneakyJoystickExt *joystick,
			cocos2d::CCPoint direction);
	virtual void isHoldingDirection(SneakyJoystickExt *joystick,
			cocos2d::CCPoint direction);
	virtual void simpleJoystickTouchEnded(SneakyJoystickExt *joystick);

	void update(float dt);
	void updatePositions();
	void setViewpointCenter(cocos2d::CCPoint position);
	void reorderActors();

	cocos2d::CCPoint tileCoordForPosition(cocos2d::CCPoint pos); //地图坐标
	Ichigo *_hero; //精灵
	cocos2d::CCSpriteBatchNode *_actors;
	cocos2d::CCTMXTiledMap *_tileMap; //地图

	//操作层
	CC_SYNTHESIZE(HudLayer*, _hud, Hud);

	void setMoveDirection(cocos2d::CCPoint _direction); //移动方向
	cocos2d::CCPoint mDirection;

	void setInBtnState(InBtnState pBtnState);
};
