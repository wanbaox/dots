LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/AudioHelper.cpp \
                   ../../Classes/CCLocalizedString.cpp \
                   ../../Classes/DataController.cpp \
                   ../../Classes/DataHandle.cpp \
                   ../../Classes/DataHandle4NoTimeLimit.cpp \
                   ../../Classes/DataHandle4NoTimeLimit1Tap.cpp \
                   ../../Classes/DataHandle4Tap.cpp \
                   ../../Classes/DataHandleClassic.cpp \
                   ../../Classes/DotGameScene.cpp \
                   ../../Classes/DotHudController.cpp \
                   ../../Classes/DotPlayingScene.cpp \
                   ../../Classes/DownStateLayer.cpp \
                   ../../Classes/DrawSprite.cpp \
                   ../../Classes/FailLayer.cpp \
                   ../../Classes/IntroLayer.cpp \
                   ../../Classes/LevelGoalAlertLayer.cpp \
                   ../../Classes/NormalEndLayer.cpp \
                   ../../Classes/SettingScene.cpp \
                   ../../Classes/SettingHelper.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/TableLayer.cpp \
                   ../../Classes/TopScoreLayer.cpp \
                   ../../Classes/UpStateLayer.cpp \
                   ../../Classes/XYCUtils.cpp 
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,CocosDenshion/android)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
