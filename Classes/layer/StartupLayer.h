#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;
//开机图层
class StartupLayer: public UILayer {
public:
	StartupLayer(void);
	~StartupLayer(void);

	bool init();
	CREATE_FUNC (StartupLayer);
	
	//关闭按钮
// a selector callback
	void closeCallback(CCObject* pSender);
};
