#include "CWataame.h"
#include"DoTween.h"
#include"Player.h"
constexpr float MELT_TIME = 1.0f;
CWataame::CWataame(D3DBUFFER vb, D3DTEXTURE tex)
	:CGridObject(vb,tex)
{
	dotween = std::make_unique<DoTween>(this);
}

CWataame::~CWataame()
{
}

void CWataame::Update()
{
	dotween->Update();
	CGridObject::Update();
}

void CWataame::Draw()
{
	CGridObject::Draw();
}

void CWataame::Melt()
{
	//this->SetBlookType(static_cast<int>(CStageMake::BlockType::HOLL));
	dotween->DoDelay(WALK_TIME);
	dotween->Append({0.0f,0.0f,1.0f}, MELT_TIME, DoTween::FUNC::SCALE);
	dotween->OnComplete([&]()
		{
			this->SetActive(false);
		});
}
