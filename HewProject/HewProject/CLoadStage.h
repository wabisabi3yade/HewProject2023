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



struct LoadData
{
	int data;
};

class CLoadStage
{



public:
	//CLoadStage();
	//~CLoadStage();
	

	std::vector<LoadData>LoadStage(const char* filePath);

};

