# This is the jni directory.
LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/localgen.mk

NDK_TOOLCHAIN_VERSION := 4.8
TARGET_ARCH_ABI := armeabi-v7a
APP_PLATFORM := android-12
APP_CPPFLAGS += $(CMAKE_CXX_FLAGS)
APP_ABI := $(TARGET_ARCH_ABI)
APP_STL := gnustl_static
LOCAL_C_INCLUDES += $(TOOLCHAIN_DIR)/sources/cxx-stl/gnu-libstdc++/4.8/include
