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
	static EffekseerSettingCore* effekseerSetting_;
	EffekseerRenderer::GraphicsDevice* graphicsDevice_ = nullptr;

public:
	EffekseerSettingCore(bool isSrgbMode=false);
	~EffekseerSettingCore();
	EffekseerRenderer::GraphicsDevice* GetGraphicsDevice() const;

	static EffekseerSettingCore* create(bool isSrgbMode=false);
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