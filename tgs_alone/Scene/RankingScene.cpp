#include "RankingScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingScene::RankingScene():back_img(0),ranking(nullptr),font(0),bgm(0), star_img(0), star_cnt(0)
{
	se[0] = 0;
	se[1] = 0;
}

RankingScene::~RankingScene()
{
	// フォントデータの削除
	DeleteFontToHandle(font);

	// 画像データの削除
	DeleteGraph(back_img);
	DeleteGraph(star_img);

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

	// フォントデータの読み込み
	font = CreateFontToHandle("Segoe UI", 45, 7, DX_FONTTYPE_ANTIALIASING);

	// 音データの読み込み
	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");
	bgm = LoadSoundMem("Resource/sounds/title/bgm2.mp3");

	// エラーチェック
	if (back_img == -1)
	{
		throw("Resource/images/ranking/ranking.pngがありません");
	}
	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
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
}

eSceneType RankingScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();

	// Bボタンが押されたら
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		// 効果音の再生
		PlaySoundMem(se[1], DX_PLAYTYPE_NORMAL, TRUE);

		// BGMを止める
		StopSoundMem(bgm);

		// タイトル画面に遷移
		return eSceneType::E_TITLE;
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
		
		// 名前の描画
		DrawFormatStringToHandle(450 - (name_num - 1) * 15, 242 + i * 100, 0x000000, font, "%s", name);

		// レベルの描画
		DrawFormatStringToHandle(810, 242 + i * 100, 0x000000, font, "%02d", ranking->GetLevel(i));

		// コンボの描画
		DrawFormatStringToHandle(1028, 242 + i * 100, 0x000000, font, "%03d", ranking->GetCombo(i));
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