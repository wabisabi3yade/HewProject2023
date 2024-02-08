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
#include"CCannon.h"
//#include "Player.h"
#include "GridTable.h"
#include "TextureFactory.h"

#define PLAYER dynamic_cast<Player*>(player)	// �킴�킴�����̂߂�ǂ�����

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	nNumProtein = 0;

	startFloor = 0;

	changeflag = false;

	FloorOnlyMap = false;

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
	stageTextureChocolateClack = texFactory->Fetch(L"asset/Stage/ChocoClack.png");
	stageTextureCake = texFactory->Fetch(L"asset/Item/Cake.png");
	stageTextureChili = texFactory->Fetch(L"asset/Item/Chili.png");
	stageTextureCoin = texFactory->Fetch(L"asset/Item/Coin.png");
	stageTextureGallChest = texFactory->Fetch(L"asset/Stage/GallChest.png");
	stageTextureGumi = texFactory->Fetch(L"asset/Stage/Gumi.png");
	stageTextureProtein = texFactory->Fetch(L"asset/Item/Protein.png");
	/*playerTexture = texFactory->Fetch(L"asset/Stage/floor_y.png");*/
	shadowTexture = texFactory->Fetch(L"asset/Item/shadow.png");
	stageTextureArrow = texFactory->Fetch(L"asset/UI/Arrow.png");
	stageTextureCannon[0] = texFactory->Fetch(L"asset/Stage/Canon_RightLeft.png");
	stageTextureCannon[1] = texFactory->Fetch(L"asset/Stage/Canon_UpDown.png");

}

// �e�N�X�`���͉�����Ȃ�
StageScene::~StageScene()
{
	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

	CLASS_DELETE(stage);

	for (int i = 0; i < oneFStgObj.size(); i++)
	{
		CLASS_DELETE(oneFStgObj[i]);
	}
	oneFStgObj.clear();

	for (int i = 0; i < secondFStgObj.size(); i++)
	{
		CLASS_DELETE(secondFStgObj[i]);
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
	for (auto i : *vStageObj)
	{
		i->Update();
	}

	StageMove();

	if (gInput->GetKeyTrigger(VK_BACK))
	{
		Undo(stageScale);
	}

	/// 
	/// �K�w�ύX���Ă���
	/// 

	if (player->GetPlayerMove()->GetisLoolMap() == true)
	{
		InputManager* input = InputManager::GetInstance();

		if (input->GetInputTrigger(InputType::L_BUTTON))
		{
			if (lockStageMap != nMaxFloor)
			{
				lockStageMap++;
			}
			if (lockStageMap == nowFloorNum)
			{
				//lockStageMap++;
			}
		}
		else if (input->GetInputTrigger(InputType::R_BUTTON))
		{

			if (lockStageMap != 1)
			{
				lockStageMap--;
			}
			if (lockStageMap == nowFloorNum)
			{
				//lockStageMap--;
			}
		}
		else if (input->GetInputTrigger(InputType::CANCEL))
		{
			player->GetPlayerMove()->CameraEnd();
		}
		else if (input->GetInputTrigger(InputType::OPTION))
		{
			FloorOnlyMap = !FloorOnlyMap;
		}


	}
	if (player->GetPlayerMove()->GetIncannon() && !cannonMove)
	{
		InCanonInput();
	}
	// �����Ă���Ƃ��Ɠ����I������u�Ԃ���
	if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
	{
		// �O���b�h�e�[�u�����X�V����
		TableUpdate();
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{
		UndoTableUpdate();
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
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CAKE)
		{
			CCake* cakeObj = dynamic_cast<CCake*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			cakeObj->BlowOff(player->GetDirection());
		}

		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CHILI)
		{
			CChili* chiliObj = dynamic_cast<CChili*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			chiliObj->BlowOff(player->GetDirection());
		}

		if (player->GetPlayerMove()->CheckNowFloorType() == CGridObject::BlockType::WATAAME)
		{
			CWataame* wataameObj = dynamic_cast<CWataame*>(GetStageObject(player->GetGridPos(), CGridObject::BlockType::WATAAME));
			wataameObj->Melt();

			//for (auto it = vStageObj.begin(); it != vStageObj.end();) {
			//	// ������v�����v�f���폜����
			//	if (*it == wataameObj) {
			//		// �폜���ꂽ�v�f�̎����w���C�e���[�^���Ԃ����B
			//		it = vStageObj.erase(it);
			//	}
			//	// �v�f�폜�����Ȃ��ꍇ�ɁA�C�e���[�^��i�߂�
			//	else {
			//		++it;
			//	}
			//}


			// �������Ō��̃I�u�W�F�N�g��new����vstageObj��pushback����

			CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
			hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
			hollObj->SetBlookType(CGridObject::BlockType::HOLL);
			hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
			vStageObj->push_back(hollObj);

		}


	}

	// �v���C���[�������I�����
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
			player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
		{
			CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextFloorType())));
			if (player->GetState() != Player::STATE::THIN)
			{
				if (chocoObj->GetBlookType() == CGridObject::BlockType::CHOCOCRACK)
				{
					CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
					hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
					hollObj->SetBlookType(CGridObject::BlockType::HOLL);
					hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
					vStageObj->push_back(hollObj);
					player->GetPlayerMove()->FallStart();
				}
				chocoObj->CRACK();
				chocoObj->SetTexture(stageTextureChocolateClack);
			}
			if (player->GetState() == Player::STATE::FAT || player->GetState() == Player::STATE::MUSCLE)
			{
				chocoObj->CRACK();
				CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
				hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
				hollObj->SetBlookType(CGridObject::BlockType::HOLL);
				hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
				vStageObj->push_back(hollObj);
				player->GetPlayerMove()->FallStart();
			}
		}
		if (player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::GUMI)
		{
			player->GetPlayerMove()->RiseStart();
		}

		// �A�C�e��������Ȃ炻�����ʂ������
		ItemDelete();
	}


	if (player->GetPlayerMove()->GetCannonMoveStartTrigger())
	{
		//player->dotween->DelayedCall(CANNONMOVE_TIME, [&]()
		//	{
		//		ItemDelete();
		//	});
		CGridObject::BlockType type = player->GetPlayerMove()->CheckNextObjectType();
		switch (type)
		{
		case CGridObject::BlockType::WALL:
		{

			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), type));
			wallObj->Break(0.0f);
			break;
		}
		case CGridObject::BlockType::CAKE:
		{
			CCake* cakeObj = dynamic_cast<CCake*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), type));
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			cakeObj->dotween->DelayedCall(CANNONMOVE_TIME, [&, cakeObj, deletePos]()
				{
					cakeObj->BlowOff(player->GetDirection());
					cakeObj->dotween->OnComplete([&, cakeObj, deletePos]()
						{
							CannonItemDelete(deletePos, cakeObj->GetBlookType());
						});

				});
			break;
		}
		case CGridObject::BlockType::CASTELLA:
			break;
		case CGridObject::BlockType::COIN:
		{
			CCoin* coinObj = dynamic_cast<CCoin*>(GetStageObject(player->GetGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNowMassType())));
			coinObj->BlowOff(player->GetDirection());
			coinObj->dotween->OnComplete([&]()
				{
					CannonItemDelete();
				});
			break;
		}
		case CGridObject::BlockType::PROTEIN:
		{
			CProtein* proObj = dynamic_cast<CProtein*>(GetStageObject(player->GetGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNowMassType())));
			proObj->BlowOff(player->GetDirection());
			CGrid::GRID_XY deletePos = player->GetGridPos();
			//nowFloor->objectTable[proObj->GetGridPos().y][proObj->GetGridPos().x] =static_cast<short> (CGridObject::BlockType::NONE);
			proObj->dotween->OnComplete([&, deletePos]()
				{
					CannonItemDelete(deletePos);
				});
			break;
		}
		case CGridObject::BlockType::CHILI:
		{
			CChili* chiliObj = dynamic_cast<CChili*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextMassType())));
			//chiliObj->BlowOff(player->GetDirection());
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			chiliObj->dotween->DelayedCall(CANNONMOVE_TIME, [&, chiliObj, deletePos]()
				{
					chiliObj->BlowOff(player->GetDirection());
					chiliObj->dotween->OnComplete([&, chiliObj, deletePos]()
						{
							CannonItemDelete(deletePos, chiliObj->GetBlookType());
						});

				});
			break;
		}
		default:
			break;
		}
	}
	if (player->GetFallTrriger() == true)
	{
		//player->SetNowFloor(player->GetNowFloor()-1);
		if (player->GetNowFloor() != 0)
		{
			ChangeFloor(player->GetNowFloor() - 1);
		}
	}

	if (player->GetRiseTrriger() == true)
	{
		if (player->GetNowFloor() != 4)
		{
			ChangeFloor(player->GetNowFloor() + 1);
			CGrid::GRID_XY playerNextGridXY = player->GetPlayerMove()->GetNextGridPos();
			auto itr = std::find_if(vStageObj->begin(), vStageObj->end(),
				[&, playerNextGridXY](CGridObject* _obj)
				{
					return (_obj->GetGridPos().x == playerNextGridXY.x && _obj->GetGridPos().y == playerNextGridXY.y &&
						_obj->GetBlookType() == CGridObject::BlockType::FLOOR);
				});
			CFloor* floor = static_cast<CFloor*>((*itr));
			floor->FloorBound();
		}
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{

		if (player->GetState() != Player::STATE::MUSCLE && nNumProtein <= 0)
		{
			player->ChangeState(Player::STATE::MUSCLE);
			player->mTransform.scale.y *= 1.5f;
		}
		// �}�b�`������Ȃ��Ȃ�
		if (player->GetState() == Player::STATE::MUSCLE) return;
		// �����I�������ƂɃJ�����[����ԕς��悤�Ȃ��Ԃ�ω�������
		Player::STATE nextState = Player::STATE::FAT;
		if (player->GetCalorie() <= THIN_CALOMAX)
		{
			nextState = Player::STATE::THIN;
		}
		else if (player->GetCalorie() <= NORMAL_CALOMAX)
		{
			nextState = Player::STATE::NORMAL;
		}

		if (player->GetState() != nextState)
			player->ChangeState(nextState);

	}

}

void StageScene::TableUpdate()
{
	// ��U�S�Ĕ����ɂ���
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// ���̍s�̍ŏ����g���Ă��Ȃ��Ȃ�I���
		if ((nowFloor)->floorTable[i][0] == 0) break;

		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// �񂪎g���Ă��Ȃ��Ȃ�
			if ((nowFloor)->floorTable[i][j] == 0) break;

			(nowFloor)->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
			(nowFloor)->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
		}
	}

	// �z��S�Č���
	for (auto itr = vStageObj->begin(); itr != vStageObj->end(); itr++)
	{
		// ���̃I�u�W�F�N�g����ʂɂȂ��Ȃ玟�ɍs��
		if (!(*itr)->GetActive()) continue;

		// �O���b�h���W�����
		CGrid::GRID_XY g = (*itr)->GetGridPos();
		// ���̊K�w�̃e�[�u���ɍX�V����
		if ((*itr)->GetCategory() == CGridObject::Category::FLOOR)
		{
			(nowFloor)->floorTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
		else
		{
			(nowFloor)->objectTable[g.y][g.x] = static_cast<int>((*itr)->GetBlookType());
		}
	}
	player->SetGridTable((nowFloor));
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

	Vector3 target = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// ���X�g�̒�����v���C���[�̈ڑ�����W�Ɠ������́@���@�J�X�e����T��
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == CGridObject::BlockType::CASTELLA);
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// ���������悪���Ȃ�
	if ((nowFloor)->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CGridObject::BlockType::HOLL))
	{
		Vector3 floorPos = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::FLOOR);
		castella->Move(target, true, floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// �I�u�W�F�N�g�e�[�u������J�X�e����������
		(nowFloor)->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CGridObject::BlockType::NONE);

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

void StageScene::InCanonInput()
{
	int isSelectDir = -1;
	InputManager* input = InputManager::GetInstance();
	Vector2 PadStick = input->GetMovement();
	if (PadStick.x > 0.0f && PadStick.y > 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::RIGHT);
	}
	else if (PadStick.x < 0.0f && PadStick.y < 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::LEFT);
		//player->mTransform.pos.x -= 0.3f;
	}
	else if (PadStick.x < 0.0f && PadStick.y > 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::UP);
		//player->mTransform.pos.y -= 0.3f;
		//player->mTransform.pos.x -= 5.0f;
	}
	else if (PadStick.x > 0.0f && PadStick.y < 0.0f)
	{
		isSelectDir = static_cast<int>(Player::DIRECTION::DOWN);
	}

	CCannon* cannonObj = dynamic_cast<CCannon*>(GetStageFloor(player->GetGridPos(), CGridObject::BlockType::CANNON));
	bool* canMoveDir = cannonObj->GetCanMove();

	// ���͂�����C�̕����Ŕ��˂ł��邩����
	for (int i = 0; i < isSelectDir; i++)
	{
		canMoveDir++;
	}
	// ���ˏo���Ȃ������Ȃ�@���͂���Ă��Ȃ��Ȃ�@�I������
	if (!canMoveDir || isSelectDir == -1) return;


	//player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
	player->SetDirection(isSelectDir);
	cannonMove = true;
	// �E or ���Ȃ�@��C������
	if (isSelectDir == 2 || isSelectDir == 1)
	{
		cannonObj->SetTexture(stageTextureCannon[0]);
		dynamic_cast<CannonAnim*>(cannonObj->GetmAnim())->PlayTurn(isSelectDir);
		player->dotween->DelayedCall(0.9f, [&, isSelectDir, cannonObj]()
			{
				cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));

				player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir]()
					{
						player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
						player->GetPlayerMove()->CannonMoveStart();
						cannonMove = false;
						cannonObj->PlayReturn();
					});
			});
	}
	else
	{
		cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));

		player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir]()
			{
				player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
				player->GetPlayerMove()->CannonMoveStart();
				cannonMove = false;
				cannonObj->PlayReturn();
			});
	}




}

void StageScene::ItemDelete()
{
	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	CGridObject* deleteObj;	// ��ʂ�������\��̃|�C���^���͂���

	switch (static_cast<CGridObject::BlockType>
		((nowFloor)->objectTable[next.y][next.x]))
	{
		// �v���C���[�̈ʒu�ɂ��̃A�C�e���������
	case CGridObject::BlockType::PROTEIN:
		nNumProtein--;
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// ���X�g�̒�����v���C���[�̍��W�Ɠ������́@���@������Ȃ�����T��
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]));

		// ��ʂ������
		deleteObj->SetActive(false);
	}

	break;

	default:
		break;
	}
}

void StageScene::CannonItemDelete(CGrid::GRID_XY _deletePos, CGridObject::BlockType _type)
{
	CGrid::GRID_XY next;
	if (_deletePos.x == -1 && _deletePos.y == -1)
	{
		next = player->GetGridPos();
	}
	else
	{
		next = _deletePos;
	}


	CGridObject* deleteObj;	// ��ʂ�������\��̃|�C���^���͂���
	CGridObject::BlockType type;
	if (_type == CGridObject::BlockType::NONE)
	{
		type = static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]);
	}
	else
	{
		type = _type;
	}
	switch (type)
	{
		// �v���C���[�̈ʒu�ɂ��̃A�C�e���������
	case CGridObject::BlockType::PROTEIN:
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::COIN:
	case CGridObject::BlockType::CHILI:
	{
		// ���X�g�̒�����v���C���[�̍��W�Ɠ������́@���@������Ȃ�����T��
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, type);

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
	if (player->GetPlayerMove()->GetIsMoving()) return;

	// 0��艺�ɍs����
	nNumUndo--;
	if (nNumUndo < 0)
	{
		// �܂��g���Ă��Ȃ��̂Ȃ�
		if (floorUndo[UNDO_ARRAY_NUM - 1].objectTable[0][0][0] == 0)
		{
			MessageBoxA(NULL, "����ȏ�߂�܂���", "Undo", MB_ICONERROR | MB_OK);
			nNumUndo = 0;
			return;	// ������
		}

		nNumUndo = UNDO_ARRAY_NUM - 1;
	}

	// �X�V����e�[�u��
	GridTable* updateTable = nowFloor;
	// �X�V����I�u�W�F�N�g�̃��X�g
	std::vector<CGridObject*>* updateObjList = vStageObj;
	// �O�ɂ����K���̃O���b�h�e�[�u�����X�V����
	const short& o_floorNum = floorUndo[nNumUndo].old_Floor;

	// �K�w���ړ����Ă��Ȃ��Ȃ�
	if (nowFloorNum == o_floorNum)
	{
		// �P������Ă���
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// ��������
				updateTable->objectTable[i][j] =
					floorUndo[nNumUndo].objectTable[o_floorNum - 1][i][j];

				// ��������
				updateTable->floorTable[i][j] =
					floorUndo[nNumUndo].floorTable[o_floorNum - 1][i][j];
			}
		}
		// ���ꂽ�K�w�̃I�u�W�F�N�g�����
		CreateStage(*updateTable, *updateObjList);
	}
	// �ړ����Ă���Ȃ�
	else
	{
		for (int loop = 0; loop < MAX_LAYER; loop++)
		{
			// �S�Ă̊K�w���X�V����
			switch (loop)
			{
			case 0:
				updateTable = oneFloor;
				updateObjList = &oneFStgObj;
				break;
			case 1:
				updateTable = secondFloor;
				updateObjList = &secondFStgObj;
				break;
			case 2:
				updateTable = thirdFloor;
				updateObjList = &thirdFStgObj;
				break;

			default:	// �G���[
				MessageBoxA(NULL, "Undo�֐���old_Floor��1�`3�K�͈̔͂ł���܂���", "�G���[", MB_ICONERROR | MB_OK);
				break;
			}

			// �K�w������ȏ�Ȃ��Ȃ�I���
			if (updateTable == nullptr) break;

			// �P������Ă���
			for (int i = 0; i < stageSquare.y; i++)
			{
				for (int j = 0; j < stageSquare.x; j++)
				{
					// ��������
					updateTable->objectTable[i][j] =
						floorUndo[nNumUndo].objectTable[loop][i][j];
					// ��������
					updateTable->floorTable[i][j] =
						floorUndo[nNumUndo].floorTable[loop][i][j];
				}
			}
			// ���ꂽ�K�w�̃I�u�W�F�N�g�����
			CreateStage(*updateTable, *updateObjList);
		}


	}

	// ���X������K�w���X�V
	nowFloorNum = o_floorNum;
	// �X�V����
	switch (floorUndo[nNumUndo].old_Floor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		nowFloor = oneFloor;

		break;

	case 2:
		vStageObj = &secondFStgObj;
		nowFloor = secondFloor;
		break;

	case 3:
		vStageObj = &thirdFStgObj;
		nowFloor = thirdFloor;
		break;
	}
	player->SetNowFloor(floorUndo[nNumUndo].old_Floor);


	FIELD_FLOOR beforeStage = floorUndo[nNumUndo];
	// �v���C���[�ɕK�v�ȏ����X�V����
	UndoPlayerSet(beforeStage.dirUndo, beforeStage.calorieUndo, beforeStage.stateUndo);

}

void StageScene::UndoTableUpdate()
{
	nNumUndo++;
	if (nNumUndo >= UNDO_ARRAY_NUM)
	{
		nNumUndo = 0;
	}

	for (int loop = 0; loop < MAX_LAYER; loop++)
	{
		GridTable* setTable = nullptr;

		switch (loop)
		{
		case 0:
			setTable = oneFloor;
			break;

		case 1:
			setTable = secondFloor;
			break;

		case 2:
			setTable = thirdFloor;
			break;
		}
		// ����ȏ�K�w���Ȃ��Ȃ�I���
		if (setTable == nullptr) break;

		// ������K�w�����X�V
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				floorUndo[nNumUndo].floorTable[loop][i][j] = setTable->floorTable[i][j];
				floorUndo[nNumUndo].objectTable[loop][i][j] = setTable->objectTable[i][j];
			}
		}
	}

	floorUndo[nNumUndo].playerUndo = player->GetGridPos();
	floorUndo[nNumUndo].stateUndo = player->GetState();
	floorUndo[nNumUndo].dirUndo = player->GetDirection();
	floorUndo[nNumUndo].calorieUndo = player->GetCalorie();
	floorUndo[nNumUndo].old_Floor = nowFloorNum;
}

void StageScene::UndoPlayerSet(const int& _dir, const int& _calorie,
	const Player::STATE& _state)
{
	player->SetGridTable(nowFloor);


	GridTable* setNextTable = nullptr;
	switch (nowFloorNum)
	{
	case 1:
		break;

	case 2:
		setNextTable = oneFloor;
		break;

	case 3:
		setNextTable = secondFloor;
		break;
	}
	player->SetNextGridTable(setNextTable);

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

	// �J�����[��ݒ�
	player->SetCalorie(_calorie);



	// �A�j���[�V�����̉摜�����f������
	player->GetmAnim()->SetPattern(static_cast<int>(animPattern));

	// ��Ԃ�ω�������
	player->ChangeState(_state);

}

void StageScene::Draw()
{
	Z_Sort(*vStageObj);

	if (player->GetPlayerMove()->GetisLoolMap() == false)
	{
		for (auto it : *vStageObj)
		{
			it->Draw();
		}
	}
	else {
		MapDraw();
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
		nMaxFloor = 2;
		if (StageData.thirdFloor.floorTable[0][0] != 0)
		{
			thirdFloor = new GridTable({ StageData.numX,StageData.numY }, _stageScale);
			nMaxFloor = 3;
		}
	}
	else
	{
		secondFloor = nullptr;
		thirdFloor = nullptr;
		nMaxFloor = 1;
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
	startFloor = startfloor;

	lockStageMap = startfloor;
	//�����ŃO���b�h�e�[�u�����쐬���� /////////////////////////////////////////

	// �X�e�[�W���쐬����
	CreateStage(*oneFloor, oneFStgObj);



	// 2�K��3�K���g���Ă���Ȃ�
	if (secondFloor != nullptr)
	{
		CreateStage(*secondFloor, secondFStgObj);
		if (thirdFloor != nullptr)
		{
			CreateStage(*thirdFloor, thirdFStgObj);
		}
	}

	GridTable* setTable = oneFloor;
	for (int k = 0; k < MAX_LAYER; k++)
	{
		if (k == 1)
		{
			setTable = secondFloor;
		}
		else if (k == 2)
		{
			setTable = thirdFloor;
		}

		// �K�w����ȏ�Ȃ��Ȃ�
		if (setTable == nullptr) break;

		for (int i = 0; i < StageData.numY; i++)
		{
			for (int j = 0; j < StageData.numX; j++)
			{
				floorReset.floorTable[k][i][j] = setTable->floorTable[i][j];
				floorReset.objectTable[k][i][j] = setTable->objectTable[i][j];
			}
		}
	}

	switch (startfloor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		nowFloor = oneFloor;
		break;

	case 2:
		vStageObj = &secondFStgObj;
		nowFloor = secondFloor;
		player->SetNextGridTable(oneFloor);
		break;
	case 3:
		vStageObj = &thirdFStgObj;
		nowFloor = thirdFloor;
		player->SetNextGridTable(secondFloor);
		break;
	default:
		break;
	}

	// �v���C���[�̏��������s���i�����ōŏ��ɂǂ̕����ɐi�ނ������߂Ă���j
	player->Init(nowFloor);

	player->SetNowFloor(startfloor);

	floorReset.playerUndo = player->GetGridPos();
	floorReset.stateUndo = player->GetState();
	floorReset.dirUndo = player->GetDirection();
	floorReset.calorieUndo = player->GetCalorie();
	floorReset.old_Floor = nowFloorNum;

	// �ŏ���Undo�ɓ���Ă���
	floorUndo[0] = floorReset;

	Z_Sort(*vStageObj);
	//ChangeFloor(nowFloorNum);
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
			case CGridObject::BlockType::CANNON:
				objWork = new CCannon(playerBuffer, stageTextureCannon[1], nowFloor);
				dynamic_cast<CCannon*>(objWork)->SetArrow(stageBuffer, stageTextureArrow);
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
				else if (objWork->GetBlookType() == CGridObject::BlockType::CANNON)
				{
					dynamic_cast<CCannon*>(objWork)->CheckCanMove(_gridTable);
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
				floorWork = new CChoco(stageBuffer, stageTextureChocolateClack);
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
	//for (int i = 0; i < stageSquare.y; i++)
	//{
	//	for (int j = 0; j < stageSquare.x; j++)
	//	{
	//		if (nowFloor->objectTable[i][j] == static_cast<short>(CGridObject::BlockType::START))
	//		{
	//			nowFloor->objectTable[i][j] = static_cast<short>(CGridObject::BlockType::NONE);
	//		}
	//	}
	//}
	//vStageObj->clear();
	//vStageObj->shrink_to_fit();

	auto removeItr = std::remove(vStageObj->begin(), vStageObj->end(), player);

	vStageObj->erase(removeItr, vStageObj->end());


	// �ړ��O�̊K�w�̃e�[�u���̃v���C���[��NONE�ɂ���
	for (int i = 0; i < stageSquare.y; i++)
	{
		for (int j = 0; j < stageSquare.x; j++)
		{
			if (nowFloor->objectTable[i][j] == static_cast<int>(CGridObject::BlockType::START))
			{
				nowFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
			}
		}
	}

	player->risingMoveTrriger = false;
	player->fallMoveTrriger = false;



	switch (_nextFloor)
	{
	case 1:
		vStageObj = &oneFStgObj;
		vStageObj->push_back(player);
		nowFloor = oneFloor;
		nowFloorNum = 1;
		player->SetGridTable(oneFloor);
		break;
	case 2:
		vStageObj = &secondFStgObj;
		vStageObj->push_back(player);
		nowFloor = secondFloor;
		nowFloorNum = 2;
		player->SetGridTable(secondFloor);
		player->SetNextGridTable(oneFloor);
		break;
	case 3:
		vStageObj = &thirdFStgObj;
		vStageObj->push_back(player);
		nowFloor = thirdFloor;
		nowFloorNum = 3;
		player->SetGridTable(thirdFloor);
		player->SetNextGridTable(secondFloor);
		break;
	default:
		break;
	}
	player->SetNowFloor(nowFloorNum);

	Z_Sort(*vStageObj);
}

void StageScene::MapDraw()
{

	switch (lockStageMap)
	{
	case 1:
		Z_Sort(oneFStgObj);
		for (std::vector<CGridObject*>::iterator i = oneFStgObj.begin(); i != oneFStgObj.end(); i++)
		{
			if (FloorOnlyMap)
			{
				if ((*i)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*i)->Draw();
				}
			}
			else
			{
				(*i)->Draw();
			}
		}
		break;
	case 2:
		Z_Sort(secondFStgObj);
		for (std::vector<CGridObject*>::iterator j = secondFStgObj.begin(); j != secondFStgObj.end(); j++)
		{
			if (FloorOnlyMap)
			{
				if ((*j)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*j)->Draw();
				}
			}
			else
			{
				(*j)->Draw();
			}
		}
		break;
	case 3:
		Z_Sort(thirdFStgObj);
		for (std::vector<CGridObject*>::iterator thir = thirdFStgObj.begin(); thir < thirdFStgObj.end(); thir++)
		{
			if (FloorOnlyMap)
			{
				if ((*thir)->GetCategory() == CGridObject::Category::FLOOR)
				{
					(*thir)->Draw();
				}
			}
			else
			{
				(*thir)->Draw();
			}
		}
		break;
	default:
		break;
	}

}

CGridObject* StageScene::GetStageObject(CGrid::GRID_XY _gridPos, CGridObject::BlockType _blockType)
{
	// ���X�g�̒�����w�肵�����W�@�I�u�W�F�N�g�e�[�u���ɂ������
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
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
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == _gridPos.x &&
				_obj->GetGridPos().y == _gridPos.y &&
				(_obj->GetBlookType() == _blockType)) &&
				_obj->GetActive() == true;
		});

	return (*itr);
}

GridTable* StageScene::GetNowFloor() const
{
	return nowFloor;
}
