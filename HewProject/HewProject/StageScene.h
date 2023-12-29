#pragma once
#include"CScene.h"
#include"CStageMake.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"


#define MAX_GRIDNUM (12)    // �O���b�h�̍ő�}�X��
#define MAX_LAYER (3)         // �K�w�̍ő吔

class StageScene :
	public CObject
{
public:
	struct FIELD
	{
		bool isUse = false;
		int gridTable[MAX_GRIDNUM][MAX_GRIDNUM] = {};   // �O���b�h�e�[�u��
		int FloorNum = 0;   // �K�w�̐���
	};

private:

	/*int PlayerState;*/

	float Offset_X;
	float Offset_Y;



	LoadData StageData;

	Vector3 stageScale;
	CLoadStage* stage;
	CStageMake* stageMake;
	std::vector<STAGEPOS> stagePos;
	const wchar_t* CsvPath[PathLength] = { L"asset/mizuno/Stage.csv" };
	CGridObject* player;
	CGridObject* stageObj;

	// �X�e�[�W�̃O���b�h�e�[�u��
	FIELD oneFloor;
	FIELD secondFloor;
	FIELD thirdFloor;

	FIELD oneFloorCopy;
	FIELD secondFloorCopy;
	FIELD thirdFloorCopy;

	D3DBUFFER stageBuffer;
	D3DBUFFER playerBuffer;

	D3DTEXTURE stageTextureFloor;

	D3DTEXTURE stageTextureFloor2;

	D3DTEXTURE stageTextureWall;
	D3DTEXTURE stageTextureWataame;
	D3DTEXTURE stageTextureCastella;
	D3DTEXTURE stageTextureBaumkuchen;
	D3DTEXTURE stageTextureChocolate;
	D3DTEXTURE stageTextureCake;
	D3DTEXTURE stageTextureChili;
	D3DTEXTURE stageTextureCoin;
	D3DTEXTURE stageTextureGallChest;
	D3DTEXTURE stageTextureGumi;
	D3DTEXTURE stageTextureProtein;
	D3DTEXTURE playerTexture;
	D3DTEXTURE playerTexture_NF;
	D3DTEXTURE playerTexture_MF;
	D3DTEXTURE playerTexture_SF;
	D3DTEXTURE playerTexture_FF;

public:

	std::vector<CGridObject*> vStageObj;
	std::vector<CGridObject*> vStageObjCopy;

	StageScene(D3DBUFFER vb, D3DTEXTURE tex);
	~StageScene();

	void Update();
	void PlayerMove();
	void PlayerNomalMove();
	void PlayerFatMove();
	void PlayerSkinnyMove();
	void PlayerMachoMove();
	void Reset(const wchar_t* filePath, float _stageScale);
	// �ǂ̕����ɂ͓����Ȃ��悤�ɂ���
	void SettingPlayerDir();

	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	void Init(const wchar_t* filePath, float _stageScale);
	Vector3 GetGridToPos(CGrid::GRID_XY _gridXY);
	Vector3 GridToPos(CGrid::GRID_XY _gridXY, CStageMake::BlockType _type);

};

