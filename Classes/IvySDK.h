#ifndef __IvySDK__DEFINED__
#define __IvySDK__DEFINED__

#include "cocos2d.h"
#include <functional>
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    #include "platform/android/jni/JniHelper.h"
#endif

namespace IvySDK
{
	typedef std::function<void(int resultCode, int billId)> onPaymentResult;
	typedef std::function<void(bool success, int rewardId)> onRewardAdResult;
	typedef std::function<void(int msg, bool success, int extra)> onSNSResult;
	typedef std::function<void(bool isSubmit, bool success, const char* leaderBoardId, const char* data)> onLeaderBoardResult;
	typedef std::function<void(int resultCode, bool success, const char* data)> onServerResult;
	typedef std::function<void(int tag, bool success, const char* data)> onCacheUrlResult;
	typedef std::function<void(int adtype, const char* tag)> onAdshowdResult;
	typedef std::function<void(int adtype, const char* tag)> onAdClickedResult;
	typedef std::function<void(int adtype, const char* tag)> onAdClosedResult;
	typedef std::function<void(const char* tag, bool success)> onAdLoadResult;
	typedef std::function<void(const char* error)> onPaymentErrorResult;
	typedef std::function<void(const char* prices)> onReceiveBillPricesResult;

	static const int AD_FULL = 1;
	static const int AD_VIDEO = 2;
	static const int AD_BANNER = 3;
	static const int AD_CROSS = 4;
    
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
	extern onAdshowdResult adshowdCallback_;
	extern onAdClickedResult adclickedCallback_;
	extern onAdClosedResult adclosedCallback_;
	extern onAdLoadResult adloadCallback_;
	extern onPaymentErrorResult paymentErrorCallback_;
	extern onReceiveBillPricesResult receiveBillPricesCallback_;
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

        static void callVoidUTFMethod2(const char* method, const char* p, const char* p2) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, method, "(Ljava/lang/String;Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
        }
        jstring tag = methodInfo.env->NewStringUTF(p);
        jstring tag2 = methodInfo.env->NewStringUTF(p2);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, tag, tag2);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(tag);
        methodInfo.env->DeleteLocalRef(tag2);
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
	
	
	static void showPromoteAd(const char* pos)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showPromoteAd", "(Ljava/lang/String;)V"))
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

	static void loadFullAd(const char* pos)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "loadFullAd", "(Ljava/lang/String;)V"))
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
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasNative", "(Ljava/lang/String;)Z"))
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
	
	static bool showNativeBanner(const char* tag, int xPrecent, int yPercent, const char* configFile)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showNativeBanner", "(Ljava/lang/String;IILjava/lang/String;)Z"))
		{
			CCLOG("%s%d: error to get methodInfo###################", __FILE__, __LINE__);
			return false;
		}
		jstring tag1 = methodInfo.env->NewStringUTF(tag);
		jstring tag2 = methodInfo.env->NewStringUTF(configFile);
		bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, tag1, xPrecent, yPercent, tag2);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(tag1);
		methodInfo.env->DeleteLocalRef(tag2);
		return result;
#else
		return false;
#endif
	}

	static bool showNativeBanner(const char* tag, int x, int y, int w, int h, const char* configFile)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showNativeBanner", "(Ljava/lang/String;IIIILjava/lang/String;)Z"))
		{
			CCLOG("%s%d: error to get methodInfo###################", __FILE__, __LINE__);
			return false;
		}
		jstring tag1 = methodInfo.env->NewStringUTF(tag);
		jstring tag2 = methodInfo.env->NewStringUTF(configFile);
		bool result = methodInfo.env->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID, tag1, x, y, w, h, tag2);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(tag1);
		methodInfo.env->DeleteLocalRef(tag2);
		return result;
#endif
		return false;
	}

	static void closeNativeBanner(const char* tag)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		callVoidUTFMethod("closeNativeBanner", tag);
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
	
	static bool isNetworkConnected()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        return callBooleanMethod("isNetworkConnected");
#else
        return false;
#endif
	}

	static bool isDeliciousAdAvailable()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		return callBooleanMethod("hasDeliciousIconAd");
#endif
		return false;
	}

	static void showDeliciousInterstitialAd(const char *  json)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showDeliciousInterstitialAd", "(Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring path = methodInfo.env->NewStringUTF(json);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, path);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(path);
#endif
	}

	static bool hasDeliciousBannerAd()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		return callBooleanMethod("hasDeliciousBannerAd");
#endif
		return false;
	}

	static void showDeliciousBannerAd(int x, int y, int w, int h, const char *  json)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showDeliciousBannerAd", "(IIIILjava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring path = methodInfo.env->NewStringUTF(json);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, x, y, w, h, path);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(path);
#endif
	}

	static void closeDeliciousBannerAd()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callVoidMethod("closeDeliciousBannerAd");
#endif
	}

	static void showDeliciousIconAd(int x, int y, int w, int h, const char *  json)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showDeliciousIconAd", "(IIIILjava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring path = methodInfo.env->NewStringUTF(json);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, x, y, w, h, path);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(path);
#endif
	}

	static void closeDeliciousIconAd()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callVoidMethod("closeDeliciousIconAd");
#endif
	}
	
    
    static void showRewardAd(int rewardId)
    {
        callVoidIntMethod("showRewardAd", rewardId);
    }
    
    static bool hasRewardAd()
    {
        return callBooleanMethod("hasRewardAd");
    }
	
	static bool hasFull(const char* tag)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasFull", "(Ljava/lang/String;)Z"))
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
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasRewardAd", "(Ljava/lang/String;)Z"))
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
	
		static void track(const char* category, const char* action) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "track", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring c = methodInfo.env->NewStringUTF(category);
		jstring a = methodInfo.env->NewStringUTF(action);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(c);
		methodInfo.env->DeleteLocalRef(a);
#endif
	}
	
	static void trackEvent(const char* event) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	    const char* data = "default,default";
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;)V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        jstring c = methodInfo.env->NewStringUTF(event);
        jstring a = methodInfo.env->NewStringUTF(data);
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        methodInfo.env->DeleteLocalRef(c);
        methodInfo.env->DeleteLocalRef(a);
#endif
    }
	
	static void trackEvent(const char* event, const char* data) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "trackEvent", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring c = methodInfo.env->NewStringUTF(event);
		jstring a = methodInfo.env->NewStringUTF(data);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, c, a);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(c);
		methodInfo.env->DeleteLocalRef(a);
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

	static void logFinishLevel(const char* level)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		callVoidUTFMethod("logFinishLevel", level);
#endif 
	}

	static void logFinishAchievement(const char* achievement)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		callVoidUTFMethod("logFinishAchievement", achievement);
#endif 
	}

	static void logFinishTutorial(const char* tutorial)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		callVoidUTFMethod("logFinishTutorial", tutorial);
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
	
    static void support(const char* email, const char* extra) {
        callVoidUTFMethod2("support", email, extra);
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

	static void query(int idx = -1) {
		callVoidIntMethod("query", idx);
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

	static void registerAdShowdCallback(onAdshowdResult callback)
	{
#if (IVY_SDK_PLATFORM == CC_PLATFORM_ANDROID)
		adshowdCallback_ = callback;
#endif
	}

	static void registerAdClickedCallback(onAdClickedResult callback)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		adclickedCallback_ = callback;
#endif
	}

	static void registerAdClosedCallback(onAdClosedResult callback)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		adclosedCallback_ = callback;
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

	static void setUserTag(const char* useTag) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callVoidUTFMethod("setUserTag", useTag);
#endif
	}

	static void setUserProperty(const char* key, const char* value) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "setUserProperty", "(Ljava/lang/String;Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		jstring value_ = methodInfo.env->NewStringUTF(value);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, key_, value_);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		methodInfo.env->DeleteLocalRef(value_);
#endif
	}

	static void pushLocalMessage(const char* key, const char* title, const char* content, int pushTime, int interval, bool useSound, const char* soundName, const char* userInfo) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "pushLocalMessage", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IIZLjava/lang/String;Ljava/lang/String;)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		jstring title_ = methodInfo.env->NewStringUTF(title);
		jstring content_ = methodInfo.env->NewStringUTF(content);
		jstring soundName_ = methodInfo.env->NewStringUTF(soundName);
		jstring userInfo_ = methodInfo.env->NewStringUTF(userInfo);
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, key_, title_, content_, pushTime, interval, useSound, soundName_, userInfo_);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		methodInfo.env->DeleteLocalRef(title_);
		methodInfo.env->DeleteLocalRef(content_);
		methodInfo.env->DeleteLocalRef(soundName_);
		methodInfo.env->DeleteLocalRef(userInfo_);
#endif
	}

	static int getRemoteConfigInt(const char* key, int defaultValue = 0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "getRemoteConfigInt", "(Ljava/lang/String;)I"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return 0;
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		int result = methodInfo.env->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID, key_);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		return result;
#endif
		return defaultValue;
	}

	static long getRemoteConfigLong(const char* key, long defaultValue = 0L) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "getRemoteConfigLong", "(Ljava/lang/String;)J"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return 0;
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		long result = methodInfo.env->CallStaticLongMethod(methodInfo.classID, methodInfo.methodID, key_);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		return result;
#endif
		return defaultValue;
	}

	static double getRemoteConfigDouble(const char* key, double defaultValue = 0.0) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "getRemoteConfigDouble", "(Ljava/lang/String;)D"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return 0.0;
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		double result = methodInfo.env->CallStaticDoubleMethod(methodInfo.classID, methodInfo.methodID, key_);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		return result;
#endif
		return defaultValue;
	}

	static bool getRemoteConfigBoolean(const char* key, bool defaultValue = false) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		return callBooleanUTFMethod("getRemoteConfigBoolean", key);
#endif
		return defaultValue;
	}

	static const char* getRemoteConfigString(const char* key, const char* defaultValue = NULL) {
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "getRemoteConfigString", "(Ljava/lang/String;)Ljava/lang/String;"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return "";
		}
		jstring key_ = methodInfo.env->NewStringUTF(key);
		jstring result = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID, key_);
		const char* cs = methodInfo.env->GetStringUTFChars(result, 0);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
		methodInfo.env->DeleteLocalRef(key_);
		methodInfo.env->DeleteLocalRef(result);
		return cs;
#endif
		return defaultValue;
	}
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" 
{
#endif
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pr(JNIEnv* env, jclass clazz, jint billingId, jint status);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pv(JNIEnv* env, jclass clazz);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_rr(JNIEnv* env, jclass clazz, jboolean success, jint rewardId, jstring tag, jboolean skip);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sns(JNIEnv* env, jclass clazz, jint msg, jboolean success, jint result);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_lb(JNIEnv* env, jclass clazz, jboolean submit, jboolean success, jstring leaderBoardId, jstring ex);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sr(JNIEnv* env, jclass clazz, jint resultCode, jboolean success, jstring ex);
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_url(JNIEnv* env, jclass clazz, jint tag, jboolean success, jstring ex);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_aws(JNIEnv* env, jclass clazz, jint adType, jstring tag);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_awc(JNIEnv* env, jclass clazz, jint adType, jstring tag);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_awd(JNIEnv* env, jclass clazz, jint adType, jstring tag);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_lar(JNIEnv* env, jclass clazz, jstring tag, jboolean success);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_pe(JNIEnv* env, jclass clazz, jstring error);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_ps(JNIEnv* env, jclass clazz, jstring prices);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_hal(JNIEnv* env, jclass clazz, jboolean success);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_gr(JNIEnv* env, jclass clazz, jint userTag, jboolean success);
	JNIEXPORT void JNICALL Java_com_android_client_Cocos_nd(JNIEnv* env, jclass clazz, jstring data);
#ifdef __cplusplus
}
#endif
#endif

#endif
