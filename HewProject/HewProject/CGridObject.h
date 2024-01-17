#pragma once
#include "CObject.h"
#include"CGrid.h"
class CGridObject :
	public CObject
{
public:
	enum class BlockType
	{
		FLOOR = 1,		// 床				1
		WALL,			// 壁				2
		HOLL,			// 穴				3
		CAKE,			// ケーキ			4
		CASTELLA,		// カステラ			5
		BAUMHORIZONTAL,	// バウムクーヘン横	6
		BAUMVERTICAL,	// バウムクーヘン縦	7
		COIN,			// コイン			8
		WATAAME,		// 綿あめ			9
		CHOCO,			// チョコ			10
		CHOCOCRACK,		// チョコひび		11
		GUMI,			// グミ				12
		PROTEIN,		// プロテイン		13
		CHILI,			// とうがらし		14
		START,			// スタート			15
		GALL,			// ゴール			16
		CASTELLA_FLOOR,	// カステラの床		17
		NONE = 99,
	};

	// ステージのオブジェクトの区分
	enum class Category
	{
		FLOOR,	// 床
		ITEM,	// アイテム(ケーキ、とうがらし、メダルとか)
		OBJECT	// アイテム以外のオブジェクト(バウムクーヘン、壁とか)
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

	// そのブロックのタイプが何のカテゴリーかを返す
	static Category TypeToCategory(BlockType _type);
};

