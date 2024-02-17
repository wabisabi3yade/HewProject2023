#pragma once
#include "UI.h"

class FloorUI
{
	short stageFloorNum = 0;  // ���̃X�e�[�W�̍ő�̊K�w��

	short nowHilghtFloor = 0;

	static const short max = 3; // 3�K�܂�
	D3DBUFFER buffer;
	UI* floor[max][2];  // UI

	UI* baseUI;

	Vector3 o_pos;

	// �D�F�̂Ƃ��̑傫��
	Vector3 grayScale = { 0.5f,0.6f, 1.0f };
	// �n�C���C�g�̎��̑傫��
	Vector3 highlightScale = { 0.8f,0.96f, 0.8f };

	// ���W�ݒ�
	void SetPosition();

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_startFloorNum">�ŏ��Ɏn�܂�K�w</param>
	/// <param name="_maxNum">�ő�̊K�w</param>
	FloorUI(const int& _startFloorNum, const int& _maxNum);

	void Update();

	~FloorUI();

	void Draw();

	// �n�C���C�g���������K�w��ݒ�
	void SetHighlight(int _set);

	DoTweenUI* GetDotween() { return baseUI->dotween; }
};

