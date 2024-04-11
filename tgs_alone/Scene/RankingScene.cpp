#include "RankingScene.h"

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
}

void RankingScene::Finalize()
{
}

eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}