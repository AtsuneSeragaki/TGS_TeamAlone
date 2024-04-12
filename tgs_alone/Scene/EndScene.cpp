#include "EndScene.h"

EndScene::EndScene():back_img(0)
{
}

EndScene::~EndScene()
{
}

void EndScene::Initialize()
{
}

eSceneType EndScene::Update()
{
	return GetNowScene();
}

void EndScene::Draw() const
{
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}