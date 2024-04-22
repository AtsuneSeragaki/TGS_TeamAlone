#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Player::Player() : sound(0),input_flg(false),theme_num(0), mistake_cnt(0)
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = -1;
		input_draw[i] = 0;
		mistake_flg[i] = 0;
		mis_data[i] = -1;
	}

	for (int i = 0; i < 5; i++)
	{
		img[i] = 0;
	}
}

Player::~Player()
{
}

void Player::Initialize()
{
	// 画像の読み込み
	img[0] = LoadGraph("Resource/images/Abotton2.png");
	img[1] = LoadGraph("Resource/images/Bbotton2.png");
	img[2] = LoadGraph("Resource/images/Ybotton2.png");
	img[3] = LoadGraph("Resource/images/Xbotton2.png");
	img[4] = LoadGraph("Resource/images/mistake.png");

	// プレイヤーの入力データの初期化
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = -1;
		input_draw[i] = -1;
	}

	input_flg = false;

	theme_num = 0;
}

void Player::Update()
{
	if (input_flg == false)
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
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
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
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
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
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
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

	if (mistake_cnt > 20)
	{
		mistake_cnt = 0;
		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (mis_data[i] != -1)
			{
				mis_data[i] = -1;
			}	
		}
		input_flg = false;

	}
	
}

void Player::Draw()
{
#ifdef _DEBUG

#endif // _DEBUG

	// プレイヤーが入力したものを表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		if (mis_data[i] != -1)
		{
			mistake_cnt++;

			DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[mis_data[i]], TRUE);
			DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[4], TRUE);
			/*if (mistake_cnt > 10)
			{
				DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[4], TRUE);
			}	*/
		}
		else if (input[i] != -1)
		{
			DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[input[i]], TRUE);
			input_draw[i] = 0;
		}
	}
	
}

void Player::Finalize()
{
}