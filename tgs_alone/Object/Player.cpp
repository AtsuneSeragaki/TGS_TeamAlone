#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
//#include "EffekseerForDXLib.h"

Player::Player() :input_flg(false),theme_num(0), mistake_cnt(0)//,effect(0)
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

	sound[0] = 0;
	sound[1] = 0;
}

Player::~Player()
{
	//DeleteEffekseerEffect(effect);
	DeleteSoundMem(sound[0]);
	DeleteSoundMem(sound[1]);
	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(img[i]);
	}
}

void Player::Initialize()
{
	// 画像の読み込み
	img[0] = LoadGraph("Resource/images/Abotton.png");
	img[1] = LoadGraph("Resource/images/Bbotton.png");
	img[2] = LoadGraph("Resource/images/Ybotton.png");
	img[3] = LoadGraph("Resource/images/Xbotton.png");
	img[4] = LoadGraph("Resource/images/mistake2.png");

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/button.mp3");
	sound[1] = LoadSoundMem("Resource/sounds/mis.mp3");

	// エラーチェック
	if (img[0] == -1)
	{
		throw("Resource/images/Abotton.pngがありません\n");
	}
	if (img[1] == -1)
	{
		throw("Resource/images/Bbotton.pngがありません\n");
	}
	if (img[2] == -1)
	{
		throw("Resource/images/Ybotton.pngがありません\n");
	}
	if (img[3] == -1)
	{
		throw("Resource/images/Xbotton.pngがありません\n");
	}
	if (img[4] == -1)
	{
		throw("Resource/images/mistake2.pngがありません\n");
	}
	if (sound[0] == -1)
	{
		throw("Resource/sounds/Button.mp3がありません\n");
	}
	if (sound[1] == -1)
	{
		throw("Resource/sounds/Miss.mp3がありません\n");
	}

	// プレイヤーの入力データの初期化
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = -1;
		input_draw[i] = -1;
	}

	input_flg = false;

	theme_num = 0;

	// Zバッファを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	//SetUseZBuffer3D(TRUE);

	// Zバッファへの書き込みを有効にする。
	// Effekseerを使用する場合、2DゲームでもZバッファを使用する。
	//SetWriteZBuffer3D(TRUE);

	//effect = "Resources/Effect/Effect.efk";
}

void Player::Update()
{
	/*mEffect = PlayEffekseer2DEffect(mEffectHndle);

	SetPosPlayingEffekseer2DEffect(mEffect, PosX, PosY, 0);

	UpdateEffekseer2D();*/

	// プレイヤーからの入力受付
	if (input_flg == false)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			input_flg = true;
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);
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
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);
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
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

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
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

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

	// プレイヤーが間違えた時
	if (mistake_cnt == 1)
	{
		PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
	}

	// プレイヤーが間違えた時
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

	//DrawEffekseer2D();

	// プレイヤーが入力したものを表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		if (mis_data[i] != -1)
		{// プレイヤーが間違えたものを表示
			mistake_cnt++;


			if (theme_num <= 10)
			{
				DrawGraph((500 - 57 * (theme_num - 3)) + i * 110, 300, img[mis_data[i]], TRUE);
				DrawGraph((500 - 57 * (theme_num - 3)) + i * 110, 300, img[4], TRUE);
				/*DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[mis_data[i]], TRUE);
				DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[4], TRUE);*/
			}
			else if (theme_num >= 11)
			{
				if (i < 8)
				{
					DrawGraph(225 + i * 110, 250, img[mis_data[i]], TRUE);
					DrawGraph(225 + i * 110, 250, img[4], TRUE);

					/*DrawGraph(300 + i * 90, 490, img[mis_data[i]], TRUE);
					DrawGraph(300 + i * 90, 490, img[4], TRUE);*/
				}
				else
				{
					DrawGraph((100 - 54 * (theme_num - 2)) + i * 110, 390, img[mis_data[i]], TRUE);
					DrawGraph((100 - 54 * (theme_num - 2)) + i * 110, 390, img[4], TRUE);


					/*DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[mis_data[i]], TRUE);
					DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[4], TRUE);*/
				}
			}

			/*if (mistake_cnt > 10)
			{
				DrawGraph((540 - 50 * (theme_num - 3) + i * 90), 500, img[4], TRUE);
			}	*/
		}
		
		if (input[i] != -1)
		{// プレイヤーの入力とお題が同じとき表示

			/*DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[input[i]], TRUE);
			input_draw[i] = 0;*/

			if (theme_num <= 10)
			{
				DrawGraph((500 - 57 * (theme_num - 3)) + i * 110, 300, img[input[i]], TRUE);
				//DrawGraph((540 - 50 * (theme_num - 3)) + i * 90, 500, img[input[i]], TRUE);
				input_draw[i] = 0;
			}
			else if (theme_num >= 11)
			{
				
				if (i < 8)
				{
					DrawGraph(225 + i * 110, 250, img[input[i]], TRUE);

					//DrawGraph(300 + i * 90, 490, img[input[i]], TRUE);
					input_draw[i] = 0;
				}
				else
				{
					DrawGraph((100 - 54 * (theme_num - 2)) + i * 110, 390, img[input[i]], TRUE);

					//DrawGraph((320 - 54 * (theme_num - 2)) + i * 90, 590, img[input[i]], TRUE);
					input_draw[i] = 0;
				}
				
			}
		}
	}
}

void Player::Finalize()
{
}