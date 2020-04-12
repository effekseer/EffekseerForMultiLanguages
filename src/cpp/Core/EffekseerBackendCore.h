#pragma once

#include <Effekseer.h>

enum class EffekseerCoreDeviceType
{
    Unknown,
    OpenGL,
}; 

#if !defined(SWIG)

class EffekseerSettingCore : public ::Effekseer::Setting
{
private:
    static EffekseerSettingCore* effekseerSetting_;
public:
    EffekseerSettingCore();
    ~EffekseerSettingCore();
    static EffekseerSettingCore* create();
};

#endif

class EffekseerBackendCore
{
    static EffekseerCoreDeviceType deviceType_;
    static EffekseerSettingCore* setting_;
public:
    EffekseerBackendCore() = default;
    ~EffekseerBackendCore() = default;

    static EffekseerCoreDeviceType GetDevice();

    static bool InitializeAsOpenGL();

    static void Terminate();
};