#include "HudLayer.h"
using namespace cocos2d;
const float JOYSTICK_POS_X = 120;
const float JOYSTICK_POS_Y = 120;
const float JOYSTICK_DEAD_RADIUS = 10;
const float JOYSTICK_THRESHOLD = 0.4f;

HudLayer::HudLayer(void) {
	//_dPad = NULL;
	//_actors = NULL;
}

HudLayer::~HudLayer(void) {
}

bool HudLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCLayer::init());

		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();


		//关闭按钮
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
				"CloseSelected.png", this,
				menu_selector(HudLayer::menuCloseCallback));
		pCloseItem->setPosition(
				ccp(origin.x+visibleSize.width-40,origin.y+visibleSize.height-40));

		// create menu, it's an autorelease object
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);
		//初始化手柄
		mJoystick = NULL;
		mJoystick = new SneakyJoystickExt();
		mJoystick->initWithRect(CCRectZero);
		mJoystick->setAutoCenter(true);
		mJoystick->setHasDeadzone(true);
		mJoystick->setDeadRadius(JOYSTICK_DEAD_RADIUS);
		SneakyJoystickSkinnedBase* jstickSkin = new SneakyJoystickSkinnedBase();
		jstickSkin->autorelease();
		jstickSkin->init();
		jstickSkin->setBackgroundSprite(
				CCSprite::createWithSpriteFrameName("JoyStick-base.png"));
		jstickSkin->setThumbSprite(
				CCSprite::createWithSpriteFrameName("JoyStick-thumb.png"));
		jstickSkin->getThumbSprite()->setScale(2.0f);
		jstickSkin->getBackgroundSprite()->setScale(2.0f);
		jstickSkin->setPosition(ccp(origin.x+JOYSTICK_POS_X, origin.y+JOYSTICK_POS_Y));
		jstickSkin->setJoystick(mJoystick);
		this->addChild(jstickSkin);

		//按钮
		mButtonA = NULL;
		mButtonA = new SneakyButton();
		mButtonA->initWithRect(CCRectZero);
		mButtonA->setIsToggleable(false);
		mButtonA->setIsHoldable(true);
		SneakyButtonSkinnedBase* btnASkin = new SneakyButtonSkinnedBase();
		btnASkin->autorelease();
		btnASkin->init();
		btnASkin->setPosition(ccp(origin.x+visibleSize.width- 50,origin.y+ 50));
		btnASkin->setDefaultSprite(
				CCSprite::createWithSpriteFrameName("button-default.png"));
		btnASkin->setPressSprite(
				CCSprite::createWithSpriteFrameName("button-pressed.png"));
		btnASkin->setActivatedSprite(
				CCSprite::createWithSpriteFrameName("button-activated.png"));
		//btnASkin->setDisabledSprite(CCSprite::createWithSpriteFrameName("button-disabled.png"));
		btnASkin->setButton(mButtonA);
		this->addChild(btnASkin);

		bRet = true;
	} while (0);

	return bRet;
}

void HudLayer::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


//按钮状态
InBtnState HudLayer::getInBtnState()
{
	InBtnState retState = IN_BTN_NO_PRESSED;

	if (mButtonA->getIsActive())
		retState = IN_BTN_PRESSED;

	return retState;
}
