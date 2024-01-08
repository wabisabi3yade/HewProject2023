#pragma once
#include "CGrid.h"
#include "Vector2.h"
#include "Vector3.h"
#include "CStageMake.h"

#define MAX_GRIDNUM (12)    // �O���b�h�̍ő�}�X��

#define ISOME_FLOOR_SUBPOSY (3.6f)	// �A�C�\���ł̗׏���Y���W�̍��i�X�P�[��������j

// �A�C�\���p�O���b�h�̔Ձi�e�[�u���j�̃N���X
class GridTable
{
	// ��̃}�X�̑傫��
	Vector3 oneGridScale;

	// [0,0]�̃O���b�h�̒��S���W(���[���h)
	Vector2 offset;

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

	/// <summary>
	/// �O���b�h�̍��W��Ԃ��i���Ɠ������W�j
	/// </summary>
	/// <param name="_gridX">�O���b�hX���W</param>
	/// <param name="_gridY">�O���b�hY���W</param>
	/// <returns>���[���h���W</returns>
	Vector3 GridToWorld(CGrid::GRID_XY _pos, CStageMake::BlockType _type);

	Vector3 GetGridScale()const { return oneGridScale; }

	Vector2 GetOffset()const { return offset; }
};

