#pragma once // �d���C���N���[�h�h�~

#include <d3d11.h> // DirectX11�Ƃ������C�u�����̃w�b�_�[
#include <DirectXMath.h>	// DirectX�̐��w�֘A�̃w�b�_�[�t�@�C��

// �N���X�������}�N��
#define CLASS_DELETE(p)	{ if( p != nullptr ) { delete p; p = nullptr; }}

// Direct3D������ȈՉ�����}�N��
#define SAFE_RELEASE(p)      { if( NULL != p ) { p->Release(); p = NULL; } }

// �����̌^����ʖ��ł��g����悤�ɂ���
typedef ID3D11ShaderResourceView* D3DTEXTURE;

typedef ID3D11Buffer* D3DBUFFER;


// �\���̂̒�`
// x,y��\���\����
struct FLOAT_XY
{
	float x, y;
};

// �萔�o�b�t�@�p�\����(c++����V�F�[�_�[�Ƀp�����[�^��n�����߂̍\���́j
struct ConstBuffer
{
	// UV���W�ړ��s��
	DirectX::XMMATRIX matrixTex;

	// ���e�s��
	DirectX::XMMATRIX matrixProj;

	// ���[���h�ϊ��s��
	DirectX::XMMATRIX matrixWorld;

	// �}�e���A���F
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };
};

// �֐��̃v���g�^�C�v�錾
HRESULT D3D_Create(HWND hwnd);
void    D3D_Release();

// �l�p�`�|���S�����쐬���A���_�o�b�t�@�������s��
void D3D_CreateSquare(FLOAT_XY size, FLOAT_XY uv, ID3D11Buffer** vb);	// **vb:�|�C���^�ϐ��̃A�h���X���i�[���ꂽ�|�C���^�ϐ�

// �e�N�X�`����ǂݍ��ފ֐�
// ��1�����F�e�N�X�`���̃t�@�C�����A��2�����F�e�N�X�`���i�[�p�ϐ��̃A�h���X
// �߂�l�F�G���[�`�F�b�N�̌���
HRESULT D3D_LoadTexture(const wchar_t* filename, ID3D11ShaderResourceView** Texture);

// ��ʓh��Ԃ��Ɛݒ���s���֐�
void D3D_ClearScreen();

//��ʍX�V����֐�
void D3D_UpdateScreen();

// �O���[�o���ϐ���extern�錾�i���낾�����쐬����A����ňႤcpp�t�@�C��������A�N�Z�X�ł���j
extern ID3D11DeviceContext* m_pImmediateContext;
extern ID3D11Buffer* m_pConstantBuffer;
extern const UINT strides;
extern const UINT offsets;
extern ID3D11BlendState* m_pBlendStateAlpha;
extern ID3D11BlendState* m_pBlendStateAdditive;