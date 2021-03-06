#pragma once
#include "cocos2d.h"
#include "Defines.h"

class ActionSprite : public cocos2d::CCSprite
{
public:
	ActionSprite(void);
	~ActionSprite(void);

	//action methods
	void idle();
	void attack();
	void hurtWithDamage(float damage);
	virtual void knockout();
	void walkWithDirection(cocos2d::CCPoint direction);

	//scheduled methods
	void update(float dt);

	BoundingBox createBoundingBoxWithOrigin(cocos2d::CCPoint origin, cocos2d::CCSize size);
	void transformBoxes();
	void setPosition(cocos2d::CCPoint position);

	//actions
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _idleAction, IdleAction);//站立动作
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _attackAction, AttackAction);//攻击动作
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _walkAction, WalkAction);//行走动作
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _hurtAction, HurtAction);//受伤动作
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _knockedOutAction, KnockedOutAction);//倒下动作
	
	//攻击效果
	CC_SYNTHESIZE_RETAIN(cocos2d::CCAction*, _attackHitAction, AttackHitAction);
	CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _hitSprite, HitSprite);
	//

	//states
	CC_SYNTHESIZE(ActionState, _actionState, ActionState);

	//attributes
	CC_SYNTHESIZE(float, _walkSpeed, WalkSpeed);
	CC_SYNTHESIZE(float, _hitPoints, HitPoints);
	CC_SYNTHESIZE(float, _damage, Damage);

	//movement
	CC_SYNTHESIZE(cocos2d::CCPoint, _velocity, Velocity);
	CC_SYNTHESIZE(cocos2d::CCPoint, _desiredPosition, DesiredPosition);

	//measurements
	CC_SYNTHESIZE(float, _centerToSides, CenterToSides);
	CC_SYNTHESIZE(float, _centerToBottom, CenterToBottom);

	CC_SYNTHESIZE(BoundingBox, _hitBox, Hitbox);
	CC_SYNTHESIZE(BoundingBox, _attackBox, AttackBox);

};
