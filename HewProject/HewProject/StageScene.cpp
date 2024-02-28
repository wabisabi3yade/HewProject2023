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
#include"CArrow.h"
#include"CCamera.h"
#include"DoTween.h"
#include"CGameClear.h"
#include"CGameOver.h"
#include"CGameStart.h"
#include "Tutorial.h"
#include"xa2.h"

#define PLAYER dynamic_cast<Player*>(player)	// わざわざ書くのめんどくさい

StageScene::StageScene(D3DBUFFER vb, D3DTEXTURE tex, short int worldNum, bool _isW11)
	: CObject(vb, tex)
{
	nNumProtein = 0;

	startFloor = 0;

	changeflag = false;

	FloorOnlyMap = false;

	isW11 = _isW11;

	dotween = std::make_unique<DoTween>(CCamera::GetInstance());

	//gameClear = new CGameClear();
	gameOver = new CGameOver();


	isGameClear = false;

	isStartStop = true;

	isLookMap = nullptr;
	isMenu = nullptr;

	// テクスチャを管理するクラスのインスタンスを取得
	TextureFactory* texFactory = TextureFactory::GetInstance();

	// 各オブジェクトのテクスチャを取得する
	switch (worldNum)
	{
	case 1:
		stageTextureFloor = texFactory->Fetch(L"asset/Stage/one_fp.png");
		stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/one_fg.png");
		selectName = CScene::SCENE_NAME::WORLD1_SELECT;
		break;

	case 2:
		stageTextureFloor = texFactory->Fetch(L"asset/Stage/floor_y.png");
		stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/floor_g.png");
		selectName = CScene::SCENE_NAME::WORLD2_SELECT;
		break;

	case 3:
		stageTextureFloor = texFactory->Fetch(L"asset/Stage/floor_y.png");
		stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/third_fr.png");
		selectName = CScene::SCENE_NAME::WORLD3_SELECT;
		break;

	case 4:
		stageTextureFloor = texFactory->Fetch(L"asset/Stage/Ex_fp.png");
		stageTextureFloor2 = texFactory->Fetch(L"asset/Stage/Ex_fy.png");
		selectName = CScene::SCENE_NAME::WORLD4_SELECT;
		break;
	}

	stageTextureWall = texFactory->Fetch(L"asset/Stage/Wall.png");
	stageTextureHoll = texFactory->Fetch(L"asset/Stage/test_Hool.png");
	stageTextureWataame = texFactory->Fetch(L"asset/Stage/Wataame.png");

	stageTextureCastella = texFactory->Fetch(L"asset/Stage/Castella.png");

	stageTextureBaumkuchen_R = texFactory->Fetch(L"asset/Stage/Baumkuchen_R.png");
	stageTextureBaumkuchen_L = texFactory->Fetch(L"asset/Stage/Baumkuchen_L.png");
	stageTextureChocolate = texFactory->Fetch(L"asset/Stage/Chocolate.png");
	stageTextureChocolateClack = texFactory->Fetch(L"asset/Stage/ChocoClack.png");
	stageTextureCake = texFactory->Fetch(L"asset/Item/Cake.png");
	stageTextureChili = texFactory->Fetch(L"asset/Item/Chili.png");
	stageTextureCoin = texFactory->Fetch(L"asset/Item/Coin.png");
	stageTextureGallChest[0] = texFactory->Fetch(L"asset/Stage/GallChest.png");
	stageTextureGallChest[1] = texFactory->Fetch(L"asset/Stage/GallChestLight.png");
	stageTextureGallChest[2] = texFactory->Fetch(L"asset/Stage/GallChestAura.png");
	stageTextureGumi = texFactory->Fetch(L"asset/Stage/Gumi.png");
	stageTextureProtein = texFactory->Fetch(L"asset/Item/Protein.png");
	shadowTexture = texFactory->Fetch(L"asset/Item/shadow.png");
	stageTextureArrow = texFactory->Fetch(L"asset/UI/Arrow.png");
	stageTextureCannon[0] = texFactory->Fetch(L"asset/Stage/Canon_RightLeft.png");
	stageTextureCannon[1] = texFactory->Fetch(L"asset/Stage/Canon_UpDown.png");

	stageTextureBaumAnim[0] = texFactory->Fetch(L"asset/Player/Baum_Down.png");
	stageTextureBaumAnim[1] = texFactory->Fetch(L"asset/Player/Baum_Left.png");
	stageTextureBaumAnim[2] = texFactory->Fetch(L"asset/Player/Baum_Right.png");
	stageTextureBaumAnim[3] = texFactory->Fetch(L"asset/Player/Baum_Up.png");

	ButtonTextureCamera = texFactory->Fetch(L"asset/UI/B_Camera.png");
	ButtonTextureFloorLook = texFactory->Fetch(L"asset/UI/B_FloorLook.png");
	ButtonTextureUndo = texFactory->Fetch(L"asset/UI/B_Undo1.png");
	TextTextureLooking = texFactory->Fetch(L"asset/Text/T_Looking 1.png");
	Button_LB_RB_Texture = texFactory->Fetch(L"asset/UI/B_LB_RB.png");
	ButtonTextureCameraBack = texFactory->Fetch(L"asset/UI/B_CameraBack.png");

	if (isW11)
	{
		GetProteinTexture = texFactory->Fetch(L"asset/UI/T_GetProtein.png");
		GoChestTexture = texFactory->Fetch(L"asset/UI/T_GoChest.png");
	}
}

// テクスチャは解放しない
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

	//メニュー
	CLASS_DELETE(Menu);

	//UI

	//プロテイン
	CLASS_DELETE(proteinUi);

	CLASS_DELETE(floorUi);
	CLASS_DELETE(calorieGage);

	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		CLASS_DELETE(Arrow[i]);
	}
	CLASS_DELETE(gameClear);
	CLASS_DELETE(gameOver);
	CLASS_DELETE(gameStart);
	CLASS_DELETE(CameraButton);
	CLASS_DELETE(FloorLookButton);
	CLASS_DELETE(UndoButton);
	CLASS_DELETE(LookingTxet);
	CLASS_DELETE(RB_Button);
	CLASS_DELETE(LB_Button);
	CLASS_DELETE(BackCameraButton);
	if (GetProtein != nullptr)
	{
		CLASS_DELETE(GetProtein);
	}
	//CLASS_DELETE();

}

void StageScene::Update()
{
	if (isStartStop == true)
	{
		gameStart->Update();
		if (*isMenu == false)
			*isMenu = true;

		if (gameStart->isMoveing == true)
		{

			if (!isDoTutorial)
			{
				isStartStop = false;
				//*isLookMap = false;

				*isMenu = false;
			}
			else
			{
				isTutorialNow = true;
				// みえるようになる
				tutorial->Display();
				isStartStop = false;
				tutorial->Update();

			}
		}
	}
	else if (isTutorialNow)
	{
		//*isLookMap = true;
		tutorial->Update();
		if (tutorial->GetState() == Tutorial::STATE::END)
		{
			isTutorialNow = false;
			*isLookMap = false;
			*isMenu = false;
		}
	}
	else {
		//メニュー画面
		if (player->GetIsMoving() == false && !isStartStop)
		{
			//static bool o_isMenu = false;
			Menu->Update();

			//if (Menu->GetisMenu() == false && o_isMenu == true)
			//{
			//	return;

			//}

			//o_isMenu = Menu->GetisMenu();
		}
	}

	if (Menu->GetisMenu() == true)
	{
		//player->GetPlayerMove()->SetIsMenu(true);
		player->GetmAnim()->animSpeed = 0;
	}
	else
	{
		if (!isStartStop && !isGameClear && !player->GetIsGameOver() && (*isLookMap) == false)
		{
			if (InputManager::GetInstance()->GetInputTrigger(InputType::Undo))
			{
				Undo(stageScale);
			}

		}

		//player->GetPlayerMove()->SetIsMenu(false);
		if (!isTutorialNow)
		{
			for (auto i : *vStageObj)
			{
				i->Update();
			}
		}
		player->GetmAnim()->animSpeed = 0.1f;


		StageMove();

		if (GetProtein != nullptr)
			GetProtein->Update();

		if (player->GetIsPlayMakeoverTrigger())
		{
			CCamera::GetInstance()->Zoom(0.25f, stageScale, { player->mTransform.pos.x, player->mTransform.pos.y, 0 });
			dotween->DelayedCall(MAKEOVER_TIME, [&]()
				{
					CCamera::GetInstance()->mTransform.pos = Vector3::zero;
					CCamera::GetInstance()->Shake(0.7f, 0.3f);
					dotween->DoEaseOutBackScale(Vector3::one, 1.0f);
					isLookMap = player->GetPlayerMove()->GetIsLookCamera();
					if (isDoTutorial)
					{
						if (tutorial->GetIs1_1())
						{
							if (!tutorial->GetIsMachoOnce())
							{
								dotween->OnComplete([&]
									{
										tutorial->MachoDisplay();
										isTutorialNow = true;
										GetProtein->SetTexture(GoChestTexture);
									});
							}

						}
					}

				});
		}

		for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
		{
			Arrow[i]->Update();
			Arrow[i]->mTransform.pos.z = -0.35f;
		}

		/// 
		/// 階層変更している
		/// 
		if (!isStartStop && !isGameClear && !player->GetIsGameOver() && !player->GetIsMoving() && !isTutorialNow)
		{
			InputManager* input = InputManager::GetInstance();


			if (*isLookMap == true)
			{
				bool changefloor = false;

				if (input->GetInputTrigger(InputType::L_BUTTON))
				{
					if (lockStageMap != 1)
					{
						lockStageMap--;
						XA_Play(SOUND_LABEL::S_FLOOR_CHANGE);
						changefloor = true;
					}
					floorUi->SetHighlight(lockStageMap);
				}
				else if (input->GetInputTrigger(InputType::R_BUTTON))
				{

					if (lockStageMap != nMaxFloor)
					{
						lockStageMap++;
						XA_Play(SOUND_LABEL::S_FLOOR_CHANGE);
						changefloor = true;
					}
					floorUi->SetHighlight(lockStageMap);
				}
				else if (input->GetInputTrigger(InputType::CAMERA))
				{
					lockStageMap = nowFloorNum;
					floorUi->SetHighlight(lockStageMap);
					//player->GetPlayerMove()->CameraEnd();
					LookingTxet->dotween->Stop();
					Vector3 pos(-13.0f, 2.5f, 0.0);
					LookingTxet->dotween->DoEaseOutBack(pos, 0.5f);
					*isLookMap = false;
					LookingTxet->dotween->OnComplete([&]()
						{
							LookingTxet->SetActive(false);
						});
				}
				else if (input->GetInputPress(InputType::DECIDE))
				{
					FloorOnlyMap = true;
				}
				else
				{
					FloorOnlyMap = false;
				}

				if (changefloor)
					switch (lockStageMap)
					{
					case 1:
						RB_Button->mTransform.pos.y = -1.0f;
						break;
					case 2:
						RB_Button->mTransform.pos.y = 0.0f;
						LB_Button->mTransform.pos.y = -1.0f * 2.0f;
						break;
					case 3:
						LB_Button->mTransform.pos.y = -1.0f;
						break;
					default:
						break;
					}
			}
			else if (*isLookMap == false)
			{
				if (input->GetInputTrigger(InputType::CAMERA))
				{
					*isLookMap = true;
					Vector3 pos(-4.5f, 2.5f, 0.0);
					LookingTxet->dotween->Stop();
					LookingTxet->dotween->DoEaseOutBack(pos, 0.5f);
					LookingTxet->SetActive(true);

					XA_Play(SOUND_LABEL::S_TEXT);
				}
			}
		}
		if (player->GetPlayerMove()->GetIncannon() && !cannonMove)
		{
			InCanonInput();
		}

		LookingTxet->Update();

		if (player->GetPlayerMove()->GetIsFallBound())
		{
			if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
				player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
			{
				CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextFloorType())));
				switch (player->GetState())
				{
				case Player::STATE::MUSCLE:
				case Player::STATE::FAT:
				{
					chocoObj->CRACK();
					CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
					hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
					hollObj->SetBlookType(CGridObject::BlockType::HOLL);
					hollObj->mTransform.scale.x = stageScale;
					hollObj->mTransform.scale.y = stageScale;
					hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
					vStageObj->push_back(hollObj);
				}
				case Player::STATE::NORMAL:
				{
					if (chocoObj->GetBlookType() == CGridObject::BlockType::CHOCOCRACK)
					{
						chocoObj->CRACK();
						CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
						hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
						hollObj->SetBlookType(CGridObject::BlockType::HOLL);
						hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
						vStageObj->push_back(hollObj);
					}
					else
					{
						chocoObj->CRACK(player->GetGridTable()->GridToWorld(player->GetPlayerMove()->GetNextGridPos(),CGridObject::BlockType::START));
						chocoObj->SetTexture(stageTextureChocolateClack);
					}

					break;
				}
				default:
					break;
				}

			}
			Vector3 pos = player->mTransform.pos;
			Vector3 scale = player->mTransform.scale;
			pos.z -= 0.0001f;
			pos.y -= 0.1f;
			scale.x *= STAR_BOUND_SCALE;
			scale.y *= STAR_BOUND_SCALE;

			player->PlayEffect(pos, scale, EffectManeger::FX_TYPE::STAR_BOUND, false);
		}
		// 動いているときと動き終わった瞬間だけ
		if (player->GetPlayerMove()->GetIsMoving() || player->GetPlayerMove()->GetIsMoveTrigger())
		{
			// グリッドテーブルを更新する
			if (player->GetPlayerMove()->GetMoveWataame())
			{
				//player->GetPlayerMove()->SetMoveWataame(false);
				player->dotween->DelayedCall(0.8f, [&]()
					{
						TableUpdate();
					});
			}
			else
			{
				TableUpdate();
			}
		}



		if (player->GetPlayerMove()->GetIsMoveTrigger())
		{
			if (player->GetPlayerMove()->GetMoveWataame())
			{
				player->GetPlayerMove()->SetMoveWataame(false);
				player->dotween->DelayedCall(0.8f, [&]()
					{
						UndoTableUpdate();
					});
			}
			else
			{
				UndoTableUpdate();
			}
		}

		dotween->Update();

		//UI
		if (coinUI != nullptr)
			coinUI->Update();

		//プロテイン
		proteinUi->Update();

		//カロリーゲージ
		calorieGage->Update();

		floorUi->Update();

		for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
		{
			Arrow[i]->Update();
		}
		if (isGameClear)
		{
			gameClear->Update();
		}
		if (player->GetIsGameOver())
		{
			gameOver->Update();
		}

	}

}

void StageScene::StageMove()
{
	// ↓プレイヤーの動きにあわせてステージ内の物を動かす
	if (player->GetPlayerMove()->GetIsMoveStart())
	{
		// プレイヤーが太ってる　かつ　移動した先がカステラなら
		if (player->GetState() == Player::STATE::FAT &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CASTELLA)
		{
			// カステラに移動しろと命令する
			CastellaMoveOrder();
		}
		// プレイヤーがマッチョ　かつ　移動先が壁なら
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::WALL)
		{
			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::WALL));
			wallObj->Break(player->GetDirection());

		}
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CAKE)
		{
			CCake* cakeObj = dynamic_cast<CCake*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			cakeObj->dotween->DelayedCall(BREAK_TIME - 0.6f, [&, cakeObj]()
				{
					cakeObj->BlowOff(player->GetDirection());
				});
		}

		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::CHILI)
		{
			CChili* chiliObj = dynamic_cast<CChili*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			chiliObj->dotween->DelayedCall(BREAK_TIME - 0.6f, [&, chiliObj]()
				{
					chiliObj->BlowOff(player->GetDirection());
				});
		}
		if (player->GetPlayerMove()->CheckNowFloorType() == CGridObject::BlockType::WATAAME)
		{
			CWataame* wataameObj = dynamic_cast<CWataame*>(GetStageObject(player->GetGridPos(), CGridObject::BlockType::WATAAME));
			wataameObj->Melt();
			player->GetPlayerMove()->SetMoveWataame(true);
			CGrid::GRID_XY xy = wataameObj->GetGridPos();
			// ↓ここで穴のオブジェクトをnewしてvstageObjにpushbackする
			nowFloor->floorTable[xy.y][xy.x] = static_cast<short>(CGridObject::BlockType::HOLL);
			CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
			hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetGridPos()));
			hollObj->SetBlookType(CGridObject::BlockType::HOLL);
			hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
			hollObj->mTransform.pos.z = wataameObj->mTransform.pos.z + 0.0001f;
			hollObj->SetTransformScale(stageScale, stageScale, wataameObj->mTransform.scale.z);
			hollObj->ChangeInvisible();
			vStageObj->push_back(hollObj);
			hollObj->dotween->DelayedCall(MELT_TIME + WALK_TIME, [&, hollObj]()
				{
					hollObj->ChangeInvisible();
				});
		}
		// 左上
		if (player->GetState() == Player::STATE::THIN &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::BAUMHORIZONTAL)
		{
			CBaum* baumObj = dynamic_cast<CBaum*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			Vector3 o_baumPos = baumObj->mTransform.pos;
			baumObj->PlayAnim(player->GetDirection(), playerBuffer);
			baumObj->SetTexture(stageTextureBaumAnim[player->GetDirection()]);
			baumObj->mTransform.scale.x *= 2.0f;
			baumObj->mTransform.scale.y *= 1.5655f;
			baumObj->mTransform.pos.x -= 0.0151f * player->GetGridTable()->GetGridScale().x;
			baumObj->mTransform.pos.y -= 0.01496f * player->GetGridTable()->GetGridScale().y;
			float offsetZ;
			float adjustValue;	// バウムクーヘン通ってる間に変わるz値
			if (player->GetDirection() == static_cast<int>(Player::DIRECTION::RIGHT))
			{
				offsetZ = 0.099991f;
				adjustValue = 0.002f;	// バウムクーヘン通ってる間に変わるz値
			}
			else
			{
				offsetZ = -0.0002f;
				adjustValue = -INFRONT_PLUSZ + 0.000001f;
			}

			baumObj->mTransform.pos.z -= offsetZ;
			player->dotween->DelayedCall(BAUM_THROWMIDTIME, [&, baumObj, offsetZ, adjustValue]()
				{
					baumObj->mTransform.pos.z += offsetZ + adjustValue;
				});

			player->dotween->DelayedCall(BAUM_THROWENDTIME, [&, baumObj, o_baumPos]()
				{
					baumObj->SetVertexBuffer(stageBuffer);
					baumObj->SetTexture(stageTextureBaumkuchen_L);
					baumObj->mTransform.scale.x = player->GetGridTable()->GetGridScale().x;
					baumObj->mTransform.scale.y = player->GetGridTable()->GetGridScale().y;
					baumObj->mTransform.pos = o_baumPos;
					player->ChangeInvisible();
				});
		}
		else if (player->GetState() == Player::STATE::THIN &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::BAUMVERTICAL)
		{
			CBaum* baumObj = dynamic_cast<CBaum*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));

			Vector3 o_baumPos = baumObj->mTransform.pos;

			baumObj->PlayAnim(player->GetDirection(), playerBuffer);
			baumObj->SetTexture(stageTextureBaumAnim[player->GetDirection()]);
			baumObj->mTransform.scale.x *= 2.0f;
			baumObj->mTransform.scale.y *= 1.5655f;
			baumObj->mTransform.pos.x += 0.0151f * player->GetGridTable()->GetGridScale().x;
			baumObj->mTransform.pos.y -= 0.01496f * player->GetGridTable()->GetGridScale().y;

			float offsetZ;
			float adjustValue;	// バウムクーヘン通ってる間に変わるz値
			if (player->GetDirection() == static_cast<int>(Player::DIRECTION::UP))
			{
				offsetZ = 0.099991f;
				adjustValue = 0.002f;	// バウムクーヘン通ってる間に変わるz値
			}
			else
			{
				offsetZ = -0.0002f;
				adjustValue = -INFRONT_PLUSZ + 0.000001f;
			}

			baumObj->mTransform.pos.z -= offsetZ;

			player->dotween->DelayedCall(BAUM_THROWMIDTIME, [&, baumObj, offsetZ, adjustValue]()
				{
					baumObj->mTransform.pos.z += offsetZ + adjustValue;
				});

			player->dotween->DelayedCall(BAUM_THROWENDTIME, [&, baumObj, o_baumPos]()
				{
					baumObj->SetVertexBuffer(stageBuffer);
					baumObj->SetTexture(stageTextureBaumkuchen_R);
					baumObj->mTransform.pos = o_baumPos;
					baumObj->mTransform.scale.x = player->GetGridTable()->GetGridScale().x;
					baumObj->mTransform.scale.y = player->GetGridTable()->GetGridScale().y;
					player->ChangeInvisible();
				});
		}
		if (player->GetState() == Player::STATE::MUSCLE &&
			player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::GALL)
		{
			CGall* gallObj = dynamic_cast<CGall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(),
				static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));

			Vector3 pos = { 10.0f, 3.0f, 0.0f };
			proteinUi->GetDotween()->DoEaseInBack(pos, 0.7f);
			pos = { -16.0f, 3.5f, 0.0 };
			calorieGage->GetDotween()->DoEaseInBack(pos, 0.7f);
			pos = { 10.0f,-2.0f,0.0f };
			floorUi->GetDotween()->DoEaseInBack(pos, 0.7f);
			if (GetProtein != nullptr)
			{
				pos.y = 2.1f;
				pos.x = 15.0f;
				GetProtein->dotween->DoEaseInBack(pos, 0.7f);
			}
			
			pos = { 10.0f,1.5f,-0.4f };

			if (coinUI != nullptr)
			{
				coinUI->GetDotween()->DoEaseInBack(pos, 0.7f);
				coinUI->GetDotween()->OnComplete([&]()
					{
						coinUI->SetPosition({ -16.0f,-0.2f,-0.455f + 0.132f });
						coinUI->SetScale({ 1.5f,1.5f });
						coinUI->SetActive(true);
					});
			}
			
			player->dotween->DelayedCall(BREAK_TIME / 9.0f, [&]()
				{
					player->GetPlayerAnim()->SetAnimSpeedRate(0.2f);
					player->GetPlayerAnim()->animSpeed = 0.1f;
				});
			player->dotween->DelayedCall(BREAK_TIME / 5.5f, [&, gallObj]()
				{
					Vector2 pos = { gallObj->mTransform.pos.x ,gallObj->mTransform.pos.y };
					CCamera::GetInstance()->Zoom(0.35f, stageScale, { pos.x,pos.y / 2, 0 });
					XA_Play(SOUND_LABEL::S_CHARGE1);
				});
			player->dotween->DelayedCall(BREAK_TIME / 1.4f, [&, gallObj]()
				{
					Vector2 pos = { gallObj->mTransform.pos.x ,gallObj->mTransform.pos.y };
					CCamera::GetInstance()->Zoom(0.31f, stageScale, { pos.x,pos.y / 2, 0 });
					XA_Play(SOUND_LABEL::S_CHARGE2);
				});
			player->dotween->DelayedCall(BREAK_TIME / 0.8f, [&, gallObj]()
				{
					Vector2 pos = { gallObj->mTransform.pos.x ,gallObj->mTransform.pos.y };
					CCamera::GetInstance()->Zoom(0.29f, stageScale, { pos.x,pos.y / 2, 0 });
					XA_Play(SOUND_LABEL::S_CHARGE3);
				});
			player->dotween->DelayedCall(BREAK_TIME / 0.75f, [&, gallObj]()
				{
					player->GetPlayerAnim()->SetAnimSpeedRate(0.0f);
					player->GetPlayerAnim()->animSpeed = 0.0f;
				});
			player->dotween->DelayedCall(BREAK_TIME / 0.5f, [&]()
				{
					player->GetPlayerAnim()->SetAnimSpeedRate(1.5f);
					player->GetPlayerAnim()->animSpeed = 0.1f;
				});
			player->dotween->DelayedCall(BREAK_TIME / 0.46f, [&, gallObj]()
				{
					gallVibration = true;
					XA_Play(SOUND_LABEL::S_CHEST_PUNCH);
					player->GetPlayerAnim()->SetAnimSpeedRate(0.0f);
					player->GetPlayerAnim()->animSpeed = 0.0f;
					player->GetPlayerAnim()->SetAnimSpeedRate(1.0f);
					player->GetPlayerAnim()->animSpeed = 0.1f;
				});
			player->dotween->DelayedCall(BREAK_TIME / 0.365f, [&, gallObj]()
				{
					Vector2 pos = { gallObj->mTransform.pos.x ,gallObj->mTransform.pos.y / 2 };
					CCamera::GetInstance()->Zoom(0.26f, stageScale, { pos.x,pos.y, 0 });
					gallObj->Open(clearBuffer, 2.0f, stageScale * 0.4f);
					XA_Play(SOUND_LABEL::S_CHEST_OPEN);
					gallObj->SetTexture(stageTextureGallChest[1]);
					gallObj->dotween->DelayedCall(BREAK_TIME / 2.5f, [&, gallObj]()
						{
							gallReduction = true;
							XA_Play(SOUND_LABEL::S_GOAL);
						});
				});
		}
	}

	if (gallVibration)
	{
		CCamera::GetInstance()->Shake(1.0f, 1.0f);
		gallVibration = false;
	}

	if (gallReduction)
	{
		CCamera::GetInstance()->mTransform.pos = Vector3::zero;
		dotween->DoEaseOutBackScale(Vector3::one, 1.0f);
		dotween->OnComplete([&]()
			{
				//CCamera::GetInstance()->Init();
				XA_Play(SOUND_LABEL::S_GAMECLRAR);
				isGameClear = true;
				player->dotween->DelayedCall(5.0f, [&]()
					{
						player->ChangeInvisible();
					});
			});
		gallReduction = false;
	}

	if (CCamera::GetInstance()->GetIsShake())
	{
		CCamera::GetInstance()->ShakeUpdate();
	}
	// プレイヤーが動き終えると
	if (player->GetPlayerMove()->GetIsWalkEnd())
	{
		if (player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCO ||
			player->GetPlayerMove()->CheckNextFloorType() == CGridObject::BlockType::CHOCOCRACK)
		{
			CChoco* chocoObj = dynamic_cast<CChoco*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(),
				static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextFloorType())));
			if (player->GetState() != Player::STATE::THIN)
			{
				if (!player->GetPlayerMove()->GetIsFalling())
				{
					if (chocoObj->GetBlookType() == CGridObject::BlockType::CHOCOCRACK)
					{
						CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
						hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
						hollObj->SetBlookType(CGridObject::BlockType::HOLL);
						hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
						hollObj->mTransform.pos.z = chocoObj->mTransform.pos.z + 0.0001f;
						hollObj->SetTransformScale(stageScale, stageScale, chocoObj->mTransform.scale.z);
						hollObj->ChangeInvisible();
						vStageObj->push_back(hollObj);
						hollObj->dotween->DelayedCall(MELT_TIME + WALK_TIME, [&, hollObj]()
							{
								hollObj->ChangeInvisible();
							});
						player->GetPlayerMove()->FallStart();
					}
					chocoObj->CRACK();
					chocoObj->SetTexture(stageTextureChocolateClack);
				}
			}
			if (player->GetState() == Player::STATE::FAT || player->GetState() == Player::STATE::MUSCLE)
			{
				chocoObj->CRACK();
				CHoll* hollObj = new CHoll(stageBuffer, stageTextureHoll);
				hollObj->SetGridPos(static_cast <CGrid::GRID_XY> (player->GetPlayerMove()->GetNextGridPos()));
				hollObj->SetBlookType(CGridObject::BlockType::HOLL);
				hollObj->mTransform.pos = (nowFloor)->GridToWorld(hollObj->GetGridPos(), static_cast<CGridObject::BlockType>(hollObj->GetBlookType()));
				hollObj->mTransform.pos.z = chocoObj->mTransform.pos.z + 0.0001f;
				hollObj->SetTransformScale(stageScale, stageScale, chocoObj->mTransform.scale.z);
				hollObj->ChangeInvisible();
				vStageObj->push_back(hollObj);
				hollObj->dotween->DelayedCall(MELT_TIME + WALK_TIME, [&, hollObj]()
					{
						hollObj->ChangeInvisible();
					});
				player->GetPlayerMove()->FallStart();
			}
		}

		if (player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::COIN)
		{
			CCoin* coinObj = dynamic_cast<CCoin*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(),
				static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
			coinObj->GetCoin();
		}

		if (player->GetPlayerMove()->CheckNextObjectType() == CGridObject::BlockType::GUMI)
		{
			player->GetPlayerMove()->RiseStart();
		}
		// アイテムがあるならそれを画面から消す
		ItemDelete();
	}


	if (player->GetPlayerMove()->GetCannonMoveStartTrigger())
	{
		CGridObject::BlockType type = player->GetPlayerMove()->CheckNextObjectType();
		switch (type)
		{
		case CGridObject::BlockType::WALL:
		{
			CWall* wallObj = dynamic_cast<CWall*>(GetStageObject(player->GetPlayerMove()->GetNextGridPos(), type));
			wallObj->Break(player->GetDirection(), 0.0f);
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
			CCoin* coinObj = dynamic_cast<CCoin*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), type));
			coinObj->GetCoin();
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			coinObj->dotween->OnComplete([&, deletePos, coinObj]()
				{
					CannonItemDelete(deletePos, coinObj->GetBlookType());
				});
			break;
		}
		case CGridObject::BlockType::PROTEIN:
		{
			CProtein* proObj = dynamic_cast<CProtein*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), type));
			proObj->BlowOff(player->GetDirection());
			CGrid::GRID_XY deletePos = player->GetPlayerMove()->GetNextGridPos();
			//nowFloor->objectTable[proObj->GetGridPos().y][proObj->GetGridPos().x] =static_cast<short> (CGridObject::BlockType::NONE);
			proObj->dotween->OnComplete([&, deletePos, proObj]()
				{
					CannonItemDelete(deletePos, proObj->GetBlookType());
					player->GameOver();
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
	if (player->GetCannonFX() == true)
	{
		CCannon* cannonObj = dynamic_cast<CCannon*>(GetStageFloor(player->GetPlayerMove()->GetNextGridPos(), static_cast<CGridObject::BlockType>(player->GetPlayerMove()->CheckNextObjectType())));
		cannonObj->InPlayer();
		bool* canmove = cannonObj->GetCanMove();
		bool* p_canmove = player->GetCanMoveDir();
		for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
		{
			*p_canmove = *canmove;
			p_canmove++;
			canmove++;
		}
	}

	if (player->GetPlayerMove()->GetIsMoveTrigger())
	{

		if (player->GetState() != Player::STATE::MUSCLE && nNumProtein <= 0 && !player->GetGameOverOnes())
		{
			player->ChangeState(Player::STATE::MUSCLE);
			calorieGage->SetCalorie(CAKE_CALORIE);
			player->SetCalorie(CAKE_CALORIE);
			//if (!player->GetIsPlayMakeover())
			//{
			//	player->mTransform.pos = player->GetGridTable()->GridToWorld(player->GetGridPos(), CGridObject::BlockType::START, static_cast<int>(Player::STATE::MUSCLE));
			//}
		}
		// マッチョじゃないなら
		if (player->GetState() == Player::STATE::MUSCLE) return;
		// 動き終えたあとにカロリーが状態変わるようなら状態を変化させる
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
		{
			player->ChangeState(nextState);
			isLookMap = player->GetPlayerMove()->GetIsLookCamera();
		}
	}
}

void StageScene::TableUpdate()
{
	// 一旦全て白紙にする
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// その行の最初が使われていないなら終わる
		if ((nowFloor)->floorTable[i][0] == 0) break;

		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// 列が使われていないなら
			if ((nowFloor)->floorTable[i][j] == 0) break;

			(nowFloor)->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
			(nowFloor)->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
		}
	}

	// 配列全て見る
	for (auto itr = vStageObj->begin(); itr != vStageObj->end(); itr++)
	{
		// そのオブジェクトが画面にないなら次に行く
		if (!(*itr)->GetActive()) continue;

		// グリッド座標取って
		CGrid::GRID_XY g = (*itr)->GetGridPos();
		// 今の階層のテーブルに更新する
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
	// 座標を求める ////////////////////////////////////////////////////
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

	// 動かす先のワールド座標を求める
	CGrid::GRID_XY targetGrid = { next.x + d.x, next.y + d.y };

	Vector3 target = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::CASTELLA);

	/////////////////////////////////////////////////////////////////////

	// リストの中からプレイヤーの移送先座標と同じもの　かつ　カステラを探す
	auto itr = std::find_if(vStageObj->begin(), vStageObj->end(),
		[&](CGridObject* _obj)
		{
			return (_obj->GetGridPos().x == next.x && _obj->GetGridPos().y == next.y &&
				_obj->GetBlookType() == CGridObject::BlockType::CASTELLA);
		});

	CCastella* castella = static_cast<CCastella*>((*itr));

	// 動かした先が穴なら
	if ((nowFloor)->floorTable[targetGrid.y][targetGrid.x] == static_cast<int>(CGridObject::BlockType::HOLL))
	{
		Vector3 floorPos = (nowFloor)->GridToWorld(targetGrid, CGridObject::BlockType::FLOOR);
		castella->Move(target, player->GetDirection(), floorPos);
		castella->SetGridPos(targetGrid.x, targetGrid.y);

		// オブジェクトテーブルからカステラを消して
		(nowFloor)->objectTable[targetGrid.y][targetGrid.x] = static_cast<int>(CGridObject::BlockType::NONE);

		//	カステラを床にする
		castella->SetCategory(CGridObject::Category::FLOOR);
		castella->SetBlookType(CGridObject::BlockType::CASTELLA_FLOOR);

		// 穴を画面から消す
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

	// 入力した大砲の方向で発射できるか見る
	for (int i = 0; i < isSelectDir; i++)
	{
		canMoveDir++;
	}
	// 発射出来ない方向なら　入力されていないなら　終了する
	if (!*canMoveDir || isSelectDir == -1) return;


	//player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
	player->SetDirection(isSelectDir);
	cannonMove = true;
	Vector3 _pos = player->mTransform.pos;
	Vector3 _Scale = player->mTransform.scale;
	_pos.z = cannonObj->mTransform.pos.z;
	player->mTransform.pos.z = _pos.z - 0.000001f;
	_Scale.x = _Scale.x * CANNON_FIRE_SCALE;
	_Scale.y = _Scale.y * CANNON_FIRE_SCALE;
	// 右 or 左なら　大砲動かす
	if (isSelectDir == 2 || isSelectDir == 1)
	{
		//右
		if (isSelectDir == 1)
		{
			_pos.x = _pos.x - (0.1f * stageScale);
			_pos.y = _pos.y - (0.1f * stageScale);
			_pos.z = _pos.z - 0.1015f;
			//_pos.z = -0.14f;
		}

		cannonObj->SetTexture(stageTextureCannon[0]);
		dynamic_cast<CannonAnim*>(cannonObj->GetmAnim())->PlayTurn(isSelectDir, 2.0f);
		player->dotween->DelayedCall(0.9f, [&, isSelectDir, cannonObj, _pos, _Scale]()
			{
				cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));
				player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir, _pos, _Scale]()
					{
						player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
						player->GetPlayerMove()->CannonMoveStart();
						XA_Play(SOUND_LABEL::S_SHOT);
						if(isSelectDir == 1)
						player->PlayEffect(_pos, _Scale, EffectManeger::FX_TYPE::CANNON_FIRE, false);
						else
						cannonObj->Fire(isSelectDir);
						player->ChangeInvisible();
						cannonMove = false;
						cannonObj->PlayReturn();
						player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir]()
							{
								dynamic_cast<CannonAnim*>(cannonObj->GetmAnim())->PlayTurn(0, 2.0f);
							});
					});
			});
	}
	else
	{
		cannonObj->SetTexture(stageTextureCannon[1]);
		cannonObj->DirSelect(static_cast<Player::DIRECTION>(isSelectDir));
		if (isSelectDir == 0)
		{
			_pos.x = _pos.x + (0.3f * stageScale);
			_pos.y = _pos.y - (0.1f * stageScale);
			_pos.z = _pos.z - (INFRONT_PLUSZ + HORIZONLINE_PLUSZ / 2.0f);
			//_pos.z = _pos.z - 0.15f;
		}
		player->dotween->DelayedCall(0.9f, [&, cannonObj, isSelectDir, _pos, _Scale]()
			{
				player->GetPlayerMove()->CannonDirSelect(static_cast<PlayerMove::DIRECTION>(isSelectDir));
				player->GetPlayerMove()->CannonMoveStart();
				XA_Play(SOUND_LABEL::S_SHOT);
				if(isSelectDir == 0)
					player->PlayEffect(_pos, _Scale, EffectManeger::FX_TYPE::CANNON_FIRE, false);
				else
				cannonObj->Fire(isSelectDir);
				player->ChangeInvisible();
				cannonMove = false;
				cannonObj->PlayReturn(2.0f);
			});
	}




}

void StageScene::ItemDelete()
{
	CGrid::GRID_XY next = player->GetPlayerMove()->GetNextGridPos();

	CGridObject* deleteObj;	// 画面から消す予定のポインタがはいる

	switch (static_cast<CGridObject::BlockType>
		((nowFloor)->objectTable[next.y][next.x]))
	{
		// プレイヤーの位置にこのアイテムがあれば
	case CGridObject::BlockType::PROTEIN:
	{
		nNumProtein--;
		player->dotween->DelayedCall(EAT_TIME, [&]()
			{
				proteinUi->AddProtein();
				XA_Play(SOUND_LABEL::S_PROTEIN_UP);
			});
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]));

		// 画面から消す
		deleteObj->SetActive(false);
		break;
	}
	case CGridObject::BlockType::COIN:
	{
		nNumCoin--;
		coinUI->AddProtein();

		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]));

		// 画面から消す
		//deleteObj->SetActive(false);
		break;
	}
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::CHILI:
	case CGridObject::BlockType::CANNON:
	{
		// リストの中からプレイヤーの座標と同じもの　かつ　床じゃない物を探す
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, static_cast<CGridObject::BlockType>((nowFloor)->objectTable[next.y][next.x]));

		// 画面から消す
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


	CGridObject* deleteObj;	// 画面から消す予定のポインタがはいる
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
		// プレイヤーの位置にこのアイテムがあれば
	case CGridObject::BlockType::COIN:
		nNumCoin--;
		coinUI->AddProtein();
	case CGridObject::BlockType::PROTEIN:
	case CGridObject::BlockType::CAKE:
	case CGridObject::BlockType::CHILI:
	{
		// リストの中からプレイヤーの座標と同じもの　かつ　床じゃない物を探す
		auto itr = std::find_if(vStageObj->begin(), vStageObj->end(), [&](CGridObject* _obj)
			{
				return (_obj->GetGridPos().x == next.x &&
					_obj->GetGridPos().y == next.y &&
					_obj->GetCategory() == CGridObject::Category::ITEM);
			});

		deleteObj = GetStageObject(next, type);

		// 画面から消す
		deleteObj->SetActive(false);
	}

	break;

	default:
		break;
	}
}

void StageScene::Undo(float _stageScale, bool isPush)
{
	if (player->GetPlayerMove()->GetIsMoving() && !isPush) return;
	short o_nNumUndo = nNumUndo;

	XA_Play(SOUND_LABEL::S_CANSEL);

	// 1より下に行く
	nNumUndo--;
	if (nNumUndo < 0)
	{
		nNumUndo = UNDO_ARRAY_NUM - 1;	// 下回ると
	}
	// まだ使われていないのなら
	if (floorUndo[nNumUndo].objectTable[0][0][0] == 0)
	{
		nNumUndo = o_nNumUndo;	// 引く前の階数に戻す
		return;	// 抜ける
	}
	bool o_MakeOver = player->GetPlayMakeover();

	// 更新するテーブル
	GridTable* updateTable = nowFloor;
	// 更新するオブジェクトのリスト
	std::vector<CGridObject*>* updateObjList = vStageObj;
	// 前にいた階数のグリッドテーブルを更新する
	const short& o_floorNum = floorUndo[nNumUndo].old_Floor;

	// 階層を移動していない  リセットじゃないなら
	if (nowFloorNum == o_floorNum)
	{
		// １つずつ入れていく
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// 情報を入れる
				updateTable->objectTable[i][j] =
					floorUndo[nNumUndo].objectTable[o_floorNum - 1][i][j];

				// 情報を入れる
				updateTable->floorTable[i][j] =
					floorUndo[nNumUndo].floorTable[o_floorNum - 1][i][j];
			}
		}
		// 入れた階層のオブジェクトを作る
		CreateStage(*updateTable, *updateObjList);
	}
	// 移動しているなら
	else
	{
		for (int loop = 0; loop < MAX_LAYER; loop++)
		{
			// 全ての階層を更新する
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

			default:	// エラー
				MessageBoxA(NULL, "Undo関数でold_Floorが1～3階の範囲でありません", "エラー", MB_ICONERROR | MB_OK);
				break;
			}

			// 階層がこれ以上ないなら終わる
			if (updateTable == nullptr) break;

			// １つずつ入れていく
			for (int i = 0; i < stageSquare.y; i++)
			{
				for (int j = 0; j < stageSquare.x; j++)
				{
					// 情報を入れる
					updateTable->objectTable[i][j] =
						floorUndo[nNumUndo].objectTable[loop][i][j];
					// 情報を入れる
					updateTable->floorTable[i][j] =
						floorUndo[nNumUndo].floorTable[loop][i][j];
				}
			}
			// 入れた階層のオブジェクトを作る
			CreateStage(*updateTable, *updateObjList);
		}
	}

	// プロテインの数を求める
	nNumProtein = 0;

	// コインの数を求める
	nNumCoin = 0;
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		// 各階層のオブジェクトテーブルをゲット
		switch (layer)
		{
		case 0:
			updateTable = oneFloor;
			break;

		case 1:
			updateTable = secondFloor;
			break;

		case 2:
			updateTable = thirdFloor;
			break;
		}

		if (updateTable == nullptr) break;

		// プロテインを見る
		for (int ver = 0; ver < stageSquare.y; ver++)
		{
			for (int hori = 0; hori < stageSquare.x; hori++)
			{
				// プロテインの数を取得する
				if (updateTable->objectTable[ver][hori] == static_cast<int>(CGridObject::BlockType::PROTEIN))
					nNumProtein++;
				else if (updateTable->objectTable[ver][hori] == static_cast<int>(CGridObject::BlockType::COIN))
					nNumCoin++;
			}
		}

		// コインの数を見る

	}

	// プロテインUIに設定する
	proteinUi->SetProtein(nNumProtein, true);

	// コインUIに設定
	if (coinUI != nullptr)
		coinUI->SetProtein(nNumCoin, true);

	// リスがいる階層を更新
	nowFloorNum = o_floorNum;
	// 更新する
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

	if (player->GetPlayMakeover() != o_MakeOver)
		player->SetPlayMakeover(o_MakeOver);

	// プレイヤーに必要な情報を更新する
	UndoPlayerSet(floorUndo[nNumUndo].dirUndo, floorUndo[nNumUndo].calorieUndo, floorUndo[nNumUndo].stateUndo);
	player->SetCalorieGage(calorieGage);
	calorieGage->SetCalorie(player->GetCalorie(), false);
	isLookMap = player->GetPlayerMove()->GetIsLookCamera();
	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		Arrow[i]->SetOwner(player, static_cast<CArrow::DIRECTION>(i), stageScale);
	}
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
		// これ以上階層がないなら終わる
		if (setTable == nullptr) break;

		// 今いる階層だけ更新
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

	// 方向を設定
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

	// カロリーを設定
	player->SetCalorie(_calorie);



	// アニメーションの画像も反映させる
	player->GetmAnim()->SetPattern(static_cast<int>(animPattern));

	// 状態を変化させる
	player->ChangeState(_state);

	player->mTransform.pos = nowFloor->GridToWorld(player->GetGridPos(), player->GetBlookType(), static_cast<int>(player->GetState()));
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



	//UI

	if (!isStartStop)
	{
		if (Menu->GetisMenu() == false && !isGameClear && !player->GetIsGameOver() && !isTutorialNow)
		{
			if (*isLookMap == true)
			{
				FloorLookButton->Draw();
				BackCameraButton->Draw();
				if (lockStageMap != 1)
					LB_Button->Draw();
				if (lockStageMap != nMaxFloor)
					RB_Button->Draw();
			}
			else if (*isLookMap == false)
			{
				CameraButton->Draw();
				UndoButton->Draw();
			}
			LookingTxet->Draw();
		}
	}
	if (isW11 && Menu->GetisMenu() == false)
	{
		GetProtein->Draw();
	}
	//プロテイン
	proteinUi->Draw();


	//階層
	floorUi->Draw();

	//カロリーゲージ
	calorieGage->Draw();

	bool* IsArrowDraw = player->GetCanMoveDir();
	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		if (!player->GetPlayerMove()->GetisLoolMap())
		{
			if (*IsArrowDraw == true && (!player->GetIsMoving() || player->GetPlayerMove()->GetIncannon()) && player->GetIsMissMove())
			{
				if (!Arrow[i]->GetIsActive())
				{
					Arrow[i]->Appear({ stageScale ,stageScale }, 0.5f);
				}

				if (!isStartStop)
				{
					Arrow[i]->Draw();
				}
			}
			else
			{
				Arrow[i]->SetActive(false);
			}
		}
		IsArrowDraw++;
	}

	if (coinUI != nullptr)
		coinUI->Draw();
	Menu->Draw();


	if (isTutorialNow)
	{
		tutorial->Draw();
	}
	if (isGameClear)
	{
		gameClear->Draw();
	}
	if (player->GetIsGameOver())
	{
		gameOver->Draw();
	}
	if (isStartStop == true)
	{
		gameStart->Draw();
	}

}

void StageScene::Z_Sort(std::vector<CGridObject*>& _sortList)
{
	std::sort(_sortList.begin(), _sortList.end(), [](CObject* a, CObject* b) {return (a->mTransform.pos.z > b->mTransform.pos.z); });
}

void StageScene::Init(const wchar_t* filePath)
{
	D3D_CreateSquare({ 1,1 }, &stageBuffer);
	D3D_CreateSquare({ 3,4 }, &playerBuffer);
	D3D_CreateSquare({ 6,7 }, &clearBuffer);
	D3D_CreateSquare({ 2,1 }, &LR_ButtonBuffer);

	// ステージの大きさを設定する

	nNumProtein = 0;

	nNumCoin = 0;

	stage = new CLoadStage;
	//stageMake = new CStageMake();

	LoadData StageData = stage->LoadStage(filePath);

	stageSquare = { StageData.numX,StageData.numY };

	switch (StageData.numX)
	{
	case 3:
		stageScale = 2.7f;
		break;
	case 4:
		stageScale = 2.5f;
		break;
	case 5:
		stageScale = 2.3f;
		break;
	case 6:
		stageScale = 2.1f;
		break;
	case 7:
		stageScale = 1.9f;
		break;
	case 9:
		stageScale = 1.5f;
		break;
	default:
		stageScale = 1;
		break;
	}

	//	ワールド座標
	/*stagePos = stageMake->StagePos(StageData);*/

	// ここでグリッドテーブルを作成する　/////////////
	// 階層ごとのテーブルに入れていく ///////////////
	oneFloor = new GridTable({ StageData.numX, StageData.numY }, stageScale);
	if (StageData.secondFloor.floorTable[0][0] != 0) //0が入っていれば作られてない　階層なし
	{
		secondFloor = new GridTable({ StageData.numX, StageData.numY }, stageScale);
		nMaxFloor = 2;
		if (StageData.thirdFloor.floorTable[0][0] != 0)
		{
			thirdFloor = new GridTable({ StageData.numX,StageData.numY }, stageScale);
			nMaxFloor = 3;
		}
	}
	else
	{
		secondFloor = nullptr;
		thirdFloor = nullptr;
		nMaxFloor = 1;
	}

	//開始する階層
	int startfloor = 0;

	// ロードしたデータからグリッドテーブルに入れる
	for (int i = 0; i < StageData.numY; i++)
	{
		for (int j = 0; j < StageData.numX; j++)
		{
			// オブジェクトのカテゴリを取得する
			CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]);
			CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

			// 床だったら
			if (bCate == CGridObject::Category::FLOOR)
			{
				// 床テーブルに入れて
				oneFloor->floorTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// オブジェクトテーブルには何も置かない(99を入れてる)
				oneFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
			}
			// オブジェクト・アイテムなら
			else
			{
				//	オブジェクトテーブルに入れて
				oneFloor->objectTable[i][j] = StageData.oneFloor.floorTable[i][j];
				// 床テーブルには通常床を入れる
				oneFloor->floorTable[i][j] = static_cast<int>(CGridObject::BlockType::FLOOR);
				//読み込んだ数字ごとに処理するモノ
				switch (static_cast<CGridObject::BlockType>(StageData.oneFloor.floorTable[i][j]))
				{
				case CGridObject::BlockType::START:
					startfloor = 1;
					nowFloor = oneFloor;
					break;
				case CGridObject::BlockType::PROTEIN:
					nNumProtein++;
					break;
				case CGridObject::BlockType::COIN:
					nNumCoin++;
					break;
				default:
					break;
				}
			}

			//２階があればテーブル作成
			if (secondFloor != nullptr)
			{
				CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.secondFloor.floorTable[i][j]);
				CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

				// 床だったら
				if (bCate == CGridObject::Category::FLOOR)
				{
					// 床テーブルに入れて
					secondFloor->floorTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// オブジェクトテーブルには何も置かない(99を入れてる)
					secondFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
				}
				// オブジェクト・アイテムなら
				else
				{
					//	オブジェクトテーブルに入れて
					secondFloor->objectTable[i][j] = StageData.secondFloor.floorTable[i][j];
					// 床テーブルには通常床を入れる
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
					case CGridObject::BlockType::COIN:
						nNumCoin++;
						break;
					default:
						break;
					}
				}

				//３階があればテーブルを作成する
				if (thirdFloor != nullptr)
				{
					CGridObject::BlockType bType = static_cast<CGridObject::BlockType>(StageData.thirdFloor.floorTable[i][j]);
					CGridObject::Category bCate = static_cast<CGridObject::Category>(CGridObject::TypeToCategory(bType));

					// 床だったら
					if (bCate == CGridObject::Category::FLOOR)
					{
						// 床テーブルに入れて
						thirdFloor->floorTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// オブジェクトテーブルには何も置かない(99を入れてる)
						thirdFloor->objectTable[i][j] = static_cast<int>(CGridObject::BlockType::NONE);
					}
					// オブジェクト・アイテムなら
					else
					{
						//	オブジェクトテーブルに入れて
						thirdFloor->objectTable[i][j] = StageData.thirdFloor.floorTable[i][j];
						// 床テーブルには通常床を入れる
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
						case CGridObject::BlockType::COIN:
							nNumCoin++;
							break;
						default:
							break;
						}
					}
				}
			}
		}
	}

	nowFloorNum = startfloor;	// 1階から
	startFloor = startfloor;

	lockStageMap = startfloor;

	//UI

	//ボタン
	CameraButton = new UI(stageBuffer, ButtonTextureCamera);
	FloorLookButton = new UI(stageBuffer, ButtonTextureFloorLook);
	UndoButton = new UI(stageBuffer, ButtonTextureUndo);
	LookingTxet = new UI(stageBuffer, TextTextureLooking);

	RB_Button = new UI(LR_ButtonBuffer, Button_LB_RB_Texture);
	LB_Button = new UI(LR_ButtonBuffer, Button_LB_RB_Texture);

	BackCameraButton = new UI(stageBuffer, ButtonTextureCameraBack);

	CameraButton->mTransform.pos = { -6.5f,-4.0f,0.0f };
	FloorLookButton->mTransform.pos = { -6.5f,-3.0f,0.0f };
	UndoButton->mTransform.pos = { -6.1f,-3.0f,0.0f };
	BackCameraButton->mTransform.pos = { -6.5f,-4.0f,0.0f };
	CameraButton->mTransform.scale = { 2.4f,0.8f,1.0f };
	FloorLookButton->mTransform.scale = { 2.4f,0.8f,1.0f };
	UndoButton->mTransform.scale = { 3.2f,0.8f,1.0f };
	BackCameraButton->mTransform.scale = { 2.4f,0.8f,1.0f };

	LookingTxet->mTransform.pos = { -13.0f,2.5f,0.0 };
	LookingTxet->mTransform.scale = { 5.4f,0.9f,0.0f };
	LookingTxet->MakeDotween();

	RB_Button->SetUV(0.5f, 0.0f);

	RB_Button->mTransform.pos = { 6.0f,0.0f,0.0 };
	LB_Button->mTransform.pos = { 6.0f,0.0f,0.0 };

	RB_Button->mTransform.scale = { 0.7f,0.7f,0.0 };
	LB_Button->mTransform.scale = { 0.7f,0.7f,0.0 };

	switch (lockStageMap)
	{
	case 1:
		RB_Button->mTransform.pos.y = -1.0f;
		break;
	case 2:
		RB_Button->mTransform.pos.y = 0.0f;
		LB_Button->mTransform.pos.y = -1.0f * 2.0f;
		break;
	case 3:
		LB_Button->mTransform.pos.y = -1.0f;
		break;
	default:
		break;
	}

	//プロテインUI作成　数が分かってから行う
	proteinUi = new ProteinUI(nNumProtein);

	Menu = new CMenu();

	proteinUi->SetPosition({ 6.0f, 3.0f, 0.0f });


	proteinUi->SetScale({ 1.3f, 1.3f });
	if (selectName == CScene::SCENE_NAME::WORLD1_SELECT)
	{
		gameStart = new CGameStart(nNumProtein, true);
	}
	else
	{
		gameStart = new CGameStart(nNumProtein);
	}

	if (isW11)
	{
		GetProtein = new UI(stageBuffer, GetProteinTexture);

		GetProtein->mTransform.scale = { 5.0f,2.0f,0.0f };

		GetProtein->mTransform.pos = { 5.5f,2.1f,0.9f };
		GetProtein->MakeDotween();

	}

	if (nNumCoin != 0)
	{
		coinUI = new CoinUI(nNumCoin);
		coinUI->SetPosition({ 6.0f,1.5f,-0.4f });
		Vector2 xy(2.0f, 2.0f);
		coinUI->SetScale(xy);
	}

 	gameClear = new CGameClear(CScene::SCENE_NAME::NONE, coinUI);

	//ここでグリッドテーブルを作成する /////////////////////////////////////////

	// ステージを作成する
	CreateStage(*oneFloor, oneFStgObj);


	int MaxFloor = 1;
	// 2階と3階が使われているなら
	if (secondFloor != nullptr)
	{
		CreateStage(*secondFloor, secondFStgObj);
		MaxFloor = 2;
		if (thirdFloor != nullptr)
		{
			CreateStage(*thirdFloor, thirdFStgObj);
			MaxFloor = 3;
		}
	}

	//階層UI作成
	floorUi = new FloorUI(startfloor, MaxFloor);


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

		// 階層これ以上ないなら
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


	gameOver->SetFunc(0, [&]()
		{
			Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, [&]()
				{
					Reset();
					gameOver->ResetPos();
					player->SetGameOverFalse();
				});
		});

	gameOver->SetFunc(1, [&]()
		{
			Undo(stageScale, true);
			gameOver->ResetPos();
			player->SetGameOverFalse();
		});

	gameOver->SetFunc(2, [&]()
		{
			Fade::GetInstance()->FadeIn(Fade::STATE::LOADING, nullptr, selectName);
		});


	gameClear->SetFunc(0, [&]()
		{
			Fade::GetInstance()->FadeIn(Fade::STATE::MOVING, nullptr, nextStageName);
		});
	gameClear->SetFunc(1, [&]()
		{
			Fade::GetInstance()->FadeIn(Fade::STATE::LOADING, nullptr, selectName);
		});

	Menu->SetFunc(
		([&]()
			{
				Fade::GetInstance()->FadeIn(Fade::STATE::FADE_OUT, [&]()
					{
						Reset();
						gameOver->ResetPos();
						player->SetGameOverFalse();
					});
			})
	);

	//カロリーゲージ
	calorieGage = new CalorieGage_hori();

	player->SetCalorieGage(calorieGage);

	player->SetNowFloor(startfloor);

	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		Arrow[i] = new CArrow(stageBuffer, stageTextureArrow);
		Arrow[i]->SetOwner(player, static_cast<CArrow::DIRECTION>(i), stageScale);
		Arrow[i]->ScaleLoop();
		Arrow[i]->mTransform.pos.z = -0.60f;
	}
	calorieGage->SetPosition({ -4.5f,3.5f,0.0 });
	calorieGage->SetScale({ 0.75f,0.75f,1.0f });


	player->SetCalorie(8);

	if (nextStageName == CScene::SCENE_NAME::STAGE4_2)
	{
		player->SetCalorie(15);
	}



	// プレイヤーの初期化を行う（ここで最初にどの方向に進むかを決めている）
	player->Init(nowFloor);

	isLookMap = player->GetPlayerMove()->GetIsLookCamera();
	isMenu = player->GetPlayerMove()->GetIsMenu();
	(*isLookMap) = false;


	floorReset.playerUndo = player->GetGridPos();
	floorReset.stateUndo = player->GetState();
	floorReset.dirUndo = player->GetDirection();
	floorReset.calorieUndo = player->GetCalorie();
	floorReset.old_Floor = nowFloorNum;

	// 最初のUndoに入れておく
	floorUndo[0] = floorReset;

	Z_Sort(*vStageObj);
}

void StageScene::CreateStage(const GridTable& _gridTable, std::vector<CGridObject*>& _settingList)
{

	// 解放する
	for (int i = 0; i < _settingList.size(); i++)
	{
		CLASS_DELETE(_settingList[i]);
	}
	_settingList.clear();

	// オブジェクトテーブル
	for (int i = 0; i < MAX_GRIDNUM; i++)
	{
		// 左端が0なら終わる　→　
		if (_gridTable.objectTable[i][0] == 0) break;

		// 一つづつ見ていく
		for (int j = 0; j < MAX_GRIDNUM; j++)
		{
			// その行で初めて0が出たなら　→　ステージで使っていないところなら
			if (_gridTable.objectTable[i][j] == 0) break;

			// オブジェクト ////////////////////////////////////
			// オブジェクトを生成する
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
				// プレイヤーは触ることが多いのでメンバ変数として持っておく
				player = dynamic_cast<Player*>(objWork);
				break;
			case CGridObject::BlockType::GALL:
				objWork = new CGall(playerBuffer, stageTextureGallChest[2]);
				break;
			case CGridObject::BlockType::CANNON:
				objWork = new CCannon(playerBuffer, stageTextureCannon[1], nowFloor);
				break;
			default:
				break;

			}

			if (objWork != nullptr)	// オブジェクトを生成しているなら
			{
				// グリッド座標を持たせる
				objWork->SetGridPos(j, i);

				// 座標を設定
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.objectTable[i][j]);

				// ステージ全体の大きさを設定
				objWork->mTransform.scale = { stageScale, stageScale, 1 };
				// オブジェクトにその種類をもたせる
				objWork->SetBlookType(b);
				// オブジェクトにカテゴリーをもたせる
				objWork->SetCategory(CGridObject::TypeToCategory(b));

				objWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// アイテムならここで影の設定する
				if (objWork->GetCategory() == CGridObject::Category::ITEM)
				{
					dynamic_cast<CItem*>(objWork)->InitItem(shadowTexture);
				}
				else if (objWork->GetBlookType() == CGridObject::BlockType::CANNON)
				{
					dynamic_cast<CCannon*>(objWork)->CheckCanMove(_gridTable);
				}
				else if (objWork->GetBlookType() == CGridObject::BlockType::GALL)
				{
					objWork->mTransform.pos.x += 0.1296f * objWork->mTransform.scale.x;
					objWork->mTransform.pos.y -= 0.111f * objWork->mTransform.scale.y;
					objWork->mTransform.scale.x *= 1.5f;
					objWork->mTransform.scale.y *= 1.5f;
				}
				_settingList.push_back(objWork);
			}
			// オブジェクト /////////////////////////////////////

			// 床 ///////////////////////////////////////////////
			CGridObject* floorWork = nullptr;
			// 床を生成する
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
			case CGridObject::BlockType::CASTELLA_FLOOR:
				floorWork = new CCastella(stageBuffer, stageTextureCastella);
				break;
			default:
				break;
			}
			// 床 //////////////////////////////////////////////////////////////////////

			if (floorWork != nullptr)
			{
				// グリッド座標を持たせる
				floorWork->SetGridPos(j, i);

				// 座標を設定
				CGridObject::BlockType b =
					static_cast<CGridObject::BlockType>(_gridTable.floorTable[i][j]);

				// ステージ全体の大きさを設定
				floorWork->mTransform.scale = { stageScale, stageScale, 1 };
				// オブジェクトにその種類をもたせる
				floorWork->SetBlookType(b);
				// 床カテゴリに設定する
				floorWork->SetCategory(CGridObject::Category::FLOOR);

				floorWork->mTransform.pos = oneFloor->GridToWorld({ j, i },
					b);
				// 配列に入れていく
				_settingList.push_back(floorWork);
			}

		}

	}
}

void StageScene::ChangeFloor(int _nextFloor)
{
	auto removeItr = std::remove(vStageObj->begin(), vStageObj->end(), player);

	vStageObj->erase(removeItr, vStageObj->end());


	// 移動前の階層のテーブルのプレイヤーをNONEにする
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
	floorUi->SetHighlight(nowFloorNum);

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
				if ((*i)->GetCategory() == CGridObject::Category::FLOOR || (*i)->GetBlookType() == CGridObject::BlockType::START)
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
				if ((*j)->GetCategory() == CGridObject::Category::FLOOR || (*j)->GetBlookType() == CGridObject::BlockType::START)
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
				if ((*thir)->GetCategory() == CGridObject::Category::FLOOR || (*thir)->GetBlookType() == CGridObject::BlockType::START)
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
	// リストの中から指定した座標　オブジェクトテーブルにあるもの
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
	// リストの中から指定した座標　オブジェクトテーブルにあるもの
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

void StageScene::Reset()
{
	nNumUndo = 0;

	bool o_MakeOver = player->GetPlayMakeover();
	*isLookMap = false;
	
	 LookingTxet->mTransform.pos = { -13.0f,2.5f,0.0 };
	// 更新するテーブル
	GridTable* updateTable = nowFloor;
	// 更新するオブジェクトのリスト
	std::vector<CGridObject*>* updateObjList = vStageObj;
	// 前にいた階数のグリッドテーブルを更新する
	const short& o_floorNum = floorReset.old_Floor;


	// 移動しているなら
	for (int loop = 0; loop < MAX_LAYER; loop++)
	{
		// 全ての階層を更新する
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

		default:	// エラー
			MessageBoxA(NULL, "Undo関数でold_Floorが1～3階の範囲でありません", "エラー", MB_ICONERROR | MB_OK);
			break;
		}

		// 階層がこれ以上ないなら終わる
		if (updateTable == nullptr) break;

		// １つずつ入れていく
		for (int i = 0; i < stageSquare.y; i++)
		{
			for (int j = 0; j < stageSquare.x; j++)
			{
				// 情報を入れる
				updateTable->objectTable[i][j] =
					floorReset.objectTable[loop][i][j];
				// 情報を入れる
				updateTable->floorTable[i][j] =
					floorReset.floorTable[loop][i][j];
			}
		}
		// 入れた階層のオブジェクトを作る
		CreateStage(*updateTable, *updateObjList);

	}

	// プロテインの数を求める
	nNumProtein = 0;
	for (int layer = 0; layer < MAX_LAYER; layer++)
	{
		// 各階層のオブジェクトテーブルをゲット
		switch (layer)
		{
		case 0:
			updateTable = oneFloor;
			break;

		case 1:
			updateTable = secondFloor;
			break;

		case 2:
			updateTable = thirdFloor;
			break;
		}

		if (updateTable == nullptr) break;

		// プロテインを見る
		for (int ver = 0; ver < stageSquare.y; ver++)
		{
			for (int hori = 0; hori < stageSquare.x; hori++)
			{
				// プロテインの数を取得する
				if (updateTable->objectTable[ver][hori] == static_cast<int>(CGridObject::BlockType::PROTEIN))
					nNumProtein++;
			}
		}

	}

	// プロテインUIに設定する
	proteinUi->SetProtein(nNumProtein, true);

	// リスがいる階層を更新
	nowFloorNum = o_floorNum;
	// 更新する
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

	if (player->GetPlayMakeover() != o_MakeOver)
		player->SetPlayMakeover(o_MakeOver);

	lockStageMap = nowFloorNum;
	floorUi->SetHighlight(lockStageMap);
	switch (lockStageMap)
	{
	case 1:
		RB_Button->mTransform.pos.y = -1.0f;
		break;
	case 2:
		RB_Button->mTransform.pos.y = 0.0f;
		LB_Button->mTransform.pos.y = -1.0f * 2.0f;
		break;
	case 3:
		LB_Button->mTransform.pos.y = -1.0f;
		break;
	default:
		break;
	}

	Menu->SetIsMenu(false);

	// プレイヤーに必要な情報を更新する
	UndoPlayerSet(floorUndo[nNumUndo].dirUndo, floorUndo[nNumUndo].calorieUndo, floorUndo[nNumUndo].stateUndo);
	player->SetCalorieGage(calorieGage);
	calorieGage->SetCalorie(player->GetCalorie(), false);
	isLookMap = player->GetPlayerMove()->GetIsLookCamera();
	for (int i = 0; i < static_cast<int>(Player::DIRECTION::NUM); i++)
	{
		Arrow[i]->SetOwner(player, static_cast<CArrow::DIRECTION>(i), stageScale);
	}

	// 未使用にしておく
	for (int i = 1; i < UNDO_ARRAY_NUM; i++)
	{
		floorUndo[i].objectTable[0][0][0] = 0;
	}
}

void StageScene::SetTutorial(Tutorial* _setTutorial)
{
	tutorial = _setTutorial;

	isDoTutorial = true;
}
