#include "DebugTable.h"
#include "CDirectWrite.h"
#include <string>

DebugTable::DebugTable(GridTable* _table, bool _isFloorTable)
{
	isFloorTable = _isFloorTable;
	displayTable = _table;

	mTransform.pos = { 800, 50,0 };
	if (isFloorTable)
	{
		mTransform.pos = { 800, 240,0 };
	}
}

void DebugTable::Update()
{

}

void DebugTable::Draw()
{
	std::string str;

	if (isFloorTable)
	{
		Write->SetFont(Font::marker, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Yellow));

		Write->DrawString("Å´Ç‰Ç©", DirectX::XMFLOAT2(mTransform.pos.x, mTransform.pos.y - 40), D2D1_DRAW_TEXT_OPTIONS_NONE);
		for (int i = 0; i < MAX_GRIDNUM; i++)
		{
			if (displayTable->floorTable[i][0] == 0)
			{
				break;
			}

			str.clear();

			for (int j = 0; j < MAX_GRIDNUM; j++)
			{
				str.push_back('|');

				if (displayTable->floorTable[i][j] == 0)
				{
					break;
				}

				if (displayTable->floorTable[i][j] < 10)
				{
					str.append("0");
				}

				str.append(std::to_string(displayTable->floorTable[i][j]));
			}

			Write->DrawString(str, DirectX::XMFLOAT2(mTransform.pos.x, mTransform.pos.y + i * 40), D2D1_DRAW_TEXT_OPTIONS_NONE); 
		}
	}
	else
	{
		Write->SetFont(Font::marker, nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 30, L"ja-jp", DWRITE_TEXT_ALIGNMENT_LEADING, D2D1::ColorF(D2D1::ColorF::Black));

		Write->DrawString("Å´Ç®Ç‘Ç∂Ç•Ç≠Ç∆", DirectX::XMFLOAT2(mTransform.pos.x, mTransform.pos.y - 40), D2D1_DRAW_TEXT_OPTIONS_NONE);
		for (int i = 0; i < MAX_GRIDNUM; i++)
		{
			if (displayTable->objectTable[i][0] == 0)
			{
				break;
			}

			str.clear();

			for (int j = 0; j < MAX_GRIDNUM; j++)
			{
				str.push_back('|');

				if (displayTable->objectTable[i][j] == 0)
				{
					break;
				}

				if (displayTable->objectTable[i][j] < 10)
				{
					str.append("0");
				}

				str.append(std::to_string(displayTable->objectTable[i][j]));
			}
			Write->DrawString(str, DirectX::XMFLOAT2(mTransform.pos.x, mTransform.pos.y + i * 40), D2D1_DRAW_TEXT_OPTIONS_NONE);
		}
	}
}

DebugTable::~DebugTable()
{
}
