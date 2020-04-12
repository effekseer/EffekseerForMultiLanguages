#include "EffekseerBackendCore.h"
#include <EffekseerRendererGL.h>

EffekseerSettingCore* EffekseerSettingCore::effekseerSetting_ = nullptr;

EffekseerSettingCore::EffekseerSettingCore() {}

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

bool EffekseerBackendCore::InitializeAsOpenGL() { return false; }

void EffekseerBackendCore::Terminate() {}
