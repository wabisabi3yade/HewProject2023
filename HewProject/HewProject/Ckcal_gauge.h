#pragma once

class Ckcal_gauge
{
private:
	int nKcal = 10;
public:
	void SetKcal(int kcal);
	int GetKcal();
	void Update();
	void Draw();
};

