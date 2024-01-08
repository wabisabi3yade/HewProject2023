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

#define START_CALORIE (10)	// �X�^�[�g���̃J�����[
#define CAKE_CALORIE (15)	// �P�[�L�H�ׂ����Ƃ̃��X�̃J�����[
#define CHILI_CALORIE (2)	// �Ƃ����炵�H�ׂ�����̃��X�̃J�����[

void Player::TextureInput(const wchar_t* _texPath, STATE _set)
{
	D3DTEXTURE tex = NULL;
	std::vector<D3DTEXTURE>* _vector = nullptr;

	switch (_set)
	{
	case STATE::NORMAL:
		_vector = &normalTex;
		break;

	case STATE::FAT:
		_vector = &fatTex;
		break;

	case STATE::THIN:
		_vector = &thinTex;
		break;

	case STATE::MUSCLE:
		_vector = &muscleTex;
		break;
	}
	D3D_LoadTexture(_texPath, &tex);
	_vector->push_back(tex);
}

Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb, tex)
{
	dotween = std::make_unique<DoTween>(this);

	move = std::make_shared<ThinMove>(this);
	
	// �A�j���[�V�������쐬
	mAnim = new CPlayerAnim();
	mAnim->SetPattern(0);
	mAnim->isStop = false;

	// �v���C���[�������e�N�X�`���������Ń��[�h���āA�e��Ԃ̔z��ɓ���Ă���
	TextureInput(L"asset/Player/N_Walk01_Forword.png", STATE::NORMAL);
	TextureInput(L"asset/Player/F_Walk01_Forword.png", STATE::FAT);
	TextureInput(L"asset/Player/S_Walk01_Forword.png", STATE::THIN);
	TextureInput(L"asset/Player/M_Walk01_Forword.png", STATE::MUSCLE);

	// �ʏ��Ԃ���n�߂�
	playerState = STATE::NORMAL;
	direction = DIRECTION::UP;
	calorie = START_CALORIE;
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

	/*case STATE::MUSCLE:
		move = std::make_shared<MuscleMove>(this);
		break;*/
	}

	// ��Ԃ��ς���čs����Ƃ�����ς��̂ōs����������X�V
	move->CheckCanMove();
}

void Player::Draw()
{
	CObject::Draw();
}

Player::~Player()
{
	CLASS_DELETE(mAnim);
	
	for (int i = 0; i < normalTex.size(); i++)
	{
		SAFE_RELEASE(normalTex[i]);
	}
	normalTex.clear();

	for (int i = 0; i < fatTex.size(); i++)
	{
		SAFE_RELEASE(fatTex[i]);
	}
	fatTex.clear();
	for (int i = 0; i < thinTex.size(); i++)
	{
		SAFE_RELEASE(thinTex[i]);
	}
	thinTex.clear();
	for (int i = 0; i < muscleTex.size(); i++)
	{
		SAFE_RELEASE(muscleTex[i]);
	}
	muscleTex.clear();
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

