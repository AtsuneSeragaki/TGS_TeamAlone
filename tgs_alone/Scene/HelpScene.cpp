#include "HelpScene.h"
#include "../Utility/InputControl.h"
#include "TitleScene.h"
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
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return eSceneType::E_TITLE;
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{
		TitleScene::menu_cursor = 0;
		return eSceneType::E_MAIN;
	}

	return GetNowScene();
}

void HelpScene::Draw() const
{
	SetFontSize(30);
	DrawString(0, 0,"HELP",0xffffff);
	DrawString(0, 30, "X:GAME MAIN B:TITLE", 0xff0000);
}

void HelpScene::Finalize()
{
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}