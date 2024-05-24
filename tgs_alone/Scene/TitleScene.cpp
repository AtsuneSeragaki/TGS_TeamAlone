#include "TitleScene.h"
#include "DxLib.h"

TitleScene::TitleScene() : back_img(0)
{

}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/title.png");

	if (back_img == -1)
	{
		throw("Resource/images/title.pngがありません");
	}
}

eSceneType TitleScene::Update()
{
	return GetNowScene();
}

void TitleScene::Draw() const
{
	// 背景表示
	DrawGraph(0, 0, back_img, TRUE);
}

void TitleScene::Finalize()
{
}

eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}