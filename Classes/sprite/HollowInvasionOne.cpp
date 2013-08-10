#include "sprite/HollowInvasionOne.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

HollowInvasionOne::HollowInvasionOne(void) {
}

HollowInvasionOne::~HollowInvasionOne(void) {
}

bool HollowInvasionOne::init() {
	CCSpriteFrame *frame = NULL;
	bool bRet = false;
	do {
		//初始
		CC_BREAK_IF(
				!ActionSprite::initWithSpriteFrameName(
						"HollowInvasionOne_idle0.png"));

		//idle animation
		CCArray *idleFrames = CCArray::createWithCapacity(5);

		// idle
		for (int i = 0; i < 5; i++) {

			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"HollowInvasionOne_idle%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-109, 111));

			idleFrames->addObject(frame);
		}

		CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(
				idleFrames, 1.0 / 6.0);
		this->setIdleAction(
				CCRepeatForever::create(CCAnimate::create(idleAnimation)));

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(5);

		// walk
		for (int i = 0; i < 5; i++) {
			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"HollowInvasionOne_walk%d.png", i)->getCString());

			//frame->setOffset(CCPointMake(-71, 94));

			walkFrames->addObject(frame);
		}

		CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(
				walkFrames, float(1.0 / 6.0));
		this->setWalkAction(
				CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		//hurt animation
		CCArray *hurtFrames = CCArray::createWithCapacity(4);
		// hurt
		for (int i = 0; i < 4; i++) {

			frame =
					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(
							CCString::createWithFormat(
									"HollowInvasionOne_hurt%d.png", i)->getCString());
			////frame.setOffset(new cc.Point(-71, 94));

			hurtFrames->addObject(frame);
		}
		CCAnimation *hurtAnimation = CCAnimation::createWithSpriteFrames(
				hurtFrames, float(1.0 / 6.0));
		this->setHurtAction(
				CCSequence::create(CCAnimate::create(hurtAnimation),
						CCCallFunc::create(this,
								callfunc_selector(HollowInvasionOne::idle)),
						NULL));

		//中心距离
		this->setCenterToBottom(35.0);
		this->setCenterToSides(35.0);

		//步速
		this->setWalkSpeed(80.0);

		_nextDecisionTime = 0;

		bRet = true;
	} while (0);

	return bRet;
}

void HollowInvasionOne::knockout() {
	Enemy::knockout();
}
