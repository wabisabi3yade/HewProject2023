#include "CDirectWrite.h"
#pragma comment(lib,"d2d1.lib")    
#pragma comment(lib,"dwrite.lib")


#include <atltypes.h>// CRectを使うのに必要なヘッダー
#include "WICTextureLoader.h" // テクスチャ読み込みライブラリ

// コンパイル済みシェーダーをインクルード
#include "VertexShader.h"
#include "PixelShader.h"
#include "direct3d.h"

// リンク設定
#pragma comment (lib, "d3d11.lib")

//=================================================================================================================================
// 第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
// 第2引数：フォントコレクション（nullptr）
// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
// 第6引数：フォントサイズ（20, 30等）
// 第7引数：ロケール名（L"ja-jp"等）
// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
//=================================================================================================================================
DirectWrite::DirectWrite(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle,
	DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, DWRITE_TEXT_ALIGNMENT textAlignment,
	D2D1_COLOR_F Color)
{
	Setting->font = font;
	Setting->fontCollection = fontCollection;
	Setting->fontWeight = fontWeight;
	Setting->fontStyle = fontStyle;
	Setting->fontStretch = fontStretch;
	Setting->fontSize = fontSize;
	Setting->localeName = localeName;
	Setting->textAlignment = textAlignment;
	Setting->Color = Color;
}

//=============================================================================
// フォント設定
// 第1引数：フォントデータ（ポインタ）
//=============================================================================
void DirectWrite::SetFont(FontData* set)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection, set->fontWeight, set->fontStyle, set->fontStretch, set->fontSize, set->localeName, &pTextFormat);
	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);
}

//=================================================================================================================================
// フォント設定
// 第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
// 第2引数：フォントコレクション（nullptr）
// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
// 第6引数：フォントサイズ（20, 30等）
// 第7引数：ロケール名（L"ja-jp"等）
// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
//=================================================================================================================================
void DirectWrite::SetFont(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight,
	DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName,
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	pDWriteFactory->CreateTextFormat(FontList[(int)font], fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &pTextFormat);
	pTextFormat->SetTextAlignment(textAlignment);
	pRT->CreateSolidColorBrush(Color, &pSolidBrush);
}

//=============================================================================
// 文字描画
// string：文字列
// pos：描画ポジション
// rect：領域指定
// options：テキストの整形
//=============================================================================
void DirectWrite::DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options)
{
	// 文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	// ターゲットサイズの取得
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	// テキストレイアウトを作成
	pDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);

	// 描画位置の確定
	D2D1_POINT_2F pounts;
	pounts.x = pos.x;
	pounts.y = pos.y;

	// 描画の開始
	pRT->BeginDraw();

	// 描画処理
	pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, options);

	// 描画の終了
	pRT->EndDraw();
}

//=============================================================================
// 文字描画
// string：文字列
// pos：描画ポジション
// rect：領域指定
// options：テキストの整形
//=============================================================================
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
{
	// 文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	// 描画の開始
	pRT->BeginDraw();

	// 描画処理
	pRT->DrawText(wstr.c_str(), wstr.size(), pTextFormat, rect, pSolidBrush, options);

	// 描画の終了
	pRT->EndDraw();
}

//=============================================================================
//     初期化
//=============================================================================
HRESULT DirectWrite::Init(HWND hwnd)
{
	HRESULT hr;

	// Direct2D,DirectWriteの初期化
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	if (FAILED(hr))
	{
		return hr;
	}


	// //バックバッファの取得
	// //型：IDXGISwapChain
	//hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer));
	hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//hr = pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	// dpiの設定
	FLOAT dpiX;
	FLOAT dpiY;

	dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
	dpiY = dpiX;

	//pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);

	// レンダーターゲットの作成
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);
	D2D1_HWND_RENDER_TARGET_PROPERTIES props2 = D2D1::HwndRenderTargetProperties(hwnd, { 1920,1080 });

	// サーフェスに描画するレンダーターゲットを作成
	pD2DFactory->CreateHwndRenderTarget(&props, &props2, &pRT);


	//// アンチエイリアシングモード
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// IDWriteFactoryの作成
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));

	if (FAILED(hr))
		return hr;

	//関数CreateTextFormat()
	//第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	//第2引数：フォントコレクション（nullptr）
	//第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	//第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	//第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	//第6引数：フォントサイズ（20, 30等）
	//第7引数：ロケール名（L""）
	//第8引数：テキストフォーマット（&g_pTextFormat）
	hr = pDWriteFactory->CreateTextFormat(FontList[(int)Setting->font],
		Setting->fontCollection,
		Setting->fontWeight,
		Setting->fontStyle,
		Setting->fontStretch,
		Setting->fontSize,
		Setting->localeName,
		&pTextFormat);

	//関数SetTextAlignment()
	//第1引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, DWRITE_TEXT_ALIGNMENT_TRAILING：後, DWRITE_TEXT_ALIGNMENT_CENTER：中央,
	//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED：行いっぱい）
	hr = pTextFormat->SetTextAlignment(Setting->textAlignment);

	//関数CreateSolidColorBrush()
	//第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
	hr = pRT->CreateSolidColorBrush(Setting->Color, &pSolidBrush);

	return hr;
}

//=============================================================================
//     終了処理
//=============================================================================
void DirectWrite::Release()
{
	// 文字描画関連のアンロード
	if (pBackBuffer) pBackBuffer->Release();
	if (pSolidBrush) pSolidBrush->Release();
	if (pRT) pRT->Release();
	if (pTextFormat) pTextFormat->Release();
	if (pDWriteFactory) pDWriteFactory->Release();
	if (pD2DFactory) pD2DFactory->Release();
	if (pTextLayout) pTextLayout->Release();
}

DirectWrite::DirectWrite()
{

}

//=============================================================================
//     stringをwstringへ変換する
//=============================================================================
std::wstring DirectWrite::StringToWString(std::string oString)
{
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	// 変換結果を返す
	return(oRet);
}

