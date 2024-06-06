#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "Theme.h"

int Player::combo = 0;
int Player::correct_num = 0;

Player::Player() :input_flg(false), mistake_cnt(0), cnt(0), button_flg(false)
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		input[i] = 0;
		input_draw[i] = false;
		mistake_flg[i] = 0;
		mis_data[i] = -1;
		player_anim[i] = 0;
		mis_anim[i] = 0;
		correct[i] = -1;
		com_cnt[i] = 0;
		mcom_cnt[i] = 0;
		mis_draw[i] = false;
		mis_anim2[i] = 0;
		mis_y[i] = 0;
		effect[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			img[i][j] = 0;
		}

		mis_img[i] = 0;
	}

	sound[0] = 0;
	sound[1] = 0;

	comment[0] = 0;
	comment[1] = 0;

	effect_img[0] = 0;
	effect_img[1] = 0;

	for (int i = 0; i < 10; i++)
	{
		combo_img[i] = 0;
	}
}

Player::~Player()
{
}

void Player::Initialize()
{
	// 画像の読み込み
	img[0][0] = LoadGraph("Resource/images/Abotton0.png");
	img[0][1] = LoadGraph("Resource/images/Abotton5.png");
	img[0][2] = LoadGraph("Resource/images/Abotton6.png");
	img[0][3] = LoadGraph("Resource/images/Abotton7.png");
	img[0][4] = LoadGraph("Resource/images/Abotton8.png");


	img[1][0] = LoadGraph("Resource/images/Bbotton0.png");
	img[1][1] = LoadGraph("Resource/images/Bbotton5.png");
	img[1][2] = LoadGraph("Resource/images/Bbotton6.png");
	img[1][3] = LoadGraph("Resource/images/Bbotton7.png");
	img[1][4] = LoadGraph("Resource/images/Bbotton8.png");

	img[2][0] = LoadGraph("Resource/images/Ybotton0.png");
	img[2][1] = LoadGraph("Resource/images/Ybotton5.png");
	img[2][2] = LoadGraph("Resource/images/Ybotton6.png");
	img[2][3] = LoadGraph("Resource/images/Ybotton7.png");
	img[2][4] = LoadGraph("Resource/images/Ybotton8.png");

	img[3][0] = LoadGraph("Resource/images/Xbotton0.png");
	img[3][1] = LoadGraph("Resource/images/Xbotton5.png");
	img[3][2] = LoadGraph("Resource/images/Xbotton6.png");
	img[3][3] = LoadGraph("Resource/images/Xbotton7.png");
	img[3][4] = LoadGraph("Resource/images/Xbotton8.png");

	mis_img[0] = LoadGraph("Resource/images/misbuttonA.png");
	mis_img[1] = LoadGraph("Resource/images/misbuttonB.png");
	mis_img[2] = LoadGraph("Resource/images/misbuttonY.png");
	mis_img[3] = LoadGraph("Resource/images/misbuttonX.png");

	LoadDivGraph("Resource/images/combo.png", 10, 5, 2, 75, 75, combo_img);

	comment[0] = LoadGraph("Resource/images/great.png");
	comment[1] = LoadGraph("Resource/images/bad.png");

	effect_img[0] = LoadGraph("Resource/images/effect3.png");
	effect_img[1] = LoadGraph("Resource/images/effect4.png");

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
		input_draw[i] = false;
		mis_data[i] = -1;
		correct[i] = -1;
		player_anim[i] = 4;
		mis_anim[i] = 4;
		mistake_flg[i] = 0;
		com_cnt[i] = 0;
		mcom_cnt[i] = 0;
		mis_draw[i] = false;
		mis_anim2[i] = 0;
		mis_y[i] = -1;
		effect[i] = -1;
	}

	// 変数の初期化
	input_flg = false;
	button_flg = false;
	mistake_cnt = 0;
	cnt = 0;
	combo = 0;
	correct_num = 0;
}

void Player::Update()
{
	// プレイヤーからの入力受付
	if (input_flg == false)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A) == true)
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

			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_B) == true)
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

			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y) == true)
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

			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_X) == true)
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

			Comparison();
		}
	}
	else
	{
		if (correct[correct_num] != -1 && input_draw[correct_num] == false)
		{// プレイヤーの入力とお題が同じとき
			cnt++;

			if (cnt != 0)
			{
				if (player_anim[correct_num] > 0)
				{
					player_anim[correct_num]--;
				}
				else
				{
					com_cnt[correct_num]++;
					input_draw[correct_num] = true;
					player_anim[correct_num] = 4;
					correct_num++;
					input_flg = false;
					
				}

				cnt = 0;
			}
		}

		if (mis_data[correct_num] != -1 && mis_draw[correct_num] == false)
		{// プレイヤーが間違えた時
			mistake_cnt++;

			if (mistake_cnt != 0)
			{
				if (mis_anim[correct_num] > 0)
				{
					mis_anim[correct_num]--;
				}
				else
				{
					mcom_cnt[correct_num]++;
					mis_draw[correct_num] = true;
				}

				mistake_cnt = 0;
			}
		}

		if (mcom_cnt[correct_num] != 0)
		{
			SetMisCom();
		}

		if (mis_anim2[correct_num] != 0)
		{
			FallAnim();
		}
	}

	SetCom();
}

void Player::Draw()
{
	// コンボ数表示
	if (combo < 10)
	{
		DrawGraph(170, 105, combo_img[combo % 10], TRUE);
	}
	else if (combo < 100)
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
		{// プレイヤーの入力とお題が同じとき表示

			if (Theme::theme_num < 10)
			{
				if (mis_draw[i] == true)
				{
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110 + 15, 370, comment[1], TRUE);
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i], mis_img[mis_data[i]], TRUE);
				}
				else
				{
					DrawGraph(((500 - mis_anim[i] * 28) - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num == 10)
			{
				if (mis_draw[i] == true)
				{
					DrawGraph(90 + i * 110 + 15, 370, comment[1], TRUE);
					DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
				}
				else
				{
					DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num >= 11 && Theme::theme_num < 16)
			{

				if (i < 8)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110 + 15, 460, comment[1], TRUE);
						DrawGraph(((100 - mis_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph(((100 - mis_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 16)
			{
				if (i < 8)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + (i - 8) * 110 + 15, 460, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + (i - 8) * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + (i - 8) * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 17)
			{
				if (i < 9)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(215 + (i - 9) * 110 + 15, 460, comment[1], TRUE);
						DrawGraph((215 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((215 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 18)
			{
				if (i < 9)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}					
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + (i - 9) * 110 + 15, 460, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 19)
			{
				if (i < 10)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + (i - 10) * 110 + 15, 460, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else
			{
				if (i < 10)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + i * 110 + 15, 315, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + (i - 10) * 110 + 15, 460, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
		}
		
		if (correct[i] != -1)
		{
			if (Theme::theme_num < 10)
			{
				if (input_draw[i] == true)
				{
					if (com_cnt[i] != 0)
					{
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 370, comment[0], TRUE);
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110 - 13, 410 -10, effect_img[effect[i]], TRUE);
					}
					
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 410, img[correct[i]][0], TRUE);
				}
				else
				{
					DrawGraph(((500 - player_anim[i] * 28) - 57 * (Theme::theme_num - 3)) + i * 110, 410 - player_anim[i] * 23, img[correct[i]][player_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num == 10)
			{
				if (input_draw[i] == true)
				{
					if (com_cnt[i] != 0)
					{
						DrawGraph(90 + i * 110, 370, comment[0], TRUE);
						DrawGraph(90 + i * 110 - 13, 410 - 10, effect_img[effect[i]], TRUE);
					}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(225 + i * 110, 315, comment[0], TRUE);
							DrawGraph(225 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(225 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);

					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 460, comment[0], TRUE);
							DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(225 + i * 110, 315, comment[0], TRUE);
							DrawGraph(225 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(225 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(225 + (i - 8) * 110, 460, comment[0], TRUE);
							DrawGraph(225 + (i - 8) * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + i * 110, 315, comment[0], TRUE);
							DrawGraph(160 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(215 + (i - 9) * 110, 460, comment[0], TRUE);
							DrawGraph(215 + (i - 9) * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + i * 110, 315, comment[0], TRUE);
							DrawGraph(160 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + (i - 9) * 110, 460, comment[0], TRUE);
							DrawGraph(160 + (i - 9) * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(90 + i * 110, 315, comment[0], TRUE);
							DrawGraph(90 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + (i - 10) * 110, 460, comment[0], TRUE);
							DrawGraph(160 + (i - 10) * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

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
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(90 + i * 110, 315, comment[0], TRUE);
							DrawGraph(90 + i * 110 - 13, 355 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + i * 110, 355, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(90 + (i - 10) * 110, 460, comment[0], TRUE);
							DrawGraph(90 + (i - 10) * 110 - 13, 500 - 10, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + (i - 10) * 110, 500, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + (i - 10) * 110, 500 - player_anim[i] * 23, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
		}

		SetFontSize(30);
		DrawFormatString(0 + i * 20, 0, 0x000000, "%d", correct[i]);
		//DrawFormatString(0 + i * 20, 60, 0xff0000, "%d", com_cnt[i]);
	}

   DrawFormatString(0, 30, 0x000000, "%d", correct_num);

	
	//DrawFormatString(0, 30, 0xff0000, "%d", input_flg);
}

void Player::Finalize()
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

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(combo_img[i]);
	}
}

void Player::SetPlayerAnim()
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		player_anim[i] = 0;
	}
}

void Player::SetMisY()
{
	if (Theme::theme_num <= 10)
	{
		mis_y[correct_num] = 410;
	}
	else if (Theme::theme_num <= 16)
	{
		if (correct_num < 8)
		{
			mis_y[correct_num] = 355;
		}
		else
		{
			mis_y[correct_num] = 500;
		}
	}
	else if (Theme::theme_num <= 18)
	{
		if (correct_num < 9)
		{
			mis_y[correct_num] = 355;
		}
		else
		{
			mis_y[correct_num] = 500;
		}
	}
	else
	{
		if (correct_num < 10)
		{
			mis_y[correct_num] = 355;
		}
		else
		{
			mis_y[correct_num] = 500;
		}
	}
}

void Player::Comparison()
{
	int tm = -1;
	int ip = -1;

	tm = Theme::theme[correct_num];
	ip = input[correct_num];

	// プレイヤーの入力とお題を比較
	if (tm == ip)
	{// 同じだった場合
		correct[correct_num] = ip;
		input_draw[correct_num] = false;
		combo++;
	}
	else
	{// 異なる場合
		PlaySoundMem(sound[1], DX_PLAYTYPE_BACK, TRUE);
		combo = 0;
		mis_data[correct_num] = ip;
		mis_draw[correct_num] = false;
		SetMisY();
		input[correct_num] = -1;
	}
}

void Player::SetMisCom()
{
	mcom_cnt[correct_num]++;

	if (mcom_cnt[correct_num] == 20)
	{
		mis_anim2[correct_num]++;
	}
}

void Player::SetCom()
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		if (com_cnt[i] > 20)
		{
			com_cnt[i] = 0;
		}
		else if (com_cnt[i] > 0)
		{
			com_cnt[i]++;

			if (effect[i] == -1)
			{
				effect[i] = 0;
			}
			else if (com_cnt[i] == 11)
			{
				effect[i] = 1;
			}
		}
	}
}

void Player::FallAnim()
{
	if (mis_y[correct_num] <= 730)
	{
		mis_y[correct_num] += 35;
	}
	else
	{
		mis_data[correct_num] = -1;
		mis_anim2[correct_num] = 0;
		mis_anim[correct_num] = 4;
		mcom_cnt[correct_num] = 0;
		input_flg = false;
	}
}

void Player::ResetPlayerState()
{
	for (int i = 0; i < INPUT_MAX; i++)
	{
		correct[i] = -1;
		input[i] = -1;
		mis_data[i] = -1;
		input_draw[i] = false;
		player_anim[i] = 4;
		effect[i] = -1;
	}

	correct_num = 0;
}