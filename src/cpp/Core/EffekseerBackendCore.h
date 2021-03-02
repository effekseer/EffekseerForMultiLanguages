#pragma once

#include <Effekseer.h>
#include <EffekseerRendererGL.h>

enum class EffekseerCoreDeviceType
{
	Unknown,
	OpenGL,
};

#if !defined(SWIG)

class EffekseerSettingCore : public ::Effekseer::Setting
{
private:
	static Effekseer::RefPtr<EffekseerSettingCore> effekseerSetting_;
	Effekseer::Backend::GraphicsDeviceRef graphicsDevice_ = nullptr;

public:
	EffekseerSettingCore(bool isSrgbMode=false);
	~EffekseerSettingCore() override;

	int Release() override;

	Effekseer::Backend::GraphicsDeviceRef GetGraphicsDevice() const;

	static Effekseer::RefPtr<EffekseerSettingCore> create(bool isSrgbMode = false);
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