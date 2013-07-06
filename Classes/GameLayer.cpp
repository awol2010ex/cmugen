#include "Pokemon.h"
#include "GameLayer.h"
#include "HudLayer.h"
#include "SimpleAudioEngine.h"
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
using namespace cocos2d;
using namespace CocosDenshion;

GameLayer::GameLayer(void) {
	_pokemon = NULL;
	_actors = NULL;
	_tileMap = NULL;
}

GameLayer::~GameLayer(void) {
	this->unscheduleUpdate();
}

// on "init" you need to initialize your instance
bool GameLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());

		this->setTouchEnabled(true);

		//初始化地图
		this->initTileMap();

		//batchNodes
		_actors = CCSpriteBatchNode::create("sprite/charmeleon.png");
		_actors->getTexture()->setAliasTexParameters();
		this->addChild(_actors, -5);

		//初始化精灵
		this->initPokemon();

		this->scheduleUpdate();
		bRet = true;
	} while (0);

	return bRet;

	return true;
}

//初始化地图
void GameLayer::initTileMap() {

	_tileMap = CCTMXTiledMap::create("map/0000000_hotel.tmx");

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	//位置
	_tileMap->setPosition(origin.x+ visibleSize.width/2-(_tileMap->getContentSize().width/2),origin.y+ visibleSize.height/2-(_tileMap->getContentSize().height/2));

	CCObject *pObject = NULL;
		CCARRAY_FOREACH(_tileMap->getChildren(), pObject)
		{
			CCTMXLayer *child = (CCTMXLayer*) pObject;
			child->getTexture()->setAliasTexParameters();
		}


	this->addChild(_tileMap, -6);
}
//精灵初始化
void GameLayer::initPokemon() {
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	_pokemon = Pokemon::create();

	_actors->addChild(_pokemon);
	_pokemon->setPosition(ccp(origin.x+ visibleSize.width/2 ,origin.y+ visibleSize.height/2 -100));
	_pokemon->setDesiredPosition(_pokemon->getPosition());
	//站立
	_pokemon->idle();

}

//方向
void GameLayer::didChangeDirectionTo(SneakyJoystickExt *joystick,
		CCPoint direction) {
	_pokemon->walkWithDirection(direction);
}
//按住
void GameLayer::isHoldingDirection(SneakyJoystickExt *joystick, CCPoint direction) {
	_pokemon->walkWithDirection(direction);
}
//按完站立
void GameLayer::simpleJoystickTouchEnded(SneakyJoystickExt *joystick) {
	if (_pokemon->getActionState() == kActionStateWalk) {
		_pokemon->idle();
	}
}
//实时更新
void GameLayer::update(float dt) {
	_pokemon->update(dt);
	this->updatePositions();//更新所有元素位置
	this->reorderActors();//前后排序
	this->setViewpointCenter(_pokemon->getPosition());
}

CCPoint GameLayer::tileCoordForPosition(CCPoint pos) {
	CCSize mapTiledNum = _tileMap->getMapSize();
	CCSize tiledSize = _tileMap->getTileSize();

	int x = (pos.x - _tileMap->getPositionX()) / tiledSize.width;
	int y = (pos.y - _tileMap->getPositionY()) / tiledSize.height;

	/* Cocos2d-x的默认Y坐标是由下至上的，所以要做一个相减操作 */
	y = mapTiledNum.height - y;

	return ccp(x, y);
}
//更新位置
void GameLayer::updatePositions() {
	float posX = MIN(
			_tileMap->getMapSize().width * _tileMap->getTileSize().width
					- _pokemon->getCenterToSides()  +_tileMap->getPositionX(),
			MAX(_pokemon->getCenterToSides()+_tileMap->getPositionX(),
					_pokemon->getDesiredPosition().x));
	float posY = MIN(
			_tileMap->getMapSize().height * _tileMap->getTileSize().height
					- _pokemon->getCenterToBottom() +_tileMap->getPositionY(),
			MAX(_pokemon->getCenterToBottom()+_tileMap->getPositionY(),
					_pokemon->getDesiredPosition().y));

	CCTMXLayer* wall = _tileMap->layerNamed("wall");
	/* 获得当前主角在地图中的格子位置 */
	CCPoint tiledPos = this->tileCoordForPosition(ccp(posX, posY));
	/* 获取地图格子的唯一标识 */
	int tiledGid = wall->tileGIDAt(tiledPos);
	//LOGD(CCString::createWithFormat("tiledGid%d", tiledGid)->getCString());
	if (tiledGid != 0) {

	} else {
		_pokemon->setPosition(ccp(posX, posY));
	}

}

//更新地图位置
void GameLayer::setViewpointCenter(CCPoint position) {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(_tileMap->getMapSize().height * _tileMap->getTileSize().height <winSize.height && _tileMap->getMapSize().width * _tileMap->getTileSize().width <winSize.width ){
    	return;
    }
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x,
			(_tileMap->getMapSize().width * _tileMap->getTileSize().width)
					- winSize.width / 2);
	y = MIN(y,
			(_tileMap->getMapSize().height * _tileMap->getTileSize().height)
					- winSize.height / 2);
	CCPoint actualPosition = ccp(x, y);

	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
	this->setPosition(viewPoint);
}
//重新对batchNode排序
void GameLayer::reorderActors() {
	CCObject *pObject = NULL;
	CCARRAY_FOREACH(_actors->getChildren(), pObject)
	{
		ActionSprite *sprite = (ActionSprite*) pObject;
		_actors->reorderChild(sprite,
				(_tileMap->getMapSize().height * _tileMap->getTileSize().height)
						- sprite->getPosition().y);
	}
}

//按方向行走
void GameLayer::setMoveDirection(cocos2d::CCPoint _direction)
{
	mDirection = _direction;


}
void GameLayer::setInBtnState(InBtnState pBtnState)
	{
		if( pBtnState==IN_BTN_PRESSED){
			_pokemon->attack();
		}

	}
