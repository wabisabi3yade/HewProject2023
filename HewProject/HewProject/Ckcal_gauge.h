#pragma once

class Ckcal_gauge
{
private:
	int nKcal;	// �\��������int�^�|�C���^
public:
	Ckcal_gauge();
	~Ckcal_gauge();

	void SetKcal(int kcal);
	int GetKcal();
	void Draw();
	
};

