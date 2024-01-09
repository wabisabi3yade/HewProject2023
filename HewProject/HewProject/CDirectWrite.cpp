#include "CDirectWrite.h"

#pragma comment(lib,"d2d1.lib")    
#pragma comment(lib,"dwrite.lib")


#include <atltypes.h>// CRect���g���̂ɕK�v�ȃw�b�_�[
#include "WICTextureLoader.h" // �e�N�X�`���ǂݍ��݃��C�u����

// �R���p�C���ς݃V�F�[�_�[���C���N���[�h
#include "VertexShader.h"
#include "PixelShader.h"
#include "direct3d.h"

// �����N�ݒ�
#pragma comment (lib, "d3d11.lib")


//=============================================================================
//		�t�H���g��
//=============================================================================
const std::wstring FontList[] = //�K���t�H���g�t�@�C������ǂݍ��ރt�H���g����Ɏ����Ă���I
{
	L"asset\\wakamura\\851MkPOP_101.otf",
	L"asset\\wakamura\\komadorimini.otf",
	L"asset\\wakamura\\MelodyLine-free.otf",
	/*L"HG�s����",
	L"HGP�n�p�p�߯�ߑ�",
	L"�l�r ����",
	L"Arial",
	L"Meiryo UI",*/
};

// �t�H���g�R���N�V�������[�_�[
class CustomFontCollectionLoader;
CustomFontCollectionLoader* pFontCollectionLoader = nullptr;

//=============================================================================
//		�J�X�^���t�@�C�����[�_�[
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
		// �t�H���g�t�@�C����ǂݍ���
		 auto res = factory_->CreateFontFileReference(fontFilePaths_[currentFileIndex_].c_str(), nullptr, fontFile);

		 return res;
	}

private:
	ULONG refCount_;

	// DirectWrite�t�@�N�g��
	IDWriteFactory* factory_;

	// �t�H���g�t�@�C���̃p�X
	std::vector<std::wstring> fontFilePaths_;

	// ���݂̃t�@�C���C���f�b�N�X
	int currentFileIndex_;
};

//=============================================================================
//		�J�X�^���t�H���g�R���N�V�������[�_�[
//=============================================================================
class CustomFontCollectionLoader : public IDWriteFontCollectionLoader
{
public:
	// �R���X�g���N�^
	CustomFontCollectionLoader() : refCount_(0) {}

	// IUnknown ���\�b�h
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

	// IDWriteFontCollectionLoader ���\�b�h
	IFACEMETHODIMP CreateEnumeratorFromKey
	(
		IDWriteFactory* factory,
		void const* collectionKey,
		UINT32 collectionKeySize,
		OUT IDWriteFontFileEnumerator** fontFileEnumerator) override
	{
		// �ǂݍ��ރt�H���g�t�@�C���̃p�X��n��
		std::vector<std::wstring> fontFilePaths(std::begin(FontList), std::end(FontList));

		// �J�X�^���t�H���g�t�@�C���񋓎q�̍쐬
		*fontFileEnumerator = new (std::nothrow) CustomFontFileEnumerator(factory, fontFilePaths);

		// �������s���̏ꍇ�̓G���[��Ԃ�
		if (*fontFileEnumerator == nullptr) { return E_OUTOFMEMORY; }

		return S_OK;
	}

private:
	ULONG refCount_;
};

//=============================================================================
// �t�H���g�ݒ�
// ��1�����F�t�H���g�f�[�^�i�|�C���^�j
//=============================================================================
void DirectWrite::SetFont(std::shared_ptr<FontData> set)
{
	Setting = set;

	//���
	if(pTextFormat != nullptr) {
		pTextFormat->Release(); 
		pTextFormat = nullptr;
	}


	// �t�H���g�����擾����
	std::wstring name = L"";
	int num = (int)Setting->font;
	IDWriteFontCollection1* fc = fontCollection;
	if (num >= (int)fontNamesList.size() || fontNamesList.empty()) {
		// num��font�̎�ނ��傫�� or �t�H���g���̃��X�g���󂾂�����Ƃ肠�����擪��font���̗p
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


//	pDWriteFactory->CreateTextFormat(L"�l�r ����", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50, L"jp-jp", &pTextFormat);
//	pDWriteFactory->CreateTextFormat(L"Matura MT Script Capitals", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 50, L"jp-jp", &pTextFormat);
//	pTextFormat->SetTextAlignment(set->textAlignment);
//	pRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &pSolidBrush);

}

//=================================================================================================================================
// �t�H���g�ݒ�
// ��1�����F�t�H���g�ԍ�
// ��2�����F�t�H���g�R���N�V�����inullptr�j
// ��3�����F�t�H���g�̑����iDWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD���j
// ��4�����F�t�H���g�X�^�C���iDWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC�j
// ��5�����F�t�H���g�̕��iDWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED���j
// ��6�����F�t�H���g�T�C�Y�i20, 30���j
// ��7�����F���P�[�����iL"ja-jp"���j
// ��8�����F�e�L�X�g�̔z�u�iDWRITE_TEXT_ALIGNMENT_LEADING�F�O, ���j
// ��9�����F�t�H���g�̐F�iD2D1::ColorF(D2D1::ColorF::Black)�F��, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))�FRGBA�w�蓙�j
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
// �����`��
// string�F������
// pos�F�`��|�W�V����
// rect�F�̈�w��
// options�F�e�L�X�g�̐��`
//=============================================================================
void DirectWrite::DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options)
{
	// ������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	// �^�[�Q�b�g�T�C�Y�̎擾
	D2D1_SIZE_F TargetSize = pRT->GetSize();

	// �e�L�X�g���C�A�E�g���쐬
	pDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), pTextFormat, TargetSize.width, TargetSize.height, &pTextLayout);

	if (pTextLayout != nullptr) {
		// �`��ʒu�̊m��
		D2D1_POINT_2F pounts;
		pounts.x = pos.x;
		pounts.y = pos.y;

		// �`��̊J�n
		pRT->BeginDraw();

		// �`�揈��
		pRT->DrawTextLayout(pounts, pTextLayout, pSolidBrush, options);

		pTextLayout->Release();
		pTextLayout = nullptr;
	}

	// �`��̏I��
	pRT->EndDraw();
}

//=============================================================================
// �����`��
// string�F������
// pos�F�`��|�W�V����
// rect�F�̈�w��
// options�F�e�L�X�g�̐��`
//=============================================================================
void DirectWrite::DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
{
	// ������̕ϊ�
	std::wstring wstr = StringToWString(str.c_str());

	// �`��̊J�n
	pRT->BeginDraw();

	// �`�揈��
	pRT->DrawText(wstr.c_str(), wstr.size(), pTextFormat, rect, pSolidBrush, options);

	// �`��̏I��
	pRT->EndDraw();
}

//=============================================================================
//     ������
//=============================================================================
HRESULT DirectWrite::Init(HWND hwnd)
{
	HRESULT hr;

	// Direct2D,DirectWrite�̏�����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	if (FAILED(hr))
	{
		return hr;
	}

	// //�o�b�N�o�b�t�@�̎擾
	// //�^�FIDXGISwapChain
	hr = m_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	// dpi�̐ݒ�
	FLOAT dpiX;
	FLOAT dpiY;

	dpiX = (FLOAT)GetDpiForWindow(GetDesktopWindow());
	dpiY = dpiX;

	// �����_�[�^�[�Q�b�g�̍쐬
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// �T�[�t�F�X�ɕ`�悷�郌���_�[�^�[�Q�b�g���쐬
	pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &pRT);

	//// �A���`�G�C���A�V���O���[�h
	pRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// IDWriteFactory�̍쐬
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pDWriteFactory));
	if (FAILED(hr))
		return hr;

	// �J�X�^���t�H���g�R���N�V�������[�_�[
	pFontCollectionLoader = new CustomFontCollectionLoader();

	// �J�X�^���t�H���g�R���N�V�������[�_�[�̍쐬
	hr = pDWriteFactory->RegisterFontCollectionLoader(pFontCollectionLoader);
	if (FAILED(hr)) { return hr; }

	// �t�H���g�t�@�C���̓ǂݍ���
	hr = pDWriteFactory->CreateCustomFontCollection
	(
		pFontCollectionLoader,
		pFontFileList.data(),
		pFontFileList.size(),
		(IDWriteFontCollection**)&fontCollection
	);
	if (FAILED(hr)) return hr;

	// �t�H���g�����擾
	hr = GetFontFamilyName(fontCollection, L"ja-JP");
	if (FAILED(hr)) return hr;

	// �t�H���g��ݒ�
	SetFont(Setting);

	return hr;
}






HRESULT DirectWrite::GetFontFamilyName(IDWriteFontCollection* customFontCollection, const WCHAR* locale)
{
	HRESULT result = S_OK;

	// �t�H���g�t�@�~���[���ꗗ�����Z�b�g
	std::vector<std::wstring>().swap(fontNamesList);

	// �t�H���g�̐����擾
	UINT32 familyCount = customFontCollection->GetFontFamilyCount();

	for (UINT32 i = 0; i < familyCount; i++)
	{
		// �t�H���g�t�@�~���[�̎擾
		IDWriteFontFamily* fontFamily = nullptr;
		result = customFontCollection->GetFontFamily(i, &fontFamily);
		if (FAILED(result)) { return result; }

		// �t�H���g�t�@�~���[���̈ꗗ���擾
		IDWriteLocalizedStrings* familyNames = nullptr;
		result = fontFamily->GetFamilyNames(&familyNames);
		if (FAILED(result)) { return result; }

		// �w�肳�ꂽ���P�[���ɑΉ�����C���f�b�N�X������
		UINT32 index = 0;
		BOOL exists = FALSE;
		result = familyNames->FindLocaleName(locale, &index, &exists);
		if (FAILED(result)) { return result; }

		// �w�肳�ꂽ���P�[����������Ȃ������ꍇ�́A�f�t�H���g�̃��P�[�����g�p
		if (!exists) {
			result = familyNames->FindLocaleName(L"en-us", &index, &exists);
			if (FAILED(result)) { return result; }
		}

		// �t�H���g�t�@�~���[���̒������擾
		UINT32 length = 0;
		result = familyNames->GetStringLength(index, &length);
		if (FAILED(result)) { return result; }

		// �t�H���g�t�@�~���[���̎擾
		WCHAR* name = new WCHAR[length + 1];
		result = familyNames->GetString(index, name, length + 1);
		if (FAILED(result)) { return result; }

		// �t�H���g�t�@�~���[����ǉ�
		fontNamesList.push_back(name);

		// �g���I������f�[�^��j��
		fontFamily->Release();
		familyNames->Release();
		delete[] name;
	}

	return result;
}

//=============================================================================
//     �I������
//=============================================================================
void DirectWrite::Release()
{
	// �����`��֘A�̃A�����[�h
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
//     string��wstring�֕ϊ�����
//=============================================================================
std::wstring DirectWrite::StringToWString(std::string oString)
{
	// SJIS �� wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	// �o�b�t�@�̎擾
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS �� wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	// string�̐���
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// �o�b�t�@�̔j��
	delete[] cpUCS2;

	// �ϊ����ʂ�Ԃ�
	return(oRet);
}
