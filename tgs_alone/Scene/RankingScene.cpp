#include "RankingScene.h"
#include "DxLib.h"

RankingScene::RankingScene():back_img(0)
{
}

RankingScene::~RankingScene()
{
}

void RankingScene::Initialize()
{
}

eSceneType RankingScene::Update()
{
	return GetNowScene();
}

void RankingScene::Draw() const
{
	SetFontSize(30);
	DrawString(0, 0, "RANKING", 0xffffff);
}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}