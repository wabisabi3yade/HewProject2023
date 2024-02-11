#include "ShadowUI.h"
#include "TextureFactory.h"

#define SHADOW_OFFSETX (0.01f)	// 本体と影のY座標差分値
#define SHADOW_OFFSETY (0.017f)	// 本体と影のY座標差分値
#define SHADOW_ALPHA (0.3f)	// 影の透明度

ShadowUI::ShadowUI(D3DBUFFER vb, D3DTEXTURE tex)
	: UI(vb, tex)
{
}

ShadowUI::~ShadowUI()
{
	CLASS_DELETE(shadow);
}

void ShadowUI::Update()
{
	UI::Update();

	if (shadow != nullptr)
	{
		// 座標と回転、スケールを代入
		shadow->mTransform = mTransform;

		// 影のずれを表現
		shadow->mTransform.pos.x += mTransform.scale.x * SHADOW_OFFSETX;
		shadow->mTransform.pos.y -= mTransform.scale.y * SHADOW_OFFSETY;
		shadow->mTransform.pos.z += UI_OFFSETZ;

		shadow->SetAlpha(materialDiffuse.w - (1.0f - SHADOW_ALPHA));
	}
}

void ShadowUI::Draw()
{
	shadow->Draw();

	UI::Draw();
}

void ShadowUI::SetShadow()
{
	shadow = new UI(mVertexBuffer, mTexture);
	// 座標と回転、スケールを代入
	shadow->mTransform = mTransform;

	// 影のずれを表現
	shadow->mTransform.pos.x += mTransform.scale.x * SHADOW_OFFSETX;
	shadow->mTransform.pos.y -= mTransform.scale.y * SHADOW_OFFSETY;
	shadow->mTransform.pos.z += UI_OFFSETZ;

	// 色と透明度を設定
	shadow->SetColor({ 0,0,0 });
	shadow->SetAlpha(SHADOW_ALPHA);
}
