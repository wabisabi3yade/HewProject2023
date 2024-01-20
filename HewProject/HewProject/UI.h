#pragma once
#include "CAnimation.h"
#include "Transform.h"

class UI
{

protected:
	bool isActive;	// �\���E��\���@�\
	CAnimation* mAnim;	// �A�j���[�V�����N���X

	Transform mTransform;	// �g�����X�t�H�[��

	// �`��Ɏg�p���钸�_�o�b�t�@
	D3DBUFFER mVertexBuffer;

	// �`��Ɏg�p����e�N�X�`��
	D3DTEXTURE mTexture;

public:
	UI();
	UI(D3DBUFFER vb, D3DTEXTURE tex);	// �o�b�t�@�A�e�N�X�`����ݒ肷��Ƃ�
	virtual ~UI();
	
	void Init();

	virtual void Draw() = 0;	// �`��֐�

	// �\���E��\���؂�ւ��֐�
	void SetActive(const bool& _setActive) { isActive = _setActive; }

	void SetBuffer(const D3DBUFFER _vb) { mVertexBuffer = _vb; }
	void SetTexture(const D3DTEXTURE _tex) { mTexture = _tex; }

};

