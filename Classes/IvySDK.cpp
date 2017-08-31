#include "IvySDK.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
namespace IvySDK {
    onPaymentResult paymentCallback_;
    onRewardAdResult rewardAdCallback_;
    onSNSResult snsCallback_;
    onLeaderBoardResult leaderBoardCallback_;
    onServerResult serverCallback_;
    onCacheUrlResult cacheCallback_;
	onAdClickedResult adclickedCallback_;
	onAdClosedResult adclosedCallback_;
	onAdLoadResult adloadCallback_;
}
#ifdef __cplusplus
extern "C" {
#endif
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pr(JNIEnv* env, jclass clazz, jint billingId, jint status) {
        CCLOG("payment result");
        if (IvySDK::paymentCallback_ != nullptr) {
            IvySDK::paymentCallback_(status, billingId);
        }
    }
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_pv(JNIEnv* env, jclass clazz) {
        CCLOG("payment system valid");
    }
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_rr(JNIEnv* env, jclass clazz, jboolean success, jint rewardId) {
        CCLOG("receive free coins");
        if (IvySDK::rewardAdCallback_ != nullptr)
            IvySDK::rewardAdCallback_(success, rewardId);
    }
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sns(JNIEnv* env, jclass clazz, jint msg, jboolean success, jint extra){
        CCLOG("receive sns message: %d, result: %d", msg, success? 1 : 0);
        if (IvySDK::snsCallback_ != nullptr) {
            IvySDK::snsCallback_(msg, success, extra);
        }
    }
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_lb(JNIEnv* env, jclass clazz, jboolean submit, jboolean success, jstring leaderBoardId, jstring extra){
        CCLOG("receive leader board message: %s, result: %d", submit ? "submit" : "load", success? 1 : 0);
        if (IvySDK::leaderBoardCallback_ != nullptr) {
            const char* id = env->GetStringUTFChars(leaderBoardId, 0);
            env->DeleteLocalRef(leaderBoardId);
            const char* ex = env->GetStringUTFChars(extra, 0);
            env->DeleteLocalRef(extra);
            IvySDK::leaderBoardCallback_(submit, success, id, ex);
        }
    }
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_sr(JNIEnv* env, jclass clazz, jint resultCode, jboolean success, jstring ex) {
        CCLOG("receive server result: %d", resultCode);
        if (IvySDK::serverCallback_ != nullptr) {
            const char* extra = env->GetStringUTFChars(ex, 0);
            env->DeleteLocalRef(ex);
            IvySDK::serverCallback_(resultCode, success, extra);
        }
    }
    
    
    JNIEXPORT void JNICALL Java_com_android_client_Cocos_url(JNIEnv* env, jclass clazz, jint tag, jboolean success, jstring ex) {
        CCLOG("receive url result: %d", tag);
        if (IvySDK::cacheCallback_ != nullptr) {
            const char* extra = env->GetStringUTFChars(ex, 0);
            env->DeleteLocalRef(ex);
            IvySDK::cacheCallback_(tag, success, extra);
        }
    }

	JNIEXPORT void JNICALL Java_com_android_client_Cocos_awc(JNIEnv* env, jclass clazz, jint adtype, jstring tag) {
		CCLOG("receive url result: %d", tag);
		if (IvySDK::adclickedCallback_ != nullptr) {
			const char* extra = env->GetStringUTFChars(tag, 0);
			env->DeleteLocalRef(tag);
			IvySDK::adclickedCallback_(adtype, extra);
		}
	}

	JNIEXPORT void JNICALL Java_com_android_client_Cocos_awd(JNIEnv* env, jclass clazz, jint adtype, jstring tag) {
		CCLOG("receive url result: %d", tag);
		if (IvySDK::adclosedCallback_ != nullptr) {
			const char* extra = env->GetStringUTFChars(tag, 0);
			env->DeleteLocalRef(tag);
			IvySDK::adclosedCallback_(adtype, extra);
		}
	}

	JNIEXPORT void JNICALL Java_com_android_client_Cocos_lar(JNIEnv* env, jclass clazz, jstring tag, jboolean success) {
		CCLOG("receive url result: %d", tag);
		if (IvySDK::adloadCallback_ != nullptr) {
			const char* extra = env->GetStringUTFChars(tag, 0);
			env->DeleteLocalRef(tag);
			IvySDK::adloadCallback_(extra, success);
		}
	}
#ifdef __cplusplus
}
#endif
#endif
