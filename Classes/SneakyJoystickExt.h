#pragma once
#include "Sneaky/SneakyJoystick.h"
class SneakyJoystickExt;
class SneakyJoystickDelegate
{
public:
	virtual void didChangeDirectionTo(SneakyJoystickExt *joystick, cocos2d::CCPoint direction) = 0;
	virtual void isHoldingDirection(SneakyJoystickExt *joystick, cocos2d::CCPoint direction) = 0;
	virtual void simpleJoystickTouchEnded(SneakyJoystickExt *joystick) = 0;
};

class SneakyJoystickExt: public SneakyJoystick {

public:
	CC_SYNTHESIZE(SneakyJoystickDelegate*, _delegate, Delegate);
	CC_SYNTHESIZE(bool, _isHeld, IsHeld);

	bool initWithRect(cocos2d::CCRect rect);

	void update(float dt);
protected:
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch,
			cocos2d::CCEvent *event);
	void updateVelocity(cocos2d::CCPoint point);
};
