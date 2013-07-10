#include "SneakyJoystickExt.h"

using namespace cocos2d;
bool SneakyJoystickExt::initWithRect(CCRect rect)
{
	SneakyJoystick::initWithRect(rect);

	this->scheduleUpdate();
}
bool SneakyJoystickExt::ccTouchBegan(CCTouch *touch, CCEvent *event) {
	bool _ret=SneakyJoystick::ccTouchBegan(touch, event);
	if(_ret){
	   _isHeld = true;
	}
	return _ret;
}

void SneakyJoystickExt::ccTouchMoved(CCTouch *touch, CCEvent *event) {


	SneakyJoystick::ccTouchMoved(touch, event);
	_isHeld = true;
}

void SneakyJoystickExt::ccTouchEnded(CCTouch *touch, CCEvent *event) {

	SneakyJoystick::ccTouchEnded(touch, event);
	_isHeld = false;
	_delegate->simpleJoystickTouchEnded(this);
}

void SneakyJoystickExt::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
	_isHeld = false;

	SneakyJoystick::ccTouchCancelled(touch, event);
}

void SneakyJoystickExt::update(float dt)
{
	if (_isHeld)
	{
		_delegate->isHoldingDirection(this, this->getVelocity());
	}
}

void SneakyJoystickExt::updateVelocity(cocos2d::CCPoint point){
	SneakyJoystick::updateVelocity(point);

	_delegate->didChangeDirectionTo(this, velocity);
}

