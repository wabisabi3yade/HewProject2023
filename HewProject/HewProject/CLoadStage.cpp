#include "CLoadStage.h"
//#include <iostream>
//#include <fstream>
//#include <sstream> 
//using namespace std;
//#include"Direct3D.h"
//#define StageYoko 5
//���R�̐����̓ǂݍ��݂̎��ɉ���s���̂��@�t�@�C�����I���܂�
//#define StageTate 3


/*
	�ꉞ������R�s�y�œ���
	�ǂݍ��ރt�@�C���̎w��ɒ���					��

	//�f�[�^�ǂݍ���
	CLoadStage* stage = new CLoadStage;				��
	vector<DATA> DataTable = stage->LoadData("asset/data.csv");
	//�ǂݍ��񂾃f�[�^�\��
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
	//�Ԃ��z��
	std::vector<DATA> dataTable;

	//�t�@�C���I�[�v��
	std::ifstream fileStream(filePath);
	if (!fileStream)
	{
		std::cout << "�t�@�C���I�[�v�����s" << std::endl;
		return dataTable;
	}

	//���s�ڂ�
	int i = 0;

	//�t�@�C�����I���܂œǂݍ���
	//���[�v�����ǂ��ɂ�������������
	while (/*!fileStream.eof()*/ i != 3)
	{
		i++;
		std::string bufferString;
		fileStream >> bufferString;
		//1�s�ڂ͗񖼂Ńf�[�^�ł͂Ȃ����߃X�L�b�v
		if (i <= 1) continue;

		//�f�[�^�����ڂ��Ƃɒ��o
		std::istringstream stringStream(bufferString);
		std::vector<std::string> datas;
		std::string tmp;
		//�J���}��؂�Ńf�[�^��؂蕪��
		while (getline(stringStream, tmp, ','))
		{
			datas.push_back(tmp);
		}
		//�؂蕪�����f�[�^���\���̂Ɋi�[
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
	//�t�@�C���N���[�Y
	fileStream.close();
	return dataTable;
}
std::vector<Stage> CLoadStage::LoadStage(const char* filePath)
{

	//�Ԃ��z��
	std::vector<Stage>stageTable;

	//�t�@�C���I�[�v��
	std::ifstream fileStream(filePath);
	if (!fileStream)
	{
		std::cout << "�t�@�C���I�[�v�����s" << std::endl;
		return stageTable;
	}

	//���s�ڂ�
	int i = 0;

	//�t�@�C�����I���܂œǂݍ���
	//���[�v�����ǂ��ɂ�������������
	while (/*!fileStream.eof()*/ i != StageTate)
	{
		i++;
		std::string bufferString;
		fileStream >> bufferString;
		//1�s�ڂ͗񖼂Ńf�[�^�ł͂Ȃ����߃X�L�b�v
		//if (i <= 1) continue;

		//�f�[�^�����ڂ��Ƃɒ��o
		std::istringstream stringStream(bufferString);
		std::vector<std::string> datas;
		std::string tmp;
		//�J���}��؂�Ńf�[�^��؂蕪��
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
	//�t�@�C���N���[�Y
	fileStream.close();
	return stageTable;
}

