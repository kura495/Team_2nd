#pragma once
#include "Log.h"
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#include "WinApp.h"
#include "Math_Structs.h"
#include <dxcapi.h>
#pragma comment(lib,"dxcompiler.lib")
#include <dxgidebug.h>
#pragma comment(lib,"dxguid.lib")
#include "externals/DirectXTex/d3dx12.h"
#include <wrl.h>

class DirectXCommon
{
public:
	static DirectXCommon* GetInstance();
	void Initialize(WinApp* winApp);

	void PreView();

	void PostView();

	void Release();
	
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	ID3D12GraphicsCommandList*GetcommandList()const { return commandList.Get(); }
	ID3D12Device* GetDevice()const { return device.Get(); }

	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc()const { return swapChainDesc; }

	D3D12_RENDER_TARGET_VIEW_DESC GetrtvDesc()const { return rtvDesc; }
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
	 GetsrvDescriptorHeap()const { return srvDescriptorHeap.Get(); }

	//ポストプロセス
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>
		CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
	Microsoft::WRL::ComPtr<ID3D12Resource>
		CreateDepthStencilTextureResource(int32_t width, int32_t height);
	void PostProsessRootSignature();
	void PostProsessPipelineStateObject();
	void PostProsessInPutLayout();
	void PostProsessDraw();
	//
	//スプライト
	///スプライト用パイプライン
	void SetSpritePipeLine();
	void SpriteRootSignature();
	void SpritePipelineStateObject();
	void SpriteInPutLayout();
	//

private:
	DirectXCommon() = default;
	~DirectXCommon() = default;
	DirectXCommon(const DirectXCommon& obj) = delete;
	DirectXCommon& operator=(const DirectXCommon& obj) = delete;

	//ポストプロセス
	IDxcBlob* PostProsessBlob=nullptr;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>PostProsessgraphicsPipelineState = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>PostProsessrootSignature = nullptr;
	ID3DBlob* PostProsesssignatureBlob = nullptr;
	ID3DBlob* PostProsesserrorBlob = nullptr;
	D3D12_INPUT_ELEMENT_DESC PostProsessinputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC PostProsessinputLayoutDesc{};
	//
	//スプライト
	IDxcBlob* SpriteVertexBlob = nullptr;
	IDxcBlob* SpritePixelBlob = nullptr;
	Microsoft::WRL::ComPtr<ID3D12PipelineState>SpriteGraphicsPipelineState = nullptr;
	Microsoft::WRL::ComPtr<ID3D12RootSignature>SpriterootSignature = nullptr;
	ID3DBlob* SpriteSignatureBlob = nullptr;
	ID3DBlob* SpriteerrorBlob = nullptr;
	D3D12_INPUT_ELEMENT_DESC SpriteinputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC SpriteinputLayoutDesc{};
	//


	WinApp* winApp_;
	HRESULT hr;

	D3D12_RESOURCE_BARRIER barrier{};
	Microsoft::WRL::ComPtr<IDXGIFactory7>dxgiFactory = nullptr;
	Microsoft::WRL::ComPtr<IDXGIAdapter4>useAdapter = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Device>device = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator>commandAllocator = nullptr;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>commandList = nullptr;
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4>swapChain = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>rtvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>srvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>dsvDescriptorHeap = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource>depthStencilResource = nullptr;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};

	Microsoft::WRL::ComPtr<ID3D12Resource>swapChainResources[2] = { nullptr };
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	Microsoft::WRL::ComPtr<ID3D12Fence>fence = nullptr;
	uint64_t fenceValue = 0;
	HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

	IDxcBlobUtf8* shaderError = nullptr;
	IDxcBlob* shaderBlob = nullptr;

	Microsoft::WRL::ComPtr<ID3D12RootSignature>rootSignature = nullptr;
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	D3D12_INPUT_ELEMENT_DESC inputElementDescs[3] = {};
	D3D12_INPUT_LAYOUT_DESC inputLayoutDesc{};

	D3D12_BLEND_DESC blendDesc{};

	D3D12_RASTERIZER_DESC rasterizerDesc{};

	IDxcBlob* vertexShaderBlob = nullptr;
	IDxcBlob* pixelShaderBlob = nullptr;

	Microsoft::WRL::ComPtr<ID3D12PipelineState>graphicsPipelineState = nullptr;

	D3D12_VIEWPORT viewport{};

	D3D12_RECT scissorRect{};
#ifdef _DEBUG
	Microsoft::WRL::ComPtr<ID3D12Debug1>debugController = nullptr;
#endif

//プライベート関数

	void MakeDXGIFactory();
	void MakeD3D12Device();
	void MakeCommandQueue();
	void MakeCommandAllocator();
	void MakeCommandList();
	void MakeSwapChain();
	void MakeDescriptorHeap();
	void MakeFence();
	void MakeDXC();
	IDxcBlob* CompileShader(const std::wstring& filePath,const wchar_t* profile);
	//PSO
	void MakeRootSignature();
	void MakeInputLayOut();
	void MakeBlendState();
	void MakeRasterizarState();
	void MakeShaderCompile();
	void MakePipelineStateObject();

	void MakeViewport();
	void MakeScissor();
};


