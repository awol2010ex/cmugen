#include "scene/StartupScene.h"
#include "layer/StartupLayer.h"
using namespace cocos2d;

StartupScene::StartupScene(void) {

}

StartupScene::~StartupScene(void) {//析构


}

bool StartupScene::init() {
	bool bRet = false;
	do {
		CC_BREAK_IF(!CCScene::init());


		//开机画面图层
		StartupLayer *layer = StartupLayer::create();
		CC_BREAK_IF(! layer);

		this->addChild(layer ,1);

		bRet = true;
	} while (0);

	return bRet;
}
