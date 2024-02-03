#include "CCoin.h"
#include"DoTween.h"

CCoin::CCoin(D3DBUFFER vb, D3DTEXTURE tex)
	:CItem(vb, tex)
{
	type = BlockType::COIN;
	category = Category::ITEM;
	dotween = std::make_unique<DoTween>(this);
}

CCoin::~CCoin()
{
}

void CCoin::Update()
{
	dotween->Update();
	CItem::Update();
}

void CCoin::Draw()
{
	CItem::Draw();
}

void CCoin::BlowOff(int _dir)
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
