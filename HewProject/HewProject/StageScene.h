#pragma once
#include"CScene.h"
#include"CStageMake.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"
#include "Player.h"

#define MAX_GRIDNUM (12)    // �O���b�h�̍ő�}�X��
#define MAX_LAYER (3)         // �K�w�̍ő吔

class GridTable;
//class Player;

class StageScene :
	public CObject
{
public:

	struct FIELD_FLOOR
	{
		// �X�e�[�W���̏�ɂ���e�[�u��
		short int objectTable[MAX_LAYER][MAX_GRIDNUM][MAX_GRIDNUM] = {};

		// �X�e�[�W���̃e�[�u��
		short int floorTable[MAX_LAYER][MAX_GRIDNUM][MAX_GRIDNUM] = {};

		short int old_Floor;

		//�v���C���[�̍��W
		CGrid::GRID_XY playerUndo;

		//�v���C���[�̏��
		Player::STATE stateUndo;

		//�v���C���[�̕���
		int dirUndo;

		//�v���C���[�̃J�����[
		int calorieUndo;

	};

private:
	CLoadStage* stage;
	CStageMake* stageMake;
	std::vector<STAGEPOS> stagePos;
	const wchar_t* CsvPath[PathLength] = { L"asset/mizuno/Stage.csv" };
	Player* player;
	CGridObject* stageObj;

	// �X�e�[�W�̃O���b�h�e�[�u��
	GridTable* oneFloor;	// 1�K
	GridTable* secondFloor;	// 2�K
	GridTable* thirdFloor;	// 3�K
	GridTable* nowFloor;	// ���݂̊K�w

	//�X�e�[�W�̏c���Ɖ���
	CGrid::GRID_XY stageSquare;

	FIELD_FLOOR floorUndo[20];
	int nNumUndo = 0;
	int nNextUndo = 1;

	std::vector<CGridObject*> oneFStgObj;	// 1�K�̃I�u�W�F�N�g�i�[
	std::vector<CGridObject*>secondFStgObj;	// 2�K
	std::vector<CGridObject*>thirdFStgObj;	// 3�K
	std::vector<CGridObject*> vStageObj;	// ���݂̊K�w�̔z��̃|�C���^�ϐ�
											//�i�����ɍ��̊K�w��vector�z��̃A�h���X������j

	D3DBUFFER stageBuffer;
	D3DBUFFER playerBuffer;

	D3DTEXTURE stageTextureFloor;

	D3DTEXTURE stageTextureFloor2;

	D3DTEXTURE stageTextureWall;
	D3DTEXTURE stageTextureHoll;
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
	D3DTEXTURE shadowTexture;

public:

	int nNumProtein;

	StageScene(D3DBUFFER vb, D3DTEXTURE tex);
	~StageScene();

	void Update();
	// �v���C���[�̓����ɂ���ăX�e�[�W�̃I�u�W�F�N�g��ω����鏈��
	void StageMove();
	// �O���b�h�e�[�u���̍X�V������
	void TableUpdate();

	// �J�X�e���ɓ������閽�߂��o��
	void CastellaMoveOrder();

	// �A�C�e���i�P�[�L�Ƃ��j�Ɠ����}�X�Ɉړ�����ƃA�C�e�����������肷��֐�
	void ItemDelete();

	void Undo(float _stageScale);
	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	void Init(const wchar_t* filePath, float _stageScale);
	// ���̊K�w�ɂ���w�肵���O���b�h���W�̃I�u�W�F�N�g���擾����
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, int _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, int _blockType);

	// �X�e�[�W���̃v���C���[���擾
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const { return nowFloor; }
};
