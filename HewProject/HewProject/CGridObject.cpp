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
	// 初期で床カテゴリにする
	Category ret = Category::FLOOR;	// 返す値
	switch (_type)
	{
		// オブジェクトなら
	case BlockType::WALL:
	case BlockType::CASTELLA:
	case BlockType::BAUMHORIZONTAL:
	case BlockType::BAUMVERTICAL:
	case BlockType::START:
	case BlockType::GALL:
	case BlockType::NONE:
		ret = Category::OBJECT;
		break;

		// アイテムなら
	case BlockType::CAKE:
	case BlockType::COIN:
	case BlockType::PROTEIN:
	case BlockType::CHILI:
		ret = Category::ITEM;
		break;

		// 床は初期で入っているので
	default:
		break;

	}

	return ret;
}

