#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

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
#include "Player.h"
#include "GridTable.h"

#define PLAYER dynamic_cast<Player*>(player)	// �킴�킴�����̂߂�ǂ�����

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	nNumProtein = 0;
}

StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);

	SAFE_RELEASE(stageTextureFloor);
	SAFE_RELEASE(stageTextureFloor2);
	SAFE_RELEASE(stageTextureBaumkuchen);
	SAFE_RELEASE(stageTextureCake);
	SAFE_RELEASE(stageTextureCastella);
	SAFE_RELEASE(stageTextureChili);
	SAFE_RELEASE(stageTextureChocolate);
	SAFE_RELEASE(stageTextureCoin);
	SAFE_RELEASE(stageTextureGallChest);
	SAFE_RELEASE(stageTextureGumi);
	SAFE_RELEASE(stageTextureProtein);
	SAFE_RELEASE(stageTextureWall);
	SAFE_RELEASE(stageTextureWataame);
	SAFE_RELEASE(playerTexture);

	CLASS_DELETE(stageMake);
	CLASS_DELETE(stage);
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it != vStageObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
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

	// �����Ă���Ƃ��Ɠ����I������u�Ԃ���
	if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
	{
		// �O���b�h�e�[�u�����X�V����
		TableUpdate();
	}
}

void StageScene::StageMove()
{
	// ���v���C���[�̓����ɂ��킹�ăX�e�[�W���̕��𓮂���
	if (player->GetPlayerMove()->GetIsMoveStart())
	{
		// �v���C���[�������Ă�@���@�ړ������悪�J�X�e���Ȃ�
		if (player->GetState() == Player::STATE::FAT &&
			player->GetPlayerMove()->CheckNextObjectType() == CStageMake::BlockType::CASTELLA)
		{
			// �J�X�e���Ɉړ�����Ɩ��߂���
			CastellaMoveOrder();
		}
		// �v���C���[���}�b�`���@���@�ړ��悪�ǂȂ�
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CStageMake::BlockType::WALL)
		{
			CWall* wallobj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<int>(CStageMake::BlockType::WALL)));
			wallobj->Break();
		}
	}

	// �v���C���[�������I�����
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		// �A�C�e��������Ȃ炻�����ʂ������
		ItemDelete();
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

			nowFloor->floorTable[i][j] = static_cast<int>(CStageMake::BlockType::FLOOR);
			nowFloor->objectTable[i][j] = static_cast<int>(CStageMake::BlockType::NONE);
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
		if ((*itr)->GetCategory() == static_cast<int>(CStageMake::Category::FLOOR))
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

	Vector3 target = nowFloor->GridToWorld(targetGrid, CStageMake::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// ���X�g�̒�����v���C���[�̈ڑ�����W�Ɠ������́@���@�J�X�e����T��
	auto itr = std::find_if(vStageObj.begin(), vStageObj.end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == static_cast<int>(CStageMake::BlockType::CASTELLA));
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// ���������悪���Ȃ�
	if (nowFloor->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CStageMake::BlockType::HOLL))
	{
		Vector3 floorPos = nowFloor->GridToWorld(targetGrid, CStageMake::BlockType::FLOOR);
		castella->Move(target, true, floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// �I�u�W�F�N�g�e�[�u������J�X�e����������
		nowFloor->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CStageMake::BlockType::NONE);

		//	�J�X�e�������ɂ���
		castella->SetCategory(static_cast<int>(CStageMake::Category::FLOOR));
		castella->SetBlookType(static_cast<int>(CStageMake::BlockType::CASTELLA_FLOOR));

		// ������ʂ������
		GetStageFloor(targetGrid, static_cast<int>(CStageMake::BlockType::HOLL))->SetActive(false);
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

	switch (static_cast<CStageMake::BlockType>
		(nowFloor->objectTable[next.y][next.x]))
	{
		// �v���C���[�̈ʒu�ɂ��̃A�C�e���������
	case CStageMake::BlockType::PROTEIN:
		nNumProtein--;
		if (nNumProtein <= 0)
		{
			player->ChangeState(Player::STATE::MUSCLE);
		}
	case CStageMake::BlockType::CAKE:
	case CStageMake::BlockType::COIN:
	case CStageMake::BlockType::CHILI:
	{
		// ���X�g�̒�����v���C���[�̍��W�Ɠ������́@���@������Ȃ�����T��
		auto itr = std::find_if(vStageObj.begin(), vStageObj.end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == static_cast<int>(CStageMake::Category::ITEM));
			});

		// ��ʂ������
		(*itr)->SetActive(false);
	}

	break;

	default:
		break;
	}
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

	D3D_LoadTexture(L"asset/Stage/floor_y.png", &stageTextureFloor);
	D3D_LoadTexture(L"asset/Stage/floor_g.png", &stageTextureFloor2);
	D3D_LoadTexture(L"asset/Stage/Baumkuchen_R.png", &stageTextureBaumkuchen);
	D3D_LoadTexture(L"asset/Item/Cake.png", &stageTextureCake);
	D3D_LoadTexture(L"asset/Stage/Castella.png", &stageTextureCastella);
	D3D_LoadTexture(L"asset/Item/Chili.png", &stageTextureChili);
	D3D_LoadTexture(L"asset/Stage/Chocolate.png", &stageTextureChocolate);
	D3D_LoadTexture(L"asset/Item/Coin.png", &stageTextureCoin);
	D3D_LoadTexture(L"asset/Stage/GallChest.png", &stageTextureGallChest);
	D3D_LoadTexture(L"asset/Stage/Gumi.png", &stageTextureGumi);
	D3D_LoadTexture(L"asset/Item/Protein.png", &stageTextureProtein);
	D3D_LoadTexture(L"asset/Stage/Wall.png", &stageTextureWall);
	D3D_LoadTexture(L"asset/Stage/Wataame.png", &stageTextureWataame);
	D3D_LoadTexture(L"asset/Player/N_Walk01_Back.png", &playerTexture);

	nNumProtein = 0;

	stage = new CLoadStage;
	stageMake = new CStageMake;

	LoadData StageData = stage->LoadStage(filePath);

	//	���[���h���W
	stagePos = stageMake->StagePos(StageData);

	// �����ŃO���b�h�e�[�u�����쐬����@/////////////
	oneFloor = new GridTable({ StageData.numX, StageData.numY }, _stageScale);

	secondFloor = nullptr;
	thirdFloor = nullptr;

	nowFloor = oneFloor;


	//��
	for (int i = 0; i < StageData.numY; i++)
	{
		// �s
		for (int j = 0; j < StageData.numX; j++)
		{
			// �J�e�S���[�ʂɃZ�b�g����
			CStageMake::Category nowObjCate;
			switch (static_cast<CStageMake::BlockType>(StageData.data[i * StageData.numX + j]))
			{
			case CStageMake::BlockType::FLOOR:
			case CStageMake::BlockType::HOLL:
			case CStageMake::BlockType::WATAAME:
			case CStageMake::BlockType::CHOCO:
				nowObjCate = CStageMake::Category::FLOOR;
				break;

			case CStageMake::BlockType::CAKE:
			case CStageMake::BlockType::COIN:
			case CStageMake::BlockType::PROTEIN:
				nowObjCate = CStageMake::Category::ITEM;
				break;

			case CStageMake::BlockType::WALL:
			case CStageMake::BlockType::CASTELLA:
			case CStageMake::BlockType::BAUMHORIZONTAL:
			case CStageMake::BlockType::BAUMVERTICAL:
			case CStageMake::BlockType::GUMI:
			case CStageMake::BlockType::GALL:
			case CStageMake::BlockType::START:
				nowObjCate = CStageMake::Category::OBJECT;
				break;
			}

			// �ǂݍ��񂾂��̂����J�e�S���Ȃ�
			if (nowObjCate == CStageMake::Category::FLOOR)
			{
				// ���e�[�u���ɓ����
				oneFloor->floorTable[i][j] = StageData.data[i * StageData.numX + j];
				// �I�u�W�F�N�g�e�[�u���ɂ͉����u���Ȃ�(99�����Ă�)
				oneFloor->objectTable[i][j] = static_cast<int>(CStageMake::BlockType::NONE);
			}
			else
			{
				oneFloor->objectTable[i][j] = StageData.data[i * StageData.numX + j];
				// ���e�[�u���ɂ͕��ʂ̏�������
				oneFloor->floorTable[i][j] = static_cast<int>(CStageMake::BlockType::FLOOR);
			}

			// ���̍��W������
			Vector3 floorPos = oneFloor->GridToWorld({ j,i }, CStageMake::BlockType::FLOOR);

			stageObj = nullptr;
			//���̉摜�Z�b�g�̏���
			switch (static_cast<CStageMake::BlockType>(StageData.data[i * StageData.numX + j]))
			{
			case CStageMake::BlockType::FLOOR:
				stageObj = new CFloor(stageBuffer, stageTextureFloor);
				if ((i + j) % 2 == 0)
				{
					stageObj->SetTexture(stageTextureFloor2);
				}
				break;

			case CStageMake::BlockType::WALL:
				stageObj = new CWall(stageBuffer, stageTextureWall);
				break;

			case CStageMake::BlockType::HOLL:
				stageObj = new CHoll(stageBuffer, NULL);
				break;

			case CStageMake::BlockType::CAKE:
				stageObj = new CCake(stageBuffer, stageTextureCake);
				break;

			case CStageMake::BlockType::CASTELLA:
				stageObj = new CCastella(stageBuffer, stageTextureCastella);
				break;

			case CStageMake::BlockType::BAUMHORIZONTAL:
				stageObj = new CBaum(stageBuffer, stageTextureBaumkuchen);
				break;

			case CStageMake::BlockType::BAUMVERTICAL:
				stageObj = new CBaum(stageBuffer, stageTextureBaumkuchen);
				break;

			case CStageMake::BlockType::COIN:
				stageObj = new CCoin(stageBuffer, stageTextureCoin);

				break;
			case CStageMake::BlockType::WATAAME:
				stageObj = new CWataame(stageBuffer, stageTextureWataame);
				break;

			case CStageMake::BlockType::CHOCO:
				stageObj = new CChoco(stageBuffer, stageTextureChocolate);
				break;

			case CStageMake::BlockType::GUMI:
				stageObj = new CGumi(stageBuffer, stageTextureGumi);
				break;

			case CStageMake::BlockType::PROTEIN:
				stageObj = new CProtein(stageBuffer, stageTextureProtein);
				nNumProtein++;
				break;

			case CStageMake::BlockType::START:
				stageObj = new Player(stageBuffer, playerTexture);
				break;

			case CStageMake::BlockType::GALL:
				stageObj = new CGall(stageBuffer, stageTextureGallChest);
				break;

			default:
				break;
			}

			if (StageData.data[i * StageData.numX + j] == static_cast<int>(CStageMake::BlockType::START))
			{
				player = dynamic_cast<Player*>(stageObj);
			}

			// �O���b�h���W����������
			stageObj->SetGridPos(j, i);
			// ���W��ݒ�
			stageObj->mTransform.pos = oneFloor->GridToWorld({ j, i },
				static_cast<CStageMake::BlockType>(StageData.data[i * StageData.numX + j]));
			// �X�e�[�W�S�̂̑傫����ݒ�
			stageObj->mTransform.scale = { _stageScale, _stageScale, 1 };
			// �I�u�W�F�N�g�ɂ��̎�ނ���������
			stageObj->SetBlookType(StageData.data[i * StageData.numX + j]);
			// �I�u�W�F�N�g�ɃJ�e�S������������
			stageObj->SetCategory(static_cast<int>(nowObjCate));
			// �I�u�W�F�N�g�����X�g�ɓ����
			vStageObj.push_back(stageObj);

			//	�����K�v�Ȃ��Ȃ玟�̃��[�v
			if (static_cast<CStageMake::Category>(stageObj->GetCategory()) == CStageMake::Category::FLOOR)
				continue;

			// �����쐬
			CGridObject* floorObj = new CFloor(stageBuffer, stageTextureFloor);
			if ((i + j) % 2 == 0)
			{
				floorObj->SetTexture(stageTextureFloor2);
			}
			floorObj->SetGridPos(j, i);
			// �p�����[�^�ݒ�
			floorObj->mTransform.pos = floorPos;
			floorObj->mTransform.scale = { _stageScale, _stageScale, 1.0f };
			// �I�u�W�F�N�g�ɂ��̎�ނ���������
			floorObj->SetBlookType(static_cast<int>(CStageMake::BlockType::FLOOR));
			floorObj->SetCategory(static_cast<int>(CStageMake::Category::FLOOR));
			vStageObj.push_back(floorObj);
		}
	}
	// �v���C���[�̏��������s���i�����ōŏ��ɂǂ̕����ɐi�ނ������߂Ă���j
	player->Init(nowFloor);

	Z_Sort(vStageObj);
}

CGridObject* StageScene::GetStageObject(CGrid::GRID_XY _gridPos, int _blockType)
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

CGridObject* StageScene::GetStageFloor(CGrid::GRID_XY _gridPos, int _blockType)
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
