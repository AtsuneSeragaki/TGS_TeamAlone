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

	back_img = LoadGraph("Resource/images/end/end.png");
}

eSceneType EndScene::Update()
{
	cnt++;

	return GetNowScene();
}

void EndScene::Draw() const
{
	DrawGraph(0, 0, back_img,TRUE);
}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}