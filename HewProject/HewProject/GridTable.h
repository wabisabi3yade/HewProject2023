#pragma once
#include "CGrid.h"
#include "Vector2.h"
#include "Vector3.h"
#include "CGridObject.h"

#define MAX_GRIDNUM (9)    // �O���b�h�̍ő�}�X��

#define ISOME_FLOOR_SUBPOSY (3.6f)	// �A�C�\���ł̗׏���Y���W�̍��i�X�P�[��������j

// �ォ��傫�����l�ɂ���
#define INFRONT_PLUSZ (0.1f)	// �A�C�\����1���ɍs���Ƒ������Z���W
#define OBJTOFLOOR_DIS_Z (0.01f)	// �I�u�W�F�N�g�Ə��Ƃ�Z���W�̋���
#define ITEMTOFLOOR_DIS_Z (0.005f)	// �A�C�e���Ə��Ƃ�Z���W�̋���
#define ISOME_BACKMOVE (0.001f)	// �A�C�\���̉��Ɉړ�����Ƃ��Ɏg�p����
#define HORIZONLINE_PLUSZ (0.0001f)	// �������̃��C���ŉE�ɍs���قǑ������


// �A�C�\���p�O���b�h�̔Ձi�e�[�u���j�̃N���X
class GridTable
{
	// ��̃}�X�̑傫��
	Vector3 oneGridScale;

	// [0,0]�̃O���b�h�̒��S���W(���[���h)
	Vector2 offset;
	float offsetZ;

	// �O���b�h��
	CGrid::GRID_XY maxGrid;
public:
	// �X�e�[�W���̏�ɂ���e�[�u��
	short int objectTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};

	// �X�e�[�W���̃e�[�u��
	short int floorTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};

	GridTable(CGrid::GRID_XY _max, float _scale);

	~GridTable();

	// �w�肵�����W�ɉ������邩�m�F����
	int CheckObjectType(CGrid::GRID_XY _gridPos);
	int CheckFloorType(CGrid::GRID_XY _gridPos);
	int CheckMassType(CGrid::GRID_XY _gridPos);

	/// <summary>
	/// �O���b�h���W���烏�[���h���W��ϊ�����
	/// </summary>
	/// <param name="_gridX">�O���b�hX���W</param>
	/// <param name="_gridY">�O���b�hY���W</param>
	/// <param name="_playerState">�v���C���[�̏�ԁi�v���C���[���݈̂����ɑ���j</param>
	/// <returns>���[���h���W</returns>
	Vector3 GridToWorld(CGrid::GRID_XY _pos, CGridObject::BlockType _type ,int _playerState = NULL);

	Vector3 GetGridScale()const { return oneGridScale; }

	Vector2 GetOffset()const { return offset; }
};

