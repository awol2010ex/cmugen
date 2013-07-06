#include "Pokemon.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d;

Pokemon::Pokemon(void) {
}

Pokemon::~Pokemon(void) {
}

bool Pokemon::init() {
	CCSpriteFrame *frame = NULL;
	bool bRet = false;
	do {
		//初始
		CC_BREAK_IF(!ActionSprite::initWithSpriteFrameName("charmeleon_idle_0.png"));

		//idle animation
		CCArray *idleFrames = CCArray::createWithCapacity(2);

		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_idle_0.png");

		idleFrames->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_idle_1.png");
		idleFrames->addObject(frame);



		CCAnimation *idleAnimation = CCAnimation::createWithSpriteFrames(
				idleFrames, 0.2);
		this->setIdleAction(
				CCRepeatForever::create(CCAnimate::create(idleAnimation)));

		//walk animation
		CCArray *walkFrames = CCArray::createWithCapacity(3);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_walk_0.png");
		walkFrames->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_walk_1.png");
		walkFrames->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_walk_2.png");
		walkFrames->addObject(frame);
		CCAnimation *walkAnimation = CCAnimation::createWithSpriteFrames(
				walkFrames, float(1.0 / 12.0));
		this->setWalkAction(
				CCRepeatForever::create(CCAnimate::create(walkAnimation)));

		//attack animation
		CCArray *attackFrames = CCArray::createWithCapacity(2);

		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_attack_0.png");
		attackFrames->addObject(frame);
		frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("charmeleon_attack_1.png");
		attackFrames->addObject(frame);
		CCAnimation *attackAnimation = CCAnimation::createWithSpriteFrames(
				attackFrames, float(1.0 /6.0));
		this->setAttackAction(
				CCSequence::create(CCAnimate::create(attackAnimation),
						CCCallFunc::create(this,
								callfunc_selector(Pokemon::idle)), NULL));

		//中心距离
		this->setCenterToBottom(35.0);
		this->setCenterToSides(35.0);

		//步速
		this->setWalkSpeed(160.0);

		//初始方向
		this->setDirect(-1.0);
		bRet = true;
	} while (0);

	return bRet;
}

void Pokemon::knockout() {
	ActionSprite::knockout();
}

