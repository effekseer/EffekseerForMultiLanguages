#pragma once

#include <Effekseer.h>
#include <EffekseerRendererGL.h>
#include <array>

enum class EffekseerCoreDeviceType
{
	Unknown,
	OpenGL,
	DirectX9,
	DirectX11,
};

#if !defined(SWIG)

class EffekseerSettingCore : public ::Effekseer::Setting
{
private:
	static Effekseer::RefPtr<EffekseerSettingCore> effekseerSetting_;
	Effekseer::Backend::GraphicsDeviceRef graphicsDevice_ = nullptr;

public:
	EffekseerSettingCore(bool isSrgbMode = false);
	~EffekseerSettingCore() override;

	bool IsValid() const;

	int Release() override;

	Effekseer::Backend::GraphicsDeviceRef GetGraphicsDevice() const;

	static Effekseer::RefPtr<EffekseerSettingCore> create(bool isSrgbMode = false);
};

#endif

class EffekseerBackendCore
{
public:
	EffekseerBackendCore() = default;
	~EffekseerBackendCore() = default;

	static EffekseerCoreDeviceType GetDevice();

	static bool InitializeWithOpenGL();

#if !defined(SWIGJAVA) && !defined(SWIGPYTHON)
	static bool InitializeWithDirectX9(void* device);

	static bool InitializeWithDirectX11(void* device, void* context);
#endif
	static void Terminate();
};