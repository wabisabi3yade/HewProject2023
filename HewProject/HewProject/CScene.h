#pragma once
#include "direct3d.h"
#include "CObject.h"
#include "CInput.h"
#include "direct3d.h"

class CSceneManager; //�}�l�[�W���̃v���g�^�C�v�錾

// �V�[���̊�b�N���X
class CScene
{
public:
	// �V�[���̖��O
	enum SCENE_NAME
	{
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
		NONE,	// �Ȃɂ��Ȃ�
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

