#include "CLoadStage.h"


LoadData CLoadStage::LoadStage(const wchar_t* filePath)
{
	LoadData LoadDataWork;
	std::ifstream ifs(filePath);

	int countY = 0;
	int countX = 0;
	int i = 0;
	int j = 0;
	if (ifs) { //読み込みに成功したかチェック
		std::string str;
		while (getline(ifs, str)) { //1 行ずつ読み込み
			std::istringstream iss(str);

			while (getline(iss, str, ','))
			{
				if (std::stoi(str) == -1  )
				{
					if (countX == 0)
					{
						countX = i;
					}
					i = 0;
					j = 0;
					break;
				}

				if ( j % MAX_GRIDNUM  == 0 || std::stoi(str) == -1)
					if(j != 0 )
					i = 0;

				switch (j / MAX_GRIDNUM)
				{
				case 0:
					LoadDataWork.oneFloor.floorTable[countY][i] = std::stoi(str);
					break;
				case 1:
					LoadDataWork.secondFloor.floorTable[countY][i] = std::stoi(str);
					break;
				case 2:
					LoadDataWork.thirdFloor.floorTable[countY][i] = std::stoi(str);
					break;
				case 3:
					break;
					j = 0;
				default:
					break;
				}
				if (std::stoi(str) != 0 )
				{
					i++;
				}
				j++;			}
					countY++;
		}
		ifs.close(); //ファイルを閉じる
	}
	// 行と列の数を求める
	LoadDataWork.numY = countY;
	LoadDataWork.numX = countX;

	return LoadDataWork;
}
