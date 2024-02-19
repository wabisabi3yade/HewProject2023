#include "StageMoveText.h"

#define BEGIN_OFFSETY (2.0f)
#define OFFSET_X (0.95f)
#define PERIOD_OFFSET_X (0.8f)
#define ALPHA_TIME (0.3f)

#define TIME_OFFSET (0.015f)
#define LOAD_TIME (0.2f)


StageMoveText::StageMoveText(int worldNum, int stageNum)
{
	base = new UI();

	D3D_LoadTexture(L"asset/UI/StageMove.png", &moveTex);
	D3D_CreateSquare({ 3,5 }, &moveBuffer);

	base->mTransform.pos.x = -2.0f;
	Vector3 begin = base->mTransform.pos;
	begin.y += BEGIN_OFFSETY;
	Vector3 sca = base->mTransform.scale;

	Vector2 uv_base = { 1.0f / 3, 1.0f / 5 };

	W = new UI(moveBuffer, moveTex);
	W->SetUV(0.0f, (1.0f / 5) * 2);

	for (int i = 0; i < 2; i++)
	{
		num[i] = new UI(moveBuffer, moveTex);

	}
	num[0]->SetUV(uv_base.x * ((worldNum - 1) % 3), uv_base.y * (int)((worldNum - 1) / 3));
	num[1]->SetUV(uv_base.x * ((stageNum - 1) % 3), uv_base.y * (int)((stageNum - 1) / 3));

	haihun = new UI(moveBuffer, moveTex);
	haihun->SetUV(uv_base.x * 1, uv_base.y * 2);

	for (int i = 0; i < 4; i++)
	{
		MoveText[i] = new UI(moveBuffer, moveTex);
		MoveText[i]->SetUV(uv_base.x * ((8 + i) % 3), uv_base.y * ((8 + i) / 3));
	}

	for (int i = 0; i < 3; i++)
	{
		period[i] = new UI(moveBuffer, moveTex);
		period[i]->SetUV(0.0f, uv_base.y * 4);
	}

	text.push_back(W);
	text.push_back(num[0]);
	text.push_back(haihun);
	text.push_back(num[1]);
	for (int i = 0; i < 4; i++)
	{
		text.push_back(MoveText[i]);
	}
	for (int i = 0; i < 3; i++)
	{
		text.push_back(period[i]);
	}

	float delayTime = 0.0f;
	for (int i = 0; i < text.size(); i++)
	{

		float offset = OFFSET_X;

		text[i]->mTransform.pos = begin;
		text[i]->mTransform.pos.x += i * offset;

		if (i >= 8)
		{
			text[i]->mTransform.pos.x = text[7]->mTransform.pos.x + ((i - 7) * PERIOD_OFFSET_X);
		}

		text[i]->mTransform.pos.z -= UI_OFFSETZ;
		text[i]->mTransform.scale = sca;
		text[i]->SetAlpha(0.0f);
		text[i]->SetColor({ 71, 81,137 });

		Vector3 p = text[i]->mTransform.pos;
		p.y = base->mTransform.pos.y;
		delayTime += i * TIME_OFFSET;

		text[i]->MakeDotween();
		text[i]->dotween->DoDelay(delayTime);
		text[i]->dotween->Append(1.0f, ALPHA_TIME, DoTweenUI::FUNC::ALPHA);
		text[i]->dotween->Join(p, ALPHA_TIME, DoTweenUI::FUNC::EASE_OUTCUBIC);

		/*text[i]->dotween->DoDelay(LOAD_TIME);
		text[i]->dotween->Append(0.0f, 0.015f, DoTweenUI::FUNC::ALPHA);*/
	}
}

void StageMoveText::Update()
{
	for (auto a : text)
	{
		a->Update();
	}
}

void StageMoveText::Draw()
{
	for (auto a : text)
	{
		a->Draw();
	}
}

StageMoveText::~StageMoveText()
{
	SAFE_RELEASE(moveTex);
	SAFE_RELEASE(moveBuffer);

	CLASS_DELETE(base);

	for (auto a : text)
	{
		CLASS_DELETE(a);
	}
	text.clear();
	text.shrink_to_fit();
}
