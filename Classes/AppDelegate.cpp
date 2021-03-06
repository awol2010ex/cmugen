#include "CCEGLView.h"
#include "AppDelegate.h"
#include "scene/GameScene.h"
#include "scene/StartupScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
	SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching() {
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(1024, 768,
			kResolutionNoBorder);
	// turn on display FPS
	pDirector->setDisplayStats(true);

	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);
	//精灵图
	CCSpriteFrameCache* cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile("sprite/cnf.plist", "sprite/cnf.pvr.ccz");
	//UI图
	cache->addSpriteFramesWithFile("UI.plist", "UI.png");
	// create a scene. it's an autorelease object
	CCScene *pScene = StartupScene::create();

	// run
	pDirector->runWithScene(pScene);

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
