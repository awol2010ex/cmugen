#include "sprite/ActionSprite.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

ActionSprite::ActionSprite(void)
{
	_idleAction = NULL;
	_attackAction = NULL;
	_walkAction = NULL;
	_hurtAction = NULL;
	_knockedOutAction = NULL;
	
	//攻击效果
	_hitSprite =NULL;
	_attackHitAction=NULL;
}

ActionSprite::~ActionSprite(void)
{
}

void ActionSprite::idle()
{
	if (_actionState != kActionStateIdle)
	{
		this->stopAllActions();
		this->runAction(_idleAction);
		_actionState = kActionStateIdle;
		_velocity = CCPointZero;
	}
}

void ActionSprite::attack()
{
	if (_actionState == kActionStateIdle || _actionState == kActionStateAttack || _actionState == kActionStateWalk)
	{
		this->stopAllActions();
		
		if(this->getHitSprite())this->getHitSprite()->stopAllActions();//停止攻击效果
		
		this->runAction(_attackAction);
		
		if(this->getHitSprite())this->getHitSprite()->runAction(this->getAttackHitAction());//攻击效果
		
		
		_actionState = kActionStateAttack;
	}
}

void ActionSprite::hurtWithDamage(float damage)
{
	if (_actionState != kActionStateKnockedOut)
	{
		int randomSound = random_range(0, 1);
		this->stopAllActions();
		this->runAction(_hurtAction);
		_actionState = kActionStateHurt;
		_hitPoints -= damage;

		if (_hitPoints <= 0)
		{
			this->knockout();
		}
	}
}

void ActionSprite::knockout()
{
	this->stopAllActions();
	
	if(this->getHitSprite())this->getHitSprite()->stopAllActions();//停止攻击效果
	
	this->runAction(_knockedOutAction);
	_hitPoints = 0;
	_actionState = kActionStateKnockedOut;
}

void ActionSprite::walkWithDirection(CCPoint direction)
{
	if (_actionState == kActionStateIdle)
	{
		this->stopAllActions();
		
		if(this->getHitSprite())this->getHitSprite()->stopAllActions();//停止攻击效果
		
		this->runAction(_walkAction);
		_actionState = kActionStateWalk;
	}
	if (_actionState == kActionStateWalk)
	{
		_velocity = ccp(direction.x * _walkSpeed, direction.y * _walkSpeed);
		if (_velocity.x >= 0)
		{
			this->setScaleX(1.0);
			if(this->getHitSprite())this->getHitSprite()->setScaleX(1.0);
		} 
		else
		{
			this->setScaleX(-1.0);
			if(this->getHitSprite())this->getHitSprite()->setScaleX(-1.0);
		}
	}
}

void ActionSprite::update(float dt)
{
	if (_actionState == kActionStateWalk)
	{
		_desiredPosition = ccpAdd(this->getPosition(), ccpMult(_velocity, dt));
	}
}

BoundingBox ActionSprite::createBoundingBoxWithOrigin(CCPoint origin, CCSize size)
{
	BoundingBox boundingBox;
	boundingBox.original.origin = origin;
	boundingBox.original.size = size;
	boundingBox.actual.origin = ccpAdd(this->getPosition(), ccp(boundingBox.original.origin.x, boundingBox.original.origin.y));
	boundingBox.actual.size = size;
	return boundingBox;
}

void ActionSprite::transformBoxes()
{
	_hitBox.actual.origin = ccpAdd(this->getPosition(), ccp(_hitBox.original.origin.x, _hitBox.original.origin.y));
	_attackBox.actual.origin = ccpAdd(this->getPosition(), ccp(_attackBox.original.origin.x + 
		(this->getScaleX() == -1 ? (- _attackBox.original.size.width - _hitBox.original.size.width) : 0),
		_attackBox.original.origin.y));
}

void ActionSprite::setPosition(CCPoint position)
{
	CCSprite::setPosition(position);
	
	if(this->getHitSprite())this->getHitSprite()->setPosition(position);//攻击效果
	
	this->transformBoxes();
}
