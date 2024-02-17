#pragma once
#include <iostream>
#include "direct3d.h"
#include <functional>

#define FADE_BACK_NUM (2)	// �t�F�[�h�w�i�̐�

class FadeUI;
class UI;

// �Q�[���S�̂̃t�F�[�h��S���N���X
class Fade
{
public:
	// DoTween�̏��
	enum STATE
	{
		STAY,	// �������Ă��Ȃ����
		FADE_IN,	// �t�F�[�h�������Ă���
		LOADING, // ���[�f�B���O
		FADE_OUT,
	};

private: 
	static Fade* instance;

	bool isSceneChange = false;
	bool isLoadChange = false;

	bool isFadeInEnd = false;

	int nextScene;	// ���̃V�[��

	// �A�N�e�B�u/��A�N�e�B�u�؂�ւ��ϐ�
	bool isActive;
	// ���[�h�̎���
	float loadingTime;

	STATE state;	// �t�F�[�h�����ǂ̏�Ԃ�
	STATE nextState;	// ���̃t�F�[�h���ǂ̏�Ԃ�

	UI* fadeBase;	// ��I�u�W�F�N�g(Fade�̑S�̂̍��W)

	// ���[�f�B���O
	UI* backGround;	// �w�i
	UI* nowLoading;	// �e�L�X�g
	UI* character;	// �L�����N�^�[

	std::function<void()> func = nullptr;

	Fade();
	~Fade();

	D3DTEXTURE tex;
	D3DBUFFER vb;

	void SceneChange();

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
	/// �����@ �t�F�[�h�C��������ɂ�����
	/// FADE_OUT:�����Ƀt�F�[�h���J����
	/// LOADING:���[�f�B���O�ɓ���
	/// 
	/// �����A�@�t�F�[�h��̂�邱��
	void FadeIn(const STATE& _nextState, std::function<void()> _onFunc = nullptr, 
		int _setScene = -1);

	// ���[�f�B���O�̂��߂̏�����������
	void LoadingInit();
	// �t�F�[�h�A�E�g����
	void FadeOutInit();

	void Draw();

	// ���[�h�V�[���ɑJ�ڂ���
	void ChangeLoadScene();

	bool GetIsChange();

	bool GetLoadChange();
	
	// ���̃V�[���Ɉڍs
	int GetNextScene();

	int GetState()const { return state; }

};

