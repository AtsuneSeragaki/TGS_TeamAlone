#include "InputRankingScene.h"
#include "../Utility/InputControl.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "DxLib.h"

InputRankingScene::InputRankingScene():back_img(0),ranking(nullptr),level(0),combo(0),name_num(0),cursor_x(0),cursor_y(0),no_name(false),font(0),bgm(0)
{
	memset(name, NULL, (sizeof(char) * 10));

	for (int i = 0; i < 7; i++)
	{
		img[i] = 0;
	}

	for (int i = 0; i < 3; i++)
	{
		se[i] = 0;
	}
}

InputRankingScene::~InputRankingScene()
{
}

void InputRankingScene::Initialize()
{
	back_img = LoadGraph("Resource/images/help/help.png");

	img[0] = LoadGraph("Resource/images/ranking/button1.png");
	img[1] = LoadGraph("Resource/images/ranking/button2.png");
	img[2] = LoadGraph("Resource/images/ranking/button3.png");
	img[3] = LoadGraph("Resource/images/ranking/input.png");
	img[4] = LoadGraph("Resource/images/ranking/noname.png");
	img[5] = LoadGraph("Resource/images/ranking/moji.png");
	img[6] = LoadGraph("Resource/images/ranking/cursor.png");

	// メモリの動的確保
	ranking = new RankingData;
	ranking->Initialize();

	level = Theme::theme_num - 3;
	combo = Player::combo;

	no_name = true;

	name_num = -1;

	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");

	font = CreateFontToHandle("Segoe UI", 70, 7, DX_FONTTYPE_ANTIALIASING);

	bgm = LoadSoundMem("Resource/sounds/title/bgm.mp3");

	

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);
}

eSceneType InputRankingScene::Update()
{
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	bool is_change = false;

	// 名前入力処理
	is_change = InputName();

	// シーン変更は可能か？
	if (is_change)
	{
		StopSoundMem(bgm);
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
	DrawGraph(0, 0, back_img, TRUE);

	DrawGraph(0, 0, img[3], TRUE);

	if (cursor_y < 3)
	{
		DrawGraph(320 + cursor_x * 73, 290 + cursor_y * 73, img[6], TRUE);
		DrawGraph(0, 0, img[0], TRUE);
	}
	else
	{
		if (cursor_x == 0)
		{
			DrawGraph(0, 0, img[1], TRUE);
		}
		else
		{
			DrawGraph(0, 0, img[2], TRUE);
		}
	}

	DrawGraph(320, 290, img[5], TRUE);

	if (no_name == true)
	{
		DrawGraph(0, 0, img[4], TRUE);
	}
	else
	{
		DrawFormatStringToHandle(600 - name_num * 20, 100, 0x000000, font, "%s", name);
	}

	//DrawFormatString(300, 100, 0xff00ff, "%d", name_num);
}

void InputRankingScene::Finalize()
{
	// ランキングにデータを格納
	ranking->SetRankingData(level, combo, name);

	DeleteFontToHandle(font);

	DeleteGraph(back_img);

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(img[i]);
	}

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
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y == 3)
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
				cursor_x = 8;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y == 3)
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
			if (cursor_x < 8)
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
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y > 0)
		{
			cursor_y--;
		}
		else
		{
			cursor_y = 3;

			if (cursor_x > 1)
			{
				cursor_x = 1;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y < 3)
		{
			cursor_y++;

			if (cursor_y == 3 && cursor_x > 1)
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
		
		if (cursor_y < 3)
		{
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

			if (name[8] == NULL)
			{
				if (no_name == true)
				{
					no_name = false;
				}

				if (cursor_y == 3 && cursor_x == 8)
				{
					name[++name_num] = '!';
				}
				else
				{
					name[++name_num] = 'A' + cursor_x + (cursor_y * 9);
				}
			}

			if (cursor_y == 3)
			{
				cursor_x = 0;
				cursor_y = 3;
			}
		}
		else if (cursor_y == 3)
		{
			if (cursor_x == 0)
			{
				PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

				if (no_name != true)
				{
					name[++name_num] = '\0';
					return true;
				}
				else
				{
					return false;
				}
			}
			else if (cursor_x == 1)
			{
				PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

				name[name_num--] = NULL;

				if (name[0] == NULL)
				{
					no_name = true;
				}
			}
		}
	}

	return false;
}