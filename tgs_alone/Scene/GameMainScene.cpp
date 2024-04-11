#include "GameMainScene.h"
#include "DxLib.h"

GameMainScene::GameMainScene() :back_img(0),bgm(0), se(0), player(nullptr), time(nullptr),theme(nullptr)
{
}

GameMainScene::~GameMainScene()
{
}

void GameMainScene::Initialize()
{
	// オブジェクトの生成
	player = new Player;
	time = new Time;
	theme = new Theme;

	// オブジェクトの初期化
	player->Initialize();
	time->Initialize();
	theme->Initialize();
}

eSceneType GameMainScene::Update()
{
	theme->Update();
	time->Update();
	player->Update();

	return GetNowScene();
}

void GameMainScene::Draw() const
{
#ifdef _DEBUG
	DrawString(0, 0, "GameMain", 0xffffff);

#endif // _DEBUG

	time->Draw();

	theme->Draw();

	player->Draw();
}

void GameMainScene::Finalize()
{
}

eSceneType GameMainScene::GetNowScene() const
{
	return eSceneType::E_MAIN;
}