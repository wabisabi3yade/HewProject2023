#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"
#include "PlayerMove.h"

#define MOVEROOT_MAX (20)	// ���܂Ŏ���Ă�������ۑ�����ő吔
#define EAT_TIME (1.0f)	// �H�ו��H�ׂ鎞��
#define THIN_CALOMAX (5)	// �K����Ԏ��ł̍ő�J�����[�� 
#define NORMAL_CALOMAX (10)	// ���ʏ�Ԏ��ł̍ő�J�����[�� 

// �v���C���[�i���X�j�̃I�u�W�F�N�g�N���X
class Player :
	public CGridObject
{
public:
	enum class STATE
	{
		NORMAL,	// �ʏ�
		THIN,	// �K��
		FAT,	// �f�u
		MUSCLE,	// �}�b�`��
		NUM
	};

	// ����
	enum class DIRECTION
	{
		UP,
		DOWN,
		RIGHT,
		LEFT,
		NUM
	};

private:
	STATE playerState;	// �v���C���[�̍��̏��

	DIRECTION direction;	// �������Ă������

	std::shared_ptr<PlayerMove> move;	// PlaterMove�N���X(��ԕʂ̃A�h���X������)

	// ���܂Œʂ��Ă����o�H��ۑ�������W
	CGrid::GRID_XY moveRoot[MOVEROOT_MAX];

	int calorie;	// �J�����[

	int nowFloor;	// �����w�ڂɂ��邩

	GridTable* gridTable;// �X�e�[�W�̃O���b�h�e�[�u���̃|�C���^��ݒ�

	// �e�N�X�`���i��ԕʁj
	std::vector<D3DTEXTURE> normalTex;	
	std::vector<D3DTEXTURE> fatTex;
	std::vector<D3DTEXTURE>	thinTex;
	std::vector<D3DTEXTURE> muscleTex;
	
	
	// �摜����ɔz��ɓ����
	// �����@�F�e�N�X�`���p�X �A �x�̏�Ԃ̔z��ɓ���邩
	void TextureInput(const wchar_t* _texPath, STATE _set);
	
public:
	std::unique_ptr<DoTween> dotween;

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̏������֐�
	/// </summary>
	/// <param name="_grid">�X�^�[�g���̃O���b�h���W</param>
	/// <param name="_pTable">�O���b�h�e�[�u��</param>
	void Init(GridTable* _pTable);

	void Update() override;

	// �J�����[�Ɋւ��鏈��
	void WalkCalorie();
	void EatCake();
	void EatChilli();

	/// <summary>
	/// ��Ԃ�ω�����Ƃ��ɏ���������֐�
	/// </summary>
	/// <param name="_set">�ω���̏��</param>
	void ChangeState(STATE _set);

	void Draw() override;

	~Player();

	int GetCalorie() const { return calorie; }
	bool GetIsMoving()const;
	int GetDirection()const;
	void SetDirection(int _set);

	PlayerMove* GetPlayerMove()const;

	void SetGridTable(GridTable* _set) { gridTable = _set; }
	GridTable* GetGridTable() const { return gridTable; }

	STATE GetState() const { return playerState; }
};

