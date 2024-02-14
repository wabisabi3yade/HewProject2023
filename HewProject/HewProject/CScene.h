#pragma once
#include "direct3d.h"
#include "CObject.h"
#include "CInput.h"
#include "direct3d.h"
#include "Fade.h"

class CSceneManager; //�}�l�[�W���̃v���g�^�C�v�錾

// �V�[���̊�b�N���X
class CScene
{
public:
	// �V�[���̖��O
	enum SCENE_NAME
	{
		NONE  = -1,	// �Ȃɂ��Ȃ�

		KAWADA,	// �͓c�V�[��
		TATEMIZO,	// ���a�V�[��
		MIZUNO,	// ����V�[��
		WAKAMURA,	// �ᑺ�V�[��
		HASHIMOTO,	// ���{�V�[��
		// ���@�V�[����ǉ�����Ȃ炱���ɏ����Ă�
		STAGE1,
		FADE_TEST,
		TITLE,
		GAMEOVER,
		GAMECLEAR,
		WORLD1_SELECT,
		WORLD2_SELECT,
		MENU,
		GAMESTART,
		WORLD3_SELECT,
		WORLD4_SELECT,
		LOADING,	// ���[�f�B���O

		SCENE_NUM,	// �V�[���̐�

		// 1���[���h
		STAGE1_1,
		STAGE1_2,
		STAGE1_3,
		STAGE1_4,
		STAGE1_5,
		STAGE1_6,

		// 2���[���h
		STAGE2_1,
		STAGE2_2,
		STAGE2_3,
		STAGE2_4,

		// 3���[���h
		STAGE3_1,
		STAGE3_2,
		STAGE3_3,
		STAGE3_4,

		// 4���[���h
		STAGE4_1,
		STAGE4_2,
		STAGE4_3,
		STAGE4_4,
		
		SELECT,	// �Z���N�g�V�[��
		HOSODA_SELECT
	};

private:
	

protected:
	// �V�[���}�l�[�W���[
	CSceneManager* pSceneManager = nullptr;

	int nextScene;

	// �V�[����ς���t���O
	bool isSceneChange = false;
	bool isExit = false;
public:
	CScene();

	virtual ~CScene();

	// �X�V����
	virtual void Update() = 0;

	// Update�̂��Ƃɍs����X�V�i�J�����̍X�V�Ƃ��͂����ɏ����j
	virtual void LateUpdate() = 0;

	// �`�������
	virtual void Draw() = 0;

	// �V�[����ς���Ƃ��ɌĂԊ֐�
	void SetScene(int _nextScene);

	void Exit();

	//�@�V�[���}�l�[�W���[��ς��Ă��邩�m�F����
	void SceneChangeCheck();

	// �I�����邩�m�F
	void ExitCheck();

	// �V�[���ς��t���O���擾
	bool GetSceneChange() { return isSceneChange; }

	// ���ɕς���V�[�����擾
	int GetNextScene() { return nextScene; }

};

