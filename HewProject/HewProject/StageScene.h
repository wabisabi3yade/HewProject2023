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
#include"CoinUI.h"
class DoTween;
class CArrow;
class CGameClear;
class CGameOver;
class CGameStart;
#define MAX_LAYER (3)         // �K�w�̍ő吔
#define UNDO_ARRAY_NUM (40)	// Undo�̔z��̗v�f��

class GridTable;

class Tutorial;

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

	CScene::SCENE_NAME selectName = CScene::SCENE_NAME::STAGE1;
	CScene::SCENE_NAME nextStageName = CScene::SCENE_NAME::STAGE1;

	bool isTrue = true;
	bool isFalse = false;

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

	bool* isLookMap;

	bool* isMenu;

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
	D3DBUFFER LR_ButtonBuffer;	// LB_RL�{�^���p�o�b�t�@

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

	D3DTEXTURE ButtonTextureCamera;
	D3DTEXTURE ButtonTextureFloorLook;
	D3DTEXTURE ButtonTextureUndo;
	D3DTEXTURE TextTextureLooking;
	D3DTEXTURE Button_LB_RB_Texture;
	D3DTEXTURE ButtonTextureCameraBack;
	D3DTEXTURE GetProteinTexture;
	D3DTEXTURE GoChestTexture;

	//UI�֌W
	UI* LookingTxet;
	UI* CameraButton;
	UI* FloorLookButton;
	UI* UndoButton;
	UI* RB_Button;
	UI* LB_Button;
	UI* BackCameraButton;
	
	UI* GetProtein;
	//�v���e�C��
	ProteinUI* proteinUi;
	//�R�C��
	CoinUI* coinUI;

	//�K�w
	FloorUI* floorUi;

	//�J�����[�Q�[�W
	CalorieGage_hori* calorieGage;

	CArrow* Arrow[static_cast<int>(Player::DIRECTION::NUM)];

	// �`���[�g���A�����邩�ǂ����t���O
	bool isDoTutorial = false;
	bool isTutorialNow = false;
	Tutorial* tutorial = nullptr;

	bool isW11 = false;


public:
	int nNumProtein;	// ���݃X�e�[�W�ɂ���v���e�C���̐�

	int nNumCoin;
	StageScene(D3DBUFFER vb, D3DTEXTURE tex, short int worldNum, bool _isW11 = false);
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
	void Undo(float _stageScale, bool isPush = false);
	// �ړ����邲�ƂɑO�̃e�[�u����ԂɍX�V����
	void UndoTableUpdate();

	void Reset();

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

	/// <summary>
	/// �Q�[���J�n���̃v���C���[�̏�Ԃ�ς���֐�
	/// </summary>
	/// <param name="_calorie">�����J�����[ MAX15</param>
	/// <param name="_state">�v���C���[�̏������  0 �ʏ�  1 �K��  2 �f�u 3 �}�b�`��</param>
	void SetPlayerStartstatus(int _calorie , int _state) { player->SetCalorie(_calorie) ,player->ChangeState(static_cast<Player::STATE>(_state)); }

	// ���̊K�w�ɂ���w�肵���O���b�h���W�̃I�u�W�F�N�g���擾����
	CGridObject* GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	CGridObject* GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType);

	// �X�e�[�W���̃v���C���[���擾
	Player* GetPlayer() const { return player; };

	GridTable* GetNowFloor() const;

	void SetTutorial(Tutorial* _setTutorial);

	void SetNextStageName(CScene::SCENE_NAME _set) { nextStageName = _set; }
};
