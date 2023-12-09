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
#define StageTate 3
#define StageYoko 13


struct Stage
{
	float stage[StageYoko];
};

enum Tag
{
	PlayerTag = 0,
	EnemyTag = 1,
	PlayerBullet = 2,
	EnemyBullet = 3,
};


struct DATA
{
	std::string Name;
	DirectX::XMFLOAT3 StartPos;
	double HP;
	Tag Tag;
};

class CLoadStage
{



public:
	//CLoadStage();
	//~CLoadStage();
	
	std::vector<DATA>LoadData(const char* filePath);
	std::vector<Stage>LoadStage(const char* filePath);
	std::list<Stage>LoadStageList(const char* filePath);

};

