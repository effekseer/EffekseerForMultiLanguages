#pragma once

#include "EffekseerBackendCore.h"

class EffekseerEffectCore;

namespace EffekseerRenderer
{
class Renderer;
}

class EffekseerManagerCore
{
private:
	::Effekseer::Manager* manager_ = nullptr;
	::EffekseerRenderer::Renderer* renderer_ = nullptr;
	float restDeltaTime_ = 0.0f;

public:
	EffekseerManagerCore() = default;
	~EffekseerManagerCore();

	bool Initialize(int32_t spriteMaxCount);

	void Update(float deltaFrames);

	int Play(EffekseerEffectCore* effect);

	void SetEffectPosition(int handle, float x, float y, float z);

	void DrawBack();

	void DrawFront();

	void SetViewProjectionMatrixWithSimpleWindow(int32_t windowWidth, int32_t windowHeight);
};