#include <d3d11.h> // DirectX11�Ƃ������C�u�����̃w�b�_�[
#include <atltypes.h>// CRect���g���̂ɕK�v�ȃw�b�_�[
#include "WICTextureLoader.h" // �e�N�X�`���ǂݍ��݃��C�u����

// �R���p�C���ς݃V�F�[�_�[���C���N���[�h
#include "VertexShader.h"
#include "PixelShader.h"
#include "direct3d.h"

// �����N�ݒ�
#pragma comment (lib, "d3d11.lib")

// �\���̂̒�`
// ���_�f�[�^�̍\����
struct Vertex
{
	// ���_�̈ʒu���W
	float x, y, z;
	// �e�N�X�`�����W�iUV���W�j
	float u, v;
};

// �O���[�o���ϐ��̐錾
// ��ID3D11�Ŏn�܂�|�C���^�ϐ��͉������K�v��������́B
ID3D11Device* m_pDevice; // �f�o�C�X��DirectX�̊e�@�\�����
// �R���e�L�X�g���`��@�\
ID3D11DeviceContext* m_pImmediateContext;
IDXGISwapChain* m_pSwapChain;// �_�u���o�b�t�@�@�\
// �����_�[�^�[�Q�b�g���`��Ώ�
ID3D11RenderTargetView* m_pRenderTargetView;
// �[�x�o�b�t�@�p�̃e�N�X�`��
ID3D11Texture2D* m_pDepthStencilTexture;
// �[�x�o�b�t�@
ID3D11DepthStencilView* m_pDepthStencilView;
// �C���v�b�g���C�A�E�g
ID3D11InputLayout* m_pInputLayout;
// ���_�V�F�[�_�[�I�u�W�F�N�g
ID3D11VertexShader* m_pVertexShader;
// �s�N�Z���V�F�[�_�[�I�u�W�F�N�g
ID3D11PixelShader* m_pPixelShader;
// �r���[�|�[�g
D3D11_VIEWPORT          m_Viewport;

// �T���v���[�p�ϐ�
ID3D11SamplerState* m_pSampler;

// �萔�p�o�b�t�@�ϐ�
ID3D11Buffer* m_pConstantBuffer;

// �u�����h�X�e�[�g�p�ϐ��i�A���t�@�u�����f�B���O�A�摜�̓��ߗp�j
ID3D11BlendState* m_pBlendStateAlpha;

// �u�����h�X�e�[�g�ϐ��@�i���Z�����j
ID3D11BlendState* m_pBlendStateAdditive;

// IASetVertexBuffers�Ŏg�p����ϐ�
const UINT strides = sizeof(Vertex);
const UINT offsets = 0;

// �֐��̃v���g�^�C�v�錾
HRESULT D3D_Create(HWND hwnd);
void D3D_Release();

// Direct3D�̏��������s���֐�
HRESULT D3D_Create(HWND hwnd)
{
	// HRESULT�^��Windows�v���O�����Ŋ֐��̌Ăяo��������/���s�������ʂ��i�[
	HRESULT hr;

	UINT flags = 0;
	//#ifdef _DEBUG
	//    flags |= D3D11_CREATE_DEVICE_DEBUG;
	//#endif
	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;

	CRect                rect;
	DXGI_SWAP_CHAIN_DESC scDesc;

	::GetClientRect(hwnd, &rect);
	::ZeroMemory(&scDesc, sizeof(scDesc));
	scDesc.BufferCount = 1;
	scDesc.BufferDesc.Width = rect.Width();
	scDesc.BufferDesc.Height = rect.Height();
	scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scDesc.OutputWindow = hwnd;
	scDesc.SampleDesc.Count = 1;
	scDesc.SampleDesc.Quality = 0;
	scDesc.Windowed = TRUE;

	// �f�o�C�X�ƁA�R���e�L�X�g�A�X���b�v�`�F�C�������֐����Ăяo��
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&scDesc,
		&m_pSwapChain,
		&m_pDevice,
		&level,
		&m_pImmediateContext);
	if (FAILED(hr)) // if�ŏ�̊֐������s���ĂȂ�������
		return hr;


	ID3D11Texture2D* pBackBuffer;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// �t���X�N���[���ɂ���
	hr = m_pSwapChain->SetFullscreenState(TRUE, NULL);
	if (FAILED(hr))
		return hr;

	// �����_�[�^�[�Q�b�g���쐬����֐����Ăяo��
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// �[�x�X�e���V���o�b�t�@�̍쐬
	// �[�x�o�b�t�@�iZ�o�b�t�@�j���O��֌W�𐳂������肵�ĕ`�悷��@�\
	D3D11_TEXTURE2D_DESC txDesc;
	ZeroMemory(&txDesc, sizeof(txDesc));
	txDesc.Width = rect.Width();
	txDesc.Height = rect.Height();
	txDesc.MipLevels = 1;
	txDesc.ArraySize = 1;
	txDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	txDesc.SampleDesc.Count = 1;
	txDesc.SampleDesc.Quality = 0;
	txDesc.Usage = D3D11_USAGE_DEFAULT;
	txDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	txDesc.CPUAccessFlags = 0;
	txDesc.MiscFlags = 0;
	hr = m_pDevice->CreateTexture2D(&txDesc, NULL, &m_pDepthStencilTexture);
	if (FAILED(hr))
		return hr;

	D3D11_DEPTH_STENCIL_VIEW_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.Format = txDesc.Format;
	dsDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsDesc.Texture2D.MipSlice = 0;
	hr = m_pDevice->CreateDepthStencilView(m_pDepthStencilTexture, &dsDesc, &m_pDepthStencilView);
	if (FAILED(hr))
		return hr;

	// �C���v�b�g���C�A�E�g���쐬
	// ���P�̒��_���ǂ�ȃf�[�^�������Ă��邩��DirectX�ɋ�����
	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]
	{
		// �ʒu���W�ixyz�j
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0 },

			// UV���W�iuv�j
			{ "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,
				D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
	if (FAILED(hr))
		return hr;

	// �V�F�[�_�[�I�u�W�F�N�g�����
	// ��VRAM�ɃV�F�[�_�[�̃}�V����f�[�^�𑗂�
	hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
	if (FAILED(hr))
		return hr;

	hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
	if (FAILED(hr))
		return hr;

	// �r���[�|�[�g��ݒ�
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)rect.Width();
	m_Viewport.Height = (FLOAT)rect.Height();
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	// �T���v���[�쐬
	// ���@�e�N�X�`�����|���S���ɓ\��Ƃ��ɁA�g��k�������ۂ̃A���S���Y��
	D3D11_SAMPLER_DESC smpDesc;

	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	// �K�p�����t�B���^�[�i�A���S���Y���j�̎��
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// LINIR:�L�����̎��蔒������@POINT�F��������Ȃ�
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr))
		return hr;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer); //��������萔�o�b�t�@�̃T�C�Y
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // �萔�o�b�t�@�쐬���w��
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// �u�����h�X�e�[�g�쐬
	// �����ߏ�������Z�������\�ɂ���F�̍������@
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// �w�i�F�Ɋ|�����킹��W��
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAlpha);

	m_pImmediateContext->OMSetBlendState(m_pBlendStateAlpha, NULL, 0xffffffff);

	// ���Z�����̐ݒ�����
	// �w�i�F�Ɋ|�����킹��W��
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAdditive);

	hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;

	return hr;
}

// Direct3D�̉���i�I�������j���s���֐�
// Release�����
// �A�v���P�[�V�����I�����Ɏ��s����
void D3D_Release()
{	
	//// �Ō�Ƀt���X�N���[�������
	m_pSwapChain->SetFullscreenState(FALSE, NULL);

	if (m_pImmediateContext) {
		m_pImmediateContext->ClearState();
	}

	// �u�����h�X�e�[�g���
	SAFE_RELEASE(m_pConstantBuffer);

	SAFE_RELEASE(m_pBlendStateAlpha);
	SAFE_RELEASE(m_pBlendStateAdditive);


	SAFE_RELEASE(m_pSampler);

	SAFE_RELEASE(m_pDepthStencilTexture);
	SAFE_RELEASE(m_pDepthStencilView);
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexShader);

	SAFE_RELEASE(m_pRenderTargetView);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pImmediateContext);
	SAFE_RELEASE(m_pDevice);

	SAFE_RELEASE(m_pConstantBuffer);
}

/// <summary>
/// �l�p�`�|���S�����쐬���A���_�o�b�t�@�������s��
/// </summary>
/// <param name="size">�|���S���̑傫��</param>
/// <param name="uv">�摜�̕�����</param>
/// <param name="vb">�f�[�^���i�[���钸�_�o�b�t�@</param>
void D3D_CreateSquare(FLOAT_XY size, FLOAT_XY uvDivide, ID3D11Buffer** vb)
{
	float left = -(size.x / 2);
	float right = (size.x / 2);
	float top = (size.y / 2);
	float bottom = -(size.y / 2);
	// uv�̒l�����߂�
	FLOAT_XY uvValue = { 1.0f / uvDivide.x, 1.0f / uvDivide.y };


	Vertex vertexList[] =
	{
		// ���v���ɒ��_�����΂��ʂ��|���S���̕\
		{ left,  top, 0.5f, 0.0f, 0.0f },  // �O�Ԗڂ̒��_�f�[�^  { x, y, z, u, v }
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // �P�Ԗڂ̒��_�f�[�^
		{ left,  bottom, 0.5f, 0.0f, uvValue.y },  // �Q�Ԗڂ̒��_�f�[�^

		{ left,  top, 0.5f, 0.0f, 0.0f },  // �R�Ԗڂ̒��_
		{ right, top, 0.5f, uvValue.x, 0.0f },  // �S�Ԗڂ̒��_
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // �T�Ԗڂ̒��_
	};

	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// �쐬���钸�_�o�b�t�@�̃T�C�Y
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@���w�肷��l
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// ��������_�o�b�t�@�ɑ���f�[�^
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	//���_�o�b�t�@�쐬���āA������3����(���_�o�b�t�@�j�ɕۑ�
	m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}


void D3D_CreateSquare(FLOAT_XY uv, ID3D11Buffer** vb)
{
	float left = -(1.0f / 2);
	float right = (1.0f / 2);
	float top = (1.0f / 2);
	float bottom = -(1.0f / 2);
	// uv�̒l�����߂�
	FLOAT_XY uvValue = { 1.0f / uv.x, 1.0f / uv.y };


	Vertex vertexList[] =
	{
		// ���v���ɒ��_�����΂��ʂ��|���S���̕\
		{ left,  top, 0.5f, 0.0f, 0.0f },  // �O�Ԗڂ̒��_�f�[�^  { x, y, z, u, v }
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // �P�Ԗڂ̒��_�f�[�^
		{ left,  bottom, 0.5f, 0.0f, uvValue.y },  // �Q�Ԗڂ̒��_�f�[�^

		{ left,  top, 0.5f, 0.0f, 0.0f },  // �R�Ԗڂ̒��_
		{ right, top, 0.5f, uvValue.x, 0.0f },  // �S�Ԗڂ̒��_
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // �T�Ԗڂ̒��_
	};

	//���_�o�b�t�@�쐬
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// �쐬���钸�_�o�b�t�@�̃T�C�Y
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@���w�肷��l
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// ��������_�o�b�t�@�ɑ���f�[�^
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	//���_�o�b�t�@�쐬���āA������3����(���_�o�b�t�@�j�ɕۑ�
	m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}

HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture)
{
	HRESULT hr;

	// �e�N�X�`���ǂݍ���
	// ��4�����F�ǂݍ��񂾃e�N�X�`���̊i�[�ϐ�
	hr = DirectX::CreateWICTextureFromFile(m_pDevice, filename,
		NULL, texture);

	if (FAILED(hr)) // �ǂݍ��݂Ɏ��s�����ꍇ
	{
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[",
			MB_ICONERROR | MB_OK);

	}

	return hr;
}

//��ʓh��Ԃ��Ɛݒ肷��֐�
void D3D_ClearScreen()
{
	// ��ʓh��Ԃ��F
	float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

	// �`���L�����o�X�Ǝg���[�x�o�b�t�@���Z�b�g
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	// �L�����o�X���w�肵���F�œh��Ԃ�
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	// �[�x�o�b�t�@�����Z�b�g
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

	// �T���v���[���s�N�Z���V�F�[�_�[�ɓn��
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);

	// �萔�o�b�t�@�𒸓_�V�F�[�_�[�ɃZ�b�g����
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// �萔�o�b�t�@���s�N�Z���V�F�[�_�[�ɃZ�b�g����
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

// ��ʂ��X�V����֐�
void D3D_UpdateScreen()
{
	// �_�u���o�b�t�@��؂�ւ��ĉ�ʍX�V
	m_pSwapChain->Present(0, 0);
}
