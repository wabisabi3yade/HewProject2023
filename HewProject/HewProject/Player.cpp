#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "PlayerMove.h"
#include "NormalMove.h"
#include "FatMove.h"
#include "ThinMove.h"
#include "MuscleMove.h"
#include "TextureFactory.h"

#define START_CALORIE (10)	// �X�^�[�g���̃J�����[
#define CAKE_CALORIE (15)	// �P�[�L�H�ׂ����Ƃ̃��X�̃J�����[
#define CHILI_CALORIE (2)	// �Ƃ����炵�H�ׂ�����̃��X�̃J�����[

void Player::TextureInput(const wchar_t* _texPath, STATE _set, ANIM_TEX _anim_tex)
{
	D3DTEXTURE tex = NULL;
	D3DTEXTURE* Arry = normalTex;

	switch (_set)
	{
	case STATE::NORMAL:
		/*Arry = normalTex;*/
		break;

	case STATE::FAT:
		Arry = fatTex;
		break;

	case STATE::THIN:
		Arry = thinTex;
		break;

	case STATE::MUSCLE:
		Arry = muscleTex;
		break;
	}
	// �e�N�X�`�����Ǘ�����N���X����w�肵���e�N�X�`�����擾����
	D3DTEXTURE texWork = TextureFactory::GetInstance()->Fetch(_texPath);
	// �z��̎w�肵���Ƃ���Ƀe�N�X�`�������i�[����
	Arry[static_cast<int>(_anim_tex)] = texWork;
}

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(static_cast<int>(CPlayerAnim::PATTERN::STAY_DOWN));
	mAnim->isStop = false;
	IsgameOver = false;
	fallFloorChangeTrriger = false;
	fallMoveTrriger = false;
	risingChangeTrriger = false;
	risingMoveTrriger = false;
	ChangeCannonTexture = false;

	// �v���C���[�������e�N�X�`���������Ń��[�h���āA�e��Ԃ̔z��ɓ���Ă���
	TextureInput(L"asset/Player/N_Walk.png", STATE::NORMAL, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/N_Wait.png", STATE::NORMAL, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/F_Walk.png", STATE::FAT, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/F_Wait.png", STATE::FAT, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/T_Walk.png", STATE::THIN, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/T_Wait.png", STATE::THIN, ANIM_TEX::WAIT);
	TextureInput(L"asset/Player/M_Walk.png", STATE::MUSCLE, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/M_Wait.png", STATE::MUSCLE, ANIM_TEX::WAIT);

	TextureInput(L"asset/Player/N_EatCake.png", STATE::NORMAL, ANIM_TEX::EAT_CAKE);
	TextureInput(L"asset/Player/F_EatCake.png", STATE::FAT, ANIM_TEX::EAT_CAKE);
	TextureInput(L"asset/Player/T_EatCake.png", STATE::THIN, ANIM_TEX::EAT_CAKE),
	TextureInput(L"asset/Player/N_EatChili.png", STATE::NORMAL, ANIM_TEX::EAT_CHILI);
	TextureInput(L"asset/Player/F_EatChili.png", STATE::FAT, ANIM_TEX::EAT_CHILI);
	TextureInput(L"asset/Player/T_EatChili.png", STATE::THIN, ANIM_TEX::EAT_CHILI);


	punchTex[0] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Down.png");
	punchTex[1] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Left.png");
	punchTex[2] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Right.png");
	punchTex[3] = TextureFactory::GetInstance()->Fetch(L"asset/Player/M_Punch_Up.png");

	cannonTex = TextureFactory::GetInstance()->Fetch(L"asset/Player/Player_CanonMove.png");

	BaumTex[0] = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_ThrowDown.png");
	BaumTex[1] = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_ThrowLeft.png");
	BaumTex[2] = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_ThorwRight.png");
	BaumTex[3] = TextureFactory::GetInstance()->Fetch(L"asset/Player/T_ThrowUp.png");
}

void Player::Init(GridTable* _pTable)
{
	// ���݂���O���b�h�e�[�u���ݒ�
	SetGridTable(_pTable);
	// ������ݒ肷��
	direction = DIRECTION::EVERY;

	// �ŏ��͕��ʏ�Ԃ���n�߂�
	move = std::make_shared<NormalMove>(this);

	// �ʏ��Ԃ���n�߂�
	/*playerState = STATE::NORMAL;*/

	ChangeState(STATE::NORMAL);


	calorie = START_CALORIE;
	/*SetTexture(normalTex[0]);*/



	/*move->CheckCanMove();*/

	//�v���C���[�̍��W���O���b�h�e�[�u���ƃO���b�h���W���狁�߂�
	mTransform.pos = GetGridTable()->GridToWorld(Grid->gridPos, CGridObject::BlockType::START);

}

void Player::Update()
{
	// �t���O�̏�����
	move->FlagInit();

	// ��FlagInit�̌�
	move->Input();
	fallMoveTrriger = false;
	risingMoveTrriger = false;

	dotween->Update();

	//fallFloorChangeTrriger = false;
	//risingChangeTrriger = false;

	if (move->GetIsCannonMove())
	{
		move->CannonMove2();
	}

	if (move->GetIsFalling() == false && move->GetIsRising() == false)
	{
		if (move->GetIsWalk_Old() == false && move->GetIsWalk_Now() == true)
		{
			ChangeTexture(ANIM_TEX::WALK);
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction));
		}
		else if (move->GetIsWalk_Old() == true && move->GetIsWalk_Now() == false && isEat == false)
		{
			ChangeTexture(ANIM_TEX::WAIT);
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(this->direction));
		}
	}
	else
	{
		if (move->GetIsFalling() == true)
		{
			// �����鏈�� 
			if (fallMoveTrriger == true)
			{
				if (this->GetNowFloor() == 1)
				{
					this->GameOver();
					return;
				}
				mTransform.pos.y = (FALL_POS_Y * -1.0f) + mTransform.scale.y / 2;  //�ŏI�n�_�̔��� �� ��ʂ̍ŏ㕔�n�_
				fallFloorChangeTrriger = true;
			}
			if (mTransform.pos == gridTable->GridToWorld(this->GetPlayerMove()->GetNextGridPos(), CGridObject::BlockType::START) && fallFloorChangeTrriger)
			{
				if (this->gridTable->CheckFloorType(move->GetNextGridPos()) != static_cast<int>(CGridObject::BlockType::HOLL))
				{
					move->WalkAfter();
				}
				move->Step();
				fallFloorChangeTrriger = false;
			}


		}
		else if (move->GetIsRising() == true)
		{
			//��鏈��
			if (risingMoveTrriger == true)
			{
				mTransform.pos.y = FALL_POS_Y - mTransform.scale.y / 2;
				risingChangeTrriger = true;
			}
			if (mTransform.pos == gridTable->GridToWorld(this->move->GetNextGridPos(), CGridObject::BlockType::START) && risingChangeTrriger)
			{
				//move->Move(static_cast<PlayerMove::DIRECTION>(direction));
				move->WalkAfter();
				this->SetGridPos(move->GetNextGridPos());
				//move->MoveAfter();
				move->Step();
				move->RiseAfter();
				risingChangeTrriger = false;
			}

		}
	}

}

// ���������̃J�����[����
void Player::WalkCalorie()
{
	calorie--;
	if (calorie < 0) calorie = 0;
}

// �P�[�L�H�ׂ�����
void Player::EatCake()
{
	calorie = CAKE_CALORIE;
}

// �Ƃ����炵
void Player::EatChilli()
{
	calorie -= CHILI_CALORIE;
	if (calorie < 0) calorie = 0;
}

// ��Ԃ�ς���Ƃ��ɌĂяo������
void Player::ChangeState(STATE _set)
{
	bool o_isMoveTrigger = false;

	if (move.get() != nullptr)
	{
		o_isMoveTrigger = move->GetIsMoveTrigger();

	}

	// �ړ��N���X���������
	move.reset();

	// �e��Ԃ̈ړ��N���X���擾����
	switch (_set)
	{
	case STATE::NORMAL:
		// �ʏ��Ԃ̓����N���X��move�Ɋm�ۂ���
		move = std::make_shared<NormalMove>(this);
		playerState = STATE::NORMAL;
		SetTexture(normalTex[ANIM_TEX::WAIT]);
		break;

	case STATE::FAT:
		move = std::make_shared<FatMove>(this);
		playerState = STATE::FAT;
		SetTexture(fatTex[ANIM_TEX::WAIT]);
		break;

	case STATE::THIN:
		move = std::make_shared<ThinMove>(this);
		playerState = STATE::THIN;
		SetTexture(thinTex[ANIM_TEX::WAIT]);
		break;

	case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		playerState = STATE::MUSCLE;
		SetTexture(muscleTex[ANIM_TEX::WAIT]);
		this->calorie = CAKE_CALORIE;
		break;
	}

	move->SetMoveTrigger(o_isMoveTrigger);

	dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk(static_cast<int>(direction));

	// �ړ��ł���������X�V
	move->CheckCanMove();
}

void Player::ChangeTexture(ANIM_TEX _animTex)
{
	if (_animTex == ANIM_TEX::CANNON)
	{
		SetTexture(cannonTex);
		return;
	}
	if (_animTex == ANIM_TEX::EAT_CAKE)
	{
		switch (playerState)
		{
		case Player::STATE::NORMAL:
			SetTexture(normalTex[_animTex]);
			break;
		case Player::STATE::THIN:
			SetTexture(thinTex[_animTex]);
			break;
		case Player::STATE::FAT:
			SetTexture(fatTex[_animTex]);
			break;
		default:
			break;
		}
		isEat = true;
		return;
	}
	if (_animTex == ANIM_TEX::EAT_CHILI)
	{
		switch (playerState)
		{
		case Player::STATE::NORMAL:
			SetTexture(normalTex[_animTex]);
			break;
		case Player::STATE::THIN:
			SetTexture(thinTex[_animTex]);
			break;
		case Player::STATE::FAT:
			SetTexture(fatTex[_animTex]);
			break;
		default:
			break;
		}
		isEat = true;
		return;
	}
	if (_animTex == ANIM_TEX::PUNCH)
	{
		SetTexture(punchTex[static_cast<int>(direction)]);
		return;
	}
	else if (_animTex == ANIM_TEX::BAUM)
	{
		switch (static_cast<int>(this->direction))
		{
		case 0:
			SetTexture(BaumTex[0]);
			break;
		case 1:
			break;
			SetTexture(BaumTex[1]);
			break;
		case 2:
			SetTexture(BaumTex[2]);
			break;
		case 3:
			SetTexture(BaumTex[3]);
			break;
		default:
			break;
		}
		return;
	}
	switch (playerState)
	{
	case Player::STATE::NORMAL:
		SetTexture(normalTex[_animTex]);
		break;
	case Player::STATE::THIN:
		//if (_animTex == ANIM_TEX::WAIT)
		//	mAnim->animSpeed = 2.0f;
		SetTexture(thinTex[_animTex]);
		break;
	case Player::STATE::FAT:
		SetTexture(fatTex[_animTex]);
		break;
	case Player::STATE::MUSCLE:
		SetTexture(muscleTex[_animTex]);
		break;
	default:
		break;
	}
}

void Player::Draw()
{
	CObject::Draw();
}

void Player::Fall()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->FallStart();
}

void Player::Rise()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayFall(static_cast<int>(direction), 2.0f);
	move->RiseStart();
}

void Player::EatEnd()
{
	isEat = false;
}

// �e�N�X�`���͉�����Ȃ�
Player::~Player()
{
	CLASS_DELETE(mAnim);
}

bool Player::GetIsMoving() const
{
	return move->GetIsMoving();
}

int Player::GetDirection() const
{
	return static_cast<int>(direction);
}

PlayerMove* Player::GetPlayerMove() const
{
	return move.get();
}

void Player::SetNowFloor(int _set)
{
	nowFloor = _set;
}

void Player::GameOver()
{
	IsgameOver = true;
}

void Player::SetDirection(int _set)
{
	direction = static_cast<DIRECTION>(_set);
}

