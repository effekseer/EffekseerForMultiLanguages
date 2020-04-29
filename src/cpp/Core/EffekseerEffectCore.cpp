#include "effekseerEffectCore.h"
#include <assert.h>

EffekseerEffectCore::EffekseerEffectCore() {}

EffekseerEffectCore::~EffekseerEffectCore() { ES_SAFE_RELEASE(effect_); }

bool EffekseerEffectCore::Load(char* data, int len, float magnification)
{
	ES_SAFE_RELEASE(effect_);
	effect_ = ::Effekseer::Effect::Create(EffekseerSettingCore::create(), (void*)data, len, magnification);
	return effect_ != nullptr;
}

const char16_t* EffekseerEffectCore::GetTexturePath(int32_t index, EffekseerTextureType type) const
{
	if (type == EffekseerTextureType::Color)
	{
		return effect_->GetColorImagePath(index);
	}
	else if (type == EffekseerTextureType::Normal)
	{
		return effect_->GetNormalImagePath(index);
	}
	else if (type == EffekseerTextureType::Distortion)
	{
		return effect_->GetDistortionImagePath(index);
	}

	assert(0);

	return nullptr;
}

int32_t EffekseerEffectCore::GetTextureCount(EffekseerTextureType type) const
{
	if (type == EffekseerTextureType::Color)
	{
		return effect_->GetColorImageCount();
	}
	else if (type == EffekseerTextureType::Normal)
	{
		return effect_->GetNormalImageCount();
	}
	else if (type == EffekseerTextureType::Distortion)
	{
		return effect_->GetDistortionImageCount();
	}

	assert(0);

	return 0;
}

bool EffekseerEffectCore::LoadTexture(char* data, int len, int32_t index, EffekseerTextureType type)
{
	auto loader = effect_->GetSetting()->GetTextureLoader();
	if (loader == nullptr)
	{
		return false;
	}

	auto texture = loader->Load((const void*)data, len, (Effekseer::TextureType)type);

	if (texture == nullptr)
	{
		return false;
	}

	effect_->SetTexture(index, (Effekseer::TextureType)type, texture);

	return true;
}

const char16_t* EffekseerEffectCore::GetModelPath(int32_t index) const { return effect_->GetModelPath(index); }

int32_t EffekseerEffectCore::GetModelCount() const { return effect_->GetModelCount(); }

bool EffekseerEffectCore::LoadModel(char* data, int len, int32_t index)
{
	auto loader = effect_->GetSetting()->GetModelLoader();
	if (loader == nullptr)
	{
		return false;
	}

	auto model = loader->Load((const void*)data, len);

	if (model == nullptr)
	{
		return false;
	}

	effect_->SetModel(index, model);

	return true;
}

Effekseer::Effect* EffekseerEffectCore::GetInternal() const { return effect_; }