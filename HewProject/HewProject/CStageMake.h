//#pragma once
//class CStage;
//#include "CLoadStage.h"
//
//struct POS
//{
//	float x, y;
//};
//struct STAGEPOS
//{
//	POS pos = {};
//	int blockType;
//};
//class CStageMake
//{
//	int Stagenum = 0;
//	std::vector<STAGEPOS> stagePos;
//public:
//	//enum class BlockType
//	//{
//	//	FLOOR = 1,		// 床				1
//	//	WALL,			// 壁				2
//	//	HOLL,			// 穴				3
//	//	CAKE,			// ケーキ			4
//	//	CASTELLA,		// カステラ			5
//	//	BAUMHORIZONTAL,	// バウムクーヘン縦	6
//	//	BAUMVERTICAL,	// バウムクーヘン横	7
//	//	COIN,			// コイン			8
//	//	WATAAME,		// 綿あめ			9
//	//	CHOCO,			// チョコ			10
//	//	CHOCOCRACK,		// チョコひび		11
//	//	GUMI,			// グミ				12
//	//	PROTEIN,		// プロテイン		13
//	//	CHILI,			// とうがらし		14
//	//	START,			// スタート			15
//	//	GALL,			// ゴール			16
//	//	CASTELLA_FLOOR,	// カステラの床		17
//	//	NONE = 99,
//	//};
//
//	//// ステージのオブジェクトの区分
//	//enum class Category
//	//{
//	//	FLOOR,	// 床
//	//	ITEM,	// アイテム(ケーキ、とうがらし、メダルとか)
//	//	OBJECT	// アイテム以外のオブジェクト(バウムクーヘン、壁とか)
//	//};
//private:
//	/*BlockType BkType;*/
//public:
//
//	int StageNum(std::vector<LoadData>, int _stageY);
//
//	//ステージのデータ: Vector<>
//	//ステージの横の数 :int　
//	std::vector<STAGEPOS> StagePos(LoadData _vStage);
//	int GetStageNum() { return Stagenum; };
//
//	//// そのブロックのタイプが何のカテゴリーかを返す
//	//static int JudgeTypeToCategory(BlockType _type);
//};
//
