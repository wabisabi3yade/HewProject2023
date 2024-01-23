#include "LoadCharacter.h"
#include "CPlayerAnim.h"

LoadCharacter::LoadCharacter(D3DBUFFER vb, D3DTEXTURE tex)
{
	mVertexBuffer = vb;
	mTexture = tex;

	mAnim = new CPlayerAnim();
	// 左向かって歩くアニメ再生
	dynamic_cast<CPlayerAnim*>(mAnim)->PlayWalk(1);
}

LoadCharacter::~LoadCharacter()
{
	CLASS_DELETE(mAnim);
}

void LoadCharacter::Update()
{
	
}

void LoadCharacter::Draw()
{
	UI::Draw();
}
