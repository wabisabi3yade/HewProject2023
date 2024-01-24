#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"
#include "Fade.h"

//static EffectManeger* EffectMane;

// �V�[�����Ǘ�����N���X
class CSceneManager
{
private:
	CScene* pNowScene = nullptr;
	CScene::SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
	Fade* fade;
	
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

	// ���݂̃V�[�����擾
	CScene::SCENE_NAME GetNowScene();
};

