#pragma once
#include "UI.h"

class ProteinUI
{
	// �S�̂̍��W
	Transform mTransform;

	UI* baseUI;

	Vector3 o_pos;

	bool isMarkActive = true;

	// �X�e�[�W�ɂ���v���e�C���̐�
	short stageProMax = 0;

	// ������v���e�C���̐�
	short getProtein = 0;

	// �S�̂̃X�e�[�W�̍ő吔
	static const short max_pro = 3;

	D3DBUFFER buffer;

	// �S�̂̔{��
	Vector2 allScale = { 1.0f, 1.0f };

	// �v���e�C������ĂȂ����̊�
	UI* proMark[max_pro];

	// �v���e�C���̃X�P�[��
	const Vector3 proScale = { 1.4f, 1.4f, 1.0f };

	float proOffset = 0.0f;

	// �v���e�C���}�[�N
	UI* protein[max_pro];
	// ���̃o�[
	UI* bar;

	const Vector3 barScale = { 3.0f, 0.05f, 1.0f };

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_proteinNum">���̃X�e�[�W�ɂ���v���e�C���̐�</param>
	ProteinUI(const int& _proteinNum, bool _isMarkActive = true);
	~ProteinUI();

	void Update();
	// �u���ɔ��f
	void SetProtein(int _getProtein, bool _isDecade = false);

	void AddProtein();

	void Draw();

	void SetPosition(const Vector3& _pos);

	void SetScale(const Vector2& _pos);

	void SetActive(bool _isActive);

	DoTweenUI* GetDotween() { return baseUI->dotween; }
};

