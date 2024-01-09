#pragma once
#include <iostream>
#include "Vector3.h"
#include <vector>
#include "GridTable.h"
#include "CStageMake.h"

#define WALK_TIME (1.0f)	// �����Ƃ��̈ړ�����

class Player;

class PlayerMove
{

public:
	// ����
	enum class DIRECTION
	{
		DOWN,
		LEFT,
		RIGHT,
		UP,
		NUM
	};

protected:
	Player* player;	// �v���C���[�N���X�̃|�C���^

	bool canMoveDir[static_cast<int>(DIRECTION::NUM)];	// �ړ��\�ł������

	bool isMoving;	// �ړ��\�t���O

	bool isMoveStartTrigger;	// �����n�߂��t���O

	bool isMovingTrigger;	// isMove = true->false�ɕς�����u�Ԃ���true

	bool isWalkEnd;	// �����I������u��true

	bool isWalking_old;	//	�O

	bool isWalking_now;	//�@��

	CGrid::GRID_XY nextGridPos;	// �ړ���̍��W�iMoveAfter�Ńv���C���[�̃O���b�h���W�ɍX�V���Ă���j

	std::vector<int> cantMoveBlock;	// �ړ��ł��Ȃ����̎�ނ�ێ�

public:
	PlayerMove(Player* _p);

	// ���͊֐�
	void Input();
	// �t���O������������
	void FlagInit();
	// ���͂����ƈړ����s���֐�
	virtual void Move(DIRECTION _dir) = 0;

	// �����I�������ɂ��鏈���i�����I����ĐH�ׂ�A�j���[�V�����������肷��j
	virtual void WalkAfter();

	// ���S�Ɉړ����I�������ɂ��鏈���i���ɐi�ޕ����������ł��߂��肷��j
	// �����@�ړ���̃O���b�h���W
	virtual void MoveAfter();

	void WalkStart();

	// �v���C���[�̈ړ���̍��W�ɂ���}�X�̎�ނ��擾����
	// �I�u�W�F�N�g�D�恨�Ȃɂ��Ȃ��Ȃ珰�̎�ނ��A���Ă���
	// �ԈႦ�Ă��邩������Ȃ������E�E�E
	CStageMake::BlockType CheckNextMassType();

	// �ړ���̃v���C���[�̃O���b�h���W�ɂ��镨�̎�ނ��擾����
	CStageMake::BlockType CheckNextObjectType();

	// �ړ���̃v���C���[�̃O���b�h���W�ɂ��鏰�̎�ނ��擾����
	CStageMake::BlockType CheckNextFloorType();

	CStageMake::BlockType CheckNowFloorType();

	// �ǂ̕����Ɉړ����ł��邩�擾����֐�
	virtual void  CheckCanMove() = 0;

	virtual ~PlayerMove();

	CGrid::GRID_XY GetNextGridPos() const { return nextGridPos; };

	bool GetIsMoving()const { return isMoving; }
	bool GetIsMoveStart()const { return isMoveStartTrigger; }
	bool GetIsMoveTrigger() const { return isMovingTrigger; }
	bool GetIsWalkEnd() const { return isWalkEnd; }
	bool GetIsWaik_Now() const { return isWalking_now; }
	bool GetIsWaik_Old() const { return isWalking_old; }
};

