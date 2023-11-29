#include "CLoadStage.h"
//#include <iostream>
//#include <fstream>
//#include <sstream> 
//using namespace std;
//#include"Direct3D.h"
//#define StageYoko 5
//ヨコの数一回の読み込みの時に何回行うのか　ファイルだ終わるまで
//#define StageTate 3


/*
	一応これをコピペで動く
	読み込むファイルの指定に注意					↓

	//データ読み込み
	CLoadStage* stage = new CLoadStage;				↓
	vector<DATA> DataTable = stage->LoadData("asset/data.csv");
	//読み込んだデータ表示
	for (auto data : DataTable)
	{
		cout << data.Name << endl;
		cout << to_string(data.StartPos.x) << "," << to_string(data.StartPos.y) << "," << to_string(data.StartPos.z) << "," << endl;
		cout << data.HP << endl;
		cout << data.Tag << endl;
		cout << endl;
	}

	delete stage;
*/



std::vector<DATA> CLoadStage::LoadData(const char* filePath)
{
	//返す配列
	std::vector<DATA> dataTable;

	//ファイルオープン
	std::ifstream fileStream(filePath);
	if (!fileStream)
	{
		std::cout << "ファイルオープン失敗" << std::endl;
		return dataTable;
	}

	//何行目か
	int i = 0;

	//ファイルが終わるまで読み込み
	//ループ文をどうにかした方がいい
	while (/*!fileStream.eof()*/ i != 3)
	{
		i++;
		std::string bufferString;
		fileStream >> bufferString;
		//1行目は列名でデータではないためスキップ
		if (i <= 1) continue;

		//データを項目ごとに抽出
		std::istringstream stringStream(bufferString);
		std::vector<std::string> datas;
		std::string tmp;
		//カンマ区切りでデータを切り分け
		while (getline(stringStream, tmp, ','))
		{
			datas.push_back(tmp);
		}
		//切り分けたデータを構造体に格納
		DATA data;
		data.Name = datas.at(0);
		data.StartPos.x = strtof(datas.at(1).c_str(), NULL);
		data.StartPos.y = strtof(datas.at(2).c_str(), NULL);
		data.StartPos.z = strtof(datas.at(3).c_str(), NULL);
		data.HP = strtod(datas.at(4).c_str(), NULL);
		auto tag = datas.at(5);
		if (tag == "Player")
		{
			data.Tag = PlayerTag;
		}
		if (tag == "Boss")
		{
			data.Tag = EnemyTag;
		}
		dataTable.push_back(data);

	}
	//ファイルクローズ
	fileStream.close();
	return dataTable;
}
std::vector<Stage> CLoadStage::LoadStage(const char* filePath)
{

	//返す配列
	std::vector<Stage>stageTable;

	//ファイルオープン
	std::ifstream fileStream(filePath);
	if (!fileStream)
	{
		std::cout << "ファイルオープン失敗" << std::endl;
		return stageTable;
	}

	//何行目か
	int i = 0;

	//ファイルが終わるまで読み込み
	//ループ文をどうにかした方がいい
	while (/*!fileStream.eof()*/ i != StageTate)
	{
		i++;
		std::string bufferString;
		fileStream >> bufferString;
		//1行目は列名でデータではないためスキップ
		//if (i <= 1) continue;

		//データを項目ごとに抽出
		std::istringstream stringStream(bufferString);
		std::vector<std::string> datas;
		std::string tmp;
		//カンマ区切りでデータを切り分け
		while (getline(stringStream, tmp, ','))
		{
			datas.push_back(tmp);
		}

		Stage stage;
		for (int j = 0; j < StageYoko; j++)
		{
			stage.stage[j] = (float)strtod(datas.at(j).c_str(), NULL);
		}
		stageTable.push_back(stage);
		//stageTable.clear();
	}
	//ファイルクローズ
	fileStream.close();
	return stageTable;
}

