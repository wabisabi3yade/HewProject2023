#include "ShadowUI.h"
#include "TextureFactory.h"

#define SHADOW_OFFSETX (0.01f)	// �{�̂Ɖe��X���W�����l
#define SHADOW_OFFSETY (0.017f)	// �{�̂Ɖe��Y���W�����l
#define SHADOW_OFFSETZ (0.0005f)	// �{�̂Ɖe��Y���W�����l

#define SHADOW_ALPHA (0.3f)	// �e�̓����x

ShadowUI::ShadowUI(D3DBUFFER vb, D3DTEXTURE tex)
	: UI(vb, tex)
{
	shadow = new UI(mVertexBuffer, mTexture);
	// �F�Ɠ����x��ݒ�
	shadow->SetColor({ 0,0,0 });

	shadowOffset = { SHADOW_OFFSETX, SHADOW_OFFSETY };
}

ShadowUI::~ShadowUI()
{
	CLASS_DELETE(shadow);
}

void ShadowUI::Update()
{
	UI::Update();
}

void ShadowUI::Draw()
{
	// ���W�Ɖ�]�A�X�P�[������
	shadow->mTransform = mTransform;

	// �e�̂����\��
	shadow->mTransform.pos.x += mTransform.scale.x * shadowOffset.x;
	shadow->mTransform.pos.y -= mTransform.scale.y * shadowOffset.y;
	shadow->mTransform.pos.z += SHADOW_OFFSETZ;
	shadow->SetUV(uv.x, uv.y);

	shadow->SetAlpha(materialDiffuse.w - (1.0f - SHADOW_ALPHA));

	shadow->Draw();

	UI::Draw();
}

void ShadowUI::SetShadowOffset(const Vector2& _offset)
{
	shadowOffset = _offset;
}
