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
    typedef void (*onSNSResult)(int msg, bool success, int extra);
    typedef void (*onLeaderBoardResult)(bool submit, bool success, const char* leaderBoardId, const char* data);
    
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
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    static const char* sdkClassName_ = "com/risesdk/client/Cocos";
    extern onPaymentResult paymentCallback_;
    extern onFreecoinResult freeCoinCallback_;
    extern onSNSResult snsCallback_;
    extern onLeaderBoardResult leaderBoardCallback_;
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
        return callBooleanMethod("hasRewardAd");
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
    
    static void registerSNSCallback(onSNSResult callback)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        snsCallback_ = callback;
#endif
    }
    
    static void registerLeaderBoardCallback(onLeaderBoardResult callback)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        leaderBoardCallback_ = callback;
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
    JNIEXPORT void JNICALL Java_com_risesdk_client_Cocos_sns(JNIEnv* env, jclass clazz, jint msg, jboolean success, jint result);
    JNIEXPORT void JNICALL Java_com_risesdk_client_Cocos_lb(JNIEnv* env, jclass clazz, jboolean submit, jboolean success, jstring leaderBoardId, jstring ex);
#ifdef __cplusplus
}
#endif
#endif

#endif
