#include "EffekseerBackendCore.h"
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

class CustomTextureLoader : public Effekseer::TextureLoader
{
	Effekseer::TextureLoader* internalLoader_ = nullptr;

public:
	CustomTextureLoader() { internalLoader_ = EffekseerRendererGL::CreateTextureLoader(); }

	~CustomTextureLoader() { ES_SAFE_DELETE(internalLoader_); }

public:
	Effekseer::TextureData* Load(const EFK_CHAR* path, Effekseer::TextureType textureType) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::TextureData* Load(const void* data, int32_t size, Effekseer::TextureType textureType) override
	{
		return internalLoader_->Load(data, size, textureType);
	}

	void Unload(Effekseer::TextureData* data) override { internalLoader_->Unload(data); }
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
