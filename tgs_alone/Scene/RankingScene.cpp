#include "RankingScene.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

RankingScene::RankingScene():back_img(0),ranking(nullptr)
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
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
	SetFontSize(30);
	DrawString(0, 0, "RANKING", 0xffffff);
	DrawString(0, 40, "B:TITLE", 0xff0000);

	// 取得したランキングデータを描画する
	for (int i = 0; i < 4; i++)
	{
		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-15s %2d %3d", ranking->GetRank(i), ranking->GetName(i), ranking->GetLevel(i), ranking->GetCombo(i));
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