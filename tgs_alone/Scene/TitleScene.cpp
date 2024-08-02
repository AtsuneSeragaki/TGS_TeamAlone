#include "TitleScene.h"
#include "../Utility/InputControl.h"
#include "RankingScene.h"
#include "HelpScene.h"
#include "DxLib.h"

int TitleScene::menu_cursor = 0;
bool TitleScene::back_title = false;

TitleScene::TitleScene() : back_img(0), bgm(0), star_img(0), star_cnt(0), transition(0), tran_img(0),tran_flg(false)
{
	se[0] = 0;
	se[1] = 0;

	for (int i = 0; i < 8; i++)
	{
		menu_img[i] = 0;
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

	DeleteGraph(star_img);

	DeleteGraph(tran_img);

	// 音データの削除
	DeleteSoundMem(se[0]);
	DeleteSoundMem(se[1]);
	DeleteSoundMem(bgm);
}

void TitleScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/title/title.png");
	
	menu_img[0] = LoadGraph("Resource/images/title/starty.png");
	menu_img[1] = LoadGraph("Resource/images/title/start.png");
	menu_img[2] = LoadGraph("Resource/images/title/helpy.png");
	menu_img[3] = LoadGraph("Resource/images/title/help.png");
	menu_img[4] = LoadGraph("Resource/images/title/rankingy.png");
	menu_img[5] = LoadGraph("Resource/images/title/ranking.png");
	menu_img[6] = LoadGraph("Resource/images/title/endy.png");
	menu_img[7] = LoadGraph("Resource/images/title/end.png");
	
	star_img = LoadGraph("Resource/images/help/star.png");

	tran_img = LoadGraph("Resource/images/tansition/transition.png");

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

	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
	}
	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
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
}

eSceneType TitleScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();

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
	DrawRotaGraph(80, 220,1.0,PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(430, 220,1.0,PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(800, 220, 1.0,PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1200, 220, 1.0,PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(250, 380, 1.0,PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(950, 380, 1.0,PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(450, 600, 1.0,PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(830, 600, 1.0,PI / 180 * (-star_cnt * 2), star_img, TRUE);
	
	// メニューの描画
	switch (menu_cursor)
	{
	case 0:
		DrawGraph(555, 240, menu_img[0], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 1:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[2], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 2:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[4], TRUE);
		DrawGraph(585, 540, menu_img[7], TRUE);
		break;
	case 3:
		DrawGraph(555, 240, menu_img[1], TRUE);
		DrawGraph(575, 340, menu_img[3], TRUE);
		DrawGraph(510, 443, menu_img[5], TRUE);
		DrawGraph(585, 540, menu_img[6], TRUE);
		break;
	default:
		break;
	}

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
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}

void TitleScene::Transition()
{
	transition += 50;
}