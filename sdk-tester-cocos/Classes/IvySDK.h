#ifndef __IvySDK__DEFINED__
#define __IvySDK__DEFINED__

#include "cocos2d.h"
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif

namespace IvySDK
{
    typedef void (*onPaymentResult)(int resultCode, int billId);
    typedef void (*onRewardAdResult)(bool success, int rewardId);
    typedef void (*onSNSResult)(int msg, bool success, int extra);
    typedef void (*onLeaderBoardResult)(bool isSubmit, bool success, const char* leaderBoardId, const char* data);
    typedef void (*onServerResult)(int resultCode, bool success, const char* data);
    typedef void (*onCacheUrlResult)(int tag, bool success, const char* data);
    
    static const int AD_POS_LEFT_TOP = 1;
    static const int AD_POS_MIDDLE_TOP = 3;
    static const int AD_POS_RIGHT_TOP = 6;
    static const int AD_POS_MIDDLE_MIDDLE = 5;
    static const int AD_POS_LEFT_BOTTOM = 2;
    static const int AD_POS_MIDDLE_BOTTOM = 4;
    static const int AD_POS_RIGHT_BOTTOM = 7;
    
    static const char* AD_POS_GAME_START = "start";
    static const char* AD_POS_GAME_PAUSE = "pause";
    static const char* AD_POS_GAME_PASSLEVEL = "passlevel";
    static const char* AD_POS_GAME_CUSTOM = "custom";
    
    static const int PAYMENT_RESULT_SUCCESS = 0;
    static const int PAYMENT_RESULT_CANCEL = 1;
    static const int PAYMENT_RESULT_FAILURE = 2;
    
    static const int SNS_RESULT_LOGIN = 1;
    static const int SNS_RESULT_INVITE = 2;
    static const int SNS_RESULT_CHALLENGE = 3;
    static const int SNS_RESULT_LIKE = 4;
    
    static const int SERVER_RESULT_RECEIVE_GAME_DATA = 1;
    static const int SERVER_RESULT_SAVE_USER_DATA = 2;
    static const int SERVER_RESULT_RECEIVE_USER_DATA = 3;
    static const int SERVER_RESULT_VERIFY_CODE = 4;
    static const int SERVER_RESULT_SALES_CLICK = 5;
    
    static const int CONFIG_KEY_APP_ID = 1;
    static const int CONFIG_KEY_LEADER_BOARD_URL = 2;
    static const int CONFIG_KEY_API_VERSION = 3;
    static const int CONFIG_KEY_SCREEN_WIDTH = 4;
    static const int CONFIG_KEY_SCREEN_HEIGHT = 5;
    static const int CONFIG_KEY_LANGUAGE = 6;
    static const int CONFIG_KEY_COUNTRY = 7;
    static const int CONFIG_KEY_VERSION_CODE = 8;
    static const int CONFIG_KEY_VERSION_NAME = 9;
    static const int CONFIG_KEY_PACKAGE_NAME = 10;
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static const char* sdkClassName_ = "com/android/client/Cocos";
    extern onPaymentResult paymentCallback_;
    extern onRewardAdResult rewardAdCallback_;
    extern onSNSResult snsCallback_;
    extern onLeaderBoardResult leaderBoardCallback_;
    extern onServerResult serverCallback_;
    extern onCacheUrlResult cacheCallback_;
    #endif
    
    static void callVoidMethod(const char* method) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "()V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
    }
    
    static void callVoidUTFMethod(const char* method, const char* p) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
        }
        jstring tag = methodInfo.env->NewStringUTF(p);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
#endif
    }
    
    static bool callBooleanMethod(const char* method) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "()Z"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return false;
        }
        bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        return result;
#else
        return false;
#endif
    }
    
    static bool callBooleanUTFMethod(const char* method, const char* p) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(Ljava/lang/String;)Z"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return false;
        }
        jstring tag = methodInfo.env->NewStringUTF(p);
        bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
        return result;
#else
        return false;
#endif
    }
    
    static const char* callUTFMethod(const char* method, const char* def) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "()Ljava/lang/String;"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return "{}";
        }
        jstring result = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        const char* cs = methodInfo.env->GetStringUTFChars(result, 0);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(result);
        return cs;
#else
        return def;
#endif
    }
    
    static const char* callUTFUTFMethod(const char* method, const char* def, const char* p) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(Ljava/lang/String;)Ljava/lang/String;"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return "{}";
        }
        jstring pp = methodInfo.env->NewStringUTF(p);
        jstring result = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, pp);
        const char* cs = methodInfo.env->GetStringUTFChars(result, 0);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(result);
        methodInfo.env->DeleteLocalRef(pp);
        return cs;
#else
        return def;
#endif
    }
    
    static const char* callIntUTFMethod(const char* method, const char* def, int key) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(I)Ljava/lang/String;"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return "{}";
        }
        jstring result = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, key);
        const char* cs = methodInfo.env->GetStringUTFChars(result, 0);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(result);
        return cs;
#else
        return def;
#endif
    }
    
    static void callVoidIntMethod(const char* method, int param) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(I)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, param);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
    }

    static void showFullAd(const char* pos)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showFullAd", "(Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
        jstring tag = methodInfo.env->NewStringUTF(pos);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
    	#endif
    }
    
    static void showBanner(const char* tag, int pos)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showBanner", "(Ljava/lang/String;I)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring t = methodInfo.env->NewStringUTF(tag);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, t, pos);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(t);
#endif
    }

    
    static void showBanner(int pos)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showBanner", "(I)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, pos);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }

    static void closeBanner()
    {
        callVoidMethod("closeBanner");
    }
    
    static bool hasNativeAd(const char* nativeTag) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasNative", "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return false;
        }
        jstring tag = methodInfo.env->NewStringUTF(nativeTag);
        bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
        return result;
#else
        return false;
#endif
    }
    
    static void showNativeAd(const char* nativeTag, int yPercent) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showNative", "(Ljava/lang/String;I)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring tag = methodInfo.env->NewStringUTF(nativeTag);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag, yPercent);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
#endif
    }
    
    static void hideNativeAd(const char* nativeTag) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hideNative", "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring tag = methodInfo.env->NewStringUTF(nativeTag);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
#endif
    }

    static void onQuit()
    {
        callVoidMethod("onQuit");
    }

    static void showMoreGame()
    {
        callVoidMethod("moreGame");
    }
    
    static void showRewardAd(int rewardId)
    {
        callVoidIntMethod("showRewardAd", rewardId);
    }
    
    static bool hasRewardAd()
    {
        return callBooleanMethod("hasRewardAd");
    }
    
    static void showRewardAd(const char* tag, int rewardId)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showRewardAd", "(Ljava/lang/String;I)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring t = methodInfo.env->NewStringUTF(tag);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, t, rewardId);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(t);
#endif
    }
    
    static bool hasRewardAd(const char* tag)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasRewardAd", "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return false;
        }
        jstring t = methodInfo.env->NewStringUTF(tag);
        bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, t);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(t);
        return result;
#else
        return false;
#endif
    }
    
    static void trackEvent(const char* category, const char* action, const char* label, int value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;I)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(category);
        jstring a = methodInfo.env->NewStringUTF(action);
        jstring l = methodInfo.env->NewStringUTF(label);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a, l, value);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
        methodInfo.env->DeleteLocalRef(a);
        methodInfo.env->DeleteLocalRef(l);
#endif
    }
    
    static void share()
    {
        callVoidMethod("share");
    }

    static void pay(int billingId)
    {
        callVoidIntMethod("pay", billingId);
    }
    
    static void rateUs() {
        callVoidMethod("rate");
    }
    
    static const char* getExtraData() {
        return callUTFMethod("getExtraData", "{}");
    }
    
    static void login() {
        callVoidMethod("login");
    }
    
    static void logout() {
        callVoidMethod("logout");
    }
    
    static bool isLogin() {
        return callBooleanMethod("isLogin");
    }
    
    static void invite() {
        callVoidMethod("invite");
    }
    
    static void challenge(const char* title, const char* message) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "challenge", "(Ljava/lang/String;Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(title);
        jstring a = methodInfo.env->NewStringUTF(message);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
        methodInfo.env->DeleteLocalRef(a);
#endif
    }
    
    static void like() {
        callVoidMethod("like");
    }
    
    static const char* me() {
        return callUTFMethod("me", "{}");
    }
    
    static const char* friends() {
        return callUTFMethod("friends", "[]");
    }
    
    static void submitScore(const char* leaderBoardId, int score, const char* extra) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "submitScore", "(Ljava/lang/String;ILjava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(leaderBoardId);
        jstring a = methodInfo.env->NewStringUTF(extra);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, score, a);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
        methodInfo.env->DeleteLocalRef(a);
#endif
    }
    
    static void loadFriendLeaderBoard(const char* leaderBoardId, int start, int end, const char* friends) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "loadLeaderBoard", "(Ljava/lang/String;IILjava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(leaderBoardId);
        jstring a = methodInfo.env->NewStringUTF(friends);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, start, end, a);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
        methodInfo.env->DeleteLocalRef(a);
#endif
    }
    
    static void loadGlobalLeaderBoard(const char* leaderBoardId, int start, int end) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "loadGlobalLeaderBoard", "(Ljava/lang/String;II)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(leaderBoardId);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, start, end);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
#endif
    }
    
    static void loadGameData(int version) {
        callVoidIntMethod("loadExtra", version);
    }
    
    static void showSales(int saleId) {
        callVoidIntMethod("showSales", saleId);
    }
    
    static void verifyCode(const char* code) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "verifyCode", "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring tag = methodInfo.env->NewStringUTF(code);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
#endif
    }
    
    static void loadUserData() {
        callVoidMethod("loadData");
    }
    
    static void saveUserData(const char* data) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "saveData", "(Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring tag = methodInfo.env->NewStringUTF(data);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
#endif
    }
    
	//注册支付回调函数
    static void registerPaymentCallback(onPaymentResult callback)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        paymentCallback_ = callback;
        #endif
    }
    //注册展示视频广告回调
    static void registerRewardAdCallback(onRewardAdResult callback)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		rewardAdCallback_ = callback;
        #endif
    }
    
    static void registerSNSCallback(onSNSResult callback)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        snsCallback_ = callback;
#endif
    }
    
    static void registerCacheUrlCallback(onCacheUrlResult callback)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        cacheCallback_ = callback;
#endif
    }
    
//    static void registerLeaderBoardCallback(onLeaderBoardResult callback)
//    {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        leaderBoardCallback_ = callback;
//#endif
//    }
    
    static void registerServerCallback(onServerResult callback)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        serverCallback_ = callback;
#endif
    }
    
    static const char* getConfig(int configKey) {
        return callIntUTFMethod("getConfig", "", configKey);
    }
    
    static const char* cacheUrl(const char* url) {
        return callUTFUTFMethod("cacheUrl", "", url);
    }
    
    static void cacheUrl(int tag, const char* url) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "cacheUrl", "(ILjava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
        }
        jstring url_ = methodInfo.env->NewStringUTF(url);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag, url_);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(url_);
#endif
    }
    
    static bool hasApp(const char* packageName) {
        return callBooleanUTFMethod("hasApp", packageName);
    }
    
    static void getApp(const char* packageName) {
        callVoidUTFMethod("getApp", packageName);
    }
    
    static void launchApp(const char* packageName) {
        callVoidUTFMethod("launchApp", packageName);
    }

	static void UM_setPlayerLevel(int levelId) {
		callVoidIntMethod("UM_setPlayerLevel", levelId);
	}

	static void UM_onPageStart(const char* pageName) {
		callVoidUTFMethod("UM_onPageStart", pageName);
	}

	static void UM_onPageEnd(const char* pageName) {
		callVoidUTFMethod("UM_onPageEnd", pageName);
	}

	static void UM_onEvent(const char* eventId) {
		callVoidUTFMethod("UM_onEvent", eventId);
	}

	static void UM_onEvent(const char* eventId, const char* tag) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "UM_onEvent", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring c = methodInfo.env->NewStringUTF(eventId);
		jstring a = methodInfo.env->NewStringUTF(tag);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(c);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}

	static void UM_startLevel(const char* level) {
		callVoidUTFMethod("UM_startLevel", level);
	}

	static void UM_failLevel(const char* level) {
		callVoidUTFMethod("UM_failLevel", level);
	}


	static void UM_finishLevel(const char* level) {
		callVoidUTFMethod("UM_finishLevel", level);
	}

	static void UM_pay(double money, const char* itemName, int number, double price) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "UM_pay", "(DLjava/lang/String;ID)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring a = methodInfo.env->NewStringUTF(itemName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, money, a, number, price);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}

	static void UM_buy(const char* itemName, int count, double price) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "UM_buy", "(Ljava/lang/String;ID)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring a = methodInfo.env->NewStringUTF(itemName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, a, count, price);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}

	static void UM_use(const char* itemName, int number, double price) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "UM_use", "(Ljava/lang/String;ID)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring a = methodInfo.env->NewStringUTF(itemName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, a, number, price);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}

	static void UM_bonus(const char* itemName, int number, double price, int trigger) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "UM_bonus", "(java/lang/String;IDI)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring a = methodInfo.env->NewStringUTF(itemName);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, a, number, price, trigger);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" 
{
#endif
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pr(JNIEnv* env, jclass clazz, jint billingId, jint status);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pv(JNIEnv* env, jclass clazz);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_rr(JNIEnv* env, jclass clazz, jboolean success, jint rewardId);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sns(JNIEnv* env, jclass clazz, jint msg, jboolean success, jint result);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_lb(JNIEnv* env, jclass clazz, jboolean submit, jboolean success, jstring leaderBoardId, jstring ex);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sr(JNIEnv* env, jclass clazz, jint resultCode, jboolean success, jstring ex);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_url(JNIEnv* env, jclass clazz, jint tag, jboolean success, jstring ex);
#ifdef __cplusplus
}
#endif
#endif

#endif
