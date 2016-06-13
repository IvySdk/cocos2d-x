#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;
#include "HelloWorldScene.h"
#include "IvySDK.h"

USING_NS_CC;

/////////////////////////////////////////////////////////////

//计费点要与平台给的ID相对应
#define BILLING_ID_ACTIVE_GAME 1

static void onPaymentSuccess(int billId) {
	switch (billId) {
	case BILLING_ID_ACTIVE_GAME:
		CCLOG("game actived!");
		break;
	}
}

void HelloWorld::onPaymentResult(int resultCode, int billingId) {
    CCLOG("billing %i failure code %i", billingId, resultCode);
	switch (resultCode) {
	case IvySDK::PAYMENT_RESULT_SUCCESS:
		onPaymentSuccess(billingId);
		break;

	default:
		CCLOG("billing %i result code %i", billingId, resultCode);
		break;
	}
}

void onFreecoinResult(int coins) {
	CCLOG("I get %i coins", coins);
}

/////////////////////////////////////////////////////////

Scene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}
	
	CCMenuItemFont::setFontSize(11);
	IvySDK::registerPaymentCallback(onPaymentResult);
	IvySDK::registerFreecoinCallback(onFreecoinResult);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(
			origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	///////////////////////////////////////////////////////////////////////////////

	float py = origin.y + 250;
	float px = origin.x + 40;

	ccMenuCallback handler = CC_CALLBACK_1(HelloWorld::AdButtonClicked, this);

	CCMenuItemFont *laber1 = CCMenuItemFont::create("Pause AD", handler);
	laber1->setPosition(ccp(px, py));
	laber1->setTag(1);
	CCMenu *menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("PassLevel AD", handler);
	laber1->setPosition(ccp(px, py - 40));
	laber1->setTag(2);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Custom AD", handler);
	laber1->setPosition(ccp(px, py - 80));
	laber1->setTag(3);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Exit AD", handler);
	laber1->setPosition(ccp(px, py - 120));
	laber1->setTag(4);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Banner AD", handler);
	laber1->setPosition(ccp(px, py - 160));
	laber1->setTag(5);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Close Banner", handler);
	laber1->setPosition(ccp(px + 100, py));
	laber1->setTag(6);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("share", handler);
	laber1->setPosition(ccp(px + 100, py - 40));
	laber1->setTag(7);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("More Game", handler);
	laber1->setPosition(ccp(px + 100, py - 80));
	laber1->setTag(8);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Free Coin", handler);
	laber1->setPosition(ccp(px + 100, py - 120));
	laber1->setTag(9);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);

	laber1 = CCMenuItemFont::create("Do billing", handler);
	laber1->setPosition(ccp(px + 100, py - 160));
	laber1->setTag(10);
	menu1 = CCMenu::create(laber1, NULL);
	menu1->setPosition(CCPointZero);
	addChild(menu1, 3);
    
    laber1 = CCMenuItemFont::create("getData", handler);
    laber1->setPosition(ccp(px + 200, py));
    laber1->setTag(11);
    menu1 = CCMenu::create(laber1, NULL);
    menu1->setPosition(CCPointZero);
    addChild(menu1, 3);
    
    laber1 = CCMenuItemFont::create("track event", handler);
    laber1->setPosition(ccp(px + 200, py - 40));
    laber1->setTag(12);
    menu1 = CCMenu::create(laber1, NULL);
    menu1->setPosition(CCPointZero);
    addChild(menu1, 3);

    laber1 = CCMenuItemFont::create("rate us", handler);
    laber1->setPosition(ccp(px + 200, py - 80));
    laber1->setTag(13);
    menu1 = CCMenu::create(laber1, NULL);
    menu1->setPosition(CCPointZero);
    addChild(menu1, 3);
	return true;
}

void HelloWorld::AdButtonClicked(Ref* ref) {
	int tag = static_cast<CCMenu*>(ref)->getTag();
	switch (tag) {
	case 1:// Show Pause Ad
		IvySDK::showInterstitial(IvySDK::AD_POS_GAME_PAUSE);
		break;
	case 2:// Show Passlevel Ad
		IvySDK::showInterstitial(IvySDK::AD_POS_GAME_PASSLEVEL);
		break;
	case 3:// Show Custom Ad
		IvySDK::showInterstitial(IvySDK::AD_POS_GAME_CUSTOM);
		break;
	case 4:// Show Exit Ad
		IvySDK::onQuit();
		break;
	case 5:// Show Banner
		IvySDK::showBanner(IvySDK::AD_POS_MIDDLE_TOP);
		break;
	case 6:// Close Banner
		IvySDK::closeBanner();
		break;
	case 7:// Share
		IvySDK::share();
		break;
	case 8:// More Game
		IvySDK::showMoreGame();
		break;
	case 9:// Show Free Coin
		IvySDK::showFreeCoin(1);
		break;
	case 10:// Do billing
		IvySDK::doBilling(BILLING_ID_ACTIVE_GAME);
		break;
            
        case 11:
            CCLOG("extra data: %s", IvySDK::getExtraData());
            break;
            
        case 12:
            IvySDK::trackEvent("test category", "test action", "test label", 3);
            break;
            
        case 13:
            IvySDK::rateUs();
            break;
	default:
		break;
	}
}

void HelloWorld::menuCloseCallback(Ref* sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox(
			"You pressed the close button. Windows Store Apps do not implement a close button.",
			"Alert");
	return;
#endif
	IvySDK::onQuit();
	//Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
