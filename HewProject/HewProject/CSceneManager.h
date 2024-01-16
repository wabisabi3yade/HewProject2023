#pragma once
#include "CScene.h"
#include "CEffectManeger.h"
#include "TextureFactory.h"

//static EffectManeger* EffectMane;

// �V�[�����Ǘ�����N���X
class CSceneManager
{

public :
	// �V�[���̖��O
	enum SCENE_NAME
	{
		KAWADA,	// �͓c�V�[��
		TATEMIZO,	// ���a�V�[��
		MIZUNO,	// ����V�[��
		WAKAMURA,	// �ᑺ�V�[��
		HASHIMOTO,	// ���{�V�[��
		// ���@�V�[����ǉ�����Ȃ炱���ɏ����Ă�

		SCENE_NUM,	// �V�[���̐�

		SELECT,	// �Z���N�g�V�[��
	};

private:
	CScene* pNowScene = nullptr;
	SCENE_NAME nowSceneName;
		
	EffectManeger* effectManeger;
	TextureFactory* textureFactory;
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

	// ���݂̃V�[�����擾
	SCENE_NAME GetNowScene();
};

