#include "CalorieGage.h"

CalorieGage::CalorieGage()
{
	mTransform.pos = {};
	mTransform.scale = Vector3::one;

	mark = new CalorieMark();
	mark->SetPosition(mTransform.pos);
	mark->SetScale(mTransform.scale);
}

CalorieGage::~CalorieGage()
{
	CLASS_DELETE(mark);
}

void CalorieGage::Update()
{
	mark->Update();
}

void CalorieGage::Draw()
{
	mark->Draw();
}

void CalorieGage::ChangePosition(const Vector3& _pos)
{
	mark->SetPosition(_pos);
}

void CalorieGage::ChangeScale(const Vector3& _scale)
{
	mark->SetScale(_scale);
}
