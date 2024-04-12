#include "InputRankingScene.h"

InputRankingScene::InputRankingScene():back_img(0)
{
}

InputRankingScene::~InputRankingScene()
{
}

void InputRankingScene::Initialize()
{
}

eSceneType InputRankingScene::Update()
{
	return GetNowScene();
}

void InputRankingScene::Draw() const
{
}

void InputRankingScene::Finalize()
{
}

eSceneType InputRankingScene::GetNowScene() const
{
	return eSceneType::E_INPUT_RANKING;
}