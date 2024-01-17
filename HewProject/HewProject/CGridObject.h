#pragma once
#include "CObject.h"
#include"CGrid.h"
class CGridObject :
	public CObject
{
public:
	enum class BlockType
	{
		FLOOR = 1,		// ��				1
		WALL,			// ��				2
		HOLL,			// ��				3
		CAKE,			// �P�[�L			4
		CASTELLA,		// �J�X�e��			5
		BAUMHORIZONTAL,	// �o�E���N�[�w����	6
		BAUMVERTICAL,	// �o�E���N�[�w���c	7
		COIN,			// �R�C��			8
		WATAAME,		// �Ȃ���			9
		CHOCO,			// �`���R			10
		CHOCOCRACK,		// �`���R�Ђ�		11
		GUMI,			// �O�~				12
		PROTEIN,		// �v���e�C��		13
		CHILI,			// �Ƃ����炵		14
		START,			// �X�^�[�g			15
		GALL,			// �S�[��			16
		CASTELLA_FLOOR,	// �J�X�e���̏�		17
		NONE = 99,
	};

	// �X�e�[�W�̃I�u�W�F�N�g�̋敪
	enum class Category
	{
		FLOOR,	// ��
		ITEM,	// �A�C�e��(�P�[�L�A�Ƃ����炵�A���_���Ƃ�)
		OBJECT	// �A�C�e���ȊO�̃I�u�W�F�N�g(�o�E���N�[�w���A�ǂƂ�)
	};

protected:
	CGrid* Grid;
	BlockType type;
	Category category;
public:
	CGridObject(D3DBUFFER vb, D3DTEXTURE tex);
	virtual ~CGridObject();
	void Draw();
	void Update();
	void SetGridPos(const int _PosX, const int _PosY);
	void SetGridPos(CGrid::GRID_XY _gridXY);
	CGrid::GRID_XY GetGridPos() const { return Grid->gridPos; };

	void SetBlookType(BlockType _BkType) { type = _BkType; };
	BlockType GetBlookType() const { return type; };

	void SetCategory(Category _category) { category = _category; };
	Category GetCategory() const { return category; };

	// ���̃u���b�N�̃^�C�v�����̃J�e�S���[����Ԃ�
	static Category TypeToCategory(BlockType _type);
};

