#include "CGridObject.h"

CGridObject::CGridObject(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb,tex)
{
	Grid = new CGrid();
}

CGridObject::~CGridObject()
{
	CLASS_DELETE(Grid)
}

void CGridObject::Draw()
{
	CObject::Draw();
}

void CGridObject::Update()
{
}

void CGridObject::SetGridPos(const int _PosX,const int _PosY)
{
	Grid->gridPos.x = _PosX;
	Grid->gridPos.y = _PosY;
}

void CGridObject::SetGridPos(CGrid::GRID_XY _gridXY)
{
	this->Grid->gridPos = _gridXY;
}

CGridObject::Category CGridObject::TypeToCategory(BlockType _type)
{
	// �����ŏ��J�e�S���ɂ���
	Category ret = Category::FLOOR;	// �Ԃ��l
	switch (_type)
	{
		// �I�u�W�F�N�g�Ȃ�
	case BlockType::WALL:
	case BlockType::CASTELLA:
	case BlockType::BAUMHORIZONTAL:
	case BlockType::BAUMVERTICAL:
	case BlockType::START:
	case BlockType::GALL:
	case BlockType::NONE:
		ret = Category::OBJECT;
		break;

		// �A�C�e���Ȃ�
	case BlockType::CAKE:
	case BlockType::COIN:
	case BlockType::PROTEIN:
	case BlockType::CHILI:
		ret = Category::ITEM;
		break;

		// ���͏����œ����Ă���̂�
	default:
		break;

	}

	return ret;
}

