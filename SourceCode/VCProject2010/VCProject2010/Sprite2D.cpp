#include "stdafx.h"
#include "Sprite2D.h"
#include "Device.h"
#include "Shaders.h"

using namespace Engine::Rendering;


ID3D11Buffer* Engine::Rendering::Sprite2D::getCBuffer()
{
	static const Transform tsf {
		DirectX::XMMatrixIdentity(),
		DirectX::XMMatrixOrthographicLH(800,600,0,1),
		DirectX::XMMatrixIdentity()
	};

	static auto cb = Engine::Rendering::CreateConstantBuffer(tsf.Transpose());
	return cb.Get();
}

ComPtr<ID3D11PixelShader> Engine::Rendering::Sprite2D::getPShader()
{
	static const auto ret = LoadPShader("Sprite2DDefault");
	return ret;
}

ComPtr<ID3D11PixelShader> Engine::Rendering::Sprite2D::getPShaderRT()
{
	static const auto ret = LoadPShader("Sprite2DRT");
	return ret;
}

ComPtr<ID3D11SamplerState> Engine::Rendering::Sprite2D::getSamplerState()
{
	static D3D11_SAMPLER_DESC samplerDesc = 
	{
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		0.0f,
		1,
		D3D11_COMPARISON_ALWAYS,
		{0,0,0,0},
		0,
		D3D11_FLOAT32_MAX
	};

	static auto smp = Engine::Rendering::CreateSampler(samplerDesc);

	return smp;
}


Engine::Rendering::Sprite2D::Sprite2D(const char * tex) 
{
	PtrTex2D t;
	DirectX::XMINT2 size;
	std::tie(t, size) = LoadTex2D(tex);
	const_cast<PtrTex2D&>(tex_) = std::move(t);
	const_cast<PtrTex2DShaderResView&>(texResView_) = Engine::Rendering::CreateShaderResView(tex_);
	const_cast<DirectX::XMINT2&>(size_) = std::move(size);

	spriteModeSplit_ = size.x;
}

Engine::Rendering::Sprite2D::Sprite2D(const Engine::Rendering::PtrTex2D & rt)
{
	D3D11_TEXTURE2D_DESC desc;
	rt->GetDesc(&desc);
	DirectX::XMINT2 size{ int(desc.Width),int(desc.Height) };

	const_cast<PtrTex2D&>(tex_) = rt;
	const_cast<PtrTex2DShaderResView&>(texResView_) = Engine::Rendering::CreateShaderResView(tex_);
	const_cast<DirectX::XMINT2&>(size_) = std::move(size);

	spriteModeSplit_ = size.x;
}

void Engine::Rendering::Sprite2D::SetColorMod(DirectX::XMFLOAT3 rgb)
{
	colorMod_.x = rgb.x;
	colorMod_.y = rgb.y;
	colorMod_.z = rgb.z;
	updatevb_ = true;
}

void Engine::Rendering::Sprite2D::SetAlpha(float a)
{
	colorMod_.w = a;
	updatevb_ = true;
}

void Engine::Rendering::Sprite2D::SetZoom(float zoom)
{
	zoom_ = zoom;
	updatevb_ = true;
}

void Engine::Rendering::Sprite2D::SetPos(float x, float y)
{
	position_.x = x;
	position_.y = y;
	updatevb_ = true;
}

void Engine::Rendering::Sprite2D::Draw() const
{
	if (updatevb_)
	{
		updatevb_ = false;
		
		for (auto& p : vbcpu_)
			p.color = colorMod_;

		const auto spilitXZoom = float(spriteModeSplit_) / size_.x;

		vbcpu_[0].position.x = position_.x - size_.x * zoom_ * spilitXZoom;
		vbcpu_[0].position.y = position_.y - size_.y * zoom_;

		vbcpu_[1].position.x = position_.x - size_.x * zoom_ * spilitXZoom;
		vbcpu_[1].position.y = position_.y + size_.y * zoom_;

		vbcpu_[2].position.x = position_.x + size_.x * zoom_ * spilitXZoom;
		vbcpu_[2].position.y = position_.y - size_.y * zoom_;

		vbcpu_[3].position.x = position_.x + size_.x * zoom_ * spilitXZoom;
		vbcpu_[3].position.y = position_.y + size_.y * zoom_;

		vbcpu_[4].position.x = position_.x + size_.x * zoom_ * spilitXZoom;
		vbcpu_[4].position.y = position_.y - size_.y * zoom_;

		vbcpu_[5].position.x = position_.x - size_.x * zoom_ * spilitXZoom;
		vbcpu_[5].position.y = position_.y + size_.y * zoom_;

		const auto left0 = float(spriteModeSplit_*usingSpriteNum_) / size_.x;
		const auto left1 = float(spriteModeSplit_*(usingSpriteNum_ + 1)) / size_.x;
		vbcpu_[0].texCoord = DirectX::XMFLOAT2(left0, 1);
		vbcpu_[1].texCoord = DirectX::XMFLOAT2(left0, 0);
		vbcpu_[2].texCoord = DirectX::XMFLOAT2(left1, 1);

		vbcpu_[3].texCoord = DirectX::XMFLOAT2(left1, 0);
		vbcpu_[4].texCoord = DirectX::XMFLOAT2(left1, 1);
		vbcpu_[5].texCoord = DirectX::XMFLOAT2(left0, 0);

		for (auto& p : vbcpu_)
			p.position.z = 0.4f;
		
		VertexIn::UpdateVBuffer(vb_, vbcpu_.data());
	}

	auto& d = Engine::GetDevice();
	auto cbp = getCBuffer();
	d.Context().VSSetConstantBuffers(0, 1, &cbp);
	d.Context().PSSetConstantBuffers(0, 0, nullptr);
	d.Context().PSSetShader(isRT ? getPShader().Get() : getPShader().Get(), nullptr, 0);
	constexpr float col[] = { 0,0,0,0 };


	d.Context().PSSetShaderResources(0, 1, texResView_.GetAddressOf());
	d.Context().PSSetSamplers(0, 1, getSamplerState().GetAddressOf());

	auto buf = vb_.Get();
	const UINT stride[] = { sizeof(VertexIn) };
	const UINT offset[] = { 0 };

	d.Context().IASetVertexBuffers(0, 1, &buf, stride, offset);
	d.Context().Draw(6, 0);

}

void Engine::Rendering::Sprite2D::SetAsSpriteSet(int xSplit, int num)
{
	spriteModeSplit_ = xSplit;
	usingSpriteNum_ = num;

	updatevb_ = true;
}

DirectX::XMFLOAT4 Engine::Rendering::Sprite2D::GetSpriteRect() const
{
	return DirectX::XMFLOAT4(
		position_.x - size_.x * zoom_,
		position_.y - size_.y*zoom_, 
		position_.x + size_.x*zoom_,
		position_.y + size_.y*zoom_);
}
