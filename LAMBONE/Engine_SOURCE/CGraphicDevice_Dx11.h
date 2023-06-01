#pragma once
#include "ZEngine.h"
#include "CGraphics.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace yha::graphics
{
	class CGraphicDevice_Dx11
	{
	public:
		CGraphicDevice_Dx11();
		~CGraphicDevice_Dx11();

	public:
		bool FnCreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		bool FnCreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		bool FnCreateShader();
		bool FnCreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);

		void FnBindViewPort(D3D11_VIEWPORT* viewPort);

		// ��� ����
		void FnSetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void FnBindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void FnBindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);

		void FnDraw();

	private:
		// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		//  dx11���� ���������� ����̽���ü ���������ʰ�
		// �̰�ü�� �̿��Ͽ� ����� ������.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// ���������� �׷��� �ؽ�ó(��ȭ��)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� �����Ѵ�.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// ���̹���
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// ���̹��ۿ� �����Ҽ� �ִ� ��
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// ������۸� �۾��� �������ִ� swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice_Dx11*& FnGetDevice()
	{
		static CGraphicDevice_Dx11* device = nullptr;
		return device;
	}
}
