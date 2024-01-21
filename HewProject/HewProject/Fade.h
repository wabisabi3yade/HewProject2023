#pragma once
#include <iostream>
#include "direct3d.h"

#define FADE_BACK_NUM (2)	// �t�F�[�h�w�i�̐�

class FadeUI;
class UI;

// �Q�[���S�̂̃t�F�[�h��S���N���X
class Fade
{
public:
	// DoTween�̏��
	enum class STATE
	{
		STAY,	// �������Ă��Ȃ����
		FADE_IN,	// �t�F�[�h�������Ă���
		LOADING, // ���[�f�B���O
		FADE_OUT,
	};

private:
	static Fade* instance;

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive;

	// ���[�h�̎���
	float loadingTime;

	STATE state;	// �t�F�[�h�����ǂ̏�Ԃ�
	STATE nextState;	// ���̃t�F�[�h���ǂ̏�Ԃ�

	UI* fadeBase;	// ��I�u�W�F�N�g(Fade�̑S�̂̍��W)
	FadeUI* backGround[FADE_BACK_NUM];	// �w�i

	Fade();
	~Fade();

	D3DTEXTURE tex;
	D3DBUFFER vb;

public:
	static Fade* GetInstance();

	static void Delete();

	void Update();

	void FadeInUpdate();
	void LoadingUpdate();
	void FadeOutUpdate();

	/// <summary>
	/// �t�F�[�h�C������֐�
	/// </summary>
	/// ���� �t�F�[�h�C��������ɂ�����
	/// FADE_OUT:�����Ƀt�F�[�h���J����
	/// LOADING:���[�f�B���O�ɓ���
	void FadeIn(const STATE& _nextState);

	// ���[�f�B���O�̂��߂̏�����������
	void LoadingInit();
	// �t�F�[�h�A�E�g����
	void FadeOutInit();

	void Draw();
};

