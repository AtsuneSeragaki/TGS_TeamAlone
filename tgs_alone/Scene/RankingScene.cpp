#include "RankingScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingScene::RankingScene():back_img(0),ranking(nullptr),font(0)
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
	back_img = LoadGraph("Resource/images/ranking/ranking.png");

	font = CreateFontToHandle("Segoe UI", 70, 7, DX_FONTTYPE_ANTIALIASING);

	// ランキング情報を取得
	ranking = new RankingData;
	ranking->Initialize();
}

eSceneType RankingScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	return GetNowScene();
}

void RankingScene::Draw() const
{
	DrawGraph(0, 0, back_img, TRUE);

	// 取得したランキングデータを描画する
	for (int i = 0; i < 3; i++)
	{
		DrawFormatStringToHandle(250, 242 + i * 135, 0x000000, font, "%s",ranking->GetName(i));
		DrawFormatStringToHandle(815, 242 + i * 135, 0x000000, font, "%02d", ranking->GetLevel(i));
		DrawFormatStringToHandle(1040, 242 + i * 135, 0x000000, font, "%03d", ranking->GetCombo(i));
	}
}

void RankingScene::Finalize()
{
	DeleteFontToHandle(font);

	DeleteGraph(back_img);

	// 動的メモリの解放
	ranking->Finalize();
	delete ranking;
}

eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}