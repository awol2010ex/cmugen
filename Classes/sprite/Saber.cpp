#include "sprite/Saber.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Saber::Saber(void) {
}

Saber::~Saber(void) {
}

//生成站立动作
CCAction* Saber::createIdleAction() {
	CCSpriteFrame *frame = NULL;
	//idle animation
	CCArray *idleFrames = CCArray::createWithCapacity(83);

	// idle
	for (int i = 0; i < 19; i++) {

		frame =
				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
						CCString::createWithFormat("saber_idle%d.png", i)->getCString());

		//frame->setOffset(CCPointMake(-31, 101));

		idleFrames->addObject(frame);
	}

	CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(idleFrames,
			float(1.0 / 12.0));


	return CCRepeatForever::create(CCAnimate::create(idleAnimation));
}
bool Saber::init() {
	CCSpriteFrame *frame = NULL;
	bool bRet = false;
	do {
		//初始
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("saber_idle0.png"));

		//站立动作
		this->setIdleAction(Saber::createIdleAction());

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(8);

		// walk
		for (int i = 0; i < 11; i++) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat("saber_walk%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-30, 100));
			frame->setOffset(CCPointMake(-24, 0));

			walkFrames->addObject(frame);
		}

		CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(
				walkFrames, float(1.0 / 12.0));
		this->setWalkAction(
				CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		//attack animation
		CCArray *attackFrames = CCArray::createWithCapacity(7);

		// attack
		for (int i = 13; i>=0; i--) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"saber_attack_one%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-50, 98));
			frame->setOffset(CCPointMake(23, -14));
			attackFrames->addObject(frame);
		}

		CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(
				attackFrames, float(1.0 / 12.0));
		this->setAttackAction(
				CCSequence::create(CCAnimate::create(attackAnimation),
						CCCallFunc::create(this,
								callfunc_selector(Saber::idle)), NULL));


		//中心距离
		this->setCenterToBottom(35.0);
		this->setCenterToSides(35.0);

		//步速
		this->setWalkSpeed(320.0);

		bRet = true;
	} while (0);

	return bRet;
}

void Saber::knockout() {
	ActionSprite::knockout();
}

