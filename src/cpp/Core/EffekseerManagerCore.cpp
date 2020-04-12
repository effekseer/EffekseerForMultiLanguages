#include "EffekseerManagerCore.h"
#include "EffekseerEffectCore.h"
#include <EffekseerRendererGL.h>

EffekseerManagerCore::~EffekseerManagerCore()
{
	if (manager_ != nullptr)
	{
		manager_->Destroy();
		manager_ = nullptr;
	}

	if (renderer_ != nullptr)
	{
		renderer_->Destroy();
		renderer_ = nullptr;
	}
}

bool EffekseerManagerCore::Initialize(int32_t spriteMaxCount)
{
	if (manager_ != nullptr || renderer_ != nullptr)
	{
		return false;
	}

	manager_ = ::Effekseer::Manager::Create(spriteMaxCount);
	renderer_ = ::EffekseerRendererGL::Renderer::Create(spriteMaxCount, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);

	if (manager_ == nullptr || renderer_ == nullptr)
	{
		ES_SAFE_RELEASE(manager_);
		ES_SAFE_RELEASE(renderer_);
		return false;
	}
	return true;
}

void EffekseerManagerCore::Update(float deltaFrames)
{
	if (manager_ == nullptr)
	{
		return;
	}

	deltaFrames += restDeltaTime_;
	restDeltaTime_ = deltaFrames - int(deltaFrames);
	for (int loop = 0; loop < int(deltaFrames); loop++)
	{
		manager_->Update(1);
	}
}

int EffekseerManagerCore::Play(EffekseerEffectCore* effect)
{
	if (manager_ == nullptr)
	{
		return -1;
	}

	return manager_->Play(effect->GetInternal(), ::Effekseer::Vector3D());
}

void EffekseerManagerCore::DrawBack()
{
	if (manager_ == nullptr)
	{
		return;
	}

	renderer_->BeginRendering();
	manager_->DrawBack();
	renderer_->EndRendering();
}

void EffekseerManagerCore::DrawFront()
{
	if (manager_ == nullptr)
	{
		return;
	}

	renderer_->BeginRendering();
	manager_->DrawFront();
	renderer_->EndRendering();
}

void EffekseerManagerCore::SetViewProjectionMatrixWithSimpleWindow(int32_t windowWidth, int32_t windowHeight)
{
	if (manager_ == nullptr)
	{
		return;
	}

	renderer_->SetProjectionMatrix(
		::Effekseer::Matrix44().OrthographicRH(static_cast<float>(windowWidth), static_cast<float>(windowHeight), 1.0f, 400.0f));

	renderer_->SetCameraMatrix(::Effekseer::Matrix44().LookAtRH(::Effekseer::Vector3D(windowWidth / 2.0f, -windowHeight / 2.0f, -200.0f),
																::Effekseer::Vector3D(windowWidth / 2.0f, -windowHeight / 2.0f, 200.0f),
																::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}