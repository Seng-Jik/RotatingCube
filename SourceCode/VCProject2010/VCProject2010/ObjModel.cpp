#include "stdafx.h"
#include "ObjModel.h"
#include "ObjLoader.h"
Game::ObjModel::ObjModel(const std::string & modelName)
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

	GSCB gscb;
	gscb_ = Engine::Rendering::CreateConstantBuffer(gscb);
}

void Game::ObjModel::Draw() const
{
	auto& d = Engine::GetDevice();
	d.Context().VSSetConstantBuffers(0, 1, tsf_.GetAddressOf());
	d.Context().GSSetShader(gs_.Get(), nullptr, 0);
	d.Context().GSSetConstantBuffers(0, 1, gscb_.GetAddressOf());
	d.Context().PSSetConstantBuffers(0, 0, nullptr);
	d.Context().PSSetShader(ps_.Get(), nullptr, 0);
	constexpr float col[] = { 0,0,0,0 };


	auto buf = vbo_.Get();
	const UINT stride[] = { sizeof(Engine::Rendering::VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().IASetIndexBuffer(ibo_.Get(), DXGI_FORMAT_R32_UINT, 0);
	d.Context().DrawIndexed(ibSize_, 0,0);

	d.Context().GSSetShader(nullptr, nullptr, 0);
	d.Context().GSSetConstantBuffers(0, 0, nullptr);

	d.Context().IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
}

void Game::ObjModel::Update(float d)
{
	Engine::Rendering::Transform tsfcpu;
	tsfcpu.prj = Engine::GetDevice().Perspective();

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0, 0, 80.0f, 0);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(0, 0, -1, 0);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);

	timer_ += d;


	tsfcpu.view = DirectX::XMMatrixLookAtLH(eye, focus, up);
	tsfcpu.world = DirectX::XMMatrixRotationY(timer_) * DirectX::XMMatrixRotationX(timer_);

	Engine::Rendering::UpdateCBuffer(tsf_, tsfcpu.Transpose());

	GSCB gscb;
	gscb.eyepos = eye;

	Engine::Rendering::UpdateCBuffer(gscb_, gscb);
}
