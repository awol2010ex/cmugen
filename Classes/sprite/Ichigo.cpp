#include "Ichigo.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Ichigo::Ichigo(void) {
}

Ichigo::~Ichigo(void) {
}

bool Ichigo::init() {
	CCSpriteFrame *frame = NULL;
	bool bRet = false;
	do {
		//初始
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("ichigo_idle0.png"));

		//idle animation
		CCArray *idleFrames = CCArray::createWithCapacity(83);
		
		// idle
		for ( int i = 0; i < 83; i++) {

			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					 CCString::createWithFormat("ichigo_idle%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-31, 101));

			idleFrames->addObject(frame);
		}



		CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(
				idleFrames,1.0 / 12.0);
		this->setIdleAction(
				CCRepeatForever::create(CCAnimate::create(idleAnimation)));

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(8);
		
		
		// walk
		for ( int i = 0; i < 6; i++) {
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
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
		for ( int i = 0; i < 7; i++) {
			frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
					 CCString::createWithFormat("ichigo_attack_one%d.png", i)->getCString());

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

