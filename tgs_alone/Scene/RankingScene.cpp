﻿#include "RankingScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include "InputRankingScene.h"
#include "DxLib.h"

bool RankingScene::to_ranking = false;

RankingScene::RankingScene():back_img(0),ranking(nullptr),font(0),bgm(0), star_img(0), star_cnt(0), transition(0), tran_img(0), tran_flg(false)
{
	se[0] = 0;
	se[1] = 0;

	for (int i = 0; i < 27; i++)
	{
		font_img[i] = 0;
	}

	for (int i = 0; i < 10; i++)
	{
		num_img[i] = 0;
	}
}

RankingScene::~RankingScene()
{
	// フォントデータの削除
	DeleteFontToHandle(font);

	// 画像データの削除
	DeleteGraph(back_img);
	DeleteGraph(star_img);
	DeleteGraph(tran_img);

	for (int i = 0; i < 27; i++)
	{
		DeleteGraph(font_img[i]);
	}

	for (int i = 0; i < 10; i++)
	{
		DeleteGraph(num_img[i]);
	}

	// 音データの削除
	DeleteSoundMem(se[0]);
	DeleteSoundMem(se[1]);
	DeleteSoundMem(bgm);
}

void RankingScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/ranking/ranking.png");
	star_img = LoadGraph("Resource/images/help/star.png");
	tran_img = LoadGraph("Resource/images/tansition/transition.png");
	LoadDivGraph("Resource/images/ranking/moji2.png", 27, 9, 3, 50, 50, font_img);
	LoadDivGraph("Resource/images/ranking/rank_num.png", 10, 5, 2, 50, 50, num_img);

	// フォントデータの読み込み
	font = CreateFontToHandle("Segoe UI", 45, 7, DX_FONTTYPE_ANTIALIASING);

	// 音データの読み込み
	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");
	bgm = LoadSoundMem("Resource/sounds/title/bgm2.mp3");

	// エラーチェック

	for (int i = 0; i < 27; i++)
	{
		if (font_img[i] == -1)
		{
			throw("font_img[%d]がありません", i);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (num_img[i] == -1)
		{
			throw("num_img[%d]がありません", i);
		}
	}

	if (back_img == -1)
	{
		throw("Resource/images/ranking/ranking.pngがありません");
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
		throw("Resource/sounds/title/bgm2.mp3がありません");
	}
	if (font == -1)
	{
		throw("Segoe UIがありません");
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();

	// 変数の初期化
	transition = -93;
	tran_flg = true;
}

eSceneType RankingScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();

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
		else if (to_ranking == true && transition <= 1943)
		{
			Transition();
		}
		else if (TitleScene::back_title == false && transition <= 1943)
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
		// Bボタンが押されたら
		if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
		{
			// 効果音の再生
			PlaySoundMem(se[1], DX_PLAYTYPE_NORMAL, TRUE);

			// BGMを止める
			StopSoundMem(bgm);

			TitleScene::back_title = true;
			transition = -1943;
			tran_flg = true;
		}
	}

	return GetNowScene();
}

void RankingScene::Draw() const
{
	// 背景の描画
	DrawGraph(0, 0, back_img, TRUE);

	// 星の描画
	DrawRotaGraph(50, 50, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1230, 50, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(50, 670, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1230, 670, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);

	// 取得したランキングデータを描画
	for (int i = 0; i < 3; i++)
	{
		// ランキングデータの名前の長さを取得
		const char* name = ranking->GetName(i);
		int name_num = (int)strlen(name);

		// ランキングデータのレベルを取得
		int level = ranking->GetLevel(i);

		// ランキングデータのコンボを取得
		int combo = ranking->GetCombo(i);
		
		// 名前の描画
		//DrawFormatStringToHandle(450 - (name_num - 1) * 15, 242 + i * 100, 0x000000, font, "%s", name);

		for (int j = 0; j < name_num; j++)
		{
			DrawGraph((450 - (name_num - 1) * 23) + j * 43, 242 + i * 100, font_img[(int)name[j] - 65], TRUE);
		}
		
		//DrawFormatString(0, 0 + i * 20, 0x000000, "%d", name_num);

		// レベルの描画
		//DrawFormatStringToHandle(810, 242 + i * 100, 0x000000, font, "%02d", ranking->GetLevel(i));
		DrawGraph(789, 242 + i * 100, num_img[level / 10], TRUE);
		DrawGraph(835, 242 + i * 100, num_img[level % 10], TRUE);

		// コンボの描画
		//DrawFormatStringToHandle(1028, 242 + i * 100, 0x000000, font, "%03d", ranking->GetCombo(i));
		DrawGraph(1000, 242 + i * 100, num_img[combo / 100], TRUE);
		DrawGraph(1045, 242 + i * 100, num_img[(combo - combo / 100 * 100) / 10], TRUE);
		DrawGraph(1090, 242 + i * 100, num_img[combo % 10], TRUE);
	}

	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void RankingScene::Finalize()
{
	// 動的メモリの解放
	ranking->Finalize();
	delete ranking;
}

eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}

void RankingScene::StarAnim()
{
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}

void RankingScene::Transition()
{
	transition += 50;
}
