﻿#pragma once

#include "SceneBase.h"

#define NUM_Y 415
#define RANK_X 730
#define RANK_Y 230

#define PI    3.1415926535897932384626433832795f

class ResultScene : public SceneBase
{
private:
	int back_img;   // 背景画像 
	int num_img[10];   // 数字画像
	int rank_img[9][5];   // ランク画像
	int star_img;      // 星画像
	int tran_img;      // トランジション画像
	int button_img[3]; // 操作ガイド画像
	int se;            // 効果音
	int bgm;           // BGM
	int rank[3];       // ランクデータ
	char name[5][15];  // 名前データ
	int level[5];      // レベルデータ
	int combo[5];      // コンボデータ
	int star_cnt;      // 星の回転用
	bool tran_flg;     // 画面遷移 false:しない true:する
	int transition;    // トランジションの値保存用
	int cnt;           // フレームカウント
	int rank_num;      // ランクのアニメーション用
	int rank_cnt;      // rank_numを増やす時間カウントダウン
	int level_max;     // プレイヤーのMAXレベル数
	int combo_max;     // プレイヤーのMAXコンボ数
	int mis_max;       // プレイヤーのMAXミス数
	int level_num;     // 表示するプレイヤーのMAXレベル数
	int combo_num;     // 表示するプレイヤーのMAXコンボ数
	int mis_num;       // 表示するプレイヤーのMAXミス数
	int numanim_cnt;   // NumAnim()を実行するまでのカウント

public:

	static bool result_tran;      // リザルトに遷移	 false:しない true:する

	// コンストラクタ
	ResultScene();

	// デストラクタ
	virtual ~ResultScene();

	// 初期化処理
	virtual void Initialize() override;

	// 更新処理
	virtual eSceneType Update() override;

	// 描画処理
	virtual void Draw() const override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーンを取得
	virtual eSceneType GetNowScene() const override;

	// 星の回転処理
	void StarAnim();

	// 画面切り替えアニメーション
	void Transition();

	// ランクアニメーション処理
	void RankAnim();

	// レベル数、コンボ数、ミス数のアニメーション
	void NumAnim();
};