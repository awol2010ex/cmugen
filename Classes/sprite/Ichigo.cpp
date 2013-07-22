#include "sprite/Ichigo.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Ichigo::Ichigo(void) {
}

Ichigo::~Ichigo(void) {
}

//生成站立动作
CCAction* Ichigo::createIdleAction() {
	CCSpriteFrame *frame = NULL;
	//idle animation
	CCArray *idleFrames = CCArray::createWithCapacity(83);

	// idle
	for (int i = 0; i < 83; i++) {

		frame =
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						CCString::createWithFormat("ichigo_idle%d.png", i)->getCString());

		//frame->setOffset(CCPointMake(-31, 101));

		idleFrames->addObject(frame);
	}

	CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames,
			float(1.0 / 12.0));


	return CCRepeatForever::create(CCAnimate::create(idleAnimation));
}
bool Ichigo::init() {
	CCSpriteFrame *frame = NULL;
	bool bRet = false;
	do {
		//初始
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("ichigo_idle0.png"));

		//站立动作
		this->setIdleAction(Ichigo::createIdleAction());

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(8);

		// walk
		for (int i = 0; i < 6; i++) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat("ichigo_run%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-30, 100));
			frame->setOffset(CCPointMake(-11, -13));

			walkFrames->addObject(frame);
		}

		CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(
				walkFrames, float(1.0 / 12.0));
		this->setWalkAction(
				CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		//attack animation
		CCArray *attackFrames = CCArray::createWithCapacity(7);

		// attack
		for (int i = 0; i < 7; i++) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"ichigo_attack_one%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-50, 98));
			frame->setOffset(CCPointMake(-19, -3));
			attackFrames->addObject(frame);
		}

		CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(
				attackFrames, float(1.0 / 12.0));
		this->setAttackAction(
				CCSequence::create(CCAnimate::create(attackAnimation),
						CCCallFunc::create(this,
								callfunc_selector(Ichigo::idle)), NULL));

		//攻击效果
		CCArray *attackHitFrames = CCArray::create();
		for (int i = 0; i < 5; i++) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"ichigo_attack_one_hit%d.png", i)->getCString());
			if (i == 0)
				//frame->setOffset(CCPointMake(-61, 159));
				frame->setOffset(CCPointMake(-30, 58));
			if (i == 1)
				//frame->setOffset(CCPointMake(-43, 159));
				frame->setOffset(CCPointMake(-12, 58));
			if (i == 2)
				//frame->setOffset(CCPointMake(27, 153));
				frame->setOffset(CCPointMake(58, 52));
			if (i == 3)
				//frame->setOffset(CCPointMake(27, 81));
				frame->setOffset(CCPointMake(58, -20));
			if (i == 4)
				//frame->setOffset(CCPointMake(27, 81));
				frame->setOffset(CCPointMake(58, -20));

			attackHitFrames->addObject(frame);
		}
		//攻击效果 初始帧
		CCSpriteFrame *emptyFrame =
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						"ichigo_attack_one_hit0.png");
		emptyFrame->setRect(CCRectMake(0, 0, 0, 0));
		attackHitFrames->addObject(emptyFrame);

		//攻击效果
		CCAnimation *attackHitAnimation = CCAnimation::createWithSpriteFrames(
				attackHitFrames, float(1.0 / 12.0));

		this->setAttackHitAction(
				CCSequence::create(CCDelayTime::create(float(2.0 / 12.0)),
						CCAnimate::create(attackHitAnimation), NULL));

		this->setHitSprite(CCSprite::createWithSpriteFrame(emptyFrame)); // 攻击效果初始空白

		//中心距离
		this->setCenterToBottom(35.0);
		this->setCenterToSides(35.0);

		//步速
		this->setWalkSpeed(320.0);

		bRet = true;
	} while (0);

	return bRet;
}

void Ichigo::knockout() {
	ActionSprite::knockout();
}

