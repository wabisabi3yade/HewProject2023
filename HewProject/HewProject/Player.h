#pragma once
#include "CGridObject.h"
#include <iostream>
#include "CGrid.h"
#include "DoTween.h"
#include "PlayerMove.h"
#include"CPlayerAnim.h"

#define MOVEROOT_MAX (20)	// ���܂Ŏ���Ă�������ۑ�����ő吔
#define EAT_TIME (1.0f)	// �H�ו��H�ׂ鎞��
#define BREAK_TIME (3.0f) //�ǂ��󂵂Ă���ړ��ł���܂ł̎���
#define FALL_TIME (3.0f) //�`���R�����Ă��痎���n�߂�܂ł̎���
#define FALLMOVE_TIME (1.0f) //������ړ�����
#define FALL_POS_Y (-4.5f) //������ŏI���W
#define JUMP_TIME (1.5f) //�W�����v�̈ړ�����
#define BOUND_TIME (1.0f) //�W�����v��̃o�E���h���鎞��
constexpr float RISING_TIME = 0.5f; //�O�~�ł̏㏸����
#define THIN_CALOMAX (5)	// �K����Ԏ��ł̍ő�J�����[�� 
#define NORMAL_CALOMAX (10)	// ���ʏ�Ԏ��ł̍ő�J�����[�� 
constexpr float CANNONMOVE_TIME = 1.0f;		//��C�ł̂��ǂ�������
constexpr float CANNONBOUND_TIME = 1.0f;	//��C�ŖړI�n�ł̃o�E���h���鎞��
constexpr float CANNONBOUND_POS_Y = 3.0f;	//��C�ŖړI�n�ł̃o�E���h���鍂��

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
		DOWN,	// ��
		LEFT,	// ��
		RIGHT,	// �E
		UP,	// ��
		NUM,
		EVERY,	// �S���ʈړ��\�i�L�����̉摜�̌����͉������j
	};

	enum ANIM_TEX
	{
		WALK,
		EAT_CAKE,
		EAT_CHILI,
		ACTION,
		WAIT,
		NUM,
		CANNON,
		CASSTELA,
		PUNCH,
	};

private:
	STATE playerState;	// �v���C���[�̍��̏��

	DIRECTION direction;	// �������Ă������

	std::shared_ptr<PlayerMove> move;	// PlaterMove�N���X(��ԕʂ̃A�h���X������)

	// ���܂Œʂ��Ă����o�H��ۑ�������W
	CGrid::GRID_XY moveRoot[MOVEROOT_MAX];

	int calorie;	// �J�����[

	int nowFloor;	// �����w�ڂɂ��邩

	bool IsgameOver;

	bool ChangeCannonTexture;

	bool fallFloorChangeTrriger; //�����ĊK�w���ς������
	bool risingChangeTrriger;

	GridTable* gridTable;// �X�e�[�W�̃O���b�h�e�[�u���̃|�C���^��ݒ�
	GridTable* nextGridTable; //���̊K�w�O���b�h�e�[�u���̃|�C���^��ݒ�

	// �e�N�X�`���i��ԕʁj
	D3DTEXTURE normalTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE fatTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE thinTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE muscleTex[static_cast<int>(ANIM_TEX::NUM)];
	D3DTEXTURE cannonTex;
	//DIRECTION�Ɠ��������̃p���`�̉摜���i�[
	D3DTEXTURE punchTex[static_cast<int>(DIRECTION::NUM)];
	// �摜����ɔz��ɓ����
	// �����@�F�e�N�X�`���p�X �A �x�̏�Ԃ̔z��ɓ���邩
	void TextureInput(const wchar_t* _texPath, STATE _set , ANIM_TEX _anim_tex);
	
public:
	bool fallMoveTrriger;
	bool risingMoveTrriger;
	std::unique_ptr<DoTween> dotween;

	Player(D3DBUFFER vb, D3DTEXTURE tex);

	/// <summary>
	/// �X�e�[�W�ɓ��������Ɏg���鏉�����֐�
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

	void ChangeTexture(ANIM_TEX _animTex);

	void Draw() override;

	void Fall();

	void Rise();

	~Player();

	int GetCalorie() const { return calorie; }
	void SetCalorie(int _cal) { calorie = _cal; }
	bool GetIsMoving()const;
	int GetDirection()const;
	void SetDirection(int _set);
	void SetChangeCannonTexture(const bool _set) { ChangeCannonTexture = _set; }

	PlayerMove* GetPlayerMove()const;

	CPlayerAnim* GetPlayerAnim() { return dynamic_cast<CPlayerAnim*> (mAnim); }

	bool GetIsGameOver() { return  IsgameOver; }
	int GetNowFloor() { return nowFloor; }
	void SetNowFloor(int _set);
	void GameOver();
	bool GetFallTrriger() { return fallMoveTrriger; }
	bool GetFallFloorChageTrriger() { return fallFloorChangeTrriger; }
	bool GetRiseFloorChangeTrriger() { return risingChangeTrriger; }
	bool GetRiseTrriger() { return risingMoveTrriger; }
	bool GetCangeCannonTexture() { return ChangeCannonTexture; }
	void SetGridTable(GridTable* _set) { gridTable = _set; }
	void SetNextGridTable(GridTable* _set) { nextGridTable = _set; }
	GridTable* GetGridTable() const { return gridTable; }
	GridTable* GetNextGridTable()const { return nextGridTable; }
	bool* GetCanMoveDir() { return move->GetCanMoveDir(); }
	STATE GetState() const { return playerState; }
};

