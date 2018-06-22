#include "stdafx.h"
#include "ObjModel.h"
#include "ObjLoader.h"

using namespace Engine::Rendering;

ObjModel::ObjModel(const std::string & modelName,bool dp):
	depthTest_ { dp }
{
	const auto obj = Engine::Rendering::LoadObjModel(modelName);
	
	vbo_ = Engine::Rendering::VertexIn::CreateVBuffer(std::get<0>(obj));
	ibo_ = Engine::Rendering::VertexIn::CreateIBuffer(std::get<1>(obj).data(), std::get<1>(obj).size());
	ibSize_ = std::get<1>(obj).size();

	ps_ = Engine::Rendering::LoadPShader("CubeModel");
	gs_ = Engine::Rendering::LoadGShader("NormalCalc");

	Engine::Rendering::Transform tsfcpu;
	tsfcpu.prj = Engine::GetDevice().Perspective();

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0, 0, 50.0f, 0);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(0, 0, -1, 0);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);

	tsfcpu.view = DirectX::XMMatrixLookAtLH(eye,focus,up);
	tsfcpu.world = DirectX::XMMatrixIdentity();

	tsf_ = Engine::Rendering::CreateConstantBuffer(tsfcpu);

	PSCB pscb;
	gscb_ = Engine::Rendering::CreateConstantBuffer(pscb);
}

void ObjModel::Draw() const
{
	auto& d = Engine::GetDevice();
	d.Context().VSSetConstantBuffers(0, 1, tsf_.GetAddressOf());
	d.Context().GSSetShader(gs_.Get(), nullptr, 0);
	d.Context().PSSetShader(ps_.Get(), nullptr, 0);
	d.Context().PSSetConstantBuffers(0, 1, gscb_.GetAddressOf());
	constexpr float col[] = { 0,0,0,0 };


	auto buf = vbo_.Get();
	const UINT stride[] = { sizeof(Engine::Rendering::VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().IASetIndexBuffer(ibo_.Get(), DXGI_FORMAT_R32_UINT, 0);
	d.DepthTest(depthTest_);
	d.Context().DrawIndexed(ibSize_, 0,0);
	d.DepthTest(false);
	d.Context().GSSetShader(nullptr, nullptr, 0);
	d.Context().GSSetConstantBuffers(0, 0, nullptr);

	d.Context().IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
}

void ObjModel::Update(float d)
{
	lightPower_.Update(d);
	alpha_.Update(d);

	Engine::Rendering::Transform tsfcpu;
	tsfcpu.prj = Engine::GetDevice().Perspective();

	const DirectX::XMVECTOR eye = DirectX::XMVectorSet(0, 0, 80.0f, 0);
	const DirectX::XMVECTOR focus = DirectX::XMVectorSet(0, 0, -1, 0);
	const DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);

	timer_ += d;


	tsfcpu.view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	tsfcpu.world = 
		DirectX::XMMatrixTranslation(centerOffset_.x, centerOffset_.y, centerOffset_.z) *
		DirectX::XMMatrixScaling(scale_,scale_,scale_) * 
		DirectX::XMMatrixRotationY(rotY_) * 
		DirectX::XMMatrixRotationX(rotX_) * 
		DirectX::XMMatrixRotationZ(rotZ_);

	Engine::Rendering::UpdateCBuffer(tsf_, tsfcpu.Transpose());

	PSCB pscb;
	pscb.eyepos = eye;
	pscb.lightPower = lightPower_;
	pscb.alpha = alpha_;

	Engine::Rendering::UpdateCBuffer(gscb_, pscb);
}

void Engine::Rendering::ObjModel::SetRotating(DirectX::XMFLOAT3 rot)
{
	SetRotating(rot.x, rot.y, rot.z);
}

void Engine::Rendering::ObjModel::SetRotating(float rotX, float rotY, float rotZ)
{
	rotX_ = rotX;
	rotY_ = rotY;
	rotZ_ = rotZ;
}

void Engine::Rendering::ObjModel::SetScale(float scale)
{
	scale_ = scale;
}

void Engine::Rendering::ObjModel::SetCenterOffset(float x,float y,float z)
{
	centerOffset_ = DirectX::XMFLOAT3(x, y, z);
}
