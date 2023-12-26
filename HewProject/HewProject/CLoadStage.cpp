#include "CLoadStage.h"
//#include <iostream>
//#include <fstream>
//#include <sstream> 
//using namespace std;
//#include"Direct3D.h"
//ヨコの数一回の読み込みの時に何回行うのか　ファイルだ終わるまで

//これを実行したいところで実行
// 
//stage = new CLoadStage;
//stageMake = new CStageMake;
//
//std::vector<aaa> ZZ = stage->LoadStage("asset/mizuno/Stage.csv");
//std::vector<STAGEPOS> stagepos = stageMake->StagePos(ZZ, 13);

LoadData CLoadStage::LoadStage(const wchar_t* filePath)
{
	std::vector<std::string> dat;
	LoadData xx;
	std::ifstream ifs(filePath);

	int countY = 0;

	if (ifs) { //読み込みに成功したかチェック
		std::string str;
		while (getline(ifs, str)) { //1 行ずつ読み込み
			std::istringstream iss(str);

			countY++;
			while (getline(iss, str, ','))
			{
				//dat.push_back(str);
				xx.data.push_back(std::stoi(str));
			}
		}
		ifs.close(); //ファイルを閉じる
	}
	// 行と列の数を求める
	xx.numY = countY;
	xx.numX = xx.data.size() / xx.numY;

	return xx;
}
