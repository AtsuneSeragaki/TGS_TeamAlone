﻿#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "RankingScene.h"
#include "HelpScene.h"
#include <math.h>
#include "DxLib.h"

int TitleScene::menu_cursor = 0;
bool TitleScene::back_title = false;

TitleScene::TitleScene() : back_img(0), bgm(0), star_cnt(0), transition(0), tran_img(0),tran_flg(false),rota_flg(false),star_flg(false),shoot_num(0),shoot_cnt(0),shoot_x(0),shoot_y(0),cloud_img(0),cnt(0),shoot_ran(0), shoot_x2(0), shoot_y2(0), shoot_ran2(0),char_y(0),move_flg(false),pos_flg(false),char_stay(0),star_cnt2(0)
{
	se[0] = 0;
	se[1] = 0;

	for (int i = 0; i < 8; i++)
	{
		menu_img[i] = 0;
	}
	
	for (int i = 0; i < 6; i++)
	{
		star_img[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		ope_img[i] = 0;
	}
}

TitleScene::~TitleScene()
{
	// 画像データの削除
	DeleteGraph(back_img);

	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(menu_img[i]);
	}

	for (int i = 0; i < 6; i++)
	{
		DeleteGraph(star_img[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(ope_img[i]);
	}

	DeleteGraph(tran_img);
	DeleteGraph(cloud_img);

	// 音データの削除
	DeleteSoundMem(se[0]);
	DeleteSoundMem(se[1]);
	DeleteSoundMem(bgm);
}

void TitleScene::Initialize()
{
	// 画像データの読み込み
	//back_img = LoadGraph("Resource/images/title/back2.png");
	back_img = LoadGraph("Resource/images/title/title2.png");
	
	menu_img[0] = LoadGraph("Resource/images/title/start_choice.png");
	menu_img[1] = LoadGraph("Resource/images/title/start_basic.png");
	menu_img[2] = LoadGraph("Resource/images/title/help_choice.png");
	menu_img[3] = LoadGraph("Resource/images/title/help_basic.png");
	menu_img[4] = LoadGraph("Resource/images/title/Ranking_choice.png");
	menu_img[5] = LoadGraph("Resource/images/title/Ranking_basic.png");
	menu_img[6] = LoadGraph("Resource/images/title/end_choice.png");
	menu_img[7] = LoadGraph("Resource/images/title/end_basic.png");

	star_img[0] = LoadGraph("Resource/images/title/line1.png");
	star_img[1] = LoadGraph("Resource/images/title/line2.png");
	star_img[2] = LoadGraph("Resource/images/title/line3.png");
	star_img[3] = LoadGraph("Resource/images/title/line4.png");
	star_img[4] = LoadGraph("Resource/images/title/line5.png");
	star_img[5] = LoadGraph("Resource/images/help/star.png");

	tran_img = LoadGraph("Resource/images/tansition/transition.png");

	ope_img[0] = LoadGraph("Resource/images/title/up-down-select.png");
	ope_img[1] = LoadGraph("Resource/images/ranking/a.png");
	ope_img[2] = LoadGraph("Resource/images/ranking/y.png");
	ope_img[3] = LoadGraph("Resource/images/ranking/b.png");


	cloud_img = LoadGraph("Resource/images/title/cloud1.png");

	// 音データの読み込み
	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");

	bgm = LoadSoundMem("Resource/sounds/title/bgm3.mp3");

	// エラーチェック
	if (back_img == -1)
	{
		throw("Resource/images/title.pngがありません");
	}

	for (int i = 0; i < 8; i++)
	{
		if (menu_img[i] == -1)
		{
			throw("menu_img[%d]がありません",i);
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (star_img[i] == -1)
		{
			throw("star_img[%d]がありません",i);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (ope_img[i] == -1)
		{
			throw("ope_img[%d]がありません", i);
		}
	}

	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
	}
	if (cloud_img == -1)
	{
		throw("Resource/images/title/cloud1.pngがありません");
	}
	if (se[0] == -1)
	{
		throw("Resource/sounds/title/move.mp3がありません");
	}
	if (se[1] == -1)
	{
		throw("Resource/sounds/title/ok.mp3がありません");
	}
	if (bgm == -1)
	{
		throw("Resource/sounds/title/bgm3.mp3がありません");
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// 変数の初期化
	star_cnt = 0;
	transition = -1943;
	tran_flg = false;
	rota_flg = false;

	star_flg = false;
	shoot_num = 0;
	shoot_cnt = 0;
	shoot_x = 0;
	shoot_y = 0;
	shoot_ran = 0;
	shoot_x2 = 0;
	shoot_y2 = 0;
	shoot_ran2 = 0;
	cnt = 0;
	char_y = 600;
	move_flg = true;
	pos_flg = false;
	char_stay = 0;
	star_cnt2 = 0;
}

eSceneType TitleScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	OpeAnim();

	StarAnim();

	CursorAnim();

	ShootStarAnim();

	SetCharY();

	if (back_title == true)
	{
		if (tran_flg == false)
		{
			tran_flg = true;
			transition = -93;
		}
		
		if (transition <= 1943)
		{
			// トランジション
			Transition();
		}
		else
		{
			back_title = false;
			tran_flg = false;
			transition = -1943;
		}
	}
	else
	{
		if (tran_flg == true)
		{
			if (transition <= -120)
			{
				// トランジション
				Transition();
			}
			else
			{
				// カーソルがある場所に遷移
				switch (menu_cursor)
				{
				case 0:
					return eSceneType::E_MAIN;
				case 1:
					return eSceneType::E_HELP;
				case 2:
					return eSceneType::E_RANKING;
				case 3:
					return eSceneType::E_END;
				default:
					break;
				}
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{// Aボタンを押したら

		// 効果音の再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		// 下にカーソル移動
		menu_cursor++;

		// カーソルが1番下にある場合1番上に移動
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_Y))
	{// Yボタンを押したら

		// 効果音の再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		// 上にカーソル移動
		menu_cursor--;

		// カーソルが1番上にある場合1番下に移動
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}
	else if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{// Bボタンを押したら

		// 効果音の再生
		PlaySoundMem(se[1], DX_PLAYTYPE_NORMAL, TRUE);

		// BGMの再生を止める
		StopSoundMem(bgm);

		tran_flg = true;
	}

	return GetNowScene();
}

void TitleScene::Draw() const
{
	// 背景の描画
	DrawGraph(0, 0, back_img, TRUE);

	// 星の描画
	/*DrawRotaGraph(200, 90,1.0,PI / 180 * star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(1100, 100,1.0,PI / 180 * -star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(1000, 300, 1.0,PI / 180 * star_cnt2, star_img[5], TRUE);*/
	/*DrawRotaGraph(1200, 220, 1.0,PI / 180 * -star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(250, 380, 1.0,PI / 180 * star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(950, 380, 1.0,PI / 180 * star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(450, 600, 1.0,PI / 180 * -star_cnt2, star_img[5], TRUE);
	DrawRotaGraph(830, 600, 1.0,PI / 180 * -star_cnt2, star_img[5], TRUE);*/

	// 流れ星の描画
	if (star_flg == true)
	{
		DrawGraph(shoot_x, shoot_y, star_img[shoot_num], TRUE);
	}

	/*DrawGraph(50, 30, star_img[shoot_num], TRUE);
	DrawGraph(200, 170, star_img[shoot_num], TRUE);
	DrawGraph(70, 400, star_img[shoot_num], TRUE);
	DrawGraph(280, 550, star_img[shoot_num], TRUE);
	DrawGraph(450, 300, star_img[shoot_num], TRUE);
	DrawGraph(700, 450, star_img[shoot_num], TRUE);
	DrawGraph(1100, 30, star_img[shoot_num], TRUE);
	DrawGraph(850, 200, star_img[shoot_num], TRUE);
	DrawGraph(1200, 250, star_img[shoot_num], TRUE);
	DrawGraph(980, 350, star_img[shoot_num], TRUE);
	DrawGraph(900, 600, star_img[shoot_num], TRUE);*/
	
	/*DrawRotaGraphF(star_x[2], 100.0f, 1.0, PI / 180 * -star_cnt, star_img[2], TRUE);
	DrawRotaGraphF(star_x[3], 100.0f, 1.0, PI / 180 * star_cnt, star_img[3], TRUE);

	DrawRotaGraphF(star_x[4], 370.0f, 1.0, PI / 180 * star_cnt, star_img[3], TRUE);
	DrawRotaGraphF(star_x[5], 370.0f, 1.0, PI / 180 * -star_cnt, star_img[2], TRUE);
	DrawRotaGraphF(star_x[6], 370.0f, 1.0, PI / 180 * star_cnt, star_img[1], TRUE);
	DrawRotaGraphF(star_x[7], 370.0f, 1.0, PI / 180 * -star_cnt, star_img[0], TRUE);

	DrawRotaGraphF(star_x[8], 650.0f, 1.0, PI / 180 * star_cnt, star_img[2], TRUE);
	DrawRotaGraphF(star_x[9], 650.0f, 1.0, PI / 180 * -star_cnt, star_img[0], TRUE);
	DrawRotaGraphF(star_x[10], 650.0f, 1.0, PI / 180 * star_cnt, star_img[3], TRUE);
	DrawRotaGraphF(star_x[11], 650.0f, 1.0, PI / 180 * -star_cnt, star_img[1], TRUE);*/

	// タイトルロゴの描画
	//DrawGraph(380, 5, logo_img, TRUE);

	// 雲の描画
	DrawGraph(0, 0, cloud_img, TRUE);

	// 操作説明の描画
	DrawGraph(800, 650, ope_img[0], TRUE);
	DrawGraph(920, 650 + sin(PI * 2 / 90 * cnt) * 6, ope_img[1], TRUE); // a
	DrawGraph(1092, 650 + sin(PI * 2 / 90 * cnt) * 6, ope_img[3], TRUE); // b
	DrawGraph(802, 650 + sin(PI * 2 / 90 * cnt) * 6, ope_img[2], TRUE); // y

	
	// メニューの描画
	switch (menu_cursor)
	{
	case 0:
		DrawGraph(555, 240 + 30 + sin(PI * 2 / 90 * cnt) * 6, menu_img[0], TRUE);
		DrawGraph(575, 340 + 30, menu_img[3], TRUE);
		DrawGraph(510, 443 + 30, menu_img[5], TRUE);
		DrawGraph(585, 540 + 40, menu_img[7], TRUE);
		DrawGraph(493, 280/*+ (float)sin(PI * 2 / 100 * cnt) * 5*/, star_img[5], TRUE);
		DrawGraph(760, 280 /*+ (float)sin(PI * 2 / 100 * cnt) * 5*/, star_img[5], TRUE);
		break;
	case 1:
		DrawGraph(555, 240 + 30, menu_img[1], TRUE);
		DrawGraph(575, 340 + 30 + sin(PI * 2 / 90 * cnt) * 6, menu_img[2], TRUE);
		DrawGraph(510, 443 + 30, menu_img[5], TRUE);
		DrawGraph(585, 540 + 40, menu_img[7], TRUE);
		DrawGraph(510, 378 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		DrawGraph(750, 378 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		break;
	case 2:
		DrawGraph(555, 240 + 30, menu_img[1], TRUE);
		DrawGraph(575, 340 + 30, menu_img[3], TRUE);
		DrawGraph(510, 443 + 30 + sin(PI * 2 / 90 * cnt) * 6, menu_img[4], TRUE);
		DrawGraph(585, 540 + 40, menu_img[7], TRUE);
		DrawGraph(450, 490 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		DrawGraph(820, 490 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		break;
	case 3:
		DrawGraph(555, 240 + 30, menu_img[1], TRUE);
		DrawGraph(575, 340 + 30, menu_img[3], TRUE);
		DrawGraph(510, 443 + 30, menu_img[5], TRUE);
		DrawGraph(585, 540 + 40 + sin(PI * 2 / 90 * cnt) * 6, menu_img[6], TRUE);
		DrawGraph(520, 585 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		DrawGraph(735, 585 /*+ (float)sin(PI * 2 / 90 * cnt) * 6*/, star_img[5], TRUE);
		break;
	default:
		break;
	}

	// トランジション画像の描画
	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void TitleScene::Finalize()
{
	
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}

void TitleScene::StarAnim()
{
	star_cnt2++;

	// 180より大きくなったら0にする
	if (star_cnt2 > 180)
	{
		star_cnt2 = 0;
	}

	star_cnt2++;

	// 180より大きくなったら0にする
	if (star_cnt2> 90)
	{
		star_cnt2 = 0;
	}

}

void TitleScene::CursorAnim()
{
	if (rota_flg == false)
	{
		star_cnt++;

		if (star_cnt > 20)
		{
			rota_flg = true;
		}
	}
	else
	{
		star_cnt--;

		if (star_cnt <= -15)
		{
			rota_flg = false;
		}
	}
}

void TitleScene::Transition()
{
	transition += 50;
}

void TitleScene::StarMove()
{
	/*for (int i = 0; i < 4; i++)
	{
		star_x[i] -= 0.3f;

		if (star_x[i] <= -335.0f)
		{
			star_x[i] = 1330.0f;
		}
	}

	for (int i = 4; i < 8; i++)
	{
		star_x[i] += 0.3f;

		if (star_x[i] >= 1330.0f)
		{
			star_x[i] = -335.0f;
		}
	}

	for (int i = 8; i < 12; i++)
	{
		star_x[i] -= 0.3f;

		if (star_x[i] <= -335.0f)
		{
			star_x[i] = 1330.0f;
		}
	}*/
}

void TitleScene::ShootStarAnim()
{
	if (star_flg == false)
	{
		shoot_cnt++;

		if (shoot_cnt >= 80)
		{
			SetStarPos();
			star_flg = true;
			shoot_cnt = 0;
		}
	}
	else
	{
		shoot_cnt++;

		if (shoot_cnt > 3)
		{
			shoot_cnt = 0;

			if (shoot_num < 4)
			{
				shoot_num++;
			}
			else
			{
				star_flg = false;
				shoot_num = 0;
				shoot_cnt = 0;
			}
		}
	}
}

void TitleScene::SetStarPos()
{
	int next_num = 0;
	int next_num2 = 0;
	
	do
	{
		next_num = GetRand(11);
	}while (shoot_ran == next_num);

	shoot_ran = next_num;

	do
	{
		next_num2 = GetRand(6);
	} while (shoot_ran2 == next_num2);

	shoot_ran2 = next_num2;

	switch (shoot_ran)
	{
	case 0:
		shoot_x = 50;
		shoot_y = 30;
		break;

	case 1:
		shoot_x = 200;
		shoot_y = 170;
		break;

	case 2:
		shoot_x = 70;
		shoot_y = 400;
		break;

	case 3:
		shoot_x = 280;
		shoot_y = 550;
		break;

	case 4:
		shoot_x = 450;
		shoot_y = 300;
		break;

	case 5:
		shoot_x = 700;
		shoot_y = 450;
		break;

	case 6:
		shoot_x = 1100;
		shoot_y = 30;
		break;

	case 7:
		shoot_x = 850;
		shoot_y = 200;
		break;

	case 8:
		shoot_x = 1200;
		shoot_y = 250;
		break;

	case 9:
		shoot_x = 980;
		shoot_y = 350;
		break;

	case 10:
		shoot_x = 900;
		shoot_y = 600;
		break;

	default:
		break;
	}

	switch (shoot_ran2)
	{
	case 0:
		shoot_x2 = 700;
		shoot_y2 = 450;
		break;

	case 1:
		shoot_x2 = 1100;
		shoot_y2 = 30;
		break;

	case 2:
		shoot_x2 = 850;
		shoot_y2 = 200;
		break;

	case 3:
		shoot_x2 = 1200;
		shoot_y2 = 250;
		break;

	case 4:
		shoot_x2 = 980;
		shoot_y2 = 350;
		break;

	case 5:
		shoot_x2 = 900;
		shoot_y2 = 600;
		break;

	default:
		break;
	}
}

void TitleScene::SetCharY()
{
	if (move_flg == false)
	{
		if (char_stay != 0)
		{
			char_stay++;

			if (char_stay >= 120)
			{
				char_stay = 0;
			}
		}
		else
		{
			char_y++;

			if (char_y >= 620)
			{
				move_flg = true;


				if (pos_flg == false)
				{
					pos_flg = true;
				}
				else
				{
					pos_flg = false;
				}
			}
		}
	}
	else
	{
		char_y--;

		if (char_y <= 400)
		{
			move_flg = false;
			char_stay = 1;
		}
	}
}

void TitleScene::OpeAnim()
{
	if (cnt >= 90)
	{
		cnt = 0;
	}
	else
	{
		cnt++;
	}
}