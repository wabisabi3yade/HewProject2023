#include "CLoadStage.h"
//#include <iostream>
//#include <fstream>
//#include <sstream> 
//using namespace std;
//#include"Direct3D.h"
//���R�̐����̓ǂݍ��݂̎��ɉ���s���̂��@�t�@�C�����I���܂�

//��������s�������Ƃ���Ŏ��s
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

	if (ifs) { //�ǂݍ��݂ɐ����������`�F�b�N
		std::string str;
		while (getline(ifs, str)) { //1 �s���ǂݍ���
			std::istringstream iss(str);

			countY++;
			while (getline(iss, str, ','))
			{
				//dat.push_back(str);
				xx.data.push_back(std::stoi(str));
			}
		}
		ifs.close(); //�t�@�C�������
	}
	// �s�Ɨ�̐������߂�
	xx.numY = countY;
	xx.numX = xx.data.size() / xx.numY;

	return xx;
}
