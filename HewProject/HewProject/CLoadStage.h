#pragma once
#include<stdio.h>
#include <string>
#include <vector>
#include<DirectXMath.h>
#include<list>
//���̃C���N���[�h�����ł��Ƃ��������Ȃ邩���@main�Ƃ���
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
	std::vector<int> data;	// �X�e�[�W�̃f�[�^������
	int numX;	// �X�e�[�W�ɗ񂪓�s���邩
	int numY;	// �X�e�[�W�̍s�����s���邩
};

class CLoadStage
{



public:
	//CLoadStage();
	//~CLoadStage();


	LoadData LoadStage(const wchar_t* filePath);

};

