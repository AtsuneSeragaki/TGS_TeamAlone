#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"

#define THEME_MAX 15

class GameMainScene : public SceneBase
{
private:
	int back_img;     // 背景画像
	int theme_img[4]; // お題画像
	int bgm;
	int se;
	float time;       // 制限時間
	int time_cnt;     // 1秒減らすタイミングをカウント
	int theme[THEME_MAX];  // お題 
	bool theme_flg;   // お題を出すか出さないかフラグ
	int theme_num;    // お題の数
	Player player;

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	void SetTheme(void);  // お題を設定する
};