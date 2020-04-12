#pragma once

#include "EffekseerBackendCore.h"

class EffekseerEffectCore
{
private:
	Effekseer::Effect* effect_ = nullptr;

public:
	EffekseerEffectCore();
	~EffekseerEffectCore();

	bool Load(char* data, int len, float magnification);

	/**
	 * TODO : imeplement a funtions to load resources
	 * Plan
	 * Load -> only load effect binary
	 * Get internal path for resources and assign resouces
	 */

#if !defined(SWIG)
	Effekseer::Effect* GetInternal() const;
#endif
};