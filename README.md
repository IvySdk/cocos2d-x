# RiseSDK for cocos2d-x
1, Copy files and init in Activity

* copy Classes and proj.android to your Cocos2d-x project folder corresponding
-- before:
<center>![before copy](assets/risesdk-cocos-89d68.png)</center>
-- after:
<center>![after copy](assets/risesdk-cocos-1ed0e.png)</center>
<center>![after copy](assets/risesdk-cocos-db52d.png)</center>

* init in your main activity
```java
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Cocos.onCreate(this);
    }

    @Override
    protected void onResume() {
        super.onResume();
        Cocos.onResume(this);
    }

    @Override
    protected void onPause() {
        super.onPause();
        Cocos.onPause();
    }

    @Override
    protected void onDestroy() {
        Cocos.onDestroy();
        super.onDestroy();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        Cocos.onActivityResult(requestCode, resultCode, data);
        super.onActivityResult(requestCode, resultCode, data);
    }
```

* if you use proguard to obfuscate your java source code, you should add these rules to your proguard rules file:
```java
-keep class com.risesdk.client.** {
    <methods>;
}

-keep class android.support.** {
    *;
}
```

2, add IvySDK.cpp to your Android.mk file
![add src](assets/risesdk-cocos-f91ad.png)

3, ADs
call these functions when you want
```c++
//show pass level full screen ad when you want
IvySDK::showInterstitial(IvySDK::AD_POS_GAME_PASSLEVEL);

// show pause ad when you want
IvySDK::showInterstitial(IvySDK::AD_POS_GAME_PAUSE);

// show banner at the top center position of your phone
IvySDK::showBanner(IvySDK::AD_POS_MIDDLE_TOP);

// close banner when needed
IvySDK::closeBanner();

// when you want to quit the game
IvySDK::onQuit();

// ask the player to share your game with his friends
IvySDK::share();

// ask the player to give you a 5-star-rating
IvySDK::rateUs();

// show more game to the player
IvySDK::showMoreGame();

// when you want to track the player behavior
IvySDK::trackEvent("your category", "your action", "your label", 1);

// get your custom data from server, return "{}" default
const char* data = IvySDK::getExtraData();
```

4, In-App Billing
When you want to use IAP, you should do this:
* register your payment callback
```c++
// define your bill ids
#define BILLING_ID_ACTIVE_GAME 1
#define BILLING_ID_BUY_CAR 2
... etc.

static void onPaymentSuccess(int billId) {
	switch (billId) {
	case BILLING_ID_ACTIVE_GAME:
		CCLOG("game actived!");
    // do your logic here
		break;

    case BILLING_ID_BUY_CAR:
    // do your logic here
        break;
	}
}

// define your callback function, this should be a global function or a member function of a class
void HelloWorld::onPaymentResult(int resultCode, int billingId) {
    CCLOG("billing %i result code %i", billingId, resultCode);
	switch (resultCode) {
	case IvySDK::PAYMENT_RESULT_SUCCESS:
		onPaymentSuccess(billingId);
		break;

	default:
		CCLOG("billing %i result code %i", billingId, resultCode);
		break;
	}
}

// call register in your initialize function
bool HelloWorld::init() {
  ...
  IvySDK::registerPaymentCallback(onPaymentResult);
  ...
}
```
* call doBilling when you want
```c++
IvySDK::doBilling(BILLING_ID_ACTIVE_GAME);
```

5, when you want to use reward ad, you should do this:
* register your reward ad callback
```c++
#define REWARD_ID_GOLD 1
#define REWARD_ID_CAR 2
... etc.

// define your callback function, this should be a global function or a member function of a class
void onFreecoinResult(int rewardId) {
	CCLOG("receive reward %i", rewardId);
  // do your logic here
  switch(rewardId) {
    case REWARD_ID_CAR:
    // do your logic
    break;

    case REWARD_ID_GOLD:
    //do your logic
    break;

    ...
  }
}

// call register in your initialize function
bool HelloWorld::init() {
  ...
  IvySDK::registerFreecoinCallback(onFreecoinResult);
  ...
}
```
* call showFreeCoin when you want
```c++
// launch reward ad for gold
IvySDK::showFreeCoin(REWARD_ID_GOLD);

// determine whether the reward ad is available
bool has = IvySDK::hasFreeCoin();
if (has)...
```

6, SNS
When you want to use SNS, you should do this:
* define sns callback and register it
```js
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

// call register in your initialize function
bool HelloWorld::init() {
  ...
  IvySDK::registerSNSCallback(onReceiveSNSResult);
  ...
}
```
* and then you can do this when needed:
```js
// login
IvySDK::login();

// log out
IvySDK::logout();

// indicates if the player logged in
IvySDK::isLogin();

// let the player to like you
IvySDK::like();

// let the player to invite his friends
IvySDK::invite();

// let the player to challenge his friends
IvySDK::challenge("challenge you", "speed coming....");

// get the player profile, the result is a json string  {"id":"xxx", "name":"xxx", "picture":"/sdcard/.cache/xxxx"}
const char* profileString = IvySDK::me();

// get the player friends profiles, the result is a json array string: [{"id":"xxx", "name":"xxx", "picture":"/sdcard/.cache/xxxx"}, ...]
const char* friendString = IvySDK::friends();
```

7, Leaderboard
When you want to use leaderboard, you should do this:
* Define leaderboard call back
```js
void onReceiveLeaderboardResult(bool submit, bool success, const char* leaderBoardId, const char* data)
{
    if (submit) {
        if (success) {
            CCLOG("submit score to %s success", leaderBoardId);
        } else {
            CCLOG("submit score to %s fails", leaderBoardId);
        }
    } else {
        if (success) {
            CCLOG("load leader board %s success; data is %s", leaderBoardId, data);
        } else {
            CCLOG("load leader board %s fails", leaderBoardId);
        }
    }
}

// call register in your initialize function
bool HelloWorld::init() {
  ...
  IvySDK::registerLeaderBoardCallback(onReceiveLeaderboardResult);
  ...
}
```

* and you can use leaderboard now, do this:
```js
// submit user score to leaderboard named "endless"
IvySDK::submitScore("endless", 320, "");

// load first 20 leaderboard data with friends
IvySDK::loadFriendLeaderBoard("endless", 0, 20, "firend_id1,friend_id2");

// load first 20 leaderboard data among all players
IvySDK::loadGlobalLeaderBoard("endless", 0, 20);
```

8, Congratulations, done. You will see some toasts when you run your game in your android phone or emulator:
<center>![toast](assets/risesdk-cocos-a0e84.png)</center>
