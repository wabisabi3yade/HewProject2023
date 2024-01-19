#pragma once
#include <iostream>
#include "direct3d.h"
#include "Transform.h"
class DoTween;

// �Q�[���S�̂̃t�F�[�h��S���N���X
class Fade
{
	// DoTween�̏��
	enum class STATE
	{
		STAY,	// �������Ă��Ȃ����
		FADE_IN,	// �t�F�[�h�������Ă���
		STOP, // �^�񒆂Ŏ~�܂��Ă�����
		FADE_OUT,
	};

	std::unique_ptr<DoTween> dotween;

	// �`��Ɏg�p���钸�_�o�b�t�@
	static D3DBUFFER mVertexBuffer;

	// �`��Ɏg�p����e�N�X�`��
	static D3DTEXTURE mTexture;

	DirectX::XMFLOAT4 materialDiffuse = { 1,1,1,1 };	// �}�e���A���F

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive = false;
	static bool isMakeInstance;	// �C���X�^���X�����ɍ������

	// �g�����X�t�H�[��
	Transform mTransform;

	Fade();
	~Fade();

public:
	static Fade* Get();

	void Draw();

	static void Init();

};

