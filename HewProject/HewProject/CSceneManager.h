#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"
#include "InputManager.h"
#include "Fade.h"
#include "xa2.h"

//static EffectManeger* EffectMane;

// �V�[�����Ǘ�����N���X
class CSceneManager
{
private:
	// �I�����邩�m�F�t���O
	bool isGameExit = false;
	CScene* pNowScene = nullptr;
	CScene::SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
	InputManager* inputManager = nullptr;
	Fade* fade;

	int playingBgm = -1;
	
	CSceneManager();

	~CSceneManager();

	// �V�[���}�l�[�W���[�Ɏ��́i�C���X�^���X�j
	static CSceneManager* instance;

public:
	// �V�[���}�l�[�W���[���擾
	// ���߂ČĂяo���ꂽ��C���X�^���X�𐶐�
	static CSceneManager* GetInstance();

	// �C���X�^���X���폜
	static void Delete();

	// �V�[���}�l�[�W���[�̎��s�֐�
	void Act();

	// �V�[����ݒ肷��
	void SceneChange(int _scene);

	// �V�[����ݒ肷��
	void SceneChangeStage(const wchar_t* _path);

	// �Q�[�����I������
	void Exit();

	// ���݂̃V�[�����擾
	CScene::SCENE_NAME GetNowScene();
	// �I���t���O�擾
	bool GetGameExit()const { return isGameExit; }

	// �V�[���ύX���Ă���m�F
	void SceneChangeCheck();

	// ���[�h�V�[���ɍs�����m�F
	void LoadSceneChangeCheck();

	// BGM��ύX����
	void SetPlayBgm(int _setBgm);
};

