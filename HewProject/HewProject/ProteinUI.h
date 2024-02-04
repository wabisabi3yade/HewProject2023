#pragma once
#include "UI.h"

class ProteinUI
{
	// �S�̂̍��W
	Transform mTransform;

	// �X�e�[�W�ɂ���v���e�C���̐�
	short stageProMax = 0;

	// ������v���e�C���̐�
	short getProtein = 0;

	// �S�̂̃X�e�[�W�̍ő吔
	static const short max_pro = 3;

	D3DBUFFER buffer;

	// �v���e�C������ĂȂ����̊�
	UI* proMark[max_pro];

	// �v���e�C���̃X�P�[��
	Vector3 proScale = { 1.4f, 1.4f, 1.0f };
	// �v���e�C���}�[�N
	UI* protein[max_pro];
	// ���̃o�[
	UI* bar;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="_proteinNum">���̃X�e�[�W�ɂ���v���e�C���̐�</param>
	ProteinUI(const int& _proteinNum);
	~ProteinUI();

	void Update();
	// �u���ɔ��f
	void SetProtein(const int& _getProtein);

	void AddProtein();

	void Draw();

	void SetPosition(const Vector3& _pos);
};

