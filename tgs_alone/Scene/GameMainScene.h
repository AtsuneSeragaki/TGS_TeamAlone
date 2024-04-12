#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Time.h"
#include "../Object/Theme.h"

class GameMainScene : public SceneBase
{
private:
	int back_img;     // 背景画像
	int bgm;
	int se;
	int player_input[15]; // プレイヤーが入力したものが当たっていた時保存
	int correct_num;  // プレイヤーが正解した数    
	Player* player;   // プレイヤー
	Time* time;       // 制限時間
	Theme* theme;     // お題

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void Comparison(); // お題とプレイヤーの入力を比較
};