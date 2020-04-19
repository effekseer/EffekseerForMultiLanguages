#pragma once

#include "EffekseerBackendCore.h"

enum class EffekseerTextureType
{
	Color,
	Normal,
	Distortion,
};

class EffekseerEffectCore
{
private:
	Effekseer::Effect* effect_ = nullptr;

public:
	EffekseerEffectCore();
	~EffekseerEffectCore();

	bool Load(char* data, int len, float magnification);

	const char16_t* GetTexturePath(int32_t index, EffekseerTextureType type) const;

	int32_t GetTextureCount(EffekseerTextureType type) const;

	bool LoadTexture(char* data, int len, int32_t index, EffekseerTextureType type);

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