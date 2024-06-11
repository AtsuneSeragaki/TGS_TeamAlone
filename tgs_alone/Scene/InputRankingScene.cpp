#include "InputRankingScene.h"
#include "../Utility/InputControl.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "DxLib.h"

InputRankingScene::InputRankingScene():back_img(0),ranking(nullptr),level(0),combo(0),name_num(0),cursor_x(0),cursor_y(0),no_name(false)
{
	memset(name, NULL, (sizeof(char) * 15));
}

InputRankingScene::~InputRankingScene()
{
}

void InputRankingScene::Initialize()
{
	// メモリの動的確保
	ranking = new RankingData;
	ranking->Initialize();

	level = Theme::theme_num - 3;
	combo = Player::combo;

	no_name = true;
}

eSceneType InputRankingScene::Update()
{
	bool is_change = false;

	// 名前入力処理
	is_change = InputName();

	// シーン変更は可能か？
	if (is_change)
	{
		// ランキングに遷移
		return eSceneType::E_RANKING;
	}
	else
	{
		return GetNowScene();
	}
}

void InputRankingScene::Draw() const
{
	SetFontSize(25);

	const int font_size = 25;
	for (int i = 0; i < 26; i++)
	{
		int x = (i % 13) * font_size + 15;
		int y = (i / 13) * font_size + 300;
		DrawFormatString(x, y, 0xffffff, "%-3c", 'a' + i);
		y = ((i / 13) + 2) * font_size + 300;
		DrawFormatString(x, y, 0xffffff, "%-3c", 'A' + i);
	}
	DrawString(40, 405, "ok", 0xffffff);
	DrawString(40 + font_size * 2, 405, "delete", 0xffffff);

	if (cursor_y < 4)
	{
		int x = cursor_x * font_size + 10;
		int y = cursor_y * font_size + 295;
		DrawBox(x, y, x + font_size, y + font_size, 0xffffff,FALSE);
	}
	else
	{
		if (cursor_x == 0)
		{
			DrawBox(35, 400, 35 + font_size, 400 + font_size, 0xffffff, FALSE);
		}
		else
		{
			DrawBox(100, 400, 100 + font_size, 400 + font_size, 0xffffff, FALSE);
		}
	}

	if (no_name == true)
	{
		DrawString(200, 200, "no name", 0xffffff);
	}
	else
	{
		DrawFormatString(200, 200, 0xffffff, "%s", name);
	}

	DrawString(0, 500, "Y:UP A:DOWN X:LEFT B:RIGHT START:OK", 0xffffff);
}

void InputRankingScene::Finalize()
{
	// ランキングにデータを格納
	ranking->SetRankingData(level, combo, name);

	// 動的メモリの解放
	delete ranking;
}

eSceneType InputRankingScene::GetNowScene() const
{
	return eSceneType::E_INPUT_RANKING;
}

bool InputRankingScene::InputName()
{
	// カーソル操作処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		if (cursor_y == 4)
		{
			if (cursor_x == 0)
			{
				cursor_x = 1;
			}
			else
			{
				cursor_x--;
			}
		}
		else
		{
			if (cursor_x > 0)
			{
				cursor_x--;
			}
			else
			{
				cursor_x = 12;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (cursor_y == 4)
		{
			if (cursor_x == 1)
			{
				cursor_x = 0;
			}
			else
			{
				cursor_x++;
			}
		}
		else
		{
			if (cursor_x < 12)
			{
				cursor_x++;
			}
			else
			{
				cursor_x = 0;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		if (cursor_y > 0)
		{
			cursor_y--;
		}
		else
		{
			cursor_y = 4;

			if (cursor_x > 1)
			{
				cursor_x = 1;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (cursor_y < 4)
		{
			cursor_y++;

			if (cursor_y == 4 && cursor_x > 1)
			{
				cursor_x = 1;
			}
		}
		else
		{
			cursor_y = 0;
		}
	}

	// カーソル位置の文字を決定する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		if (cursor_y < 2)
		{
			if (no_name == true)
			{
				no_name = false;
			}

			name[name_num++] = 'a' + cursor_x + (cursor_y * 13);

			if (cursor_y == 4)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else if (cursor_y < 4)
		{
			if (no_name == true)
			{
				no_name = false;
			}

			name[name_num++] = 'A' + cursor_x + ((cursor_y - 2) * 13);

			if (cursor_y == 4)
			{
				cursor_x = 0;
				cursor_y = 4;
			}
		}
		else
		{
			if (cursor_x == 0)
			{
				if (name == NULL)
				{
					no_name = true;
				}
				else
				{
					name[name_num] = '\0';
					return true;
				}
			}
			else
			{
				name[name_num--] = NULL;
			}
		}
	}

	return false;
}