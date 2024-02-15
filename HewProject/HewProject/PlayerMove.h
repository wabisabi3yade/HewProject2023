#pragma once
#include <iostream>
#include "Vector3.h"
#include <vector>
#include "GridTable.h"

class CEffect;
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

	//��C�ړ����Ɉ�}�X�ړ���ɂ��Ԃ�̃}�X���m�F��
	//�����̃^�C�v���擾���邽�߈ړ������u�ԂɎ��̃^�C�v��ێ�����ϐ�
	CGridObject::BlockType nextCannonType;

	bool canMoveDir[static_cast<int>(DIRECTION::NUM)];	// �ړ��\�ł������

	bool cannonMoveDir[static_cast<int>(DIRECTION::NUM)];

	bool isMoving;	// �ړ��\�t���O

	bool isMoveStartTrigger;	// �����n�߂��t���O

	bool isMovingTrigger;	// isMove = true->false�ɕς�����u�Ԃ���true

	bool isWalkEnd;	// �����I������u��true

	bool isWalking_old;	//	�O

	bool isWalking_now;	//�@��

	bool isFalling;   //������

	bool isRising;   //�㏸��

	bool isLookMap;   //�}�b�v������

	bool isFallBound;

	bool isMenu;   //���j���[��ʂ��J���Ă���

	bool flagInit;

	bool cannonFX;
	bool inCannon;
	bool isCannonMove;
	bool isCannonMoveStart;
	bool isCannonMoveStartTrigger;
	bool isCannonMoveEnd;

	CGrid::GRID_XY nextGridPos;	// �ړ���̍��W�iMoveAfter�Ńv���C���[�̃O���b�h���W�ɍX�V���Ă���j
	CGrid::GRID_XY nextCannonPos;
	std::vector<int> cantMoveBlock;	// �ړ��ł��Ȃ����̎�ނ�ێ�

public:
	PlayerMove(Player* _p);

	// ���͊֐�
	void Input();
	// �t���O������������
	void FlagInit();
	// ���͂����ƈړ����s���֐�
	virtual void Move(DIRECTION _dir) = 0;

	virtual void Step() =  0 ;

	// �����I�������ɂ��鏈���i�����I����ĐH�ׂ�A�j���[�V�����������肷��j
	virtual void WalkAfter();

	// ���S�Ɉړ����I�������ɂ��鏈���i���ɐi�ޕ����������ł��߂��肷��j
	// �����@�ړ���̃O���b�h���W
	virtual void MoveAfter();

	void WalkStart();

	void  FallStart();

	void RiseStart();
	//�����I��������Ƃɂ��鏈��
	virtual void FallAfter();

	virtual void RiseAfter();

	void InCannon();

	void CannonMove1();

	void CannonMove2();

	void CannonMoveStart();

	void CannonDirSelect(DIRECTION _dir);

	bool kari = false;

	void CameraEnd();

	bool GetisLoolMap() const { return isLookMap; };

	// �v���C���[�̈ړ���̍��W�ɂ���}�X�̎�ނ��擾����
	// �I�u�W�F�N�g�D�恨�Ȃɂ��Ȃ��Ȃ珰�̎�ނ��A���Ă���
	// �ԈႦ�Ă��邩������Ȃ������E�E�E
	CGridObject::BlockType CheckNextMassType();

	// �ړ���̃v���C���[�̃O���b�h���W�ɂ��镨�̎�ނ��擾����
	CGridObject::BlockType CheckNextObjectType();

	// �ړ���̃v���C���[�̃O���b�h���W�ɂ��鏰�̎�ނ��擾����
	CGridObject::BlockType CheckNextFloorType();

	CGridObject::BlockType CheckNowFloorType();

	CGridObject::BlockType CheckNowObjectType();

	CGridObject::BlockType CheckNowMassType();

	// �ǂ̕����Ɉړ����ł��邩�擾����֐�
	virtual void  CheckCanMove() = 0;

	virtual ~PlayerMove();

	CGrid::GRID_XY GetNextGridPos() const { return nextGridPos; };

	void SetNextGridPos(const CGrid::GRID_XY _nextGirdPos) { nextGridPos = _nextGirdPos; }

	bool GetMoveTrigger() { return isMovingTrigger; }
	void SetMoveTrigger(bool _set) { isMovingTrigger = _set; }

	bool GetIsMoving()const { return isMoving; }
	bool GetIsMoveStart()const { return isMoveStartTrigger; }
	bool GetIsMoveTrigger() const { return isMovingTrigger; }
	bool GetIsWalkEnd() const { return isWalkEnd; }
	bool GetIsWalk_Now() const { return isWalking_now; }
	bool GetIsWalk_Old() const { return isWalking_old; }
	bool GetIsFalling()const { return isFalling; }
	bool GetIsRising()const { return isRising; }
	bool GetIsCannonMove()const { return isCannonMove; }
	bool* GetCanMoveDir() { return &canMoveDir[0]; }
	bool GetCannonMoveEnd()const { return isCannonMoveEnd; }
	bool GetCannonMoveStart()const { return isCannonMoveStart; }
	bool GetCannonMoveStartTrigger()const { return isCannonMoveStartTrigger; }
	bool GetIncannon()const { return inCannon; }
	bool GetIsFallBound()const { return isFallBound; }
	bool GetCannonFX()const { return cannonFX; }
	void SetCannonDir(bool* _set) { *cannonMoveDir = _set; }
	void SetIsMenu(bool _set) { isMenu = _set; }
	CGridObject::BlockType GetNextCannonType()const { return nextCannonType; }
};

