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

std::vector<aaa>CLoadStage::LoadStage(const char* filePath)
{
	std::vector<std::string> dat;
	std::vector<aaa> xx;
	aaa bb;
	std::ifstream ifs(filePath);
	if (ifs) { //�ǂݍ��݂ɐ����������`�F�b�N
		std::string str;
		while (getline(ifs, str)) { //1 �s���ǂݍ���
			std::istringstream iss(str);
			while (getline(iss, str, ','))
			{
				//dat.push_back(str);
				bb.data = std::stoi(str);
				xx.push_back(bb);
			}
		}
		ifs.close(); //�t�@�C�������
	}
	return xx;
}
