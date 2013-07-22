LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

LOCAL_SRC_FILES := cmugen/main.cpp \
                   ../Classes/AppDelegate.cpp \
                   ../Classes/layer/GameLayer.cpp \
                   ../Classes/layer/HudLayer.cpp \
                   ../Classes/layer/StartupLayer.cpp \
                   ../Classes/sprite/ActionSprite.cpp \
                   ../Classes/sprite/Ichigo.cpp \
                   ../Classes/sprite/Saber.cpp \
                   ../Classes/sprite/HollowInvasionOne.cpp \
                   ../Classes/scene/StartupScene.cpp \
                   ../Classes/scene/GameScene.cpp \
                   ../Classes/Sneaky/SneakyButton.cpp \
                   ../Classes/Sneaky/SneakyButtonSkinnedBase.cpp \
                   ../Classes/Sneaky/SneakyJoystick.cpp \
                   ../Classes/Sneaky/SneakyJoystickSkinnedBase.cpp \
                   ../Classes/Sneaky/SneakyJoystickExt.cpp 
                   
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android)
$(call import-module,cocos2dx)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)