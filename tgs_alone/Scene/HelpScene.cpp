#include "HelpScene.h"
#include "DxLib.h"

HelpScene::HelpScene():back_img(0)
{
}

HelpScene::~HelpScene()
{
}

void HelpScene::Initialize()
{
}

eSceneType HelpScene::Update()
{
	return GetNowScene();
}

void HelpScene::Draw() const
{
	SetFontSize(30);
	DrawString(0, 0,"HELP",0xffffff);
}

void HelpScene::Finalize()
{
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}