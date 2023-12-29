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
#include"Ckcal_gauge.h"

#define ISOME_FLOOR_SUBPOSY (3.6f)	// �A�C�\���ł̗׏���Y���W�̍��i�X�P�[��������j
#define PLAYER dynamic_cast<Player*>(player)	// �킴�킴�����̂߂�ǂ�����

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex)
	: CObject(vb, tex)
{
	oneFloor.FloorNum = 1;
	secondFloor.FloorNum = 2;
	thirdFloor.FloorNum = 3;
	/*PlayerState = 0;*/
}

StageScene::~StageScene()
{
	CLASS_DELETE(stageObj);

	SAFE_RELEASE(stageBuffer);
	SAFE_RELEASE(playerBuffer);

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
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		CLASS_DELETE((*it));
	}
}

void StageScene::Update()
{
	player->mTransform.pos;



	PLAYER->Update();
	PlayerMove();


	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		(*it)->Update();
	}
}

void StageScene::PlayerMove()
{
	Player::STATE PlayerState = PLAYER->GetPlayerState();
	switch (PlayerState)
	{
	case Player::STATE::NORMAL:
		PlayerNomalMove();
		break;
	case Player::STATE::THIN:
		PlayerSkinnyMove();
		break;
	case Player::STATE::FAT:
		PlayerFatMove();
		break;
	case Player::STATE::MUSCLE:
		PlayerMachoMove();
		break;
	case Player::STATE::NUM:
		break;
	default:
		break;
	}
	SettingPlayerDir();
}
//�m�[�}����Ԃ̈ړ�
//�P�[�L�̏ꏊ�Ńv���C���[�̏�ԕω�
//�v���e�C���̏ꏊ�Ńv���C���[�̏�ԕω�
// �ړ��悪���@�ǁ@�J�X�e���@�o�E���N�[�w���̎��͈ړ��ł��Ȃ�
// 
void StageScene::PlayerNomalMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1];
			switch (bkType)
			{
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x -= 1;

					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
						for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
						{
							if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
							{
								(*it)->SetTexture(NULL);
								PLAYER->CakeEat();
								oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
						PLAYER->SetTexture(playerTexture);
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1];
			switch (bkType)
			{
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x  > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
						for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
						{
							if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
							{
								(*it)->SetTexture(NULL);
								PLAYER->CakeEat();
								oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
							}
						}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x  > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x  > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
					
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					PLAYER->SetTexture(playerTexture_NF);
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
	}
}
//��������Ԃ̈ړ�
//�P�[�L�̏ꏊ�Ńv���C���[�̏�ԕω�
//�ړ��悪���@�ǁ@�o�E���N�[�w���̎��͈ړ��ł��Ȃ�
//�ړ���ɃJ�X�e��������΂��̐悪�������m�F����
//���ł���Η��Ƃ��ď��ɂ��ړ�����
//���ł���Ώ��̏�ɃJ�X�e�����ړ������ăv���C���[���J�X�e�����������ꏊ�܂ňړ�
//�J�X�e�����������Ȃ��̂ł���Ή������Ȃ�
//
void StageScene::PlayerFatMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1];
			switch (bkType)
			{
			case CStageMake::CASTELLA:
				playerGridPos.x += 1;
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
					{
						if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] == (int)CStageMake::BlockType::HOLL)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.x += 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::FLOOR));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							playerGridPos.x -= 1;
						}
						else if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != (int)CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != (int)CStageMake::BlockType::WALL
							&& oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] != 0)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.x += 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::CASTELLA;
							playerGridPos.x -= 1;
						}
						else
						{
							playerGridPos.x -= 2;

						}
					}
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();

			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1];
			switch (bkType)
			{
			case CStageMake::CASTELLA:
				playerGridPos.x -= 1;
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
					{
						if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] == (int)CStageMake::BlockType::HOLL)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.x -= 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::FLOOR));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							playerGridPos.x += 1;
						}
						else if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != (int)CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != (int)CStageMake::BlockType::WALL
							&& oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] != 0 )
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.x -= 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::CASTELLA;
							playerGridPos.x += 1;
						}
						else
						{
							playerGridPos.x += 2;

						}
					}
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::CASTELLA:
				playerGridPos.y += 1;
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
					{
						if (oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] == (int)CStageMake::BlockType::HOLL)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.y -= 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::FLOOR));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							playerGridPos.y += 1;
						}
						else if (oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != (int)CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != (int)CStageMake::BlockType::WALL
							&& oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] != 0)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.y -= 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::CASTELLA;
							playerGridPos.y += 1;
						}
						else
						{
							playerGridPos.y += 2;

						}
					}
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();

			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::CASTELLA:
				playerGridPos.y += 1;
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CASTELLA)
					{
						if (oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] == (int)CStageMake::BlockType::HOLL)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.y += 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::FLOOR));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							playerGridPos.y -= 1;
						}
						else if (oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != (int)CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != (int)CStageMake::BlockType::WALL
							&& oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] != 0)
						{
							CGrid::GRID_XY xy = playerGridPos;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::FLOOR;
							xy.y += 1;
							Vector3 v = (GridToPos(xy, CStageMake::BlockType::CASTELLA));
							(*it)->mTransform.pos = v;
							oneFloor.gridTable[xy.y][xy.x] = (int)CStageMake::BlockType::CASTELLA;
							playerGridPos.y -= 1;
						}
						else
						{
							playerGridPos.y -= 2;

						}
					}
				}
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
				break;
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
	}

}

//��������Ԃ̈ړ�
//�P�[�L�̏ꏊ�Ńv���C���[�̏�ԕω�
//�v���e�C���̏ꏊ�Ńv���C���[�̏�ԕω�
//�ړ��悪�ǁ@�J�X�e���̎��͈ړ��ł��Ȃ�
//�ړ���Ƀo�E���N�[�w��������΂��̐���m�F����
//���̐悪���Ȃǂ̈ړ��o���郂�m�ł���΂��̏ꏊ�܂ňړ�
//�悪�����Ȃ��Ȃǈړ��o���Ȃ����m�ł���Έړ����Ȃ�
//
void StageScene::PlayerSkinnyMove()
{
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1];
			switch (bkType)
			{
			case CStageMake::BAUM:
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 2] != CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 2] != CStageMake::BlockType::WALL
					&& oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 2] != 0)
				{
					playerGridPos.x += 1;
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1];
			switch (bkType)
			{
			case CStageMake::BAUM:
				if (oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 2] != CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 2] != CStageMake::BlockType::WALL)
				{
					if (playerGridPos.x - 2 < 0)
					{
						playerGridPos.x += 1;
					}
					else
					{
						playerGridPos.x -= 1;
					}
					if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x > 0)
					{
						playerGridPos.x -= 1;
						Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
						PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
						PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					}
					break;
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::BAUM:
				if (oneFloor.gridTable[playerGridPos.y - 2][playerGridPos.x] != CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y - 2][playerGridPos.x] != CStageMake::BlockType::WALL
					&& oneFloor.gridTable[playerGridPos.y - 2][playerGridPos.x] != 0)
				{
					playerGridPos.y -= 1;
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}

		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::BAUM:
				if (oneFloor.gridTable[playerGridPos.y + 2][playerGridPos.x] != CStageMake::BlockType::HOLL && oneFloor.gridTable[playerGridPos.y + 2][playerGridPos.x] != CStageMake::BlockType::WALL
					&& oneFloor.gridTable[playerGridPos.y + 2][playerGridPos.x] != 0)
				{
					playerGridPos.y += 1;
				}
			case CStageMake::CAKE:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::CAKE)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
					for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
					{
						if ((*it)->GetBlookType() == (int)CStageMake::BlockType::PROTEIN)
						{
							(*it)->SetTexture(NULL);
							PLAYER->CakeEat();
							PLAYER->DrinkProtein();
							PLAYER->mTransform.scale.y *= 1.5f;
							oneFloor.gridTable[playerGridPos.y][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
						}
					}
				}
				break;
			case CStageMake::START:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					PLAYER->SetTexture(playerTexture_SF);
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
	}

}

//�}�b�`����Ԃ̈ړ�
// �ړ��悪���@�J�X�e���@�o�E���N�[�w���̎��͈ړ��ł��Ȃ�
//�ړ���ɕǂ�����Ή�
//
void StageScene::PlayerMachoMove()
{

	//�}�b�`�����ǂ̃e�N�X�`���Ȃ����Ȃ�쉺����
	if (PLAYER->GetPlayerMove()->GetIsMoving() == false)
	{
		if (gInput->GetKeyTrigger(VK_RIGHT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1];
			switch (bkType)
			{
			case CStageMake::WALL:
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::WALL)
					{
						(*it)->SetTexture(NULL);
						oneFloor.gridTable[playerGridPos.y][playerGridPos.x + 1] = (int)CStageMake::BlockType::FLOOR;
					}
				}
			case CStageMake::CAKE:
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
			case CStageMake::START:
			case CStageMake::GALL:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::LEFT)
				{
					playerGridPos.x += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_LEFT))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1];
			switch (bkType)
			{
			case CStageMake::WALL:
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::WALL)
					{
						(*it)->SetTexture(NULL);
						oneFloor.gridTable[playerGridPos.y][playerGridPos.x - 1] = (int)CStageMake::BlockType::FLOOR;
					}
				}
			case CStageMake::CAKE:
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
			case CStageMake::START:
			case CStageMake::GALL:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::RIGHT && playerGridPos.x  > 0)
				{
					playerGridPos.x -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_UP))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::WALL:
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::WALL)
					{
						(*it)->SetTexture(NULL);
						oneFloor.gridTable[playerGridPos.y - 1][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
					}
				}
			case CStageMake::CAKE:
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
			case CStageMake::START:
			case CStageMake::GALL:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::DOWN)
				{
					playerGridPos.y -= 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
		else if (gInput->GetKeyTrigger(VK_DOWN))
		{
			CGrid::GRID_XY playerGridPos = PLAYER->GetGridPos();
			CStageMake::BlockType bkType = (CStageMake::BlockType)oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x];
			switch (bkType)
			{
			case CStageMake::WALL:
				for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
				{
					if ((*it)->GetBlookType() == (int)CStageMake::BlockType::WALL)
					{
						(*it)->SetTexture(NULL);
						oneFloor.gridTable[playerGridPos.y + 1][playerGridPos.x] = (int)CStageMake::BlockType::FLOOR;
					}
				}
			case CStageMake::CAKE:
			case CStageMake::COIN:
			case CStageMake::PROTEIN:
			case CStageMake::START:
			case CStageMake::GALL:
			case CStageMake::FLOOR:
				if (PLAYER->GetPlayerMove()->GetDirection() != PlayerMove::DIRECTION::UP)
				{
					PLAYER->SetTexture(playerTexture_MF);
					playerGridPos.y += 1;
					Vector3 v = (GridToPos(playerGridPos, CStageMake::BlockType::START));
					PLAYER->GetPlayerMove()->Move(PLAYER->mTransform.pos, v);
					PLAYER->SetGridPos(playerGridPos.x, playerGridPos.y);
				}
				break;
			default:
				break;
			}
		}
	}

}

void StageScene::Reset(const wchar_t* filePath, float _stageScale)
{
	oneFloor = oneFloorCopy;
	//std::vector<CGridObject*>::iterator cit = vStageObjCopy.begin();
	//for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); )
	//{ 
	//	�O���b�h���W�Œl��������Ώۂ��𔻒f����
	//	CGrid::GRID_XY itXY = (*it)->GetGridPos();
	//	CGrid::GRID_XY citXY = (*cit)->GetGridPos();

	//	if (itXY.x == citXY.x && itXY.y == citXY.y)
	//	{
	//		(*it)->mTransform = (*cit)->mTransform;
	//		it++;
	//		cit = vStageObjCopy.begin();
	//	}
	//	if(cit != vStageObjCopy.end())
	//	cit++;
	//}

	vStageObj.clear();
	Init(filePath, _stageScale);
}

void StageScene::SettingPlayerDir()
{
	Player::STATE PlayerState = PLAYER->GetPlayerState();
	switch (PlayerState)
	{
	case Player::STATE::NORMAL:
		PLAYER->SetTexture(playerTexture_NF);
		break;
	case Player::STATE::THIN:
		PLAYER->SetTexture(playerTexture_SF);
		break;
	case Player::STATE::FAT:
		PLAYER->SetTexture(playerTexture_FF);
		break;
	case Player::STATE::MUSCLE:
		PLAYER->SetTexture(playerTexture_MF);
		break;
	case Player::STATE::NUM:
		break;
	default:
		break;
	}
	Z_Sort(vStageObj);

}

void StageScene::Draw()
{
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
	/*D3D_CreateSquare({ 3,4 }, &playerBuffer);*/

	D3D_LoadTexture(L"asset/mizuno/floor_y (1).png", &stageTextureFloor);
	D3D_LoadTexture(L"asset/mizuno/floor_g.png", &stageTextureFloor2);
	D3D_LoadTexture(L"asset/hashimoto/Baumkuchen.png", &stageTextureBaumkuchen);
	D3D_LoadTexture(L"asset/hashimoto/Cake.png", &stageTextureCake);
	D3D_LoadTexture(L"asset/hashimoto/Castella.png", &stageTextureCastella);
	D3D_LoadTexture(L"asset/hashimoto/Chili.png", &stageTextureChili);
	D3D_LoadTexture(L"asset/hashimoto/Chocolate.png", &stageTextureChocolate);
	D3D_LoadTexture(L"asset/hashimoto/Coin.png", &stageTextureCoin);
	D3D_LoadTexture(L"asset/hashimoto/GallChest.png", &stageTextureGallChest);
	D3D_LoadTexture(L"asset/hashimoto/Gumi.png", &stageTextureGumi);
	D3D_LoadTexture(L"asset/hashimoto/Protein.png", &stageTextureProtein);
	D3D_LoadTexture(L"asset/hashimoto/Wall.png", &stageTextureWall);
	D3D_LoadTexture(L"asset/hashimoto/Wataame.png", &stageTextureWataame);
	D3D_LoadTexture(L"asset/hashimoto/N_Walk01_Back.png", &playerTexture);
	D3D_LoadTexture(L"asset/mizuno/N_Walk01_Forword.png", &playerTexture_NF);
	D3D_LoadTexture(L"asset/mizuno/M_Walk01_Forword.png", &playerTexture_MF);
	D3D_LoadTexture(L"asset/mizuno/S_Walk01_Forword.png", &playerTexture_SF);
	D3D_LoadTexture(L"asset/mizuno/F_Walk01_Forword.png", &playerTexture_FF);

	stage = new CLoadStage;
	stageMake = new CStageMake;

	StageData = stage->LoadStage(filePath);

	//	���[���h���W
	stagePos = stageMake->StagePos(StageData);

	// �����ŃO���b�h�e�[�u�����쐬����@/////////////
	oneFloor.isUse = true;

	// �X�e�[�W�̑傫��
	stageScale = { _stageScale,_stageScale,1.0f };

	// [0,0]�̏��̍��W
	Offset_X = -stageScale.x * (StageData.numX - 1) / 2.0f;
	// ���v����
	Offset_Y = -stageScale.y / 2.0f;	// ���Ȃ̂ŏ������ɉ�����

   // �s
	for (int i = 0; i < StageData.numY; i++)
	{
		// ��
		for (int j = 0; j < StageData.numX; j++)
		{
			// �O���b�h�e�[�u���Ɉ���f�[�^�����Ă���
			oneFloor.gridTable[i][j] = StageData.data[i * StageData.numX + j];

			// �ŏ��ɏ��̍��W�����߂�
			Vector3 floorPos = Vector3::zero;
			floorPos.x = Offset_X + (i + j) * (stageScale.x / 2.0f);
			floorPos.y = Offset_Y + (j - i) * stageScale.y / ISOME_FLOOR_SUBPOSY;
			floorPos.z = floorPos.y * 0.01f;

			// ������A�C�e���܂ł̋����i���̃X�P�[���Ɋ|���邱�ƂŒ�������j
			float disTimes = 0;

			stageObj = nullptr;

			//���̉摜�Z�b�g�̏���
			switch (oneFloor.gridTable[i][j])
			{
			case CStageMake::BlockType::FLOOR:
				//stageObj = new CFloor(stageBuffer, stageTextureFloor);
				//if ((i + j) % 2 == 0)
				//{
				//	stageObj->SetTexture(stageTextureFloor2);
				//}
				//stageObj->mTransform.pos = floorPos;
				//stageObj->CheckFloor();
				break;

			case CStageMake::BlockType::WALL:
				stageObj = new CWall(stageBuffer, stageTextureWall);
				stageObj->SetBlookType((int)CStageMake::BlockType::WALL);
				disTimes = 0.455f;
				stageObj->SetGridPos(j, i);
				break;

			case CStageMake::BlockType::HOLL:
				stageObj = new CHoll(stageBuffer, NULL);
				stageObj->SetBlookType((int)CStageMake::BlockType::HOLL);
				break;

			case CStageMake::BlockType::CAKE:
				stageObj = new CCake(stageBuffer, stageTextureCake);
				stageObj->SetBlookType((int)CStageMake::BlockType::CAKE);
				disTimes = 0.7f;
				break;

			case CStageMake::BlockType::CASTELLA:
				stageObj = new CCastella(stageBuffer, stageTextureCastella);
				stageObj->SetBlookType((int)CStageMake::BlockType::CASTELLA);
				stageObj->SetGridPos(j, i);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::BAUM:
				stageObj = new CBaum(stageBuffer, stageTextureBaumkuchen);
				stageObj->SetBlookType((int)CStageMake::BlockType::BAUM);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::COIN:
				stageObj = new CCoin(stageBuffer, stageTextureCoin);
				stageObj->SetBlookType((int)CStageMake::BlockType::COIN);
				disTimes = 0.455f;
				break;
			case CStageMake::BlockType::WATAAME:
				stageObj = new CWataame(stageBuffer, stageTextureWataame);
				stageObj->SetBlookType((int)CStageMake::BlockType::WATAAME);
				break;

			case CStageMake::BlockType::CHOCO:
				stageObj = new CChoco(stageBuffer, stageTextureChocolate);
				stageObj->SetBlookType((int)CStageMake::BlockType::CHOCO);
				break;

			case CStageMake::BlockType::GUMI:
				stageObj = new CGumi(stageBuffer, stageTextureGumi);
				stageObj->SetBlookType((int)CStageMake::BlockType::GUMI);
				disTimes = 0.455f;
				break;

			case CStageMake::BlockType::PROTEIN:
				stageObj = new CProtein(stageBuffer, stageTextureProtein);
				stageObj->SetBlookType((int)CStageMake::BlockType::PROTEIN);
				disTimes = 0.7f;
				break;

			case CStageMake::BlockType::START:
				player = new Player(stageBuffer, playerTexture);
				player->mTransform.pos = floorPos;
				player->mTransform.pos.y += stageScale.y * 0.5f;
				player->mTransform.pos.z -= 0.55f;
				player->mTransform.scale = stageScale;
				player->SetGridPos(j, i);
				vStageObj.push_back(player);
				break;

			case CStageMake::BlockType::GALL:
				stageObj = new CGall(stageBuffer, stageTextureGallChest);
				stageObj->SetBlookType((int)CStageMake::BlockType::GALL);
				stageObj->SetGridPos(j, i);
				disTimes = 0.55f;
				break;

			default:
				break;
			}

			// �����܂łɃI�u�W�F�N�g���쐬���Ă���Ȃ�i���ȊO�j
			if (stageObj != nullptr)
			{
				// �X�e�[�W�S�̂̑傫����ݒ�
				stageObj->mTransform.scale = stageScale;
				// ���W��ݒ�
				stageObj->mTransform.pos = floorPos;
				stageObj->mTransform.pos.y += stageScale.y * disTimes;
				stageObj->mTransform.pos.z -= 0.55f;
				// �I�u�W�F�N�g�����X�g�ɓ����
				vStageObj.push_back(stageObj);
			}

			// ��������Ȃ��I�u�W�F�N�g�͎��̃��[�v�ɐi�߂�
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::CHOCO) continue;
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::WATAAME) continue;
			if (oneFloor.gridTable[i][j] == CStageMake::BlockType::HOLL) continue;

			// �����쐬
			CGridObject* floorObj = new CFloor(stageBuffer, stageTextureFloor);
			if ((i + j) % 2 == 0)
			{
				floorObj->SetTexture(stageTextureFloor2);
			}
			// �p�����[�^�ݒ�
			floorObj->SetBlookType((int)CStageMake::BlockType::FLOOR);
			floorObj->mTransform.pos = floorPos;
			floorObj->mTransform.scale = stageScale;
			floorObj->SetGridPos(j, i);
			vStageObj.push_back(floorObj);
		}
	}
	oneFloorCopy = oneFloor;
	Z_Sort(vStageObj);
	vStageObjCopy = vStageObj;

}

Vector3 StageScene::GetGridToPos(CGrid::GRID_XY _gridXY)
{
	for (std::vector<CGridObject*>::iterator it = vStageObj.begin(); it < vStageObj.end(); it++)
	{
		if ((*it)->GetGridPos().x == _gridXY.x && (*it)->GetGridPos().y == _gridXY.y && (*it)->GetBlookType() == 2)
		{
			return (*it)->mTransform.pos;
		}
	}
	return Vector3();
}

Vector3 StageScene::GridToPos(CGrid::GRID_XY _gridXY, CStageMake::BlockType _type)
{
	float disTimes = 0.0f;
	switch (_type)
	{
	case CStageMake::FLOOR:
	{

		Vector3 floorPos = Vector3::zero;
		floorPos.x = Offset_X + (_gridXY.y + _gridXY.x) * (stageScale.x / 2.0f);
		floorPos.y = Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY;
		floorPos.z = floorPos.y * 0.01f ;
		return floorPos;
	}
	break;
	case CStageMake::WALL:
	case CStageMake::CASTELLA:
	case CStageMake::BAUM:
	case CStageMake::COIN:
	case CStageMake::GUMI:
		disTimes = 0.455f;

		break;

	case CStageMake::CAKE:
	case CStageMake::PROTEIN:
		disTimes = 0.7f;
		break;

	case CStageMake::START:
		Player::STATE PlayerState = PLAYER->GetPlayerState();
		if (PlayerState == Player::STATE::MUSCLE)
		{
			disTimes = 0.5f * 1.5f;
		}
		else
		{
			disTimes = 0.5f;
		}

		break;
	}

	Vector3 v;
	v.x = Offset_X + (_gridXY.y + _gridXY.x) * (stageScale.x / 2.0f);
	v.y = Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY
		+ stageScale.y * disTimes;
	v.z = (Offset_Y + (_gridXY.x - _gridXY.y) * stageScale.y / ISOME_FLOOR_SUBPOSY) * 0.01f - 0.55f;

	return v;
}