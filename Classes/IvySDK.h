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
    typedef void (*onFreecoinResult)(int rewardId);
    
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
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static const char* sdkClassName_ = "com/risesdk/client/Cocos";
    extern onPaymentResult paymentCallback_;
    extern onFreecoinResult freeCoinCallback_;
    #endif

    static void showInterstitial(const char* pos)
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
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "closeBanner", "()V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }

    static void onQuit()
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "onQuit", "()V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        #endif
    }

    static void showMoreGame()
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "moreGame", "()V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }
    
    static void showFreeCoin(int rewardId)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "showRewardAd", "(I)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, rewardId);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }
    
    static bool hasFreeCoin()
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "hasRewardAd", "()Z"))
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
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "share", "()V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }

    static void doBilling(int billingId)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
		if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "pay", "(I)V"))
		{
			CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
			return;
		}
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, billingId);
		methodInfo.env->DeleteLocalRef(methodInfo.classID);
    	#endif
    }
    
    static void rateUs() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "rate", "()V"))
        {
            CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
            return;
        }
        methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
#endif
    }
    
    static const char* getExtraData() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        JniMethodInfo methodInfo;
        if (!JniHelper::getStaticMethodInfo(methodInfo, sdkClassName_, "getExtraData", "()Ljava/lang/String;"))
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
        return "{}";
#endif
    }
    
    static void registerPaymentCallback(onPaymentResult callback)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        paymentCallback_ = callback;
        #endif
    }
    
    static void registerFreecoinCallback(onFreecoinResult callback)
    {
        #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        freeCoinCallback_ = callback;
        #endif
    }
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#ifdef __cplusplus
extern "C" 
{
#endif
    JNIEXPORT void JNICALL Java_com_risesdk_client_Cocos_pr(JNIEnv* env, jclass clazz, jint billingId, jboolean success);
    JNIEXPORT void JNICALL Java_com_risesdk_client_Cocos_pv(JNIEnv* env, jclass clazz);
    JNIEXPORT void JNICALL Java_com_risesdk_client_Cocos_rr(JNIEnv* env, jclass clazz, jint rewardId);
#ifdef __cplusplus
}
#endif
#endif

#endif
