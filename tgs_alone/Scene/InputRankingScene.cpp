#include "InputRankingScene.h"
#include "../Utility/InputControl.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "DxLib.h"

InputRankingScene::InputRankingScene():back_img(0),ranking(nullptr),level(0),combo(0),name_num(0),cursor_x(0),cursor_y(0)
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
		if (cursor_x > 0)
		{
			cursor_x--;
		}
		else
		{
			cursor_x = 12;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
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
	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		if (cursor_y > 0)
		{
			cursor_y--;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (cursor_y < 4)
		{
			cursor_y++;

			if (cursor_y == 4)
			{
				cursor_y = 0;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (cursor_y < 4)
		{
			cursor_y++;

			if (cursor_y == 4)
			{
				cursor_y = 0;
			}
		}
	}

	// カーソル位置の文字を決定する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (cursor_y < 4)
		{
			cursor_y++;

			if (cursor_y == 4)
			{
				cursor_y = 0;
			}
		}
	}

	return false;
}