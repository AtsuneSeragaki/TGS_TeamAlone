#include "ResultScene.h"

ResultScene::ResultScene():back_img(0)
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{
}

eSceneType ResultScene::Update()
{
	return GetNowScene();
}

void ResultScene::Draw() const
{
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}