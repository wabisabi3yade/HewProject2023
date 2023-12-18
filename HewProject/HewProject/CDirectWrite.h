#pragma once
#include <dwrite_3.h>
#include <d2d1.h>
#include <d3d11_1.h>
#include <DirectXColors.h>
#include <Windows.h>
#include <iostream>
#include <DirectXMath.h>
#include <vector>						// ���I�z��


//=============================================================================
//		�t�H���g���X�g
//=============================================================================
enum class Font
{
	marker,
	komadorimini,
	MelodyLine,
	HG_Gyosyo,
	HGP_POP,
	MS_Mincho,
	Arial,
	MeiryoUI,
};


//=============================================================================
//		�t�H���g�ݒ�
//=============================================================================
struct FontData
{
	Font font;					// �t�H���g��
	DWRITE_FONT_WEIGHT fontWeight;			// �t�H���g�̑���
	DWRITE_FONT_STYLE fontStyle;			// �t�H���g�X�^�C��
	DWRITE_FONT_STRETCH fontStretch;		// �t�H���g�̕�
	FLOAT fontSize;					// �t�H���g�T�C�Y
	WCHAR const* localeName;			// ���P�[����
	DWRITE_TEXT_ALIGNMENT textAlignment;		// �e�L�X�g�̔z�u
	D2D1_COLOR_F Color;				// �t�H���g�̐F

	// �f�t�H���g�ݒ�
	FontData()
	{
		font = Font::MS_Mincho; //�K���ȏ����t�H���g
		fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize = 30;
		localeName = L"ja-jp";
		textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color = D2D1::ColorF(D2D1::ColorF::White);
	}
};

//=============================================================================
//		DirectWrite�ݒ�
//=============================================================================
class DirectWrite
{
private:
	ID2D1Factory* pD2DFactory = NULL;
	IDWriteFontCollection1* pDWFontCollection = NULL;
	IDWriteFactory5* pDWriteFactory = NULL;
	IDWriteTextFormat* pTextFormat = NULL;
	IDWriteTextLayout* pTextLayout = NULL;
	ID2D1RenderTarget* pRT = NULL;
	ID2D1SolidColorBrush* pSolidBrush = NULL;
	IDXGISurface* pBackBuffer = NULL;

	// �t�H���g�f�[�^
	FontData* Setting = new FontData();

	// string��wstring�֕ϊ�����
	std::wstring StringToWString(std::string oString);

public:
	DirectWrite();
	~DirectWrite();

	// �R���X�g���N�^
	// ��1�����F�t�H���g�ݒ�
	DirectWrite(FontData* set) :Setting(set) { };

	// �t�H���g�ݒ�
	// ��1�����F�t�H���g�f�[�^�\����
	void SetFont(FontData* set);

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
	void SetFont(Font font,												// �t�H���g��
		IDWriteFontCollection* fontCollection = nullptr,				// �t�H���g�R���N�V����
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL,		// �t�H���g�̑���
		DWRITE_FONT_STYLE fontStyle = DWRITE_FONT_STYLE_NORMAL,			// �t�H���g�X�^�C��
		DWRITE_FONT_STRETCH fontStretch = DWRITE_FONT_STRETCH_NORMAL,	// �t�H���g�̕�
		FLOAT fontSize = 30,											// �t�H���g�T�C�Y
		WCHAR const* localeName = L"ja-jp",								// ���P�[����
		DWRITE_TEXT_ALIGNMENT textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING,	// �e�L�X�g�̔z�u
		D2D1_COLOR_F Color = D2D1::ColorF(D2D1::ColorF::Black));		// �t�H���g�̐F

	// �����`��
	// string�F������
	// pos�F�`��|�W�V����
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options);

	// �����`��
	// string�F������
	// rect�F�̈�w��
	// options�F�e�L�X�g�̐��`
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);

	// ������
	HRESULT Init(HWND hwnd);

	// �I������
	void Release();

private:
	// �t�H���g�����X�g
	std::vector<std::wstring> fontNamesList;


	// �t�H���g�����擾����
	HRESULT GetFontFamilyName(IDWriteFontCollection* customFontCollection, const WCHAR* locale = L"en-us");

	// �J�X�^���t�H���g�R���N�V����
	IDWriteFontCollection1* fontCollection = nullptr;

	// �t�H���g�t�@�C�����X�g
	std::vector< IDWriteFontFile*>pFontFileList;

public:
	int nKcal = 10;
};


extern ID3D11Device* m_pDevice; // �f�o�C�X��DirectX�̊e�@�\�����
extern IDXGISwapChain* m_pSwapChain;// �_�u���o�b�t�@�@�\
extern ID3D11DeviceContext* m_pImmediateContext;// �R���e�L�X�g���`��@�\
extern ID3D11RenderTargetView* m_pRenderTargetView;
