#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "Theme.h"

int Player::combo = 0;
int Player::correct_num = 0;

Player::Player() :input_flg(false),/*theme_num(0), */mistake_cnt(0),cnt(0),button_flg(false), mis_img(0)//,effect(0)
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = -1;
		input_draw[i] = 0;
		mistake_flg[i] = 0;
		mis_data[i] = -1;
		player_anim[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			img[i][j] = 0;
		}
	}

	/*for (int j = 0; j < 5; j++)
	{
		mis_img[j] = 0;
	}*/

	sound[0] = 0;
	sound[1] = 0;

	for (int i = 0; i < 10; i++)
	{
		combo_img[i] = 100;
	}
}

Player::~Player()
{
	// 音データの削除
	DeleteSoundMem(sound[0]);
	DeleteSoundMem(sound[1]);

	// 画像データの削除
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			DeleteGraph(img[i][j]);
		}
	}

	/*for (int j = 0; j < 5; j++)
	{
		DeleteGraph(mis_img[j]);
	}*/

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(combo_img[i]);
	}
}

void Player::Initialize()
{
	// 画像の読み込み
	img[0][0] = LoadGraph("Resource/images/Abotton.png");
	img[0][1] = LoadGraph("Resource/images/Abotton1.png");
	img[0][2] = LoadGraph("Resource/images/Abotton2.png");
	img[0][3] = LoadGraph("Resource/images/Abotton3.png");
	img[0][4] = LoadGraph("Resource/images/Abotton4.png");


	img[1][0] = LoadGraph("Resource/images/Bbotton.png");
	img[1][1] = LoadGraph("Resource/images/Bbotton1.png");
	img[1][2] = LoadGraph("Resource/images/Bbotton2.png");
	img[1][3] = LoadGraph("Resource/images/Bbotton3.png");
	img[1][4] = LoadGraph("Resource/images/Bbotton4.png");

	img[2][0] = LoadGraph("Resource/images/Ybotton.png");
	img[2][1] = LoadGraph("Resource/images/Ybotton1.png");
	img[2][2] = LoadGraph("Resource/images/Ybotton2.png");
	img[2][3] = LoadGraph("Resource/images/Ybotton3.png");
	img[2][4] = LoadGraph("Resource/images/Ybotton4.png");

	img[3][0] = LoadGraph("Resource/images/Xbotton.png");
	img[3][1] = LoadGraph("Resource/images/Xbotton1.png");
	img[3][2] = LoadGraph("Resource/images/Xbotton2.png");
	img[3][3] = LoadGraph("Resource/images/Xbotton3.png");
	img[3][4] = LoadGraph("Resource/images/Xbotton4.png");

	/*mis_img[0] = LoadGraph("Resource/images/mistake.png");
	mis_img[1] = LoadGraph("Resource/images/mistake1.png");
	mis_img[2] = LoadGraph("Resource/images/mistake2.png");
	mis_img[3] = LoadGraph("Resource/images/mistake3.png");
	mis_img[4] = LoadGraph("Resource/images/mistake4.png");*/

	mis_img = LoadGraph("Resource/images/mistake.png");
	LoadDivGraph("Resource/images/combo.png", 10, 5, 2, 75, 75, combo_img);

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/button.mp3");
	sound[1] = LoadSoundMem("Resource/sounds/mis.mp3");

	// エラーチェック
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++) 
		{
			if (img[i][j] == -1)
			{
				throw("img[%d][%d]がありません\n", i,j);
			}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (combo_img[i] == -1)
		{
			throw("combo_img[%d]がありません\n", i);
		}
	}

	/*for (int j = 0; j < 5; j++)
	{
		if (mis_img[j] == -1)
		{
			throw("mis_img[%d]がありません\n",j);
		}
	}*/

	if (mis_img == -1)
	{
		throw("Resource/images/mistake.pngがありません\n");
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
		player_anim[i] = 4;
	}

	// 変数の初期化
	input_flg = false;
	button_flg = false;
	cnt = 0;
	combo = 0;
}

void Player::Update()
{
	// プレイヤーからの入力受付
	if (input_flg == false)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			input_flg = true;
			button_flg = true;
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);
			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 0;
					break;
				}
			}

			
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			input_flg = true;
			button_flg = true;
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);
			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 1;
					break;
				}
			}
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
		{
			input_flg = true;
			button_flg = true;
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 2;
					break;
				}
			}
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
		{
			input_flg = true;
			button_flg = true;
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 3;
					break;
				}
			}
			Comparison();
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
		for (int i = 0; i < INPUT_MAX; i++)
		{
			if (mis_data[i] != -1)
			{
				mis_data[i] = -1;
			}
		}

		input_flg = false;
		button_flg = false;
		mistake_cnt = 0;
	}

	for (int i = 0; i < INPUT_MAX; i++)
	{
		if (input[i] != -1 && input_draw[i] != 0)
		{// プレイヤーの入力とお題が同じとき
			cnt++;

			if (cnt > 1)
			{
				if (player_anim[i] > 0)
				{
					player_anim[i]--;
				}
				else
				{
					input_draw[i] = 0;
					player_anim[i] = 4;
				}

				cnt = 0;
			}
		}
	}
}

void Player::Draw()
{
#ifdef _DEBUG

#endif // _DEBUG

	// コンボ数表示
	if (combo < 10)
	{
		//DrawGraph(143, 105, combo_img[0], TRUE);
		DrawGraph(170, 105, combo_img[combo % 10], TRUE);
	}
	else if(combo < 100)
	{
		DrawGraph(143, 105, combo_img[combo / 10], TRUE);
		DrawGraph(207, 105, combo_img[combo % 10], TRUE);
	}
	else
	{
		DrawGraph(110, 105, combo_img[combo / 100], TRUE);
		DrawGraph(165, 105, combo_img[(combo - combo / 100 * 100) / 10], TRUE);
		DrawGraph(230, 105, combo_img[combo % 10], TRUE);
	}

	// プレイヤーが入力したものを表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		if (mis_data[i] != -1)
		{// プレイヤーが間違えたものを表示
			mistake_cnt++; 
			if (Theme::theme_num < 10)
			{
				DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 410, img[mis_data[i]][0], TRUE);
				DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 410, mis_img, TRUE);
			}
			else if (Theme::theme_num == 10)
			{	
				DrawGraph(90 + i * 110, 410, img[mis_data[i]][0], TRUE);
				DrawGraph(90 + i * 110, 410, mis_img, TRUE);
				input_flg = false;
				button_flg = false;
			}
			else if (Theme::theme_num >= 11 && Theme::theme_num < 16)
			{
				if (i < 8)
				{
					DrawGraph(225 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(225 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
					DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
			}
			else if (Theme::theme_num == 16)
			{
				if (i < 8)
				{
					DrawGraph(225 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(225 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
					DrawGraph(225 + (i - 8) * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph(225 + (i - 8) * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
			}
			else if (Theme::theme_num == 17)
			{
				if (i < 9)
				{
						
					DrawGraph(160 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(160 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
					DrawGraph(215 + (i - 9) * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph(215 + (i - 9) * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
			}
			else if (Theme::theme_num == 18)
			{
				if (i < 9)
				{
					DrawGraph(160 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(160 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
						
					DrawGraph(160 + (i - 9) * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph(160 + (i - 9) * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}	
			}
			else if (Theme::theme_num == 19)
			{
				if (i < 10)
				{
					DrawGraph(90 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(90 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
					DrawGraph(160 + (i - 10) * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph(160 + (i - 10) * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
			}
			else
			{
				if (i < 10)
				{
					DrawGraph(90 + i * 110, 355, img[mis_data[i]][0], TRUE);
					DrawGraph(90 + i * 110, 355, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
				else
				{
					DrawGraph(90 + (i - 10) * 110, 500, img[mis_data[i]][0], TRUE);
					DrawGraph(90 + (i - 10) * 110, 500, mis_img, TRUE);
					input_flg = false;
					button_flg = false;
				}
			}
		}
		
		if (input[i] != -1)
		{// プレイヤーの入力とお題が同じとき表示

			if (Theme::theme_num < 10)
			{
				if (input_draw[i] == 0)
				{
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 410, img[input[i]][0], TRUE);
				}
				else
				{
					DrawGraph(((500 - player_anim[i] * 28) - 57 * (Theme::theme_num - 3)) + i * 110, 410 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num == 10)
			{
				if (input_draw[i] == 0)
				{
					DrawGraph(90 + i * 110, 410, img[input[i]][0], TRUE);
				}
				else
				{
					DrawGraph((90 - player_anim[i] * 28) + i * 110, 410 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num >= 11 && Theme::theme_num < 16)
			{
				if (i < 8)
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(225 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);

					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph(((100 - player_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 16)
			{
				if (i < 8)
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(225 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(225 + (i - 8) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + (i - 8) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);

					}
				}
			}
			else if (Theme::theme_num == 17)
			{
				if (i < 9)
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(160 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(215 + (i - 9) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((215 - player_anim[i] * 28) + (i - 9) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 18)
			{
				if (i < 9)
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(160 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(160 + (i - 9) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + (i - 9) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 19)
			{
				if (i < 10)
				{
					if (input_draw[i] == 0)
					
						DrawGraph(90 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(160 + (i - 10) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + (i - 10) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
			else
			{
				if (i < 10)
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(90 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == 0)
					{
						DrawGraph(90 + (i - 10) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + (i - 10) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
	}

	//SetFontSize(30);
	/*DrawFormatString(0, 0, 0x000000, "%d", mistake_cnt);
	DrawFormatString(30, 0, 0xff0000, "%d", mis_data[0]);
	DrawFormatString(60, 0, 0xff0000, "%d", input[0]);*/

	for (int i = 0; i < INPUT_MAX; i++)
	{
		DrawFormatString(0 + i * 20, 0, 0xff0000, "%d", input[i]);
	}
}

	



void Player::Finalize()
{
}

void Player::SetPlayerAnim()
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		player_anim[i] = 0;
	}
}

void Player::ResetPlayerAnim()
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		player_anim[i] = 4;
	}
}

void Player::SetPlayerMis(int num)
{
	mis_data[num] = input[num];

	//ResetPlayerInput(num);

	ResetInputDraw(num);
}

void Player::Comparison()
{
	int tm[THEME_MAX];
	int ip[INPUT_MAX];

	tm[correct_num] = Theme::theme[correct_num];
	ip[correct_num] = input[correct_num];

	// プレイヤーの入力とお題を比較
	if (tm[correct_num] == ip[correct_num])
	{// 同じだった場合
		correct_num++;
		combo++;
		input_flg = false;
		button_flg = false;
	}
	else
	{// 異なる場合
		combo = 0;
		mis_data[correct_num] = ip[correct_num];
		input[correct_num] = -1;
		input_draw[correct_num] = -1;
	}
}