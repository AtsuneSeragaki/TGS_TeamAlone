#include "HelpScene.h"

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
}

void HelpScene::Finalize()
{
}

eSceneType HelpScene::GetNowScene() const
{
	return eSceneType::E_HELP;
}