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
		SCENE_NUM,	// �V�[���̐�

		SELECT,	// �Z���N�g�V�[��
	};

private:
	// �V�[���}�l�[�W���[
	CSceneManager* pSceneManager = nullptr;

protected:
	int nextScene;

	// �V�[����ς���t���O
	bool isSceneChange = false;
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

	//�@�V�[���}�l�[�W���[��ς��Ă��邩�m�F����
	void SceneChangeCheck();

	// �V�[���ς��t���O���擾
	bool GetSceneChange() { return isSceneChange; }

	// ���ɕς���V�[�����擾
	int GetNextScene() { return nextScene; }

};

