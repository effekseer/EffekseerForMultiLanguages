#include "EffekseerManagerCore.h"
#include "EffekseerBackendCore.h"
#include "EffekseerEffectCore.h"
#include <EffekseerRendererGL.h>
#include "EffekseerRenderer/GraphicsDevice.h"

inline void matrixFromValues(::Effekseer::Matrix44& matrix, 
	float matrixArray0,
	float matrixArray1,
	float matrixArray2,
	float matrixArray3,
	float matrixArray4,
	float matrixArray5,
	float matrixArray6,
	float matrixArray7,
	float matrixArray8,
	float matrixArray9,
	float matrixArray10,
	float matrixArray11,
	float matrixArray12,
	float matrixArray13,
	float matrixArray14,
	float matrixArray15
)
{
	matrix.Values[0][0] = matrixArray0;
	matrix.Values[1][0] = matrixArray1;
	matrix.Values[2][0] = matrixArray2;
	matrix.Values[3][0] = matrixArray3;
	matrix.Values[0][1] = matrixArray4;
	matrix.Values[1][1] = matrixArray5;
	matrix.Values[2][1] = matrixArray6;
	matrix.Values[3][1] = matrixArray7;
	matrix.Values[0][2] = matrixArray8;
	matrix.Values[1][2] = matrixArray9;
	matrix.Values[2][2] = matrixArray10;
	matrix.Values[3][2] = matrixArray11;
	matrix.Values[0][3] = matrixArray12;
	matrix.Values[1][3] = matrixArray13;
	matrix.Values[2][3] = matrixArray14;
	matrix.Values[3][3] = matrixArray15;
}



inline void matrixFromValues(::Effekseer::Matrix43& matrix, 
	float matrixArray0,
	float matrixArray1,
	float matrixArray2,
	float matrixArray3,
	float matrixArray4,
	float matrixArray5,
	float matrixArray6,
	float matrixArray7,
	float matrixArray8,
	float matrixArray9,
	float matrixArray10,
	float matrixArray11
)
{
	matrix.Value[0][0] = matrixArray0;
	matrix.Value[1][0] = matrixArray1;
	matrix.Value[2][0] = matrixArray2;
	matrix.Value[3][0] = matrixArray3;

	matrix.Value[0][1] = matrixArray4;
	matrix.Value[1][1] = matrixArray5;
	matrix.Value[2][1] = matrixArray6;
	matrix.Value[3][1] = matrixArray7;

	matrix.Value[0][2] = matrixArray8;
	matrix.Value[1][2] = matrixArray9;
	matrix.Value[2][2] = matrixArray10;
	matrix.Value[3][2] = matrixArray11;
}


EffekseerManagerCore::~EffekseerManagerCore()
{
	manager_.Reset();
	renderer_.Reset();
}

bool EffekseerManagerCore::Initialize(int32_t spriteMaxCount, bool srgbMode )
{
	if (manager_ != nullptr || renderer_ != nullptr)
	{
		return false;
	}
	auto setting = EffekseerSettingCore::create(srgbMode);
	if (setting == nullptr)
	{
		Effekseer::Log(Effekseer::LogType::Error, "Failed to initialize EffekseerManagerCore : GraphicsError");
		return false;
	}

	manager_ = ::Effekseer::Manager::Create(spriteMaxCount);
	renderer_ = ::EffekseerRendererGL::Renderer::Create(spriteMaxCount, EffekseerRendererGL::OpenGLDeviceType::OpenGL3);

	if (manager_ == nullptr || renderer_ == nullptr)
	{
		manager_.Reset();
		renderer_.Reset();
		Effekseer::Log(Effekseer::LogType::Error, "Failed to initialize EffekseerManagerCore : RendererError");
		return false;
	}

	manager_->SetSetting(setting);

	manager_->SetSpriteRenderer(renderer_->CreateSpriteRenderer());
	manager_->SetRibbonRenderer(renderer_->CreateRibbonRenderer());
	manager_->SetRingRenderer(renderer_->CreateRingRenderer());
	manager_->SetTrackRenderer(renderer_->CreateTrackRenderer());
	manager_->SetModelRenderer(renderer_->CreateModelRenderer());

	return true;
}

void EffekseerManagerCore::BeginUpdate()
{
	if (manager_ == nullptr)
	{
		return;
	}

	manager_->BeginUpdate();

}

void EffekseerManagerCore::EndUpdate()
{
	if (manager_ == nullptr)
	{
		return;
	}

	manager_->EndUpdate();

}

void EffekseerManagerCore::UpdateHandleToMoveToFrame(int handle,float v){
	if (manager_ == nullptr)
	{
		return;
	}

	manager_->UpdateHandleToMoveToFrame(handle,v);
}


void EffekseerManagerCore::UnsetBackground(){
	renderer_->SetBackground(nullptr);
}

void EffekseerManagerCore::SetBackground(uint32_t glid,bool hasMipmap){
	if(backgroundtx_==nullptr){
		backgroundtx_=::EffekseerRendererGL::CreateTexture(renderer_->GetGraphicsDevice(),glid,hasMipmap,nullptr);
	}
	auto texture = static_cast<::EffekseerRendererGL::Backend::Texture*>(backgroundtx_.Get());
	texture->Init(glid, hasMipmap, nullptr);
	renderer_->SetBackground(backgroundtx_);
}

void EffekseerManagerCore::SetDepth(uint32_t glid, bool hasMipmap){
	if(depthtx_==nullptr){
		depthtx_=::EffekseerRendererGL::CreateTexture(renderer_->GetGraphicsDevice(),glid,hasMipmap,nullptr);
	}else{
		auto texture = static_cast<::EffekseerRendererGL::Backend::Texture*>(depthtx_.Get());
		texture->Init(glid, hasMipmap, nullptr);
	}

	auto projMat = renderer_->GetProjectionMatrix();

	::EffekseerRenderer::DepthReconstructionParameter params;	
	params.DepthBufferScale = 1.0f;
	params.DepthBufferOffset = 0.0f;		

	params.ProjectionMatrix33 = projMat.Values[2][2];
	params.ProjectionMatrix43 = projMat.Values[2][3];
	params.ProjectionMatrix34 = projMat.Values[3][2];
	params.ProjectionMatrix44 = projMat.Values[3][3];

	renderer_->SetDepth(depthtx_,params);	
}

void EffekseerManagerCore::UnsetDepth(){
	::EffekseerRenderer::DepthReconstructionParameter params;
	renderer_->SetDepth(nullptr,params);	
}

void EffekseerManagerCore::LaunchWorkerThreads(int32_t n){
	manager_->LaunchWorkerThreads(n);
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

void EffekseerManagerCore::StopAllEffects()
{
	return manager_->StopAllEffects();
}

void EffekseerManagerCore::Stop(int handle)
{
	return manager_->StopEffect(handle);
}

void EffekseerManagerCore::SetShown(int handle, bool v)
{
	return manager_->SetShown(handle,v);
}

void EffekseerManagerCore::SetEffectPosition(int handle, float x, float y, float z)
{
	manager_->SetLocation(handle, x, y, z);
}

void EffekseerManagerCore::SetEffectRotation(int handle, float x, float y, float z)
{
	manager_->SetRotation(handle, x, y, z);
}

void EffekseerManagerCore::SetEffectScale(int handle, float x, float y, float z)
{
	manager_->SetScale(handle, x, y, z);
}

void EffekseerManagerCore::SetEffectTransformMatrix(int handle, float v0,float v1,float v2,float v3,float v4,float v5,float v6,float v7,float v8,float v9,float v10,float v11)
{
	::Effekseer::Matrix43 m=::Effekseer::Matrix43();
	matrixFromValues(m,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11);		
	manager_->SetMatrix(handle,m);
}


void EffekseerManagerCore::SetEffectTransformBaseMatrix(int handle, float v0,float v1,float v2,float v3,float v4,float v5,float v6,float v7,float v8,float v9,float v10,float v11)
{
	::Effekseer::Matrix43 m=::Effekseer::Matrix43();
	matrixFromValues(m,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11);		
	manager_->SetBaseMatrix(handle,m);
}

void EffekseerManagerCore::SetPaused(int handle, bool v)
{
	manager_->SetPaused(handle,v);
}

void EffekseerManagerCore::DrawBack(int layer)
{
	if (manager_ == nullptr)
	{
		return;
	}

	renderer_->BeginRendering();
	
	Effekseer::Manager::DrawParameter params;
	params.CameraCullingMask=layer;
	manager_->DrawBack(params);	
	
	renderer_->EndRendering();
}

void EffekseerManagerCore::DrawFront(int layer)
{
	if (manager_ == nullptr)
	{
		return;
	}
	
	renderer_->BeginRendering();
	
	Effekseer::Manager::DrawParameter params;
	params.CameraCullingMask=layer;
	manager_->DrawFront(params);

	renderer_->EndRendering();
}

void EffekseerManagerCore::SetLayer(int handle,int layer)
{
	return manager_->SetLayer(handle,layer);
}

bool EffekseerManagerCore::Exists(int handle)
{
	return manager_->Exists(handle);
}


void EffekseerManagerCore::SetProjectionMatrix(float v0,float v1,float v2,float v3,float v4,float v5,float v6,float v7,float v8,float v9,float v10,float v11,float v12,float v13,float v14,float v15)
{
	if (manager_ == nullptr)
	{
		return;
	}

	::Effekseer::Matrix44 m=::Effekseer::Matrix44();
	matrixFromValues(m,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);		
	renderer_->SetProjectionMatrix(m);
}
	
void EffekseerManagerCore::SetCameraMatrix(float v0,float v1,float v2,float v3,float v4,float v5,float v6,float v7,float v8,float v9,float v10,float v11,float v12,float v13,float v14,float v15)
{
	if (manager_ == nullptr)
	{
		return;
	}

	::Effekseer::Matrix44 m=::Effekseer::Matrix44();
	matrixFromValues(m,v0,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10,v11,v12,v13,v14,v15);		
	renderer_->SetCameraMatrix(m);
}

void EffekseerManagerCore::SetViewProjectionMatrixWithSimpleWindow(int32_t windowWidth, int32_t windowHeight)
{
	if (manager_ == nullptr)
	{
		return;
	}

	renderer_->SetProjectionMatrix(
		::Effekseer::Matrix44().OrthographicRH(static_cast<float>(windowWidth), static_cast<float>(windowHeight), 1.0f, 400.0f));

	renderer_->SetCameraMatrix(::Effekseer::Matrix44().LookAtRH(::Effekseer::Vector3D(windowWidth / 2.0f, windowHeight / 2.0f, 200.0f),
																::Effekseer::Vector3D(windowWidth / 2.0f, windowHeight / 2.0f, -200.0f),
																::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));
}

	void EffekseerManagerCore::SetDynamicInput(int handle,int32_t index,float value){
		manager_->SetDynamicInput(handle,index,value);
	}

	float EffekseerManagerCore::GetDynamicInput(int handle,int32_t index){
		return manager_->GetDynamicInput(handle,index);
	}

