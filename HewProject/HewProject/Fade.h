#pragma once
#include <iostream>
#include "direct3d.h"
#include "Transform.h"

class CObject;
class DoTween;

// �Q�[���S�̂̃t�F�[�h��S���N���X
class Fade
{
	// DoTween�̏��
	enum class STATE
	{
		STAY,	// �������Ă��Ȃ����
		FADE_IN,	// �t�F�[�h�������Ă���
		LOADING, // ���[�f�B���O
		FADE_OUT,
	};

	static Fade* instance;

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive = false;

	// �t�F�[�h�����x�̏�Ԃ�
	STATE state;

	// �`��Ɏg�p���钸�_�o�b�t�@
	D3DBUFFER mVertexBuffer;

	// �`��Ɏg�p����e�N�X�`��
	D3DTEXTURE mTexture;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// �}�e���A���F

	// �g�����X�t�H�[��
	CObject* empty;

	Fade();
	~Fade();

public:
	static Fade* GetInstance();

	static void Delete();

	void Update();
	void StayUpdate();
	void FadeInUpdate();
	void LoadingUpdate();
	void FadeOutUpdate();

	void Draw();
};

