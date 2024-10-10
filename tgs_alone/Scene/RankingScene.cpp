#include "RankingScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
#include "InputRankingScene.h"
#include <math.h>
#include "DxLib.h"

bool RankingScene::to_ranking = false;

RankingScene::RankingScene():back_img(0),ranking(nullptr),font(0),bgm(0), star_img(0), star_cnt(0), transition(0), tran_img(0), tran_flg(false),ope_num(0),cnt(0),ope_flg(false)
{
	se[0] = 0;
	se[1] = 0;

	ope_img[0] = 0;
	ope_img[1] = 0;
	ope_img[2] = 0;

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

	DeleteGraph(ope_img[0]);
	DeleteGraph(ope_img[1]);
	DeleteGraph(ope_img[2]);

	// 音データの削除
	DeleteSoundMem(se[0]);
	DeleteSoundMem(se[1]);
	DeleteSoundMem(bgm);
}

void RankingScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/ranking/ranking3.png");
	star_img = LoadGraph("Resource/images/help/star.png");
	tran_img = LoadGraph("Resource/images/tansition/transition.png");
	ope_img[0] = LoadGraph("Resource/images/result/title1.png");
	ope_img[1] = LoadGraph("Resource/images/ranking/title3.png");
	ope_img[2] = LoadGraph("Resource/images/result/b.png");
	LoadDivGraph("Resource/images/ranking/moji6.png", 27, 9, 3, 50, 50, font_img);
	LoadDivGraph("Resource/images/ranking/rank_num1.png", 10, 5, 2, 50, 50, num_img);

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
	if (ope_img[0] == -1)
	{
		throw("Resource/images/result/title1.pngがありません");
	}
	if (ope_img[1] == -1)
	{
		throw("Resource/images/result/title2.pngがありません");
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
	ope_num = 0;
	cnt = 0;
	ope_flg = 0;
}

eSceneType RankingScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 操作説明のボタンのアニメーション
	OpeAnim();

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
			ope_num++;

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

	// 操作説明の描画
	//DrawGraph(640, 610, ope_img[1], TRUE);
	DrawGraph(570, 618 + sin(PI * 2 / 90 * cnt) * 6, ope_img[2], TRUE);

	// 星の描画
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);
	DrawRotaGraph(368, 95, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(935, 95, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	/*DrawGraph(345, 70, star_img, TRUE);
	DrawGraph(907, 70, star_img, TRUE);*/
	//DrawRotaGraph(80, 630, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	//DrawRotaGraph(1200, 630, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

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
			DrawGraph((450 - (name_num - 1) * 26) + j * 53, 242 + i * 115 + 35, font_img[(int)name[j] - 65], TRUE);
		}
		
		//DrawFormatString(0, 0 + i * 20, 0x000000, "%d", name_num);

		// レベルの描画
		//DrawFormatStringToHandle(810, 242 + i * 100, 0x000000, font, "%02d", ranking->GetLevel(i));
		DrawGraph(789, 242 + i * 115 + 35, num_img[level / 10], TRUE);
		DrawGraph(835, 242 + i * 115 + 35, num_img[level % 10], TRUE);

		// コンボの描画
		//DrawFormatStringToHandle(1028, 242 + i * 100, 0x000000, font, "%03d", ranking->GetCombo(i));
		DrawGraph(1000, 242 + i * 115 + 35, num_img[combo / 100], TRUE);
		DrawGraph(1045, 242 + i * 115 + 35, num_img[(combo - combo / 100 * 100) / 10], TRUE);
		DrawGraph(1090, 242 + i * 115 + 35, num_img[combo % 10], TRUE);
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

void RankingScene::OpeAnim()
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