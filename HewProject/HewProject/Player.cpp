#include "Player.h"
#include "CGrid.h"
#include "CInput.h"


Player::Player(D3DBUFFER vb, D3DTEXTURE tex)
	:CObject(vb, tex)
{
	// �O���b�h�N���X�̃|�C���^
	grid = std::make_shared<CGrid>();
	grid->gridPos = { 0,0 };

	dotween = new DoTween();

	canMove = true;	// ��U�ړ��ł��Ȃ��悤�ɂ���
	moveDir = DIR::UP;	// ��U�����ɂ���
}

void Player::Update()
{
	Move();
	dotween->Update();
}

void Player::Draw()
{
	CObject::Draw();
}

void Player::Move()
{
	if (!canMove) return;

	if (gInput->GetKeyTrigger(VK_UP))
	{
		canMove = true;
		Vector3 target = mTransform.pos;
		target.x += 2.0f;
		target.y += 3.0f;
		dotween->DoMoveY(this, target.y, 2.0f);
	}
	if (gInput->GetKeyTrigger(VK_DOWN))
	{
		canMove = true;
	}
	if (gInput->GetKeyTrigger(VK_RIGHT))
	{
		canMove = true;
	}
	if (gInput->GetKeyTrigger(VK_LEFT))
	{
		canMove = true;
	}
}

Player::~Player()
{
	CLASS_DELETE(dotween);
}

CGrid* Player::GetGrid()
{
	return grid.get();
}
