LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := game
LOCAL_CPPFLAGS  := -Wall -Wextra -std=c++14
LOCAL_SRC_FILES := ../cpp/game.cpp jni.cpp
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2

include $(BUILD_SHARED_LIBRARY)