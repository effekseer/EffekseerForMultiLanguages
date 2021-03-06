#include "EffekseerEffectCore.h"
#include <assert.h>

EffekseerEffectCore::EffekseerEffectCore() {}

EffekseerEffectCore::~EffekseerEffectCore() {}

bool EffekseerEffectCore::Load(char* data, int len, float magnification) { return Load((const unsigned char*)data, len, magnification); }

bool EffekseerEffectCore::Load(const unsigned char* data, int len, float magnification)
{
	effect_ = ::Effekseer::Effect::Create(EffekseerSettingCore::create().DownCast<Effekseer::Setting>(), (void*)data, len, magnification);
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
	return LoadTexture((const unsigned char*)data, len, index, type);
}

bool EffekseerEffectCore::LoadTexture(const unsigned char* data, int len, int32_t index, EffekseerTextureType type)
{
	auto loader = effect_->GetSetting()->GetTextureLoader();
	if (loader == nullptr)
	{
		return false;
	}

	auto texture = loader->Load((const void*)data, len, (Effekseer::TextureType)type, true);

	if (texture == nullptr)
	{
		return false;
	}

	effect_->SetTexture(index, (Effekseer::TextureType)type, texture);

	return true;
}

bool EffekseerEffectCore::HasTextureLoaded(int32_t index, EffekseerTextureType type)
{
	if (type != EffekseerTextureType::Color)
		return effect_->GetColorImage(index) != nullptr;

	if (type != EffekseerTextureType::Normal)
		return effect_->GetNormalImage(index) != nullptr;

	if (type != EffekseerTextureType::Distortion)
		return effect_->GetDistortionImage(index) != nullptr;

	return false;
}

const char16_t* EffekseerEffectCore::GetModelPath(int32_t index) const { return effect_->GetModelPath(index); }

int32_t EffekseerEffectCore::GetModelCount() const { return effect_->GetModelCount(); }

bool EffekseerEffectCore::LoadModel(char* data, int len, int32_t index) { return LoadModel((const unsigned char*)data, len, index); }

bool EffekseerEffectCore::LoadModel(const unsigned char* data, int len, int32_t index)
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

bool EffekseerEffectCore::HasModelLoaded(int32_t index) { return effect_->GetModel(index) != nullptr; }

const char16_t* EffekseerEffectCore::GetMaterialPath(int32_t index) const { return effect_->GetMaterialPath(index); }

int32_t EffekseerEffectCore::GetMaterialCount() const { return effect_->GetMaterialCount(); }

bool EffekseerEffectCore::LoadMaterial(char* data, int len, int32_t index) { return LoadMaterial((const unsigned char*)data, len, index); }

bool EffekseerEffectCore::LoadMaterial(const unsigned char* data, int len, int32_t index)
{
	auto loader = effect_->GetSetting()->GetMaterialLoader();
	if (loader == nullptr)
	{
		return false;
	}

	auto material = loader->Load((const void*)data, len, Effekseer::MaterialFileType::Code);

	if (material == nullptr)
	{
		return false;
	}

	effect_->SetMaterial(index, material);

	return true;
}

bool EffekseerEffectCore::HasMaterialLoaded(int32_t index) { return effect_->GetMaterial(index) != nullptr; }

const char16_t* EffekseerEffectCore::GetCurvePath(int32_t index) const { return effect_->GetCurvePath(index); }

int32_t EffekseerEffectCore::GetCurveCount() const { return effect_->GetCurveCount(); }

bool EffekseerEffectCore::LoadCurve(char* data, int len, int32_t index) { return LoadCurve((const unsigned char*)data, len, index); }

bool EffekseerEffectCore::LoadCurve(const unsigned char* data, int len, int32_t index)
{
	auto loader = effect_->GetSetting()->GetCurveLoader();
	if (loader == nullptr)
	{
		return false;
	}

	auto curve = loader->Load((const void*)data, len);

	if (curve == nullptr)
	{
		return false;
	}

	effect_->SetCurve(index, curve);

	return true;
}

bool EffekseerEffectCore::HasCurveLoaded(int32_t index) { return effect_->GetCurve(index) != nullptr; }

Effekseer::EffectRef EffekseerEffectCore::GetInternal() const { return effect_; }

int32_t EffekseerEffectCore::GetTermMax()
{
	Effekseer::EffectTerm t = effect_->CalculateTerm();
	return t.TermMax;
}

int32_t EffekseerEffectCore::GetTermMin()
{
	Effekseer::EffectTerm t = effect_->CalculateTerm();
	return t.TermMin;
}