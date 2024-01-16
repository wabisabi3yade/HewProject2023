#pragma once

class Ckcal_gauge
{
private:
	int nKcal;	// 表示したいint型ポインタ
public:
	Ckcal_gauge();
	~Ckcal_gauge();

	void SetKcal(int kcal);
	int GetKcal();
	void Draw();
	
};

