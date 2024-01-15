#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "Player.h"
#include "CGrid.h"
#include "CInput.h"
#include "PlayerMove.h"
#include "CPlayerAnim.h"
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

	move = std::make_shared<NormalMove>(this);

	// �A�j���[�V�������쐬
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;

	// �v���C���[�������e�N�X�`���������Ń��[�h���āA�e��Ԃ̔z��ɓ���Ă���
	TextureInput(L"asset/Player/N_Walk.png", STATE::NORMAL, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/F_Walk.png", STATE::FAT, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/T_Walk.png", STATE::THIN, ANIM_TEX::WALK);
	TextureInput(L"asset/Player/M_Walk01_Forword.png", STATE::MUSCLE, ANIM_TEX::WALK);

	// �ʏ��Ԃ���n�߂�
	playerState = STATE::NORMAL;
	direction = DIRECTION::UP;
	calorie = START_CALORIE;
	SetTexture(normalTex[0]);
}

void Player::Init(GridTable* _pTable)
{
	// ���݂���O���b�h�e�[�u���ݒ�
	SetGridTable(_pTable);

	move->CheckCanMove();

	//�v���C���[�̍��W���O���b�h�e�[�u���ƃO���b�h���W���狁�߂�
	mTransform.pos = GetGridTable()->GridToWorld(Grid->gridPos, CStageMake::BlockType::START);

}

void Player::Update()
{
	// �t���O�̏�����
	move->FlagInit();

	// ��FlagInit�̌�
	move->Input();
	if (move->GetIsFalling() == false)
	{
		if (move->GetIsWalk_Old() == false && move->GetIsWalk_Now() == true)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction));
		}
		else if (move->GetIsWalk_Old() == true && move->GetIsWalk_Now() == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk();
		}
		else if (move->GetIsWalk_Old() == false && move->GetIsWalk_Now() == false)
		{
			dynamic_cast<CPlayerAnim*>(mAnim)->StopWalk();
		}
	}
	dotween->Update();
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
	// �ړ��N���X���������
	move.reset();

	// �e��Ԃ̈ړ��N���X���擾����
	switch (_set)
	{
	case STATE::NORMAL:
		// �ʏ��Ԃ̓����N���X��move�Ɋm�ۂ���
		move = std::make_shared<NormalMove>(this);
		playerState = STATE::NORMAL;
		SetTexture(normalTex[0]);
		break;

	case STATE::FAT:
		move = std::make_shared<FatMove>(this);
		playerState = STATE::FAT;
		SetTexture(fatTex[0]);
		break;

	case STATE::THIN:
		move = std::make_shared<ThinMove>(this);
		playerState = STATE::THIN;
		SetTexture(thinTex[0]);
		break;

	case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		playerState = STATE::MUSCLE;
		SetTexture(muscleTex[0]);
		break;
	}

	// ��Ԃ��ς���čs����Ƃ�����ς��̂ōs����������X�V
	move->CheckCanMove();
}

void Player::Draw()
{
	CObject::Draw();
}

void Player::Fall()
{
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(static_cast<int>(direction), 2.0f);
	move->FallStart();
}

Player::~Player()
{
	CLASS_DELETE(mAnim);

	/*for (int i = 0; i < static_cast<int>(ANIM_TEX::NUM); i++)
	{
		SAFE_RELEASE(normalTex[i]);
	}

	for (int i = 0; i < static_cast<int>(ANIM_TEX::NUM); i++)
	{
		SAFE_RELEASE(fatTex[i]);
	}
	for (int i = 0; i < static_cast<int>(ANIM_TEX::NUM); i++)
	{
		SAFE_RELEASE(thinTex[i]);
	}
	for (int i = 0; i < static_cast<int>(ANIM_TEX::NUM); i++)
	{
		SAFE_RELEASE(muscleTex[i]);
	}*/
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

void Player::SetDirection(int _set)
{
	direction = static_cast<DIRECTION>(_set);
}

