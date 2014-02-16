LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := snake_shared

LOCAL_MODULE_FILENAME := libsnake

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorld.cpp \
                   ../../Classes/GameOverScene.cpp \
                   ../../Classes/PauseLayer.cpp \
                   ../../Classes/GlobalValue.cpp \
                   ../../Classes/Snake.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)

