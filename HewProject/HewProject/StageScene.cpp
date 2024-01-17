//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include "StageScene.h"
#include<iostream>
#include<algorithm>
#include"CCake.h"
#include"CChoco.h"
#include"CCastella.h"
#include"CWall.h"
#include"CHoll.h"
#include "CFloor.h"
#include"CBaum.h"
#include"CCoin.h"
#include"CWataame.h"
#include"CGumi.h"
#include"CProtein.h"
#include"CGall.h"
#include"CChili.h"
//#include "Player.h"
#include "GridTable.h"
#include "TextureFactory.h"

#define PLAYER dynamic_cast<Player*>(player)	// �킴�킴�����̂߂�ǂ�����

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	nNumProtein = 0;

	// �e�N�X�`�����Ǘ�����N���X�̃C���X�^���X���擾
	TextureFactory* texFactory = TextureFactory::GetInstance();

	// �e�I�u�W�F�N�g�̃e�N�X�`�����擾����
	stageTextureFloor = texFactory->Fetch(L"asset/Stage/floor_y.png");
	stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/floor_g.png");
	/*stageTextureFloor = texFactory->Fetch(L"asset/Stage/2floor_y.png");
	stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/2floor_g.png"); */


	stageTextureWall = texFactory->Fetch(L"asset/Stage/Wall.png");
	stageTextureHoll = texFactory->Fetch(L"asset/Stage/test_Hool.png");
	stageTextureWataame = texFactory->Fetch(L"asset/Stage/Wataame.png");

	/*stageTextureCastella = texFactory->Fetch(L"asset/Stage/Castella.png");*/
	stageTextureCastella = texFactory->Fetch(L"asset/Stage/2castella.png");

	stageTextureBaumkuchen_R = texFactory->Fetch(L"asset/Stage/Baumkuchen_R.png");
	stageTextureBaumkuchen_L = texFactory->Fetch(L"asset/Stage/Baumkuchen_L.png");
	stageTextureChocolate = texFactory->Fetch(L"asset/Stage/Chocolate.png");
	stageTextureCake = texFactory->Fetch(L"asset/Item/Cake.png");
	stageTextureChili = texFactory->Fetch(L"asset/Item/Chili.png");
	stageTextureCoin = texFactory->Fetch(L"asset/Item/Coin.png");
	stageTextureGallChest = texFactory->Fetch(L"asset/Stage/GallChest.png");
	stageTextureGumi = texFactory->Fetch(L"asset/Stage/Gumi.png");
	stageTextureProtein = texFactory->Fetch(L"asset/Item/Protein.png");
	/*playerTexture = texFactory->Fetch(L"asset/Stage/floor_y.png");*/
	shadowTexture = texFactory->Fetch(L"asset/Item/shadow.png");

}

// �e�N�X�`���͉�����Ȃ�
StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

	CLASS_DELETE(stage);

	for (std::vector<CGridObject*>::iterator it = oneFStgObj.begin(); it != oneFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	oneFStgObj.clear();

	for (std::vector<CGridObject*>::iterator it = secondFStgObj.begin(); it != secondFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	secondFStgObj.clear();

	for (std::vector<CGridObject*>::iterator it = thirdFStgObj.begin(); it != thirdFStgObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
	thirdFStgObj.clear();

	CLASS_DELETE(oneFloor);
	CLASS_DELETE(secondFloor);
	CLASS_DELETE(thirdFloor);
}

void StageScene::Update()
{
	for (int i = 0; i < vStageObj.size(); i++)
	{
		vStageObj[i]->Update();
	}

	StageMove();

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		Undo(stageScale);
	}

	if (gInput->GetKeyTrigger(VK_ESCAPE))
	{
		ChangeFloor(2);
	}

	// �����Ă���Ƃ��Ɠ����I������u�Ԃ���
	if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
	{
		// �O���b�h�e�[�u�����X�V����
		TableUpdate();
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		for (int k = 0; k < MAX_LAYER; k++)
		{
			if (k == 1 && secondFloor == nullptr)
			{
				break;
			}
			else if (k == 2 && thirdFloor == nullptr)
			{
				break;
			}

			for (int i = 0; i < stageSquare.y; i++)
			{
				for (int j = 0; j < stageSquare.x; j++)
				{
					floorUndo[nNextUndo].floorTable[k][i][j] = nowFloor->floorTable[i][j];
					floorUndo[nNextUndo].objectTable[k][i][j] = nowFloor->objectTable[i][j];
				}
			}
		}

		floorUndo[nNextUndo].playerUndo = player->GetGridPos();
		floorUndo[nNextUndo].stateUndo = player->GetState();
		floorUndo[nNextUndo].dirUndo = player->GetDirection();
		floorUndo[nNextUndo].calorieUndo = player->GetCalorie();
		floorUndo[nNextUndo].old_Floor = nowFloorNum;

		nNextUndo++;
		nNumUndo = nNextUndo;
		if (nNextUndo > 20)
		{
			nNextUndo = 0;
		}
	}
}

void StageScene::StageMove()
{
	// ���v���C���[�̓����ɂ��킹�ăX�e�[�W���̕��𓮂���
	if (player->GetPlayerMove()->GetIsMoveStart())
	{
		// �v���C���[�������Ă�@���@�ړ������悪�J�X�e���Ȃ�
		if (player->GetState() == Player::STATE::FAT &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CASTELLA)
		{
			// �J�X�e���Ɉړ�����Ɩ��߂���
			CastellaMoveOrder();
		}
		// �v���C���[���}�b�`���@���@�ړ��悪�ǂȂ�
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::WALL)
		{
			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::WALL));
			wallObj->Break();
		}
		if (player->GetPlayerMove()->CheckNowFloorType() == CGridObject::BlockType::WATAAME)
		{
			CWataame* wataameObj = dynamic_cast<CWataame*>(GetStageObject(player->GetGridPos(), CGridObject::BlockType::WATAAME));
			wataameObj->Melt();

			// �������Ō��̃I�u�W�F�N�g��new����vstageObj��pushback����

			CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
			hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
			hollObj->SetBlookType(CGridObject::BlockType::HOLL);
			hollObj->mTransform.pos = nowFloor->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
			vStageObj.push_back(hollObj);
		}
	}

	// �v���C���[�������I�����
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
			player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
		{
			CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType> (player->GetPlayerMove()->CheckNextFloorType())));
			chocoObj->CRACK();
			if (player->GetState() == Player::STATE::FAT)
			{
				chocoObj->CRACK();
			}
			if (chocoObj->GetActive() == false)
			{
				CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
				hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
				hollObj->SetBlookType(CGridObject::BlockType::HOLL);
				hollObj->mTransform.pos = nowFloor->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
				vStageObj.push_back(hollObj);
			}
		}
		// �A�C�e��������Ȃ炻�����ʂ������
		ItemDelete();
	}
	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		if (player->GetState() != Player::STATE::MUSCLE && nNumProtein <= 0)
		{
			player->ChangeState(Player::STATE::MUSCLE);
		}

	}

}

void StageScene::TableUpdate()
{
	// ��U�S�Ĕ����ɂ���
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// ���̍s�̍ŏ����g���Ă��Ȃ��Ȃ�I���
		if (nowFloor->floorTable[i][0] == 0) break;

		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// �񂪎g���Ă��Ȃ��Ȃ�
			if (nowFloor->floorTable[i][j] == 0) break;

			nowFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
			nowFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
		}
	}

	// �z��S�Č���
	for (auto itr = vStageObj.begin(); itr != vStageObj.end(); itr++)
	{
		// ���̃I�u�W�F�N�g����ʂɂȂ��Ȃ玟�ɍs��
		if (!(*itr)->GetActive()) continue;

		// �O���b�h���W�����
		CGrid::GRID_XY g = (*itr)->GetGridPos();
		// ���̊K�w�̃e�[�u���ɍX�V����
		if ((*itr)->GetCategory() == CGridObject::Category::FLOOR)
		{
			nowFloor->floorTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
		else
		{
			nowFloor->objectTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
	}
}

void StageScene::CastellaMoveOrder()
{
	// ���W�����߂� ////////////////////////////////////////////////////
	CGrid::GRID_XY d = {};
	switch (static_cast<Player::DIRECTION>(player->GetDirection()))
	{
	case Player::DIRECTION::UP:
		d.y = -1;
		break;

	case Player::DIRECTION::DOWN:
		d.y = 1;
		break;

	case Player::DIRECTION::RIGHT:
		d.x = 1;
		break;

	case Player::DIRECTION::LEFT:
		d.x = -1;
		break;
	}

	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	// ��������̃��[���h���W�����߂�
	CGrid::GRID_XY targetGrid = { next.x + d.x, next.y + d.y };

	Vector3 target = nowFloor->GridToWorld(targetGrid, CGridObject::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// ���X�g�̒�����v���C���[�̈ڑ�����W�Ɠ������́@���@�J�X�e����T��
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == CGridObject::BlockType::CASTELLA);
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// ���������悪���Ȃ�
	if (nowFloor->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CGridObject::BlockType::HOLL))
	{
		Vector3 floorPos = nowFloor->GridToWorld(targetGrid, CGridObject::BlockType::FLOOR);
		castella->Move(target, true, floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// �I�u�W�F�N�g�e�[�u������J�X�e����������
		nowFloor->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CGridObject::BlockType::NONE);

		//	�J�X�e�������ɂ���
		castella->SetCategory(CGridObject::Category::FLOOR);
		castella->SetBlookType(CGridObject::BlockType::CASTELLA_FLOOR);

		// ������ʂ������
		GetStageFloor(targetGrid, CGridObject::BlockType::HOLL)->SetActive(false);
	}
	else
	{
		castella->Move(target, player->GetDirection());
		castella->SetGridPos(targetGrid.x, targetGrid.y);
	}
}

void StageScene::ItemDelete()
{
	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	CGridObject* deleteObj;	// ��ʂ�������\��̃|�C���^���͂���

	switch (static_cast<CGridObject::BlockType>
		(nowFloor->objectTable[next.y][next.x]))
	{
		// �v���C���[�̈ʒu�ɂ��̃A�C�e���������
	case CGridObject::BlockType::PROTEIN:
		nNumProtein--;
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// ���X�g�̒�����v���C���[�̍��W�Ɠ������́@���@������Ȃ�����T��
		auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>(nowFloor->objectTable[next.y][next.x]));

		// ��ʂ������
		deleteObj->SetActive(false);
	}

	break;

	default:
		break;
	}
}

void StageScene::Undo(float _stageScale)
{
	// ��O��Undo���Q�Ƃ���
	nNumUndo--;
	if (nNumUndo < 0)
	{
		nNumUndo = 0;
	}

	// �X�V����e�[�u��
	GridTable* updateTable = nowFloor;
	// �X�V����I�u�W�F�N�g�̃��X�g
	std::vector<CGridObject*>& updateObjList = vStageObj;
	// �O�ɂ����K���̃O���b�h�e�[�u�����X�V����
	const short& o_floorNum = floorUndo[nNumUndo].old_Floor;
	switch (o_floorNum)
	{
	case 1:

		break;
	case 2:
		updateTable = secondFloor;
		updateObjList = secondFStgObj;
		break;
	case 3:
		updateTable = thirdFloor;
		updateObjList = thirdFStgObj;
		break;

	default:	// �G���[
		MessageBoxA(NULL, "Undo�֐���old_Floor��1�`3�K�͈̔͂ł���܂���", "�G���[", MB_ICONERROR | MB_OK);
		break;
	}

	// �P������Ă���
	for (int i = 0; i < stageSquare.y; i++)
	{
		for (int j = 0; j < stageSquare.x; j++)
		{
			// ��������
			updateTable->objectTable[i][j] =
				floorUndo[nNumUndo].objectTable[o_floorNum - 1][i][j];
		}
	}
	// ���ꂽ�K�w�̃I�u�W�F�N�g�����
	CreateStage(*updateTable, updateObjList);

	// ���݂̊K�w�̃e�[�u���A�I�u�W�F�N�g�ɐݒ肷��
	nowFloor = updateTable;
	vStageObj = updateObjList;

	// ���̊K�w�ƑO�̊K�w���Ⴄ�Ȃ獡����K�w������Ȃ���
	if (nowFloorNum != o_floorNum)
	{
		switch (nowFloorNum)
		{
		case 1:
			updateTable = oneFloor;
			updateObjList = oneFStgObj;
			break;
		case 2:
			updateTable = secondFloor;
			updateObjList = secondFStgObj;
			break;
		case 3:
			updateTable = thirdFloor;
			updateObjList = thirdFStgObj;
			break;

		default:
			MessageBoxA(NULL, "Undo�֐���nowFloorNum��1�`3�K�͈̔͂ł���܂���", "�G���[", MB_ICONERROR | MB_OK);
			break;
		}

		// �P������Ă���
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// ��������
				updateTable->objectTable[i][j] =
					floorUndo[nNumUndo].objectTable[nowFloorNum - 1][i][j];
			}
		}
		// ���ꂽ�K�w�̃I�u�W�F�N�g�����
		CreateStage(*updateTable, updateObjList);
	}
	// ���X������K�w���X�V
	nowFloorNum = o_floorNum;

	FIELD_FLOOR beforeStage = floorUndo[nNumUndo];
	// �v���C���[�ɕK�v�ȏ����X�V����
	UndoPlayerSet(beforeStage.dirUndo, beforeStage.calorieUndo, beforeStage.stateUndo);
}

void StageScene::UndoPlayerSet(const int& _dir, const int& _calorie,
	const Player::STATE& _state)
{
	player->SetGridTable(nowFloor);

	// ������ݒ�
	player->SetDirection(_dir);


	CPlayerAnim::PATTERN animPattern;
	switch (static_cast<Player::DIRECTION>(_dir))
	{
	case Player::DIRECTION::DOWN:
	case Player::DIRECTION::EVERY:
		animPattern = CPlayerAnim::PATTERN::STAY_DOWN;
		break;

	case Player::DIRECTION::LEFT:
		animPattern = CPlayerAnim::PATTERN::STAY_LEFT;
		break;

	case Player::DIRECTION::RIGHT:
		animPattern = CPlayerAnim::PATTERN::STAY_RIGHT;
		break;

	case Player::DIRECTION::UP:
		animPattern = CPlayerAnim::PATTERN::STAY_UP;
		break;
	}

	// �A�j���[�V�����̉摜�����f������
	player->GetmAnim()->SetPattern(static_cast<int>(animPattern));

	// �J�����[��ݒ�
	player->SetCalorie(_calorie);

	// ��Ԃ�ω�������
	player->ChangeState(_state);

}

void StageScene::Draw()
{
	Z_Sort(vStageObj);
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Draw();
	}
}

void StageScene::Z_Sort(std::vector<CGridObject*>& _sortList)
{
	std::sort(_sortList.begin(), _sortList.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });
}

void StageScene::Init(const wchar_t* filePath, float _stageScale)
{
	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	D3D_CreateSquare({ 3,4 }, &playerBuffer);

	stageTextureHoll = NULL;

	// �X�e�[�W�̑傫����ݒ肷��
	stageScale = _stageScale;
	nNumProtein = 0;

	stage = new CLoadStage;
	//stageMake = new CStageMake();

	LoadData StageData = stage->LoadStage(filePath);

	stageSquare = { StageData.numX,StageData.numY };

	//	���[���h���W
	/*stagePos = stageMake->StagePos(StageData);*/

	// �����ŃO���b�h�e�[�u�����쐬����@/////////////
	// �K�w���Ƃ̃e�[�u���ɓ���Ă��� ///////////////
	oneFloor = new GridTable({ StageData.numX, StageData.numY }, _stageScale);
	if (StageData.secondFloor.floorTable[0][0] != 0) //0�������Ă���΍���ĂȂ��@�K�w�Ȃ�
	{
		secondFloor = new GridTable({ StageData.numX, StageData.numY }, _stageScale);
		if (StageData.thirdFloor.floorTable[0][0] != 0)
		{
			thirdFloor = new GridTable({ StageData.numX,StageData.numY }, _stageScale);
		}
	}
	else
	{
		secondFloor = nullptr;
		thirdFloor = nullptr;
	}

	//�J�n����K�w
	int startfloor = 0;

	// ���[�h�����f�[�^����O���b�h�e�[�u���ɓ����
	for (int i = 0; i < StageData.numY; i++)
	{
		for (int j = 0; j < StageData.numX; j++)
		{
			// �I�u�W�F�N�g�̃J�e�S�����擾����
			CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]);
			CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

			// ����������
			if (bCate == CGridObject::Category::FLOOR)
			{
				// ���e�[�u���ɓ����
				oneFloor->floorTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// �I�u�W�F�N�g�e�[�u���ɂ͉����u���Ȃ�(99�����Ă�)
				oneFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
			}
			// �I�u�W�F�N�g�E�A�C�e���Ȃ�
			else
			{
				//	�I�u�W�F�N�g�e�[�u���ɓ����
				oneFloor->objectTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// ���e�[�u���ɂ͒ʏ폰������
				oneFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
				//�ǂݍ��񂾐������Ƃɏ������郂�m
				switch (static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]))
				{
				case CGridObject::BlockType::START:
					startfloor = 1;
					nowFloor = oneFloor;
					break;
				case CGridObject::BlockType::PROTEIN:
					nNumProtein++;
					break;
				default:
					break;
				}
			}

			//�Q�K������΃e�[�u���쐬
			if (secondFloor != nullptr)
			{
				CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.secondFloor.floorTable[i][j]);
				CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

				// ����������
				if (bCate == CGridObject::Category::FLOOR)
				{
					// ���e�[�u���ɓ����
					secondFloor->floorTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// �I�u�W�F�N�g�e�[�u���ɂ͉����u���Ȃ�(99�����Ă�)
					secondFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
				}
				// �I�u�W�F�N�g�E�A�C�e���Ȃ�
				else
				{
					//	�I�u�W�F�N�g�e�[�u���ɓ����
					secondFloor->objectTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// ���e�[�u���ɂ͒ʏ폰������
					secondFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
					switch (static_cast<CGridObject::BlockType>(StageData.secondFloor.floorTable[i][j]))
					{
					case CGridObject::BlockType::START:
						startfloor = 2;
						nowFloor = secondFloor;
						break;
					case CGridObject::BlockType::PROTEIN:
						nNumProtein++;
						break;
					default:
						break;
					}
				}

				//�R�K������΃e�[�u�����쐬����
				if (thirdFloor != nullptr)
				{
					CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.thirdFloor.floorTable[i][j]);
					CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

					// ����������
					if (bCate == CGridObject::Category::FLOOR)
					{
						// ���e�[�u���ɓ����
						thirdFloor->floorTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// �I�u�W�F�N�g�e�[�u���ɂ͉����u���Ȃ�(99�����Ă�)
						thirdFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
					}
					// �I�u�W�F�N�g�E�A�C�e���Ȃ�
					else
					{
						//	�I�u�W�F�N�g�e�[�u���ɓ����
						thirdFloor->objectTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// ���e�[�u���ɂ͒ʏ폰������
						thirdFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
						switch (static_cast<CGridObject::BlockType>(StageData.thirdFloor.floorTable[i][j]))
						{
						case CGridObject::BlockType::START:
							startfloor = 3;
							nowFloor = thirdFloor;
							break;
						case CGridObject::BlockType::PROTEIN:
							nNumProtein++;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}

	nowFloorNum = startfloor;	// 1�K����


	//�����ŃO���b�h�e�[�u�����쐬���� /////////////////////////////////////////

	// �X�e�[�W���쐬����
	CreateStage(*oneFloor, oneFStgObj);

	vStageObj = oneFStgObj;

	// 2�K��3�K���g���Ă���Ȃ�
	if (secondFloor != nullptr)
	{
		CreateStage(*secondFloor, secondFStgObj);
		if (thirdFloor != nullptr)
		{
			CreateStage(*thirdFloor, thirdFStgObj);
		}
	}

	for (int k = 0; k < MAX_LAYER; k++)
	{
		if (k == 1 && secondFloor == nullptr)
		{
			break;
		}
		else if (k == 2 && thirdFloor == nullptr)
		{
			break;
		}

		for (int i = 0; i < StageData.numY; i++)
		{
			for (int j = 0; j < StageData.numX; j++)
			{
				floorUndo[0].floorTable[k][i][j] = oneFloor->floorTable[i][j];
				floorUndo[0].objectTable[k][i][j] = oneFloor->objectTable[i][j];
			}
		}
	}

	// �v���C���[�̏��������s���i�����ōŏ��ɂǂ̕����ɐi�ނ������߂Ă���j
	player->Init(nowFloor);

	floorUndo[0].playerUndo = player->GetGridPos();
	floorUndo[0].stateUndo = player->GetState();
	floorUndo[0].dirUndo = player->GetDirection();
	floorUndo[0].calorieUndo = player->GetCalorie();
	floorUndo[0].old_Floor = 1;
	Z_Sort(vStageObj);
}

void StageScene::CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList)
{

	// �������
	for (int i = 0; i < _settingList.size(); i++)
	{
		CLASS_DELETE(_settingList[i]);
	}
	_settingList.clear();

	// �I�u�W�F�N�g�e�[�u��
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// ���[��0�Ȃ�I���@���@
		if (_gridTable.objectTable[i][0] == 0) break;

		// ��Â��Ă���
		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// ���̍s�ŏ��߂�0���o���Ȃ�@���@�X�e�[�W�Ŏg���Ă��Ȃ��Ƃ���Ȃ�
			if (_gridTable.objectTable[i][0] == 0) break;

			// �I�u�W�F�N�g ////////////////////////////////////
			// �I�u�W�F�N�g�𐶐�����
			CGridObject* objWork = nullptr;
			switch (static_cast<CGridObject::BlockType>(_gridTable.objectTable[i][j]))
			{
			case CGridObject::BlockType::WALL:
				objWork = new CWall(stageBuffer, stageTextureWall);
				break;

			case CGridObject::BlockType::CAKE:
				objWork = new CCake(stageBuffer, stageTextureCake);
				break;

			case CGridObject::BlockType::CASTELLA:
				objWork = new CCastella(stageBuffer, stageTextureCastella);
				break;

			case CGridObject::BlockType::BAUMHORIZONTAL:
				objWork = new CBaum(stageBuffer, stageTextureBaumkuchen_L);
				break;

			case CGridObject::BlockType::BAUMVERTICAL:
				objWork = new CBaum(stageBuffer, stageTextureBaumkuchen_R);
				break;

			case CGridObject::BlockType::COIN:
				objWork = new CCoin(stageBuffer, stageTextureCoin);
				break;

			case CGridObject::BlockType::GUMI:
				objWork = new CGumi(stageBuffer, stageTextureGumi);
				break;

			case CGridObject::BlockType::PROTEIN:
				objWork = new CProtein(stageBuffer, stageTextureProtein);
				break;

			case CGridObject::BlockType::CHILI:
				objWork = new CChili(stageBuffer, stageTextureChili);
				break;

			case CGridObject::BlockType::START:
				objWork = new Player(playerBuffer, NULL);
				// �v���C���[�͐G�邱�Ƃ������̂Ń����o�ϐ��Ƃ��Ď����Ă���
				player = dynamic_cast<Player*>(objWork);
				break;

			case CGridObject::BlockType::GALL:
				objWork = new CGall(stageBuffer, stageTextureGallChest);
				break;

			default:
				break;

			}

			if (objWork != nullptr)	// �I�u�W�F�N�g�𐶐����Ă���Ȃ�
			{
				// �O���b�h���W����������
				objWork->SetGridPos(j, i);

				// ���W��ݒ�
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.objectTable[i][j]);

				// �X�e�[�W�S�̂̑傫����ݒ�
				objWork->mTransform.scale = { stageScale, stageScale, 1 };
				// �I�u�W�F�N�g�ɂ��̎�ނ���������
				objWork->SetBlookType(b);
				// �I�u�W�F�N�g�ɃJ�e�S���[����������
				objWork->SetCategory(CGridObject::TypeToCategory(b));

				objWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// �A�C�e���Ȃ炱���ŉe�̐ݒ肷��
				if (objWork->GetCategory() == CGridObject::Category::ITEM)
				{
					dynamic_cast<CItem*>(objWork)->InitItem(shadowTexture);
				}


				_settingList.push_back(objWork);
			}
			// �I�u�W�F�N�g /////////////////////////////////////

			// �� ///////////////////////////////////////////////
			CGridObject* floorWork = nullptr;
			// ���𐶐�����
			switch (static_cast<CGridObject::BlockType>(_gridTable.floorTable[i][j]))
			{
			case CGridObject::BlockType::FLOOR:
				floorWork = new CFloor(stageBuffer, stageTextureFloor);
				if ((i + j) % 2 == 0)
				{
					floorWork->SetTexture(stageTextureFloor2);
				}
				break;

			case CGridObject::BlockType::HOLL:
				floorWork = new CHoll(stageBuffer, stageTextureHoll);
				break;


			case CGridObject::BlockType::WATAAME:
				floorWork = new CWataame(stageBuffer, stageTextureWataame);
				break;

			case CGridObject::BlockType::CHOCO:
				floorWork = new CChoco(stageBuffer, stageTextureChocolate);
				break;

			case CGridObject::BlockType::CHOCOCRACK:
				floorWork = new CChoco(stageBuffer, stageTextureChocolate);
				break;

			default:
				break;
			}
			// �� //////////////////////////////////////////////////////////////////////

			if (floorWork != nullptr)
			{
				// �O���b�h���W����������
				floorWork->SetGridPos(j, i);

				// ���W��ݒ�
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.floorTable[i][j]);

				// �X�e�[�W�S�̂̑傫����ݒ�
				floorWork->mTransform.scale = { stageScale, stageScale, 1 };
				// �I�u�W�F�N�g�ɂ��̎�ނ���������
				floorWork->SetBlookType(b);
				// ���J�e�S���ɐݒ肷��
				floorWork->SetCategory(CGridObject::Category::FLOOR);

				floorWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// �z��ɓ���Ă���
				_settingList.push_back(floorWork);
			}

		}

	}
}

void StageScene::ChangeFloor(int _nextFloor)
{
	vStageObj.clear();
	switch (_nextFloor)
	{
	case 1:
		vStageObj = oneFStgObj;
		player->SetGridTable(oneFloor);
		break;
	case 2:
		vStageObj = secondFStgObj;
		player->SetGridTable(secondFloor);
		break;
	case 3:
		vStageObj = thirdFStgObj;
		player->SetGridTable(thirdFloor);
		break;
	default:
		break;
	}
}

CGridObject* StageScene::GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// ���X�g�̒�����w�肵�����W�@�I�u�W�F�N�g�e�[�u���ɂ������
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType));
		});

	return (*itr);
}

CGridObject* StageScene::GetStageFloor(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// ���X�g�̒�����w�肵�����W�@�I�u�W�F�N�g�e�[�u���ɂ������
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType));
		});

	return (*itr);
}
