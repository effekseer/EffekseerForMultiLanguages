#include "EffekseerBackendCore.h"
#include <Effekseer.h>
#include <EffekseerRendererGL.h>

class CustomTextureLoader : public Effekseer::TextureLoader
{
	Effekseer::TextureLoader* internalLoader_ = nullptr;

public:
	CustomTextureLoader(bool isSrgbMode=false) { internalLoader_ = EffekseerRendererGL::CreateTextureLoader(nullptr,isSrgbMode?Effekseer::ColorSpaceType::Linear:Effekseer::ColorSpaceType::Gamma); }

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

class CustomModelLoader : public Effekseer::ModelLoader
{
	Effekseer::ModelLoader* internalLoader_ = nullptr;

public:
	CustomModelLoader() { internalLoader_ = EffekseerRendererGL::CreateModelLoader(); }

	~CustomModelLoader() { ES_SAFE_DELETE(internalLoader_); }

public:
	Effekseer::Model* Load(const EFK_CHAR* path) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::Model* Load(const void* data, int32_t size) override { return internalLoader_->Load(data, size); }

	void Unload(Effekseer::Model* data) override { internalLoader_->Unload(data); }
};

class CustomMaterialLoader : public Effekseer::MaterialLoader
{
	Effekseer::MaterialLoader* internalLoader_ = nullptr;

public:
	CustomMaterialLoader(EffekseerRenderer::GraphicsDevice* graphicsDevice)
	{
		internalLoader_ = EffekseerRendererGL::CreateMaterialLoader(graphicsDevice);
	}

	~CustomMaterialLoader() { ES_SAFE_DELETE(internalLoader_); }

public:
	Effekseer::MaterialData* Load(const EFK_CHAR* path) override
	{
		// Invalid
		return nullptr;
	}

	Effekseer::MaterialData* Load(const void* data, int32_t size, Effekseer::MaterialFileType fileType) override
	{
		return internalLoader_->Load(data, size, fileType);
	}

	void Unload(Effekseer::MaterialData* data) override { internalLoader_->Unload(data); }
};

EffekseerSettingCore* EffekseerSettingCore::effekseerSetting_ = nullptr;

EffekseerSettingCore::EffekseerSettingCore(bool isSrgbMode)
{
	graphicsDevice_ = EffekseerRendererGL::CreateDevice(EffekseerRendererGL::OpenGLDeviceType::OpenGL3);

	SetTextureLoader(new CustomTextureLoader(isSrgbMode));
	SetModelLoader(new CustomModelLoader());
	SetMaterialLoader(new CustomMaterialLoader(graphicsDevice_));
}

EffekseerSettingCore::~EffekseerSettingCore()
{
	ES_SAFE_RELEASE(graphicsDevice_);
	effekseerSetting_ = nullptr;
}

EffekseerRenderer::GraphicsDevice* EffekseerSettingCore::GetGraphicsDevice() const { return graphicsDevice_; }

EffekseerSettingCore* EffekseerSettingCore::create(bool isSrgbMode)
{
	if (effekseerSetting_ == nullptr)
	{
		effekseerSetting_ = new EffekseerSettingCore(isSrgbMode);
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
