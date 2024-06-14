#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Time.h"
#include "../Object/Theme.h"
#include "../Object/Comment.h"

class GameMainScene : public SceneBase
{
private:
	int sound[5];     // 音データ
	int img[7];       // 画像データ
	int begin_time;   // 開始までのカウントダウン
	int begin_cnt;    // カウントダウンまでのカウントダウン
	int draw_cnt;     // お題の設定を数フレーム後に
	bool timeup_flg;  // 時間0かどうかのフラグ
	int timeup_cnt;   // タイムアップのアニメーション用
	bool pause;       // ポーズフラグ
	int pause_cursor; // ポーズ画面のカーソル
	int pause_img[8]; // ポーズ画面の画像
	
    Player* player;   // プレイヤー
	Time* time;       // 制限時間
	Theme* theme;     // お題
	Comment* comment; // コメント

public:
	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

private:
	/* タイムアップアニメーション */
	void TimeupAnim(); 
};