#include "EffekseerBackendCore.h"
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

class CustomTextureLoader : public Effekseer::TextureLoader
{
	Effekseer::TextureLoaderRef internalLoader_ = nullptr;

public:
	CustomTextureLoader(Effekseer::Backend::GraphicsDeviceRef graphicsDevice, bool isSrgbMode = false)
	{
		internalLoader_ = EffekseerRendererGL::CreateTextureLoader(
			graphicsDevice, nullptr, isSrgbMode ? Effekseer::ColorSpaceType::Linear : Effekseer::ColorSpaceType::Gamma);
	}

	~CustomTextureLoader() override = default;

public:
	Effekseer::TextureRef Load(const EFK_CHAR* path, Effekseer::TextureType textureType) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::TextureRef Load(const void* data, int32_t size, Effekseer::TextureType textureType, bool isMipMapEnabled) override
	{
		return internalLoader_->Load(data, size, textureType, isMipMapEnabled);
	}

	void Unload(Effekseer::TextureRef data) override { internalLoader_->Unload(data); }
};

class CustomModelLoader : public Effekseer::ModelLoader
{
	Effekseer::ModelLoaderRef internalLoader_ = nullptr;

public:
	CustomModelLoader() { internalLoader_ = EffekseerRendererGL::CreateModelLoader(); }

	~CustomModelLoader() override = default;

public:
	Effekseer::ModelRef Load(const EFK_CHAR* path) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::ModelRef Load(const void* data, int32_t size) override { return internalLoader_->Load(data, size); }

	void Unload(Effekseer::ModelRef data) override { internalLoader_->Unload(data); }
};

class CustomMaterialLoader : public Effekseer::MaterialLoader
{
	Effekseer::MaterialLoaderRef internalLoader_ = nullptr;

public:
	CustomMaterialLoader(Effekseer::Backend::GraphicsDeviceRef graphicsDevice)
	{
		internalLoader_ = EffekseerRendererGL::CreateMaterialLoader(graphicsDevice);
	}

	~CustomMaterialLoader() override = default;

public:
	Effekseer::MaterialRef Load(const EFK_CHAR* path) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::MaterialRef Load(const void* data, int32_t size, Effekseer::MaterialFileType fileType) override
	{
		return internalLoader_->Load(data, size, fileType);
	}

	void Unload(Effekseer::MaterialRef data) override { internalLoader_->Unload(data); }
};

Effekseer::RefPtr<EffekseerSettingCore> EffekseerSettingCore::effekseerSetting_ = nullptr;

EffekseerSettingCore::EffekseerSettingCore(bool isSrgbMode)
{
	graphicsDevice_ = EffekseerRendererGL::CreateGraphicsDevice(EffekseerRendererGL::OpenGLDeviceType::OpenGL3);

	SetTextureLoader(Effekseer::MakeRefPtr<CustomTextureLoader>(graphicsDevice_, isSrgbMode));
	SetModelLoader(Effekseer::MakeRefPtr<CustomModelLoader>());
	SetMaterialLoader(Effekseer::MakeRefPtr<CustomMaterialLoader>(graphicsDevice_));
}

EffekseerSettingCore::~EffekseerSettingCore()
{
	graphicsDevice_.Reset();
	effekseerSetting_ = nullptr;
}

int EffekseerSettingCore::Release()
{
	auto ret = ::Effekseer::Setting::Release();
	if (ret == 1)
	{
		effekseerSetting_ = nullptr;
	}

	return ret;
}

Effekseer::Backend::GraphicsDeviceRef EffekseerSettingCore::GetGraphicsDevice() const { return graphicsDevice_; }

Effekseer::RefPtr<EffekseerSettingCore> EffekseerSettingCore::create(bool isSrgbMode)
{
	if (effekseerSetting_ == nullptr)
	{
		effekseerSetting_ = Effekseer::MakeRefPtr<EffekseerSettingCore>(isSrgbMode);
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
