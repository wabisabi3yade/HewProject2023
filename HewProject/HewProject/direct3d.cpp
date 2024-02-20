#include <d3d11.h> // DirectX11というライブラリのヘッダー
#include <atltypes.h>// CRectを使うのに必要なヘッダー
#include "WICTextureLoader.h" // テクスチャ読み込みライブラリ

// コンパイル済みシェーダーをインクルード
#include "VertexShader.h"
#include "PixelShader.h"
#include "direct3d.h"

// リンク設定
#pragma comment (lib, "d3d11.lib")

// 構造体の定義
// 頂点データの構造体
struct Vertex
{
	// 頂点の位置座標
	float x, y, z;
	// テクスチャ座標（UV座標）
	float u, v;
};

// グローバル変数の宣言
// ※ID3D11で始まるポインタ変数は解放する必要があるもの。
ID3D11Device* m_pDevice; // デバイス＝DirectXの各機能を作る
// コンテキスト＝描画機能
ID3D11DeviceContext* m_pImmediateContext;
IDXGISwapChain* m_pSwapChain;// ダブルバッファ機能
// レンダーターゲット＝描画対象
ID3D11RenderTargetView* m_pRenderTargetView;
// 深度バッファ用のテクスチャ
ID3D11Texture2D* m_pDepthStencilTexture;
// 深度バッファ
ID3D11DepthStencilView* m_pDepthStencilView;
// インプットレイアウト
ID3D11InputLayout* m_pInputLayout;
// 頂点シェーダーオブジェクト
ID3D11VertexShader* m_pVertexShader;
// ピクセルシェーダーオブジェクト
ID3D11PixelShader* m_pPixelShader;
// ビューポート
D3D11_VIEWPORT          m_Viewport;

// サンプラー用変数
ID3D11SamplerState* m_pSampler;

// 定数用バッファ変数
ID3D11Buffer* m_pConstantBuffer;

// ブレンドステート用変数（アルファブレンディング、画像の透過用）
ID3D11BlendState* m_pBlendStateAlpha;

// ブレンドステート変数　（加算合成）
ID3D11BlendState* m_pBlendStateAdditive;

// IASetVertexBuffersで使用する変数
const UINT strides = sizeof(Vertex);
const UINT offsets = 0;

// 関数のプロトタイプ宣言
HRESULT D3D_Create(HWND hwnd);
void D3D_Release();

// Direct3Dの初期化を行う関数
HRESULT D3D_Create(HWND hwnd)
{
	// HRESULT型＝Windowsプログラムで関数の呼び出しが成功/失敗した結果を格納
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

	// デバイスと、コンテキスト、スワップチェインを作る関数を呼び出し
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
	if (FAILED(hr)) // ifで上の関数が失敗してないか判定
		return hr;


	ID3D11Texture2D* pBackBuffer;

	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (FAILED(hr))
		return hr;

	// フルスクリーンにする
	hr = m_pSwapChain->SetFullscreenState(TRUE, NULL);
	if (FAILED(hr))
		return hr;

	// レンダーターゲットを作成する関数を呼び出し
	hr = m_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	if (FAILED(hr))
		return hr;

	// 深度ステンシルバッファの作成
	// 深度バッファ（Zバッファ）→前後関係を正しく判定して描画する機能
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

	// インプットレイアウトを作成
	// →１つの頂点がどんなデータを持っているかをDirectXに教える
	D3D11_INPUT_ELEMENT_DESC g_VertexDesc[]
	{
		// 位置座標（xyz）
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
			D3D11_INPUT_PER_VERTEX_DATA, 0 },

			// UV座標（uv）
			{ "TEX",    0, DXGI_FORMAT_R32G32_FLOAT, 0,
				D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	hr = m_pDevice->CreateInputLayout(g_VertexDesc, ARRAYSIZE(g_VertexDesc),
		g_vs_main, sizeof(g_vs_main),
		&m_pInputLayout);
	if (FAILED(hr))
		return hr;

	// シェーダーオブジェクトを作る
	// →VRAMにシェーダーのマシン語データを送る
	hr = m_pDevice->CreateVertexShader(&g_vs_main, sizeof(g_vs_main), NULL, &m_pVertexShader);
	if (FAILED(hr))
		return hr;

	hr = m_pDevice->CreatePixelShader(&g_ps_main, sizeof(g_ps_main), NULL, &m_pPixelShader);
	if (FAILED(hr))
		return hr;

	// ビューポートを設定
	m_Viewport.TopLeftX = 0;
	m_Viewport.TopLeftY = 0;
	m_Viewport.Width = (FLOAT)rect.Width();
	m_Viewport.Height = (FLOAT)rect.Height();
	m_Viewport.MinDepth = 0.0f;
	m_Viewport.MaxDepth = 1.0f;

	// サンプラー作成
	// →　テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
	D3D11_SAMPLER_DESC smpDesc;

	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	// 適用されるフィルター（アルゴリズム）の種類
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;	// LINIR:キャラの周り白がかる　POINT：白がからない
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr))
		return hr;

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer); //今から作る定数バッファのサイズ
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // 定数バッファ作成を指定
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;

	// ブレンドステート作成
	// →透過処理や加算合成を可能にする色の合成方法
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	// 背景色に掛け合わせる係数
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAlpha);

	m_pImmediateContext->OMSetBlendState(m_pBlendStateAlpha, NULL, 0xffffffff);

	// 加算合成の設定を作る
	// 背景色に掛け合わせる係数
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_pDevice->CreateBlendState(&BlendState, &m_pBlendStateAdditive);

	hr = m_pDevice->CreateBuffer(&cbDesc, NULL, &m_pConstantBuffer);
	if (FAILED(hr)) return hr;

	return hr;
}

// Direct3Dの解放（終了処理）を行う関数
// Release＝解放
// アプリケーション終了時に実行する
void D3D_Release()
{	
	//// 最後にフルスクリーンを解放
	m_pSwapChain->SetFullscreenState(FALSE, NULL);

	if (m_pImmediateContext) {
		m_pImmediateContext->ClearState();
	}

	// ブレンドステート解放
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
/// 四角形ポリゴンを作成し、頂点バッファ生成を行う
/// </summary>
/// <param name="size">ポリゴンの大きさ</param>
/// <param name="uv">画像の分割数</param>
/// <param name="vb">データを格納する頂点バッファ</param>
void D3D_CreateSquare(FLOAT_XY size, FLOAT_XY uvDivide, ID3D11Buffer** vb)
{
	float left = -(size.x / 2);
	float right = (size.x / 2);
	float top = (size.y / 2);
	float bottom = -(size.y / 2);
	// uvの値を求める
	FLOAT_XY uvValue = { 1.0f / uvDivide.x, 1.0f / uvDivide.y };


	Vertex vertexList[] =
	{
		// 時計回りに頂点が結ばれる面がポリゴンの表
		{ left,  top, 0.5f, 0.0f, 0.0f },  // ０番目の頂点データ  { x, y, z, u, v }
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // １番目の頂点データ
		{ left,  bottom, 0.5f, 0.0f, uvValue.y },  // ２番目の頂点データ

		{ left,  top, 0.5f, 0.0f, 0.0f },  // ３番目の頂点
		{ right, top, 0.5f, uvValue.x, 0.0f },  // ４番目の頂点
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // ５番目の頂点
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 作成する頂点バッファのサイズ
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファを指定する値
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// 作った頂点バッファに送るデータ
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	//頂点バッファ作成して、それを第3引数(頂点バッファ）に保存
	m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}


void D3D_CreateSquare(FLOAT_XY uv, ID3D11Buffer** vb)
{
	float left = -(1.0f / 2);
	float right = (1.0f / 2);
	float top = (1.0f / 2);
	float bottom = -(1.0f / 2);
	// uvの値を求める
	FLOAT_XY uvValue = { 1.0f / uv.x, 1.0f / uv.y };


	Vertex vertexList[] =
	{
		// 時計回りに頂点が結ばれる面がポリゴンの表
		{ left,  top, 0.5f, 0.0f, 0.0f },  // ０番目の頂点データ  { x, y, z, u, v }
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // １番目の頂点データ
		{ left,  bottom, 0.5f, 0.0f, uvValue.y },  // ２番目の頂点データ

		{ left,  top, 0.5f, 0.0f, 0.0f },  // ３番目の頂点
		{ right, top, 0.5f, uvValue.x, 0.0f },  // ４番目の頂点
		{ right, bottom, 0.5f, uvValue.x, uvValue.y },  // ５番目の頂点
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 作成する頂点バッファのサイズ
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファを指定する値
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// 作った頂点バッファに送るデータ
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	//頂点バッファ作成して、それを第3引数(頂点バッファ）に保存
	m_pDevice->CreateBuffer(&bufferDesc, &subResourceData, vb);
}

HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** texture)
{
	HRESULT hr;

	// テクスチャ読み込み
	// 第4引数：読み込んだテクスチャの格納変数
	hr = DirectX::CreateWICTextureFromFile(m_pDevice, filename,
		NULL, texture);

	if (FAILED(hr)) // 読み込みに失敗した場合
	{
		MessageBoxA(NULL, "テクスチャ読み込み失敗", "エラー",
			MB_ICONERROR | MB_OK);

	}

	return hr;
}

//画面塗りつぶしと設定する関数
void D3D_ClearScreen()
{
	// 画面塗りつぶし色
	float clearColor[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; //red,green,blue,alpha

	// 描画先キャンバスと使う深度バッファをセット
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);
	// キャンバスを指定した色で塗りつぶす
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, clearColor);
	// 深度バッファをリセット
	m_pImmediateContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pImmediateContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pImmediateContext->RSSetViewports(1, &m_Viewport);
	m_pImmediateContext->PSSetShader(m_pPixelShader, NULL, 0);

	// サンプラーをピクセルシェーダーに渡す
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);

	// 定数バッファを頂点シェーダーにセットする
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// 定数バッファをピクセルシェーダーにセットする
	m_pImmediateContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
}

// 画面を更新する関数
void D3D_UpdateScreen()
{
	// ダブルバッファを切り替えて画面更新
	m_pSwapChain->Present(0, 0);
}
