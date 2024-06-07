#include "EndScene.h"
#include "DxLib.h"

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
	SetFontSize(30);
	DrawString(0, 0, "END", 0xffffff);
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}