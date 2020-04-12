#include "EffekseerManagerCore.h"
#include "EffekseerEffectCore.h"
#include <EffekseerRendererGL.h>

EffekseerManagerCore::~EffekseerManagerCore()
{
    if(manager_ != nullptr)
    {
        manager_->Destroy();
        manager_ = nullptr;
    }

    if(renderer_ != nullptr)
    {
       renderer_->Destroy();
       renderer_ = nullptr;
    }
}

bool EffekseerManagerCore::Initialize(int32_t spriteMaxCount)
{
    if(manager_ != nullptr || renderer_ != nullptr)
    {
        return false;
    }

    manager_ = ::Effekseer::Manager::Create(spriteMaxCount);
	renderer_ = ::EffekseerRendererGL::Renderer::Create(spriteMaxCount, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);
		
    if(manager_ == nullptr || renderer_ == nullptr)
    {
        ES_SAFE_RELEASE(manager_);
        ES_SAFE_RELEASE(renderer_);
        return false;
    }
    return true;
}

void EffekseerManagerCore::Update(float deltaFrames)
{
    if(manager_ == nullptr)
    {
        return;
    }

    deltaFrames += restDeltaTime_;
	restDeltaTime_ = deltaFrames - int(deltaFrames);
	for(int loop = 0; loop < int(deltaFrames); loop++)
	{
		manager_->Update(1);
	}
}

int EffekseerManagerCore::Play(EffekseerEffectCore *effect)
{
    if(manager_ == nullptr)
    {
        return -1;
    }

    return manager_->Play(effect->GetInternal(), ::Effekseer::Vector3D());
}