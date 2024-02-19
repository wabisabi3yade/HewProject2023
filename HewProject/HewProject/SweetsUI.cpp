#include "SweetsUI.h"

SweetsUI::SweetsUI(D3DBUFFER _sweetsBuffer, D3DTEXTURE _sweetsTex)
{
	Sweets = new UI(_sweetsBuffer, _sweetsTex);
	Sweets->MakeDotween();

	Sweets->materialDiffuse = { 1,1,1,1 };

	pos = -6.0f;
	speed = 10.0f;

	vCopy = Vector3::zero;
	isResporn = false;
	isON = false;

	SetPosition(Vector3::zero);
	SetScale(Vector3::one);
	SetRotation(Vector3::zero);
	SetRotateZ(0);
	SetPosSpeed(0,0);
}

SweetsUI::~SweetsUI()
{
	CLASS_DELETE(Sweets);
}

void SweetsUI::Update()
{
	if (isON == false)
	{
		isON = true;
		Sweets->dotween->DoMoveY(pos, speed);
		Sweets->dotween->OnComplete([&]() {
			isON = false;
			isResporn = true;
			});
	}
	
	Sweets->Update();
}

void SweetsUI::Draw()
{
	Sweets->Draw();
}

void SweetsUI::SetScale(const Vector3& _scale)
{
	Sweets->mTransform.scale = { _scale };
}

void SweetsUI::SetPosition(const Vector3& _position)
{
	Sweets->mTransform.pos = { _position };
}

void SweetsUI::SetRotation(const Vector3& _rotation)
{
	Sweets->mTransform.rotation = { _rotation };
}

void SweetsUI::SetPosSpeed(const float _pos, const float _speed)
{
	pos = _pos;
	speed = _speed;
}

void SweetsUI::SetRotateZ(const float rotatez)
{
	Sweets->mTransform.rotation.z += rotatez;
}

void SweetsUI::SetTexture(const D3DTEXTURE _tex)
{
	Sweets->SetTexture(_tex);
}
