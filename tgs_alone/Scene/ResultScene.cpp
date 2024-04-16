#include "ResultScene.h"
#include "DxLib.h"

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
#ifdef _DEBUG
	SetFontSize(20);
	DrawString(0, 0, "Result", 0xffffff);

#endif // _DEBUG
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowScene() const
{
	return eSceneType::E_RESULT;
}