#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : sound(0),input{-1},input_flg(false)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	// プレイヤーの入力データの初期化
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = -1;
	}

	input_flg = false;
}

void Player::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		input_flg = true;
		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (input[i] == -1)
			{
				input[i] = 0;
				break;
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		input_flg = true;
		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (input[i] == -1)
			{
				input[i] = 1;
				break;
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{
		input_flg = true;
		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (input[i] == -1)
			{
				input[i] = 2;
				break;
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		input_flg = true;

		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (input[i] == -1)
			{
				input[i] = 3;
				break;
			}
		}
	}
}

void Player::Draw()
{
#ifdef _DEBUG

	// お題表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		//DrawGraph(100 + i * 20, 300, theme_img[theme[i]], TRUE);
		SetFontSize(20);
		DrawFormatString(0 + i * 30, 500, 0xffffff, "%d", input[i]);
	}

#endif // _DEBUG

	// お題表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		//DrawGraph(100 + i * 20, 300, theme_img[theme[i]], TRUE);
		SetFontSize(20);
		DrawFormatString(0 + i * 30, 500, 0xffffff, "%d", input[i]);
	}
}

void Player::Finalize()
{
}