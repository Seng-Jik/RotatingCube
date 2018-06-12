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

	Engine::Rendering::Transform tsfcpu;
	tsfcpu.prj = Engine::GetDevice().Perspective();

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0, 0, 1.5f, 0);
	DirectX::XMVECTOR focus = DirectX::XMVectorSet(0, 0, -10, 0);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0, 1, 0, 0);

	tsfcpu.view = DirectX::XMMatrixLookAtLH(eye,focus,up);
	tsfcpu.world = DirectX::XMMatrixIdentity();

	tsf_ = Engine::Rendering::CreateConstantBuffer(tsfcpu);
}

void Game::ObjModel::Draw() const
{
	auto& d = Engine::GetDevice();
	d.Context().VSSetConstantBuffers(0, 1, tsf_.GetAddressOf());
	d.Context().PSSetConstantBuffers(0, 0, nullptr);
	d.Context().PSSetShader(ps_.Get(), nullptr, 0);
	constexpr float col[] = { 0,0,0,0 };


	auto buf = vbo_.Get();
	const UINT stride[] = { sizeof(Engine::Rendering::VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().IASetIndexBuffer(ibo_.Get(), DXGI_FORMAT_R32_UINT, 0);
	d.Context().DrawIndexed(ibSize_, 0,0);

	d.Context().IASetIndexBuffer(nullptr, DXGI_FORMAT_R32_UINT, 0);
}

void Game::ObjModel::Update(float)
{
}
