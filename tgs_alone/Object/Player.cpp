#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "Theme.h"

int Player::combo = 0;
int Player::correct_num = 0;
int Player::mis_num = 0;
int Player::all_mis = 0;

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
	/*img[0][0] = LoadGraph("Resource/images/main/button/Abotton0.png");
	img[0][1] = LoadGraph("Resource/images/main/button/Abotton5.png");
	img[0][2] = LoadGraph("Resource/images/main/button/Abotton6.png");
	img[0][3] = LoadGraph("Resource/images/main/button/Abotton7.png");
	img[0][4] = LoadGraph("Resource/images/main/button/Abotton8.png");

	img[1][0] = LoadGraph("Resource/images/main/button/Bbotton0.png");
	img[1][1] = LoadGraph("Resource/images/main/button/Bbotton5.png");
	img[1][2] = LoadGraph("Resource/images/main/button/Bbotton6.png");
	img[1][3] = LoadGraph("Resource/images/main/button/Bbotton7.png");
	img[1][4] = LoadGraph("Resource/images/main/button/Bbotton8.png");

	img[2][0] = LoadGraph("Resource/images/main/button/Ybotton0.png");
	img[2][1] = LoadGraph("Resource/images/main/button/Ybotton5.png");
	img[2][2] = LoadGraph("Resource/images/main/button/Ybotton6.png");
	img[2][3] = LoadGraph("Resource/images/main/button/Ybotton7.png");
	img[2][4] = LoadGraph("Resource/images/main/button/Ybotton8.png");

	img[3][0] = LoadGraph("Resource/images/main/button/Xbotton0.png");
	img[3][1] = LoadGraph("Resource/images/main/button/Xbotton5.png");
	img[3][2] = LoadGraph("Resource/images/main/button/Xbotton6.png");
	img[3][3] = LoadGraph("Resource/images/main/button/Xbotton7.png");
	img[3][4] = LoadGraph("Resource/images/main/button/Xbotton8.png");*/

	img[0][0] = LoadGraph("Resource/images/main/button/a1.png");
	img[0][1] = LoadGraph("Resource/images/main/button/a2.png");
	img[0][2] = LoadGraph("Resource/images/main/button/a3.png");
	img[0][3] = LoadGraph("Resource/images/main/button/a4.png");
	img[0][4] = LoadGraph("Resource/images/main/button/a5.png");


	img[1][0] = LoadGraph("Resource/images/main/button/b1.png");
	img[1][1] = LoadGraph("Resource/images/main/button/b2.png");
	img[1][2] = LoadGraph("Resource/images/main/button/b3.png");
	img[1][3] = LoadGraph("Resource/images/main/button/b4.png");
	img[1][4] = LoadGraph("Resource/images/main/button/b5.png");

	img[2][0] = LoadGraph("Resource/images/main/button/y1.png");
	img[2][1] = LoadGraph("Resource/images/main/button/y2.png");
	img[2][2] = LoadGraph("Resource/images/main/button/y3.png");
	img[2][3] = LoadGraph("Resource/images/main/button/y4.png");
	img[2][4] = LoadGraph("Resource/images/main/button/y5.png");

	img[3][0] = LoadGraph("Resource/images/main/button/x1.png");
	img[3][1] = LoadGraph("Resource/images/main/button/x2.png");
	img[3][2] = LoadGraph("Resource/images/main/button/x3.png");
	img[3][3] = LoadGraph("Resource/images/main/button/x4.png");
	img[3][4] = LoadGraph("Resource/images/main/button/x5.png");

	/*mis_img[0] = LoadGraph("Resource/images/main/button/misbuttonA.png");
	mis_img[1] = LoadGraph("Resource/images/main/button/misbuttonB.png");
	mis_img[2] = LoadGraph("Resource/images/main/button/misbuttonY.png");
	mis_img[3] = LoadGraph("Resource/images/main/button/misbuttonX.png");*/

	mis_img[0] = LoadGraph("Resource/images/main/button/misa.png");
	mis_img[1] = LoadGraph("Resource/images/main/button/misb.png");
	mis_img[2] = LoadGraph("Resource/images/main/button/misy.png");
	mis_img[3] = LoadGraph("Resource/images/main/button/misx.png");

	LoadDivGraph("Resource/images/ranking/rank_num1.png", 10, 5, 2, 50, 50, combo_img);

	comment[0] = LoadGraph("Resource/images/main/string/great.png");
	comment[1] = LoadGraph("Resource/images/main/string/bad.png");

	effect_img[0] = LoadGraph("Resource/images/main/effect/effect3.png");
	effect_img[1] = LoadGraph("Resource/images/main/effect/effect4.png");

	// サウンド読み込み
	sound[0] = LoadSoundMem("Resource/sounds/main/se/button.mp3");
	sound[1] = LoadSoundMem("Resource/sounds/main/se/mis.mp3");

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

	for (int i = 0; i < 4; i++)
	{
		if (mis_img[i] == -1)
		{
			throw("mis_img[%d]がありません\n", i);
		}
	}

	if (comment[0] == -1)
	{
		throw("Resource/images/main/string/great.pngがありません\n");
	}
	if (comment[1] == -1)
	{
		throw("Resource/images/main/string/bad.pngがありません\n");
	}
	if (effect_img[0] == -1)
	{
		throw("Resource/images/main/effect/effect3.pngがありません\n");
	}
	if (effect_img[1] == -1)
	{
		throw("Resource/images/main/effect/effect4.pngがありません\n");
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
	mis_num = 0;
	all_mis = 0;
}

void Player::Update()
{
	// プレイヤーからの入力受付
	if (input_flg == false)
	{
		if (InputControl::GetButtonDown(XINPUT_BUTTON_A) == true)
		{// Aボタンが押されたら

			input_flg = true;

			// 効果音の再生
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 0;
					break;
				}
			}

			// プレイヤーの入力とお題を判定
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_B) == true)
		{// Bボタンが押されたら

			input_flg = true;

			// 効果音の再生
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 1;
					break;
				}
			}

			// プレイヤーの入力とお題を判定
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y) == true)
		{// Yボタンが押されたら

			input_flg = true;

			// 効果音の再生
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 2;
					break;
				}
			}

			// プレイヤーの入力とお題を判定
			Comparison();
		}
		else if (InputControl::GetButtonDown(XINPUT_BUTTON_X) == true)
		{// Xボタンが押されたら

			input_flg = true;

			// 効果音の再生
			PlaySoundMem(sound[0], DX_PLAYTYPE_BACK, TRUE);

			for (int i = 0; i < INPUT_MAX; i++)
			{
				if (input[i] == -1)
				{
					input[i] = 3;
					break;
				}
			}

			// プレイヤーの入力とお題を判定
			Comparison();
		}
	}
	else
	{
		if (correct[correct_num] != -1 && input_draw[correct_num] == false)
		{// プレイヤーの入力とお題が同じとき、アニメーションを再生

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
		{// プレイヤーが間違えた時、アニメーションを再生
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

		// 間違えた時のコメント処理
		if (mcom_cnt[correct_num] != 0)
		{
			SetMisCom();
		}

		// 間違えた時のアニメーション処理
		if (mis_anim2[correct_num] != 0)
		{
			FallAnim();
		}
	}

	// コメントの更新処理
	SetCom();
}

void Player::Draw()
{
	// コンボ数表示
	if (combo < 10)
	{
		DrawGraph(325 + 12, 90, combo_img[combo % 10], TRUE);
	}
	else if (combo >= 10 && combo < 20)
	{
		DrawGraph(300 + 8, 90, combo_img[combo / 10], TRUE);
		DrawGraph(343 + 8, 90, combo_img[combo % 10], TRUE);
	}
	else if (combo < 100)
	{
		DrawGraph(300 + 16, 90, combo_img[combo / 10], TRUE);
		DrawGraph(343 + 16, 90, combo_img[combo % 10], TRUE);
	}
	else if(combo >= 100 && combo < 200)
	{
		DrawGraph(278 + 10, 90, combo_img[combo / 100], TRUE);
		DrawGraph(320 + 10, 90, combo_img[(combo - combo / 100 * 100) / 10], TRUE);
		DrawGraph(364 + 10, 90, combo_img[combo % 10], TRUE);
	}
	else
	{
		DrawGraph(278 + 15, 90, combo_img[combo / 100], TRUE);
		DrawGraph(320 + 15, 90, combo_img[(combo - combo / 100 * 100) / 10], TRUE);
		DrawGraph(364 + 15, 90, combo_img[combo % 10], TRUE);
	}

	// 間違えた数の表示
	if (all_mis < 10)
	{
		DrawGraph(500 + 33, 90, combo_img[all_mis % 10], TRUE);
	}
	else if (all_mis >= 10 && all_mis < 20)
	{
		DrawGraph(475 + 30, 90, combo_img[all_mis / 10], TRUE);
		DrawGraph(518 + 30, 90, combo_img[all_mis % 10], TRUE);
	}
	else if (all_mis < 100)
	{
		DrawGraph(475 + 38, 90, combo_img[all_mis / 10], TRUE);
		DrawGraph(518 + 38, 90, combo_img[all_mis % 10], TRUE);
	}
	else if (all_mis >= 100 && all_mis < 200)
	{
		DrawGraph(453 + 32, 90, combo_img[all_mis / 100], TRUE);
		DrawGraph(495 + 32, 90, combo_img[(all_mis - all_mis / 100 * 100) / 10], TRUE);
		DrawGraph(539 + 32, 90, combo_img[all_mis % 10], TRUE);
	}
	else
	{
		DrawGraph(453 + 37, 90, combo_img[all_mis / 100], TRUE);
		DrawGraph(495 + 37, 90, combo_img[(all_mis - all_mis / 100 * 100) / 10], TRUE);
		DrawGraph(539 + 37, 90, combo_img[all_mis % 10], TRUE);
	}

	// コンボ数の表示
	//SetFontSize(75);
	//DrawFormatString(325, 85, 0x000000, "%d", combo);

	// 間違えた数の表示
	//SetFontSize(75);
	//DrawFormatString(500, 85, 0x000000, "%d", all_mis);

	// プレイヤーが入力したものを表示
	for (int i = 0; i < INPUT_MAX; i++)
	{
		// 間違えた時
		if (mis_data[i] != -1)
		{// プレイヤーの入力とお題が同じとき表示

			if (Theme::theme_num < 10)
			{
				if (mis_draw[i] == true)
				{
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110 + 15, 370 - 30, comment[1], TRUE);
					//DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i], mis_img[mis_data[i]], TRUE);

					if (mis_y[i] > 410)
					{
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i] - 30, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i] - 30, img[mis_data[i]][0], TRUE);
					}
				}
				else
				{
					DrawGraph(((500 - mis_anim[i] * 28) - 57 * (Theme::theme_num - 3)) + i * 110, mis_y[i] - mis_anim[i] * 23 - 30, img[mis_data[i]][mis_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num == 10)
			{
				if (mis_draw[i] == true)
				{
					DrawGraph(90 + i * 110 + 15, 370 - 30, comment[1], TRUE);
					DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 30, mis_img[mis_data[i]], TRUE);
				}
				else
				{
					DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 30, img[mis_data[i]][mis_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num >= 11 && Theme::theme_num < 16)
			{

				if (i < 8)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph(((100 - mis_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph(((100 - mis_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 16)
			{
				if (i < 8)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(225 + (i - 8) * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph((225 - mis_anim[i] * 28) + (i - 8) * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((225 - mis_anim[i] * 28) + (i - 8) * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 17)
			{
				if (i < 9)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(215 + (i - 9) * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph((215 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((215 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 18)
			{
				if (i < 9)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}					
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + (i - 9) * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + (i - 9) * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else if (Theme::theme_num == 19)
			{
				if (i < 10)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(160 + (i - 10) * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph((160 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((160 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
			else
			{
				if (i < 10)
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + i * 110 + 15, 315 - 20, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + i * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
				else
				{
					if (mis_draw[i] == true)
					{
						DrawGraph(90 + (i - 10) * 110 + 15, 460 - 20, comment[1], TRUE);
						DrawGraph((90 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23 - 20, mis_img[mis_data[i]], TRUE);
					}
					else
					{
						DrawGraph((90 - mis_anim[i] * 28) + (i - 10) * 110, mis_y[i] - mis_anim[i] * 23 - 20, img[mis_data[i]][mis_anim[i]], TRUE);
					}
				}
			}
		}
		
		// 正解したとき
		if (correct[i] != -1)
		{
			if (Theme::theme_num < 10)
			{
				if (input_draw[i] == true)
				{
					if (com_cnt[i] != 0)
					{
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 370 - 30, comment[0], TRUE);
						DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110 - 13, 410 -10 - 30, effect_img[effect[i]], TRUE);
					}
					
					DrawGraph((500 - 57 * (Theme::theme_num - 3)) + i * 110, 410 - 30, img[correct[i]][0], TRUE);
				}
				else
				{
					DrawGraph(((500 - player_anim[i] * 28) - 57 * (Theme::theme_num - 3)) + i * 110, 410 - player_anim[i] * 23 - 30, img[correct[i]][player_anim[i]], TRUE);
				}
			}
			else if (Theme::theme_num == 10)
			{
				if (input_draw[i] == true)
				{
					if (com_cnt[i] != 0)
					{
						DrawGraph(90 + i * 110, 370 - 30, comment[0], TRUE);
						DrawGraph(90 + i * 110 - 13, 410 - 10 - 30, effect_img[effect[i]], TRUE);
					}

					DrawGraph(90 + i * 110, 410 - 30, img[input[i]][0], TRUE);
				}
				else
				{
					DrawGraph((90 - player_anim[i] * 28) + i * 110, 410 - player_anim[i] * 23 - 30, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(225 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(225 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(225 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);

					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 460 - 20, comment[0], TRUE);
							DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph((100 - 54 * (Theme::theme_num - 2)) + i * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph(((100 - player_anim[i] * 28) - 54 * (Theme::theme_num - 2)) + i * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(225 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(225 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(225 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(225 + (i - 8) * 110, 460 - 20, comment[0], TRUE);
							DrawGraph(225 + (i - 8) * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(225 + (i - 8) * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((225 - player_anim[i] * 28) + (i - 8) * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(160 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(160 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(215 + (i - 9) * 110, 460 - 20, comment[0], TRUE);
							DrawGraph(215 + (i - 9) * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(215 + (i - 9) * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((215 - player_anim[i] * 28) + (i - 9) * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(160 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(160 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + (i - 9) * 110, 460 - 20, comment[0], TRUE);
							DrawGraph(160 + (i - 9) * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + (i - 9) * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + (i - 9) * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(90 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(90 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(160 + (i - 10) * 110, 460 - 20, comment[0], TRUE);
							DrawGraph(160 + (i - 10) * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(160 + (i - 10) * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((160 - player_anim[i] * 28) + (i - 10) * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
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
							DrawGraph(90 + i * 110, 315 - 20, comment[0], TRUE);
							DrawGraph(90 + i * 110 - 13, 355 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + i * 110, 355 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + i * 110, 355 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
				else
				{
					if (input_draw[i] == true)
					{
						if (com_cnt[i] != 0)
						{
							DrawGraph(90 + (i - 10) * 110, 460 - 20, comment[0], TRUE);
							DrawGraph(90 + (i - 10) * 110 - 13, 500 - 10 - 20, effect_img[effect[i]], TRUE);
						}

						DrawGraph(90 + (i - 10) * 110, 500 - 20, img[input[i]][0], TRUE);
					}
					else
					{
						DrawGraph((90 - player_anim[i] * 28) + (i - 10) * 110, 500 - player_anim[i] * 23 - 20, img[input[i]][player_anim[i]], TRUE);
					}
				}
			}
		}
	}
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

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(mis_img[i]);
	}

	DeleteGraph(comment[0]);
	DeleteGraph(comment[1]);
	DeleteGraph(effect_img[0]);
	DeleteGraph(effect_img[1]);
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
		mis_num++;
		all_mis++;
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
		mis_y[correct_num] += 30;
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
	mis_num = 0;
}