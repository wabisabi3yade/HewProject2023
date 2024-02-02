#pragma once

class UI;

class ProteinUI
{
	// �X�e�[�W�ɂ���v���e�C���̐�
	short stageProMax;

	// �S�̂̃X�e�[�W�̍ő吔
	static const short max_pro = 3;
	// �v���e�C������ĂȂ����̊�
	UI* circle[max_pro];

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

	void Draw();
};

