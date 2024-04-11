#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene():back_img(0)
{
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
}

eSceneType GameMainScene::Update()
{
	return GetNowScene();
}

void GameMainScene::Draw() const
{
#ifdef _DEBUG
	DrawString(0, 0, "GameMain", 0xffffff);

#endif // _DEBUG

}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}