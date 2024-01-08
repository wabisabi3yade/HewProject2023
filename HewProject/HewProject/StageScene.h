#pragma once
#include"CScene.h"
#include"CStageMake.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"

#define MAX_GRIDNUM (12)    // グリッドの最大マス数
#define MAX_LAYER (3)         // 階層の最大数

class GridTable;
class Player;

class StageScene :
	public CObject
{
public:

private:
	CLoadStage* stage;
	CStageMake* stageMake;
	std::vector<STAGEPOS> stagePos;
	const wchar_t* CsvPath[PathLength] = { L"asset/mizuno/Stage.csv" };
	Player* player;
	CGridObject* stageObj;

	// ステージのグリッドテーブル
	GridTable* oneFloor;	// 1階
	GridTable* secondFloor;	// 2階
	GridTable* thirdFloor;	// 3階
	GridTable* nowFloor;	// 現在の階層


	std::vector<CGridObject*> oneFStgObj;	// 1階のオブジェクト格納
	std::vector<CGridObject*>secondFStgObj;	// 2階
	std::vector<CGridObject*>thirdFStgObj;	// 3階
	std::vector<CGridObject*> vStageObj;	// 現在の階層の配列のポインタ変数
											//（ここに今の階層のvector配列のアドレスを入れる）

	D3DBUFFER stageBuffer;
	D3DBUFFER playerBuffer;

	D3DTEXTURE stageTextureFloor;

	D3DTEXTURE stageTextureFloor2;

	D3DTEXTURE stageTextureWall;
	D3DTEXTURE stageTextureWataame;
	D3DTEXTURE stageTextureCastella;
	D3DTEXTURE stageTextureBaumkuchen;
	D3DTEXTURE stageTextureChocolate;
	D3DTEXTURE stageTextureCake;
	D3DTEXTURE stageTextureChili;
	D3DTEXTURE stageTextureCoin;
	D3DTEXTURE stageTextureGallChest;
	D3DTEXTURE stageTextureGumi;
	D3DTEXTURE stageTextureProtein;
	D3DTEXTURE playerTexture;

public:

	int nNumProtein;

	StageScene(D3DBUFFER vb, D3DTEXTURE tex);
	~StageScene();

	void Update();
	// プレイヤーの動きによってステージのオブジェクトを変化する処理
	void StageMove();
	// グリッドテーブルの更新をする
	void TableUpdate();

	// カステラに動かせる命令を出す
	void CastellaMoveOrder();

	// アイテム（ケーキとか）と同じマスに移動するとアイテムを消したりする関数
	void ItemDelete();

	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	void Init(const wchar_t* filePath, float _stageScale);
	// 今の階層にある指定したグリッド座標のオブジェクトを取得する
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, int _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, int _blockType);

	// ステージ内のプレイヤーを取得
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const { return nowFloor; }
};
