#pragma once
#include "Transform.h"
#include "UI.h"

#define MARKNUM_MAX (15)	// �ڐ���̍ő吔

class CalorieMark;

// �J�����[�Q�[�W�̃N���X
class CalorieGage_hori
{
	UI* base;

	Vector3 o_pos;
	/*Transform mTransform;*/	// �Q�[�W�S�̂̃g�����X�t�H�[��

	D3DBUFFER oneBuffer;
	D3DBUFFER markBuffer;
	D3DBUFFER numBuffer;

	CalorieMark* mark[MARKNUM_MAX];	// �ڐ���
	const Vector3 markScale = { 0.3f, 0.8f, 1.0f };	// �ڐ���̊�ƂȂ�傫��

	static const short calorieDigits = 2;	// �J�����[�̐����̌���
	UI* number[calorieDigits];	// ������UI
	const Vector3 numScale = { 0.8f, 0.8f, 1.0f };

	UI* rogo;	// ���X�̃��S
	const Vector3 rogoScale = { 1.75f, 1.75f, 1.0f };	// ���S�̊�ƂȂ�傫��

	UI* back;	// �Q�[�W�̔w�i
	const Vector3 backScale = { 6.0f, 1.0f, 1.0f };	// ���S�̊�ƂȂ�傫��

	float mark_offsetX;

	short int calorieNum = 8;

	/// <summary>
	/// �ڐ����ς���
	/// </summary>
	/// <param name="_oldNum">�ς��O�̖ڐ���</param>
	/// <param name="_add">�������ڐ���</param>
	void MarkAdd(const short& _oldNum, const short& _add);

	void NumUISetting();

public:
	CalorieGage_hori();
	~CalorieGage_hori();

	void Update();

	void Draw();

	void SetPosition(const Vector3& _pos);
	void SetScale(const Vector3& _scale);

	/// <summary>
	/// �J�����[�̐���ݒ�(�P�[�L�H�ׂ�Ƃ��͂���)
	/// </summary>
	/// <param name="_set">�ݒ肵������</param>
	/// <param name="action">���o���肩�ǂ���(Undo�͉��o�Ȃ�)</param>
	void SetCalorie(const short& _set, bool action = true);

	// �J�����[�𑫂�(�����Ƃ��̓}�C�i�X�̒l)�@(�ړ��A�Ƃ����炵�͂���)
	void AddCalorie(const short& _add);

	DoTweenUI* GetDotween() { return base->dotween; }
};

