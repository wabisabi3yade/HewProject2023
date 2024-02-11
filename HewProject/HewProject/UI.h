#pragma once
#include "CAnimation.h"
#include "Transform.h"
#include "DotweenUI.h"

#define UI_OFFSETZ (0.0001f)

class UI
{

protected:
	bool isActive;	// �\���E��\���@�\
	// uv���W��錾
	FLOAT_XY uv = { 0,0 };

	CAnimation* mAnim;	// �A�j���[�V�����N���X

	// �`��Ɏg�p���钸�_�o�b�t�@
	D3DBUFFER mVertexBuffer;

	// �`��Ɏg�p����e�N�X�`��
	D3DTEXTURE mTexture;
public:
	Transform mTransform;	// �g�����X�t�H�[��
	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// �}�e���A���F

	DoTweenUI* dotween;

	UI();
	UI(D3DBUFFER vb, D3DTEXTURE tex);	// �o�b�t�@�A�e�N�X�`����ݒ肷��Ƃ�
	virtual ~UI();

	void Init();

	virtual void Update();

	virtual void Draw();	// �`��֐�

	void MakeDotween();	// DoTween���g�p����ꍇ��new������ɌĂяo��

	// �\���E��\���؂�ւ��֐�
	void SetActive(const bool& _setActive) { isActive = _setActive; }

	void SetBuffer(const D3DBUFFER _vb) { mVertexBuffer = _vb; }
	void SetTexture(const D3DTEXTURE _tex) { mTexture = _tex; }

	void SetUV(const float& _setU, const float& _setV) { uv.x = _setU; uv.y = _setV; }

	/// <summary>
	/// UI�̐F��ݒ肷��
	/// </summary>
	/// <param name="_color">x�F�� y�F�� z�F�� �i0�`255)</param>
	void SetColor(DirectX::XMFLOAT3 _color);
	
	/// <summary>
	///  UI�̓����x��ݒ肷��
	/// </summary>
	/// <param name="_alpha">�����x�i0.0�`1.0�j</param>
	void SetAlpha(float _alpha);
};

