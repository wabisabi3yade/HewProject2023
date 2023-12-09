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

std::vector<aaa>CLoadStage::LoadStage(const char* filePath)
{
	std::vector<std::string> dat;
	std::vector<aaa> xx;
	aaa bb;
	std::ifstream ifs(filePath);
	if (ifs) { //読み込みに成功したかチェック
		std::string str;
		while (getline(ifs, str)) { //1 行ずつ読み込み
			std::istringstream iss(str);
			while (getline(iss, str, ','))
			{
				//dat.push_back(str);
				bb.data = std::stoi(str);
				xx.push_back(bb);
			}
		}
		ifs.close(); //ファイルを閉じる
	}
	return xx;
}
