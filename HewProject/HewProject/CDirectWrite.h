#pragma once
#include <dwrite.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <DirectXColors.h>
#include <Windows.h>
#include <iostream>
#include <DirectXMath.h>


//=============================================================================
//		フォントリスト
//=============================================================================
enum class Font
{
	Meiryo,
	Arial,
	MeiryoUI
};

//=============================================================================
//		フォント名
//=============================================================================
namespace
{
	const wchar_t* FontList[]
	{
		L"メイリオ",
		L"Arial",
		L"Meiryo UI"
	};
}

//=============================================================================
//		フォント設定
//=============================================================================
struct FontData
{
	Font font;					// フォント名
	IDWriteFontCollection* fontCollection;		// フォントコレクション
	DWRITE_FONT_WEIGHT fontWeight;			// フォントの太さ
	DWRITE_FONT_STYLE fontStyle;			// フォントスタイル
	DWRITE_FONT_STRETCH fontStretch;		// フォントの幅
	FLOAT fontSize;					// フォントサイズ
	WCHAR const* localeName;			// ロケール名
	DWRITE_TEXT_ALIGNMENT textAlignment;		// テキストの配置
	D2D1_COLOR_F Color;				// フォントの色

	// デフォルト設定
	FontData()
	{
		font = Font::Meiryo;
		fontCollection = nullptr;
		fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize = 20;
		localeName = L"ja-jp";
		textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color = D2D1::ColorF(D2D1::ColorF::White);
	}
};

//=============================================================================
//		DirectWrite設定
//=============================================================================
class DirectWrite
{
private:
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteFactory* pDWriteFactory = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	IDWriteTextLayout* pTextLayout = NULL;
	ID2D1HwndRenderTarget* pRT = NULL;
	ID2D1SolidColorBrush* pSolidBrush = NULL;
	IDXGISurface* pBackBuffer = NULL;

	//IDXGISwapChain* pSwapChain = NULL;

	// フォントデータ
	FontData* Setting = new FontData();

	// stringをwstringへ変換する
	std::wstring StringToWString(std::string oString);

public:
	// デフォルトコンストラクタを制限
	DirectWrite();

	// コンストラクタ
	// 第1引数：フォント設定
	DirectWrite(FontData* set) :Setting(set) {};

	// コンストラクタ
	// 第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	// 第2引数：フォントコレクション（nullptr）
	// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	// 第6引数：フォントサイズ（20, 30等）
	// 第7引数：ロケール名（L"ja-jp"等）
	// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
	// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
	DirectWrite(Font font,					// フォント名
		IDWriteFontCollection* fontCollection,	// フォントコレクション
		DWRITE_FONT_WEIGHT fontWeight,		// フォントの太さ
		DWRITE_FONT_STYLE fontStyle,		// フォントスタイル
		DWRITE_FONT_STRETCH fontStretch,		// フォントの幅
		FLOAT fontSize,				// フォントサイズ
		WCHAR const* localeName,			// ロケール名
		DWRITE_TEXT_ALIGNMENT textAlignment,	// テキストの配置
		D2D1_COLOR_F Color				// フォントの色
	);

	// フォント設定
	// 第1引数：フォントデータ構造体
	void SetFont(FontData* set);

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
	void SetFont(Font font,						// フォント名
		IDWriteFontCollection* fontCollection,		// フォントコレクション
		DWRITE_FONT_WEIGHT fontWeight,			// フォントの太さ
		DWRITE_FONT_STYLE fontStyle,			// フォントスタイル
		DWRITE_FONT_STRETCH fontStretch,			// フォントの幅
		FLOAT fontSize,					// フォントサイズ
		WCHAR const* localeName,				// ロケール名
		DWRITE_TEXT_ALIGNMENT textAlignment,		// テキストの配置
		D2D1_COLOR_F Color);				// フォントの色

	// 文字描画
	// string：文字列
	// pos：描画ポジション
	// options：テキストの整形
	void DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options);

	// 文字描画
	// string：文字列
	// rect：領域指定
	// options：テキストの整形
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);

	// 初期化
	HRESULT Init(HWND hwnd);

	// 終了処理
	void Release();

};


extern ID3D11Device* m_pDevice; // デバイス＝DirectXの各機能を作る
extern IDXGISwapChain* m_pSwapChain;// ダブルバッファ機能
// コンテキスト＝描画機能
extern ID3D11DeviceContext* m_pImmediateContext;


