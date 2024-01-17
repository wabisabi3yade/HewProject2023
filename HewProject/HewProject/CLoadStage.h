#pragma once
#include<stdio.h>
#include <string>
#include <vector>
#include<DirectXMath.h>
#include<list>
//このインクルードここでやるとおかしくなるかも　mainとかで
#include <iostream>
#include <fstream>
#include <sstream>
//
#define MAX_GRIDNUM (9)

//struct Stage
//{
//	float stage[13];
//};
//enum Stagesuu
//{
//	stageone
//};
struct STAGE_XY
{
	DirectX::XMFLOAT2 pos;
};

struct StageGridTable
{
	short int floorTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};
};

struct LoadData
{
	// ステージのデータが入る
	StageGridTable oneFloor;
	StageGridTable secondFloor;
	std::vector<int> data;
	StageGridTable thirdFloor;

	int numX;	// ステージに列が難行あるか
	int numY;	// ステージの行が何行あるか
};

class CLoadStage
{



public:
	//CLoadStage();
	//~CLoadStage();


	LoadData LoadStage(const wchar_t* filePath );

};

