#include "CCake.h"
#include"DoTween.h"
CCake::CCake(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb,tex)
{
	type = BlockType::CAKE;
	category = Category::ITEM;
	dotween = std::make_unique<DoTween>(this);

}

CCake::~CCake()
{
}

void CCake::Update()
{
	dotween->Update();
	CItem::Update();
}

void CCake::Draw()
{
	CItem::Draw();
}

void CCake::BlowOff(int _dir)
{
	this->SetShadow(NULL);
	switch (_dir)
	{
		//‰E‚É
	case 0:
	case 2:
		dotween->DoMoveXY({ MAX_POS_X + mTransform.scale.x / 2, MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME / 2, DoTween::FUNC::ROTATION);
		break;

		//¶‚É
	case 1:
	case 3:
		dotween->DoMoveXY({ (MAX_POS_X * -1.0f) - mTransform.scale.x / 2,MAX_POS_Y + 2.0f }, BLOWOFF_TIME / 2);
		dotween->Join(360.0f, BLOWOFF_TIME, DoTween::FUNC::ROTATION);
		break;
	default:
		break;
	}
}
