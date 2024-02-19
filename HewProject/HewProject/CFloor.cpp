#include "CFloor.h"
#include"DoTween.h"
constexpr float FLOOR_BOUND_MAXPOS_Y = 5.0f;
constexpr float FLOOR_BOUND_MOVE_TIME = 1.0f;

CFloor::CFloor(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	type = BlockType::FLOOR;
	category = Category::FLOOR;
	dotween = std::make_unique<DoTween>(this);
}

CFloor::~CFloor()
{
}

void CFloor::Update()
{
	dotween->Update();
	CGridObject::Update();
}

void CFloor::Draw()
{
	CGridObject::Draw();
}

void CFloor::FloorBound()
{
	//プレイヤーが画面下から床の位置に行くまでの時間まつ
	dotween->DoDelay(RISING_TIME *  1.5f);
	dotween->Append(this->mTransform.pos, FLOOR_BOUND_MOVE_TIME, DoTween::FUNC::MOVECURVE, FLOOR_BOUND_MAXPOS_Y);
}
