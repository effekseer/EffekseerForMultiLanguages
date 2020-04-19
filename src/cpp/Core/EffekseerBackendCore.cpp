#include "EffekseerBackendCore.h"
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

class CustomTextureLoader : public Effekseer::TextureLoader
{
public:
	CustomTextureLoader() = default;
	~CustomTextureLoader() = default;

public:
	Effekseer::TextureData* Load(const EFK_CHAR* path, Effekseer::TextureType textureType) override
	{
		// Invalid
		return nullptr;
	}
};

EffekseerSettingCore* EffekseerSettingCore::effekseerSetting_ = nullptr;

EffekseerSettingCore::EffekseerSettingCore() { SetTextureLoader(new CustomTextureLoader()); }

EffekseerSettingCore::~EffekseerSettingCore() { effekseerSetting_ = nullptr; }

EffekseerSettingCore* EffekseerSettingCore::create()
{
	if (effekseerSetting_ == nullptr)
	{
		effekseerSetting_ = new EffekseerSettingCore();
	}
	else
	{
		effekseerSetting_->AddRef();
	}

	return effekseerSetting_;
}

EffekseerCoreDeviceType EffekseerBackendCore::deviceType_ = EffekseerCoreDeviceType::Unknown;
EffekseerSettingCore* EffekseerBackendCore::setting_ = nullptr;

EffekseerCoreDeviceType EffekseerBackendCore::GetDevice() { return deviceType_; }

bool EffekseerBackendCore::InitializeAsOpenGL()
{
	deviceType_ = EffekseerCoreDeviceType::OpenGL;
	return true;
}

void EffekseerBackendCore::Terminate() {}
