#include "Ckcal_gauge.h"
#include "CScene.h"

Ckcal_gauge::Ckcal_gauge()
{
	nKcal = 0;
}

void Ckcal_gauge::SetKcal(int kcal)
{
	nKcal = kcal;
}

int Ckcal_gauge::GetKcal()
{
	return nKcal;
}

void Ckcal_gauge::Draw()
{
	
}



Ckcal_gauge::~Ckcal_gauge()
{
}
