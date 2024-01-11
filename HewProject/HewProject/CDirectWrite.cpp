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


//=============================================================================
//		フォント名
//=============================================================================
const std::wstring FontList[] = //必ずフォントファイルから読み込むフォントを上に持ってくる！
{
	L"asset\\wakamura\\851MkPOP_101.otf",
	L"asset\\wakamura\\komadorimini.otf",
	L"asset\\wakamura\\MelodyLine-free.otf",
	/*L"HG行書体",
	L"HGP創英角ﾎﾟｯﾌﾟ体",
	L"ＭＳ 明朝",
	L"Arial",
	L"Meiryo UI",*/
};

// フォントコレクションローダー
class CustomFontCollectionLoader;
CustomFontCollectionLoader* pFontCollectionLoader = nullptr;

//=============================================================================
//		カスタムファイルローダー
//=============================================================================
class CustomFontFileEnumerator : public IDWriteFontFileEnumerator
{
public:
	CustomFontFileEnumerator(IDWriteFactory* factory, const std::vector<std::wstring>& fontFilePaths)
		: refCount_(0), factory_(factory), fontFilePaths_(fontFilePaths), currentFileIndex_(-1)
	{
		factory_->AddRef();
	}

	~CustomFontFileEnumerator()
	{
		factory_->Release();
	}

	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override
	{
		if (iid == __uuidof(IUnknown) || iid == __uuidof(IDWriteFontCollectionLoader))
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else
		{
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
	}

	IFACEMETHODIMP_(ULONG) AddRef() override
	{
		return InterlockedIncrement(&refCount_);
	}

	IFACEMETHODIMP_(ULONG) Release() override
	{
		ULONG newCount = InterlockedDecrement(&refCount_);
		if (newCount == 0)
			delete this;

		return newCount;
	}

	IFACEMETHODIMP MoveNext(OUT BOOL* hasCurrentFile) override {
		if (++currentFileIndex_ < static_cast<int>(fontFilePaths_.size())) {
			*hasCurrentFile = TRUE;
			return S_OK;
		}
		else {
			*hasCurrentFile = FALSE;
			return S_OK;
		}
	}

	IFACEMETHODIMP GetCurrentFontFile(OUT IDWriteFontFile** fontFile) override
	{
		// フォントファイルを読み込む
		 auto res = factory_->CreateFontFileReference(fontFilePaths_[currentFileIndex_].c_str(), nullptr, fontFile);

		 return res;
	}

private:
	ULONG refCount_;

	// DirectWriteファクトリ
	IDWriteFactory* factory_;

	// フォントファイルのパス
	std::vector<std::wstring> fontFilePaths_;

	// 現在のファイルインデックス
	int currentFileIndex_;
};

//=============================================================================
//		カスタムフォントコレクションローダー
//=============================================================================
class CustomFontCollectionLoader : public IDWriteFontCollectionLoader
{
public:
	// コンストラクタ
	CustomFontCollectionLoader() : refCount_(0) {}

	// IUnknown メソッド
	IFACEMETHODIMP QueryInterface(REFIID iid, void** ppvObject) override
	{
		if (iid == __uuidof(IUnknown) || iid == __uuidof(IDWriteFontCollectionLoader))
		{
			*ppvObject = this;
			AddRef();
			return S_OK;
		}
		else
		{
			*ppvObject = nullptr;
			return E_NOINTERFACE;
		}
	}

	IFACEMETHODIMP_(ULONG) AddRef() override
	{
		return InterlockedIncrement(&refCount_);
	}

	IFACEMETHODIMP_(ULONG) Release() override
	{
		ULONG newCount = InterlockedDecrement(&refCount_);
		if (newCount == 0)
			delete this;

		return newCount;
	}

	// IDWriteFontCollectionLoader メソッド
	IFACEMETHODIMP CreateEnumeratorFromKey
	(
		IDWriteFactory* factory,
		void const* collectionKey,
		UINT32 collectionKeySize,
		OUT IDWriteFontFileEnumerator** fontFileEnumerator) override
	{
		// 読み込むフォントファイルのパスを渡す
		std::vector<std::wstring> fontFilePaths(std::begin(FontList), std::end(FontList));

		// カスタムフォントファイル列挙子の作成
		*fontFileEnumerator = new (std::nothrow) CustomFontFileEnumerator(factory, fontFilePaths);

		// メモリ不足の場合はエラーを返す
		if (*fontFileEnumerator == nullptr) { return E_OUTOFMEMORY; }

		return S_OK;
	}

private:
	ULONG refCount_;
};

//=============================================================================
// フォント設定
// 第1引数：フォントデータ（ポインタ）
//=============================================================================
void DirectWrite::SetFont(std::shared_ptr<FontData> set)
{
	Setting = set;

	//解放
	if(pTextFormat != nullptr) {
		pTextFormat->Release(); 
		pTextFormat = nullptr;
	}


	// フォント名を取得する
	std::wstring name = L"";
	int num = (int)Setting->font;
	IDWriteFontCollection1* fc = fontCollection;
	if (num >= (int)fontNamesList.size() || fontNamesList.empty()) {
		// numがfontの種類より大きい or フォント名のリストが空だったらとりあえず先頭のfontを採用
		if (num >= (int)FontList->size()) {

			name = fontNamesList[0];
		} else {
			name = FontList[num];
//			if (fontCollection != nullptr) {
//				fontCollection->Release();
//				fontCollection = nullptr;
//			}
			fc = nullptr;
		}
	}
	else
	{
		name = fontNamesList[num];
	}

	HRESULT res = pDWriteFactory->CreateTextFormat(
		name.c_str(),
		fc,
		Setting->fontWeight,
		Setting->fontStyle,
		Setting->fontStretch,
		Setting->fontSize,
		Setting->localeName,
		&pTextFormat);
	if (FAILED(res)) return;

	pTextFormat->SetTextAlignment(set->textAlignment);
	pRT->CreateSolidColorBrush(set->Color, &pSolidBrush);


//	pDWriteFactory->CreateTextFormat(L"ＭＳ 明朝", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50, L"jp-jp", &pTextFormat);
//	pDWriteFactory->CreateTextFormat(L"Matura MT Script Capitals", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50, L"jp-jp", &pTextFormat);
//	pTextFormat->SetTextAlignment(set->textAlignment);
//	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pSolidBrush);

}

//=================================================================================================================================
// フォント設定
// 第1引数：フォント番号
// 第2引数：フォントコレクション（nullptr）
// 第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
// 第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
// 第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
// 第6引数：フォントサイズ（20, 30等）
// 第7引数：ロケール名（L"ja-jp"等）
// 第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
// 第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等）
//=================================================================================================================================
void DirectWrite::SetFont(Font font, IDWriteFontCollection* fontCollection, 
	DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle,
	DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, 
	DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	std::shared_ptr<FontData> fdat(new FontData);
	fdat->font = font;
	fdat->fontWeight = fontWeight;
	fdat->fontStyle = fontStyle;
	fdat->fontStretch = fontStretch;
	fdat->fontSize = fontSize;
	fdat->localeName = localeName;
	fdat->textAlignment = textAlignment;
	fdat->Color = Color;

	SetFont(fdat);
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

	if (pTextLayout != nullptr) {
		// 描画位置の確定
		D2D1_POINT_2F pounts;
		pounts.x = pos.x;
		pounts.y = pos.y;

		// 描画の開始
		pRT->BeginDraw();

		// 描画処理
		pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, options);

		pTextLayout->Release();
		pTextLayout = nullptr;
	}

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
	hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	// dpiの設定
	FLOAT dpiX;
	FLOAT dpiY;

	dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
	dpiY = dpiX;

	// レンダーターゲットの作成
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// サーフェスに描画するレンダーターゲットを作成
	pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	//// アンチエイリアシングモード
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// IDWriteFactoryの作成
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
		return hr;

	// カスタムフォントコレクションローダー
	pFontCollectionLoader = new CustomFontCollectionLoader();

	// カスタムフォントコレクションローダーの作成
	hr = pDWriteFactory->RegisterFontCollectionLoader(pFontCollectionLoader);
	if (FAILED(hr)) { return hr; }

	// フォントファイルの読み込み
	hr = pDWriteFactory->CreateCustomFontCollection
	(
		pFontCollectionLoader,
		pFontFileList.data(),
		pFontFileList.size(),
		(IDWriteFontCollection**)&fontCollection
	);
	if (FAILED(hr)) return hr;

	// フォント名を取得
	hr = GetFontFamilyName(fontCollection, L"ja-JP");
	if (FAILED(hr)) return hr;

	// フォントを設定
	SetFont(Setting);

	return hr;
}






HRESULT DirectWrite::GetFontFamilyName(IDWriteFontCollection* customFontCollection, const WCHAR* locale)
{
	HRESULT result = S_OK;

	// フォントファミリー名一覧をリセット
	std::vector<std::wstring>().swap(fontNamesList);

	// フォントの数を取得
	UINT32 familyCount = customFontCollection->GetFontFamilyCount();

	for (UINT32 i = 0; i < familyCount; i++)
	{
		// フォントファミリーの取得
		IDWriteFontFamily* fontFamily = nullptr;
		result = customFontCollection->GetFontFamily(i, &fontFamily);
		if (FAILED(result)) { return result; }

		// フォントファミリー名の一覧を取得
		IDWriteLocalizedStrings* familyNames = nullptr;
		result = fontFamily->GetFamilyNames(&familyNames);
		if (FAILED(result)) { return result; }

		// 指定されたロケールに対応するインデックスを検索
		UINT32 index = 0;
		BOOL exists = FALSE;
		result = familyNames->FindLocaleName(locale, &index, &exists);
		if (FAILED(result)) { return result; }

		// 指定されたロケールが見つからなかった場合は、デフォルトのロケールを使用
		if (!exists) {
			result = familyNames->FindLocaleName(L"en-us", &index, &exists);
			if (FAILED(result)) { return result; }
		}

		// フォントファミリー名の長さを取得
		UINT32 length = 0;
		result = familyNames->GetStringLength(index, &length);
		if (FAILED(result)) { return result; }

		// フォントファミリー名の取得
		WCHAR* name = new WCHAR[length + 1];
		result = familyNames->GetString(index, name, length + 1);
		if (FAILED(result)) { return result; }

		// フォントファミリー名を追加
		fontNamesList.push_back(name);

		// 使い終わったデータを破棄
		fontFamily->Release();
		familyNames->Release();
		delete[] name;
	}

	return result;
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

	if (fontCollection) fontCollection->Release();
	if (pFontCollectionLoader) pFontCollectionLoader->Release();
	
	for (int i = 0; i < pFontFileList.size(); i++)pFontFileList[i]->Release();
	pFontFileList.clear();
}

DirectWrite::DirectWrite()
{

}

DirectWrite::~DirectWrite()
{
	Release();
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
