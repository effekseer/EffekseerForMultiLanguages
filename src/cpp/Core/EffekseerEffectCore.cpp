#include "effekseerEffectCore.h"

EffekseerEffectCore::EffekseerEffectCore() {}

EffekseerEffectCore::~EffekseerEffectCore() { ES_SAFE_RELEASE(effect_); }

bool EffekseerEffectCore::Load(char* data, int len, float magnification)
{
	ES_SAFE_RELEASE(effect_);
	effect_ = ::Effekseer::Effect::Create(EffekseerSettingCore::create(), (void*)data, len, magnification);
	return effect_ != nullptr;
}

Effekseer::Effect* EffekseerEffectCore::GetInternal() const { return effect_; }