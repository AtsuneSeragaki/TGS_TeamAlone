#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include <math.h>
#include "DxLib.h"

bool HelpScene::game_start = false;

HelpScene::HelpScene():bcnt(0),anim(0),cnt_flg(false),se(0),bgm(0), star_img(0),star_cnt(0), transition(0), tran_img(0), tran_flg(false),cnt(0), cbutton_num(0)
{
	for (int i = 0; i < 7; i++)
	{
		back_img[i] = 0;
	}

	for (int i = 0; i < 8; i++)
	{
		cbutton_img[i] = 0;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			button_img[i][j] = 0;
		}
	}
}

HelpScene::~HelpScene()
{
	// 画像データの削除
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(back_img[i]);
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			DeleteGraph(button_img[i][j]);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		DeleteGraph(cbutton_img[i]);
	}

	DeleteGraph(star_img);

	DeleteGraph(tran_img);

	// 音データの削除
	DeleteSoundMem(se);
	DeleteSoundMem(bgm);
}

void HelpScene::Initialize()
{
	// 画像データの読み込み
	//back_img[0] = LoadGraph("Resource/images/help/help.png");
	back_img[0] = LoadGraph("Resource/images/help/help4.png");
	back_img[1] = LoadGraph("Resource/images/help/start-title4.png");
	back_img[2] = LoadGraph("Resource/images/help/x.png");
	back_img[3] = LoadGraph("Resource/images/help/star2.png");
	back_img[4] = LoadGraph("Resource/images/help/line2.png");
	back_img[5] = LoadGraph("Resource/images/help/ui.png");
	back_img[6] = LoadGraph("Resource/images/help/b.png");

	/*button_img[0][0] = LoadGraph("Resource/images/main/button/Abotton0.png");
	button_img[0][1] = LoadGraph("Resource/images/main/button/Abotton5.png");
	button_img[0][2] = LoadGraph("Resource/images/main/button/Abotton6.png");
	button_img[0][3] = LoadGraph("Resource/images/main/button/Abotton7.png");
	button_img[0][4] = LoadGraph("Resource/images/main/button/Abotton8.png");

	button_img[1][0] = LoadGraph("Resource/images/main/button/Bbotton0.png");
	button_img[1][1] = LoadGraph("Resource/images/main/button/Bbotton5.png");
	button_img[1][2] = LoadGraph("Resource/images/main/button/Bbotton6.png");
	button_img[1][3] = LoadGraph("Resource/images/main/button/Bbotton7.png");
	button_img[1][4] = LoadGraph("Resource/images/main/button/Bbotton8.png");

	button_img[2][0] = LoadGraph("Resource/images/main/button/Ybotton0.png");
	button_img[2][1] = LoadGraph("Resource/images/main/button/Ybotton5.png");
	button_img[2][2] = LoadGraph("Resource/images/main/button/Ybotton6.png");
	button_img[2][3] = LoadGraph("Resource/images/main/button/Ybotton7.png");
	button_img[2][4] = LoadGraph("Resource/images/main/button/Ybotton8.png");

	button_img[3][0] = LoadGraph("Resource/images/main/button/Xbotton0.png");
	button_img[3][1] = LoadGraph("Resource/images/main/button/Xbotton5.png");
	button_img[3][2] = LoadGraph("Resource/images/main/button/Xbotton6.png");
	button_img[3][3] = LoadGraph("Resource/images/main/button/Xbotton7.png");
	button_img[3][4] = LoadGraph("Resource/images/main/button/Xbotton8.png");*/

	button_img[0][0] = LoadGraph("Resource/images/main/button/a1.png");
	button_img[0][1] = LoadGraph("Resource/images/main/button/a2.png");
	button_img[0][2] = LoadGraph("Resource/images/main/button/a3.png");
	button_img[0][3] = LoadGraph("Resource/images/main/button/a4.png");
	button_img[0][4] = LoadGraph("Resource/images/main/button/a5.png");
	button_img[0][5] = LoadGraph("Resource/images/main/button/a.png");

	button_img[1][0] = LoadGraph("Resource/images/main/button/b1.png");
	button_img[1][1] = LoadGraph("Resource/images/main/button/b2.png");
	button_img[1][2] = LoadGraph("Resource/images/main/button/b3.png");
	button_img[1][3] = LoadGraph("Resource/images/main/button/b4.png");
	button_img[1][4] = LoadGraph("Resource/images/main/button/b5.png");
	button_img[1][5] = LoadGraph("Resource/images/main/button/b.png");

	button_img[2][0] = LoadGraph("Resource/images/main/button/y1.png");
	button_img[2][1] = LoadGraph("Resource/images/main/button/y2.png");
	button_img[2][2] = LoadGraph("Resource/images/main/button/y3.png");
	button_img[2][3] = LoadGraph("Resource/images/main/button/y4.png");
	button_img[2][4] = LoadGraph("Resource/images/main/button/y5.png");
	button_img[2][5] = LoadGraph("Resource/images/main/button/y.png");

	button_img[3][0] = LoadGraph("Resource/images/main/button/x1.png");
	button_img[3][1] = LoadGraph("Resource/images/main/button/x2.png");
	button_img[3][2] = LoadGraph("Resource/images/main/button/x3.png");
	button_img[3][3] = LoadGraph("Resource/images/main/button/x4.png");
	button_img[3][4] = LoadGraph("Resource/images/main/button/x5.png");
	button_img[3][5] = LoadGraph("Resource/images/main/button/x.png");

	star_img = LoadGraph("Resource/images/help/star.png");
	tran_img = LoadGraph("Resource/images/tansition/transition.png");

	cbutton_img[0] = LoadGraph("Resource/images/help/a1.png");
	cbutton_img[1] = LoadGraph("Resource/images/help/a2.png");
	cbutton_img[2] = LoadGraph("Resource/images/help/x1.png");
	cbutton_img[3] = LoadGraph("Resource/images/help/x2.png");
	cbutton_img[4] = LoadGraph("Resource/images/help/y1.png");
	cbutton_img[5] = LoadGraph("Resource/images/help/y2.png");
	cbutton_img[6] = LoadGraph("Resource/images/help/b1.png");
	cbutton_img[7] = LoadGraph("Resource/images/help/b2.png");


	// 音データの読み込み
	se = LoadSoundMem("Resource/sounds/title/ok.mp3");
	bgm = LoadSoundMem("Resource/sounds/title/bgm2.mp3");

	// エラーチェック
	for (int i = 0; i < 7; i++)
	{
		if (back_img[i] == -1)
		{
			throw("back_img[%d]がありません", i);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (button_img[i][j] == -1)
			{
				throw("button_img[%d][%d]がありません", i,j);
			}
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if (cbutton_img[i] == -1)
		{
			throw("cbutton_img[%d]がありません", i);
		}
	}

	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
	}
	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
	}
	if (se == -1)
	{
		throw("Resource/sounds/title/ok.mp3がありません");
	}
	if (bgm == -1)
	{
		throw("Resource/sounds/title/bgm2.mp3がありません");
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// 変数の初期化
	bcnt = 0;
	cnt_flg = false;
	anim = 1;
	star_cnt = 0;
	transition = -93;
	tran_flg = true;
	game_start = false;
	cbutton_num = 0;
}

eSceneType HelpScene::Update()
{
	// 操作説明のボタンのアニメーション
	OpeAnim();

	// 星を回転させる
	StarAnim();

	// ボタンのアニメーション
	ButtonAnim();

	if (tran_flg == true)
	{
		if (TitleScene::back_title == true && transition <= -120)
		{
			// トランジション
			Transition();
		}
		else if (TitleScene::back_title == true && transition > -120)
		{
			// タイトル画面に遷移
			return eSceneType::E_TITLE;
		}
		else if (game_start == true && transition <= -120)
		{
			// トランジション
			Transition();
		}
		else if (game_start == true && transition > -120)
		{
			// ゲームメイン画面に遷移
			return eSceneType::E_MAIN;
		}
		else if (TitleScene::back_title == false && game_start == false && transition <= 1943)
		{
			// トランジション
			Transition();
		}
		else
		{
			tran_flg = false;
		}
	}
	else
	{
		// BGMの再生
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{// Bボタンが押されたら

			// 効果音の再生
			PlaySoundMem(se, DX_PLAYTYPE_NORMAL, TRUE);

			// BGMの再生を止める
			StopSoundMem(bgm);

			tran_flg = true;
			TitleScene::back_title = true;
			transition = -1943;
		}

		if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
		{// Xボタンが押されたら

			// 効果音の再生
			PlaySoundMem(se, DX_PLAYTYPE_NORMAL, TRUE);

			// BGMの再生を止める
			StopSoundMem(bgm);

			// タイトル画面のメニューカーソルの位置を0に戻す
			TitleScene::menu_cursor = 0;

			tran_flg = true;
			game_start = true;
			transition = -1943;
		}
	}

	return GetNowScene();
}

void HelpScene::Draw() const
{
	// 背景の描画
	DrawGraph(0, 0, back_img[0], FALSE);

	// 星の描画
	//DrawRotaGraph(450, 90, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	//DrawRotaGraph(850, 90, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	//DrawRotaGraph(50, 670, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	//DrawRotaGraph(1230, 670, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);

	// 操作説明の描画
	//DrawGraph(400, 580, back_img[1], TRUE);
	DrawGraph(425, 578 + sin(PI * 2 / 90 * cnt) * 6, back_img[2], TRUE); // xbutton
	DrawGraph(673, 578 + sin(PI * 2 / 90 * cnt) * 6, back_img[6], TRUE); // bbutton

	// 操作説明(コントローラーのボタン)の描画
	switch (cbutton_num)
	{
	case 0:
		DrawGraph(964, 505, cbutton_img[0], TRUE);
		DrawGraph(932, 475, cbutton_img[2], TRUE);
		DrawGraph(964, 446, cbutton_img[4], TRUE);
		DrawGraph(993, 475, cbutton_img[6], TRUE);
		break;

	case 1:
		DrawGraph(964, 505, cbutton_img[1], TRUE);
		DrawGraph(932, 475, cbutton_img[2], TRUE);
		DrawGraph(964, 446, cbutton_img[4], TRUE);
		DrawGraph(993, 475, cbutton_img[6], TRUE);
		break;

	case 2:
		DrawGraph(964, 505, cbutton_img[0], TRUE);
		DrawGraph(932, 475, cbutton_img[2], TRUE);
		DrawGraph(964, 446, cbutton_img[4], TRUE);
		DrawGraph(993, 475, cbutton_img[7], TRUE);
		break;

	case 3:
		DrawGraph(964, 505, cbutton_img[0], TRUE);
		DrawGraph(932, 475, cbutton_img[2], TRUE);
		DrawGraph(964, 446, cbutton_img[5], TRUE);
		DrawGraph(993, 475, cbutton_img[6], TRUE);
		break;

	case 4:
		DrawGraph(964, 505, cbutton_img[0], TRUE);
		DrawGraph(932, 475, cbutton_img[3], TRUE);
		DrawGraph(964, 446, cbutton_img[4], TRUE);
		DrawGraph(993, 475, cbutton_img[6], TRUE);
		break;

	default:
		break;
	}

	// ボタンの描画(お題)
	// 画像を薄く表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	for (int i = 0; i < 4; i++)
	{
		DrawGraph(BUTTON_X + i * 120, BUTTON_Y, button_img[i][0], TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// ボタンの描画(動くボタン)
	if (anim >= 1 && anim < 3)
	{
		DrawGraph(BUTTON_X - 4 * 28, BUTTON_Y - 4 * 23, button_img[0][4], TRUE);
	}
	else if (anim >= 3 && anim < 5)
	{
		DrawGraph(BUTTON_X - 3 * 28, BUTTON_Y - 3 * 23, button_img[0][3], TRUE);
	}
	else if (anim >= 5 && anim < 7)
	{
		DrawGraph(BUTTON_X - 2 * 28, BUTTON_Y - 2 * 23, button_img[0][2], TRUE);
	}
	else if (anim >= 7 && anim < 9)
	{
		DrawGraph(BUTTON_X - 28, BUTTON_Y - 23, button_img[0][1], TRUE);
	}
	else if (anim >= 9 && anim < 15)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
	}
	else if(anim >= 15 && anim < 17)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph((BUTTON_X - 4 * 28) + 120, BUTTON_Y - 4 * 23, button_img[1][4], TRUE);
	}
	else if (anim >= 17 && anim < 19)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph((BUTTON_X - 3 * 28) + 120, BUTTON_Y - 3 * 23, button_img[1][3], TRUE);
	}
	else if (anim >= 19 && anim < 21)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph((BUTTON_X - 2 * 28) + 120, BUTTON_Y - 2 * 23, button_img[1][2], TRUE);
	}
	else if (anim >= 21 && anim < 23)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph((BUTTON_X - 28) + 120, BUTTON_Y - 23, button_img[1][1], TRUE);
	}
	else if (anim >= 23 && anim < 29)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
	}
	else if (anim >= 29 && anim < 31)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph((BUTTON_X - 4 * 28) + 240, BUTTON_Y - 4 * 23, button_img[2][4], TRUE);
	}
	else if (anim >= 31 && anim < 33)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph((BUTTON_X - 3 * 28) + 240, BUTTON_Y - 3 * 23, button_img[2][3], TRUE);
	}
	else if (anim >= 33 && anim < 35)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph((BUTTON_X - 2 * 28) + 240, BUTTON_Y - 2 * 23, button_img[2][2], TRUE);
	}
	else if (anim >= 35 && anim < 37)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph((BUTTON_X - 28) + 240, BUTTON_Y - 23, button_img[2][1], TRUE);
	}
	else if (anim >= 37 && anim < 43)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
	}
	else if (anim >= 43 && anim < 45)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
		DrawGraph((BUTTON_X - 4 * 28) + 360, 350 - 4 * 23, button_img[3][4], TRUE);
	}
	else if (anim >= 45 && anim < 47)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
		DrawGraph((BUTTON_X - 3 * 28) + 360, BUTTON_Y - 3 * 23, button_img[3][3], TRUE);
	}
	else if (anim >= 47 && anim < 49)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
		DrawGraph((BUTTON_X - 2 * 28) + 360, BUTTON_Y - 2 * 23, button_img[3][2], TRUE);
	}
	else if (anim >= 49 && anim < 51)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
		DrawGraph((BUTTON_X - 28) + 360, BUTTON_Y - 23, button_img[3][1], TRUE);
	}
	else if (anim >= 51 && anim < 100)
	{
		DrawGraph(BUTTON_X, BUTTON_Y, button_img[0][0], TRUE);
		DrawGraph(BUTTON_X + 120, BUTTON_Y, button_img[1][0], TRUE);
		DrawGraph(BUTTON_X + 240, BUTTON_Y, button_img[2][0], TRUE);
		DrawGraph(BUTTON_X + 360, BUTTON_Y, button_img[3][0], TRUE);
	}

	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void HelpScene::Finalize()
{
	
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}

void HelpScene::ButtonAnim()
{
	// ボタンアニメーションフラグがtrueだったら
	if (cnt_flg == true)
	{
		bcnt++;

		// cntが140より大きかったら
		if (bcnt > 140)
		{
			bcnt = 0;
			anim++;
			cbutton_num = 1;
			cnt_flg = false;
		}
	}
	
	// animの値が0より大きかったら
	if (anim > 0)
	{
		anim++;

		if (anim == 15)
		{
			cbutton_num = 2;
		}
		else if (anim == 29)
		{
			cbutton_num = 3;
		}
		else if (anim == 43)
		{
			cbutton_num = 4;
		}
		else if (anim == 51)
		{
			cbutton_num = 0;
		}

		// animが100より大きかったら
		if (anim > 100)
		{
			anim = 0;
			cnt_flg = true;
			cbutton_num = 0;
		}
	}
}

void HelpScene::StarAnim()
{
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}

void HelpScene::Transition()
{
	transition += 50;
}

void HelpScene::OpeAnim()
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