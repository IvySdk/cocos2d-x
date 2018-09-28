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
	case IvySDK::PAYMENT_RESULT_FAILURE:
		break;
	case IvySDK::PAYMENT_RESULT_CANCEL:
		break;
	default:
		CCLOG("billing %i result code %i", billingId, resultCode);
		break;
	}
}

void onRewardAdResult(bool success, int coins) {
    CCLOG("free coin: success? %s and I get %i coins", success? "true" : "false", coins);
}

void onReceiveSNSResult(int resultType, bool success, int extra) {
    switch(resultType) {
        case IvySDK::SNS_RESULT_LOGIN:
            if (success) {
                // now do your login logic, get profile, friends etc.
                const char* mestring = IvySDK::me();
                CCLOG("me string is %s", mestring);
            }
            break;
            
        case IvySDK::SNS_RESULT_LIKE:
            if (success) {
                CCLOG("thank you for like us.");
            }
            break;
            
        case IvySDK::SNS_RESULT_INVITE:
            if (success) {
                CCLOG("thank you invite your friends. you will receive 10 golds.");
            }
            break;
            
        case IvySDK::SNS_RESULT_CHALLENGE:
            if (extra > 3) {
                CCLOG("thank you challenge 3 friends, you will receive 10 golds.");
            }
            break;
    }
}
//
//void onReceiveLeaderboardResult(bool submit, bool success, const char* leaderBoardId, const char* data)
//{
//    if (submit) {
//        if (success) {
//            CCLOG("submit score to %s success", leaderBoardId);
//        } else {
//            CCLOG("submit score to %s fails", leaderBoardId);
//        }
//    } else {
//        if (success) {
//            CCLOG("load leader board %s success; data is %s", leaderBoardId, data);
//        } else {
//            CCLOG("load leader board %s fails", leaderBoardId);
//        }
//    }
//}

void onReceiveServerResult(int resultCode, bool success, const char* data) {
    switch(resultCode) {
        case IvySDK::SERVER_RESULT_SALES_CLICK:
            if (success) {
                int saleId = atoi(data);
                CCLOG("sales clicked here: id %d", saleId);
                
            }
            break;
            
        case IvySDK::SERVER_RESULT_VERIFY_CODE:
            if (success) {
                CCLOG("verify code success");
            } else {
                CCLOG("verify code fails");
            }
            break;
            
        case IvySDK::SERVER_RESULT_RECEIVE_GAME_DATA:
            if (success) {
                CCLOG("game data is %s", data);
                
            }
            break;
    }
}

void onCacheUrlResult(int tag, bool success, const char* path) {
    switch(tag){
        case 1:
            CCLOG("tag 1 success? %d, path %s", success ? 1 : 0, path);
            break;
    }
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
	IvySDK::registerRewardAdCallback(onRewardAdResult);
    IvySDK::registerSNSCallback(onReceiveSNSResult);
    IvySDK::registerCacheUrlCallback(onCacheUrlResult);
//    IvySDK::registerLeaderBoardCallback(onReceiveLeaderboardResult);
    IvySDK::registerServerCallback(onReceiveServerResult);
	IvySDK::registerAdClosedCallback([](int adtype, const char* tag) {
		CCLOG("<<<<<<<%d_%s>>>>>>>>>>>", adtype, tag);
	});

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
    const int label_size = 41;
    const char* labels[label_size] = {
        "Pause AD", // 1
        "PassLevel",// 2
        "Custom", // 3
        "Exit AD",// 4
        "Banner",// 5
        "Close Banner",// 6
        "Share", // 7
        "MoreGame", // 8
        "RewardAd", // 9
        "Pay", // 10
        "Get Data", // 11
        "Track Event", // 12
        "Rate", //13
        "login", // 14
        "logout", // 15
        "isLogin",// 16
        "Like", // 17
        "Challenge", // 18
        "Me", // 19
        "Friends", // 20
        "Invite", // 21
        "Submit", //22
        "Load Leader Board", //23
        "Load global", //24
        "Show Native", //25,
        "Hide Native", //26,
        "show sales", //27
        "load game data", //28
        "get app id", //29
        "cache url", //30
        "cache url tag", //31
		"UM_startLevel",//32
		"UM_failLevel",//33
		"UM_finishLevel",//34
		"UM_PlayerLevel",//35
		"UM_PageStart",//36
		"UM_PageEnd",//37
		"UM_onEvent",//38
		"logFinishLevel",//39
		"logFinishAchievement",//40
		"logFinishTutorial"//41
    };
    
    int xOffset = 0;
    int yOffset = 0;
    
    for(int i=0; i<label_size; ++i) {
        CCMenuItemFont *laber1 = CCMenuItemFont::create(labels[i], handler);
        laber1->setPosition(ccp(px + xOffset, py - yOffset));
        laber1->setTag(i+1);
        CCMenu *menu1 = CCMenu::create(laber1, NULL);
        menu1->setPosition(Vec2(0, 0));
        addChild(menu1, 3);
        
        yOffset += 20;
        if (yOffset > 200) {
            xOffset += 100;
            yOffset = 0;
        }
    }
    
	return true;
}

void HelloWorld::AdButtonClicked(Ref* ref) {
	int tag = static_cast<CCMenu*>(ref)->getTag();
	switch (tag) {
		case 1:// 暂停广告
			IvySDK::showFullAd(IvySDK::AD_POS_GAME_PAUSE);
			break;
		case 2:// 过关广告
			IvySDK::showFullAd(IvySDK::AD_POS_GAME_PASSLEVEL);
			break;
		case 3:// 自定义广告
			IvySDK::showFullAd(IvySDK::AD_POS_GAME_CUSTOM);
			break;
		case 4:// 退出广告
			IvySDK::onQuit();
			break;
		case 5:// Banner广告
			IvySDK::showBanner("default", IvySDK::AD_POS_MIDDLE_TOP);
			break;
		case 6:// 关闭Banner广告
			IvySDK::closeBanner();
			break;
		case 7:// 分享
			IvySDK::share();
			break;
		case 8:// 更多游戏
			IvySDK::showMoreGame();
			break;
		case 9:// 视频广告
			IvySDK::showRewardAd("default", 1);
			break;
		case 10:// 支付
			IvySDK::pay(BILLING_ID_ACTIVE_GAME);
			break;      
        case 11:
            CCLOG("extra data: %s", IvySDK::getExtraData());
            break;      
        case 12:
            IvySDK::trackEvent("test category", "test action", "test label", 3);
            break;        
        case 13://给应用，游戏等五星好评
            IvySDK::rateUs();
            break;          
        case 14://登陆facebook账户
            IvySDK::login();
            break;           
        case 15://退出facebook账户
            IvySDK::logout();
            break;         
        case 16://是否登陆facebook账户
            CCLOG("isLogin: %s", IvySDK::isLogin() ? "true": "false");
            break;         
        case 17://facebook点赞
            IvySDK::like();
            break;        
        case 18://向你的facebook朋友发出挑战
            IvySDK::challenge("wa challenge", "speed come with me");
            break;        
        case 19://获取我的faceook个人信息
            CCLOG("me is %s", IvySDK::me());
            break;        
        case 20://获取faceook朋友信息列表
            CCLOG("friends are: %s", IvySDK::friends());
            break;          
        case 21://facebook邀请好友安装应用，游戏等
            IvySDK::invite();
            break;           
//        case 22:
//            IvySDK::submitScore("endless", 320, "");
//            break;
//            
//        case 23:
//            IvySDK::loadFriendLeaderBoard("endless", 0, 20, "");
//            break;
//            
//        case 24:
//            IvySDK::loadGlobalLeaderBoard("endless", 0, 20);
//            break;           
        case 25:
            IvySDK::showNativeAd("lock_pre", 80);
            break;            
        case 26:
            IvySDK::hideNativeAd("lock_pre");
            break;            
//        case 27:
//            IvySDK::showSales(2);
//            break;
//            
//        case 28:
//            IvySDK::loadGameData(1);
//            break;
            
        case 29:
            CCLOG("app id is %s", IvySDK::getConfig(IvySDK::CONFIG_KEY_APP_ID));
            break;            
        case 30:
            CCLOG("cached result path is %s", IvySDK::cacheUrl("http://img4.imgtn.bdimg.com/it/u=3087502007,2322343371&fm=21&gp=0.jpg"));
            break;            
        case 31:
            IvySDK::cacheUrl(1, "http://img4.imgtn.bdimg.com/it/u=3087502007,2322343371&fm=21&gp=0.jpg");
            break;
		case 32:
			IvySDK::UM_startLevel("level 0");
			break;
		case 33:
			IvySDK::UM_failLevel("level 0");
			break;
		case 34:
			IvySDK::UM_finishLevel("level 0");
			break;
		case 35:
			IvySDK::UM_setPlayerLevel(1);
			break;
		case 36:
			IvySDK::UM_onPageStart("mainPage");
			break;
		case 37:
			IvySDK::UM_onPageEnd("mainPage");
			break;
		case 38:
			//IvySDK::UM_onEvent("button1", "onclick");
			break;
		case 39:
			IvySDK::logFinishLevel("level_1");
			break;
		case 40:
			IvySDK::logFinishAchievement("chieve_1");
			break;
		case 41:
			IvySDK::logFinishTutorial("tutorial_1");
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
