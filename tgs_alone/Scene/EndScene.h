﻿#pragma once

#include "SceneBase.h"

#define PI    3.1415926535897932384626433832795f

class EndScene : public SceneBase
{
private:
	int back_img;  // 背景画像
	int star_img;  // 星画像
	int tran_img;         // トランジション画像
	int star_cnt;  // 星の回転用
	bool tran_flg;        // 画面遷移 false:しない true:する
	int transition;     // トランジションの値保存用
	
public:
	static int cnt;  // 終了までのカウント用変数

public:

	// コンストラクタ
	EndScene();

	// デストラクタ
	virtual ~EndScene();

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
};
