#include "CGameStart.h"
#include "UI.h"
#include "TextureFactory.h"
#include "ProteinUI.h"

#define GAMESTART_POS_Z (-0.496f)
#define GAMESTART_POS_Y (-1.3f)

#define MOVEMENT (17.0f)
#define DOTWEEN_OUTTIME (0.4f)
#define DOTWEEN_INTIME (0.7f)
#define DOTWEEN_DELAY_PROTEIN (0.1f)
#define DOTWEEN_DELAY_TEXT_WORLD1 (2.5f)
#define DOTWEEN_DELAY_TEXT (1.3f)
#define DOTWEEN_DELAYEDCALL_PROTEIN_WORLD1 (2.4f)
#define DOTWEEN_DELAYEDCALL_PROTEIN (1.2f)

CGameStart::CGameStart(int _num, bool _world1)
{
	TextEndPos = { 0,2.0f,GAMESTART_POS_Z - 0.00001f };
	NeedEndPos = { 5.0f,-0.5f,GAMESTART_POS_Z - 0.00001f };
	ProteinEndPos = { 0,GAMESTART_POS_Y ,GAMESTART_POS_Z };
	
	D3D_CreateSquare({ 1,1 }, &bgBuffer);
	bgTexture = TextureFactory::GetInstance()->Fetch(L"asset/UI/FadeBlack.png");

	Bg = new UI(bgBuffer, bgTexture);
	Bg->MakeDotween();
	Bg->SetColor({ 0,0,0 });
	Bg->SetAlpha(0);
	Bg->mTransform.pos = { 0,0,GAMESTART_POS_Z };
	Bg->mTransform.scale = { 16.0f,9.0f,1.0f };

	D3D_CreateSquare({ 1,1 }, &textBuffer);
	textTexture = TextureFactory::GetInstance()->Fetch(L"asset/Text/T_GoalAt.png");
	D3D_LoadTexture(L"asset/Text/T_Need.png", &needTexture);

	Text = new UI(textBuffer, textTexture);
	Text->MakeDotween();
	Text->mTransform.pos = TextEndPos;
	Text->mTransform.pos.x += MOVEMENT;
	Text->mTransform.scale = { 6.0f,1.5f,1.0f };

	Need = new UI(textBuffer, needTexture);
	Need->MakeDotween();
	Need->mTransform.pos = NeedEndPos;
	Need->mTransform.pos.x += MOVEMENT;
	Need->mTransform.scale = { 4.5f,1.5f,1.0f };

	nNumProtein = _num;
	isWorld1 = _world1;

	fProteinZ = GAMESTART_POS_Z - 0.00002f;

	Vector3 a = ProteinEndPos;
	a.x += MOVEMENT;

	Protein = new ProteinUI(nNumProtein, false);
	Protein->SetPosition(a);
	Protein->SetScale({ 2,2 });
	Protein->SetActive(false);


	isProtein = false;
	isMoveing = false;
}

CGameStart::~CGameStart()
{
	CLASS_DELETE(Bg);
	CLASS_DELETE(Text);
	CLASS_DELETE(Protein);
	CLASS_DELETE(Need);

	SAFE_RELEASE(bgBuffer);
	SAFE_RELEASE(textBuffer);
	SAFE_RELEASE(needTexture);
}

void CGameStart::Update()
{

	if (isProtein == false)
	{
		isProtein = true;

		if (isWorld1 == false)
		{
			Bg->dotween->DoAlpha(0.5f, 0.2f);
			Bg->dotween->OnComplete([&]() {
				Text->dotween->DoEaseOutBack(TextEndPos, DOTWEEN_OUTTIME);
				Text->dotween->Append(0, DOTWEEN_DELAY_TEXT, DoTweenUI::FUNC::DELAY);
				Vector3 text = TextEndPos;
				text.x -= MOVEMENT;
				Text->dotween->Append(text, DOTWEEN_INTIME, DoTweenUI::FUNC::EASE_INBACK);

				Need->dotween->DoEaseOutBack(NeedEndPos, DOTWEEN_OUTTIME);
				Need->dotween->Append(0, DOTWEEN_DELAY_TEXT, DoTweenUI::FUNC::DELAY);
				Vector3 need = NeedEndPos;
				need.x -= MOVEMENT;
				Need->dotween->Append(need, DOTWEEN_INTIME, DoTweenUI::FUNC::EASE_INBACK);

				Need->dotween->OnComplete([&]() {
					Protein->SetProtein(false);
					isMoveing = true;
					Need->SetActive(false);
					Text->SetActive(false);
					});

				if (nNumProtein == 1)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN, [&]() {
							Vector3 protein = ProteinEndPos;
							protein.x -= MOVEMENT;
							Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
							Protein->GetDotween()->OnComplete([&]() {
								Bg->dotween->DoAlpha(0, 0.2f);
								});
							});
						});
				}
				else if (nNumProtein == 2)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
							Protein->AddProtein();
							Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN - 0.1f, [&]() {
								Vector3 protein = ProteinEndPos;
								protein.x -= MOVEMENT;
								Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
								Protein->GetDotween()->OnComplete([&]() {
									Bg->dotween->DoAlpha(0, 0.2f);
									});
								});
							});

						});
				}
				else if (nNumProtein == 3)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
							Protein->AddProtein();
							Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
								Protein->AddProtein();
								Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN - 0.2f, [&]() {
									Vector3 protein = ProteinEndPos;
									protein.x -= MOVEMENT;
									Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
									Protein->GetDotween()->OnComplete([&]() {
										Bg->dotween->DoAlpha(0, 0.2f);
										});
									});
								});
							});
						});
				}
				});
		}
		else {
			Bg->dotween->DoAlpha(0.5f, 0.2f);
			Bg->dotween->OnComplete([&]() {
				Text->dotween->DoEaseOutBack(TextEndPos, DOTWEEN_OUTTIME);
				Text->dotween->Append(0, DOTWEEN_DELAY_TEXT_WORLD1, DoTweenUI::FUNC::DELAY);
				Vector3 text = TextEndPos;
				text.x -= MOVEMENT;
				Text->dotween->Append(text, DOTWEEN_INTIME, DoTweenUI::FUNC::EASE_INBACK);

				Need->dotween->DoEaseOutBack(NeedEndPos, DOTWEEN_OUTTIME);
				Need->dotween->Append(0, DOTWEEN_DELAY_TEXT_WORLD1, DoTweenUI::FUNC::DELAY);
				Vector3 need = NeedEndPos;
				need.x -= MOVEMENT;
				Need->dotween->Append(need, DOTWEEN_INTIME, DoTweenUI::FUNC::EASE_INBACK);

				Need->dotween->OnComplete([&]() {
					Protein->SetProtein(false);
					isMoveing = true;
					Need->SetActive(false);
					Text->SetActive(false);
					});

				if (nNumProtein == 1)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN_WORLD1, [&]() {
							Vector3 protein = ProteinEndPos;
							protein.x -= MOVEMENT;
							Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
							Protein->GetDotween()->OnComplete([&]() {
								Bg->dotween->DoAlpha(0, 0.2f);
								});
							});
						});
				}
				else if (nNumProtein == 2)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
							Protein->AddProtein();
							Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN_WORLD1 - 0.1f, [&]() {
								Vector3 protein = ProteinEndPos;
								protein.x -= MOVEMENT;
								Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
								Protein->GetDotween()->OnComplete([&]() {
									Bg->dotween->DoAlpha(0, 0.2f);
									});
								});
							});

						});
				}
				else if (nNumProtein == 3)
				{
					Protein->GetDotween()->DoEaseOutBack(ProteinEndPos, DOTWEEN_OUTTIME);
					Protein->GetDotween()->Append(ProteinEndPos, DOTWEEN_DELAY_PROTEIN, DoTweenUI::FUNC::DELAY);
					Protein->GetDotween()->OnComplete([&]() {
						Protein->SetActive(true);
						Protein->AddProtein();
						Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
							Protein->AddProtein();
							Protein->GetDotween()->DelayedCall(DOTWEEN_DELAY_PROTEIN, [&]() {
								Protein->AddProtein();
								Protein->GetDotween()->DelayedCall(DOTWEEN_DELAYEDCALL_PROTEIN_WORLD1 - 0.2f, [&]() {
									Vector3 protein = ProteinEndPos;
									protein.x -= MOVEMENT;
									Protein->GetDotween()->DoEaseInBack(protein, DOTWEEN_INTIME);
									Protein->GetDotween()->OnComplete([&]() {
										Bg->dotween->DoAlpha(0, 0.2f);
										});
									});
								});
							});
						});
				}
				});
		}
		




	}

	Bg->Update();

	Text->Update();

	Need->Update();

	Protein->Update();
}

void CGameStart::LateUpdate()
{
}

void CGameStart::Draw()
{
	Bg->Draw();

	Text->Draw();

	Need->Draw();

	Protein->Draw();
}
