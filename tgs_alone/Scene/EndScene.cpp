#include "EndScene.h"
#include "DxLib.h"

int EndScene::cnt = 0;

EndScene::EndScene():back_img(0),bgm(0), star_img(0), star_cnt(0)
{
}

EndScene::~EndScene()
{
}

void EndScene::Initialize()
{
	// 画像データの読み込み
	back_img = LoadGraph("Resource/images/end/end.png");
	star_img = LoadGraph("Resource/images/help/star.png");

	// 音データの読み込み
	bgm = LoadSoundMem("Resource/sounds/title/bgm2.mp3");

	// エラーチェック
	if (back_img == -1)
	{
		throw("Resource/images/end/end.pngがありません");
	}
	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
	}
	if (bgm == -1)
	{
		throw("Resource/sounds/title/bgm2.mp3がありません");
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// 変数の初期化
	cnt = 0;
	star_cnt = 0;
}

eSceneType EndScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();

	cnt++;

	return GetNowScene();
}

void EndScene::Draw() const
{
	// 背景の描画
	DrawGraph(0, 0, back_img,TRUE);

	// 星の描画
	DrawRotaGraph(350, 60, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(800, 60, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1200, 60, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(70, 290, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(650, 290, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1060, 290, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(350, 390, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(900, 500, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(480, 600, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(750, 660, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);

}

void EndScene::Finalize()
{
}

eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}

void EndScene::StarAnim()
{
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}