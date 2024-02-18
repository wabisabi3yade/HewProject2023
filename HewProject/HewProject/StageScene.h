#pragma once
#include"CScene.h"
#include"CLoadStage.h"
#include"Ccontroller.h"
#include"CFade.h"
#include<vector>
#include<list>
#include"CGridObject.h"
#include "Player.h"
#include"ProteinUI.h"
#include"FloorUI.h"
#include "CalorieGage_hori.h"
#include "CMenu.h"
class DoTween;
class CArrow;
class CGameClear;
class CGameOver;
class CGameStart;
#define MAX_LAYER (3)         // �K�w�̍ő吔
#define UNDO_ARRAY_NUM (40)	// Undo�̔z��̗v�f��

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

	std::unique_ptr<DoTween> dotween;

	CGameClear* gameClear;
	CGameOver* gameOver;
	CGameStart* gameStart;

	//�X�e�[�W�̏c���Ɖ���
	CGrid::GRID_XY stageSquare;
	// �X�e�[�W�̑傫��
	float stageScale = 0.0f;

	//���j���[���
	CMenu* Menu;

	//�J�n�t���A
	int startFloor;

	int lockStageMap;

	bool changeflag;

	bool FloorOnlyMap;

	bool cannonMove = false;

	bool isLookMap;

	bool isMenu;

	bool gallVibration = false;

	bool gallReduction = false;

	bool isGameClear;

	bool isStartStop;

	//�ő�t���A
	int nMaxFloor;

	// ���Z�b�g�̂Ƃ��Ɏg�p����ŏ��̏��
	FIELD_FLOOR floorReset;

	// ��蒼���@�\
	FIELD_FLOOR floorUndo[UNDO_ARRAY_NUM];
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
	D3DBUFFER clearBuffer;	// �N���A

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
	D3DTEXTURE stageTextureChocolateClack;
	D3DTEXTURE stageTextureCake;
	D3DTEXTURE stageTextureChili;
	D3DTEXTURE stageTextureCoin;
	D3DTEXTURE stageTextureGallChest[3];//0�@�ʏ�@1�@���J���@2�@���I�[��
	D3DTEXTURE stageTextureGumi;
	D3DTEXTURE stageTextureProtein;
	D3DTEXTURE playerTexture;
	D3DTEXTURE shadowTexture;
	D3DTEXTURE stageTextureCannon[2]; //0�ɍ��E 1�ɏ㉺
	D3DTEXTURE stageTextureArrow;
	D3DTEXTURE stageTextureBaumAnim[4];

	//UI�֌W

	//�v���e�C��
	ProteinUI* proteinUi;

	//�K�w
	FloorUI* floorUi;

	//�J�����[�Q�[�W
	CalorieGage_hori* calorieGage;

	CArrow* Arrow[static_cast<int>(Player::DIRECTION::NUM)];

public:
	int nNumProtein;	// ���݃X�e�[�W�ɂ���v���e�C���̐�

	StageScene(D3DBUFFER vb, D3DTEXTURE tex, short int worldNum);
	~StageScene();

	void Update();
	// �v���C���[�̓����ɂ���ăX�e�[�W�̃I�u�W�F�N�g��ω����鏈��
	void StageMove();
	// �O���b�h�e�[�u���̍X�V������
	void TableUpdate();

	// �J�X�e���ɓ������閽�߂��o��
	void CastellaMoveOrder();

	// ��C�̒��ł̓��͂��󂯕t����
	void InCanonInput();

	// �A�C�e���i�P�[�L�Ƃ��j�Ɠ����}�X�Ɉړ�����ƃA�C�e�����������肷��֐� ���̃}�X�p
	void ItemDelete();
	//���ݒn�̃A�C�e���������֐�
	void CannonItemDelete(CGrid::GRID_XY _deletePos = {-1,-1}, CGridObject::BlockType _type = CGridObject::BlockType::NONE);

	// �X�e�[�W�̏�Ԃ���O�ɖ߂��֐�
	void Undo(float _stageScale);
	// �ړ����邲�ƂɑO�̃e�[�u����ԂɍX�V����
	void UndoTableUpdate();

	// �ЂƂO�ɖ߂��Ƃ��Ƀv���C���[�̏���ݒ肷��
	void UndoPlayerSet(const int& _dir, const int& _calorie, const Player::STATE& _state);

	void Draw();
	void Z_Sort(std::vector<CGridObject*>& _sortList);
	// �X�e�[�W�̏������֐�
	void Init(const wchar_t* filePath);

	// �X�e�[�W���O���b�h�e�[�u��������֐�
	void CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList);

	void ChangeFloor(int _nextFloor);

	void MapDraw();

	// ���̊K�w�ɂ���w�肵���O���b�h���W�̃I�u�W�F�N�g���擾����
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	// �X�e�[�W���̃v���C���[���擾
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const;
};
