#include "EndScene.h"
#include "DxLib.h"

int EndScene::cnt = 0;

EndScene::EndScene():back_img(0)
{
}

EndScene::~EndScene()
{
}

void EndScene::Initialize()
{
	cnt = 0;
}

eSceneType EndScene::Update()
{
	cnt++;

	return GetNowScene();
}

void EndScene::Draw() const
{
	SetFontSize(30);
	DrawString(0, 0, "END", 0xffffff);
	DrawFormatString(30, 0,0xffffff,"%d",cnt);
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}