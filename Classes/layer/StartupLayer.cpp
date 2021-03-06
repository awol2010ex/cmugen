#include "layer/StartupLayer.h"
#include "scene/GameScene.h"
#include "SimpleAudioEngine.h"
#include <android/log.h>

#include "sprite/Saber.h"
#include "sprite/Ichigo.h"
#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;

StartupLayer::StartupLayer(void) {
}

StartupLayer::~StartupLayer(void) {
}

// on "init" you need to initialize your instance
bool StartupLayer::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!UILayer::init());

		this->addWidget(
				CCUIHELPER->createWidgetFromJsonFile(
						"ui/startup/Export/startup_1/startup_1.ExportJson"));


		//关闭按钮
		UIButton* closeButton = dynamic_cast<UIButton*>(this->getWidgetByName(
				"closeButton"));
		closeButton->addReleaseEvent(this,
				coco_releaseselector(StartupLayer::closeCallback));

		//开始游戏按钮
		UIButton* playButton = dynamic_cast<UIButton*>(this->getWidgetByName(
				"playButton"));
		playButton->addReleaseEvent(this,
				coco_releaseselector(StartupLayer::playCallback));

		bRet = true;
	} while (0);

	return bRet;

	return true;
}

//关闭按钮
void StartupLayer::closeCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//开始游戏按钮
void StartupLayer::playCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->replaceScene(
			CCTransitionFade::create(float(1.2), GameScene::create()));
}
