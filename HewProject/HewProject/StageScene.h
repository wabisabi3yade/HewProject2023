#pragma once
#include"CScene.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"
#include "Player.h"

#define MAX_LAYER (3)         // �K�w�̍ő吔

class GridTable;

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
		
		//�@�v���C���[��1�O�ɂ������K�w�ɂ����� 
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
	/*CStageMake* stageMake;*/
	/*std::vector<STAGEPOS> stagePos;*/
	const wchar_t* CsvPath[PathLength] = { L"asset/mizuno/Stage.csv" };
	Player* player;
	short nowFloorNum;	// ���݂ɂ���K�w�̐���

	// �X�e�[�W�̃O���b�h�e�[�u��
	GridTable* oneFloor;	// 1�K
	GridTable* secondFloor;	// 2�K
	GridTable* thirdFloor;	// 3�K
	GridTable* nowFloor;	// ���݂̊K�w

	//�X�e�[�W�̏c���Ɖ���
	CGrid::GRID_XY stageSquare;
	// �X�e�[�W�̑傫��
	float stageScale = 0.0f;

	//�J�n�t���A
	int startFloor;

	bool changeflag;

	// ��蒼���@�\
	FIELD_FLOOR floorUndo[20];
	int nNumUndo = 0;
	int nNextUndo = 1;

	std::vector<CGridObject*> oneFStgObj;	// 1�K�̃I�u�W�F�N�g�i�[
	std::vector<CGridObject*>secondFStgObj;	// 2�K
	std::vector<CGridObject*>thirdFStgObj;	// 3�K
	std::vector<CGridObject*> *vStageObj;	// ���݂̊K�w�̔z��̃|�C���^�ϐ�
											//�i�����ɍ��̊K�w��vector�z��̃A�h���X������j
	// �o�b�t�@	
	D3DBUFFER stageBuffer;	// �X�e�[�W�̃I�u�W�F�N�g
	D3DBUFFER playerBuffer;	// �v���C���[

	// �e�N�X�`��
	D3DTEXTURE stageTextureFloor;
	D3DTEXTURE stageTextureFloor2;
	D3DTEXTURE stageTextureWall;
	D3DTEXTURE stageTextureHoll;
	D3DTEXTURE stageTextureWataame;
	D3DTEXTURE stageTextureCastella;
	D3DTEXTURE stageTextureBaumkuchen_R;
	D3DTEXTURE stageTextureBaumkuchen_L;
	D3DTEXTURE stageTextureChocolate;
	D3DTEXTURE stageTextureCake;
	D3DTEXTURE stageTextureChili;
	D3DTEXTURE stageTextureCoin;
	D3DTEXTURE stageTextureGallChest;
	D3DTEXTURE stageTextureGumi;
	D3DTEXTURE stageTextureProtein;
	D3DTEXTURE playerTexture;
	D3DTEXTURE shadowTexture;
	D3DTEXTURE stageTextureCannon;

public:
	int nNumProtein;	// ���݃X�e�[�W�ɂ���v���e�C���̐�

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

	// �X�e�[�W�̏�Ԃ���O�ɖ߂��֐�
	void Undo(float _stageScale);

	// �ЂƂO�ɖ߂��Ƃ��Ƀv���C���[�̏���ݒ肷��
	void UndoPlayerSet(const int& _dir, const int& _calorie, const Player::STATE& _state);

	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	// �X�e�[�W�̏������֐�
	void Init(const wchar_t* filePath, float _stageScale);

	// �X�e�[�W���O���b�h�e�[�u��������֐�
	void CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList);

	void ChangeFloor(int _nextFloor);

	// ���̊K�w�ɂ���w�肵���O���b�h���W�̃I�u�W�F�N�g���擾����
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	// �X�e�[�W���̃v���C���[���擾
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const;
};
