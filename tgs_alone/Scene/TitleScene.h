﻿#pragma once

#include "SceneBase.h"

#define PI    3.1415926535897932384626433832795f

class TitleScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int menu_img[8];  // メニュー画像
	int star_img[4];     // 星画像
	int tran_img;     // トランジション画像
	int se[2];        // 効果音
	int bgm;          // BGM
	int star_cnt;     // 星の回転用
	int star_x[8];       // 星のx座標
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用
	bool rota_flg;    // 回転変数 false:プラス true:マイナス

public:
	static int menu_cursor;  // カーソルがどこにあるか
	static bool back_title;  // タイトルに戻るか false:戻らない true:戻る

public:

	// コンストラクタ
	TitleScene();

	// デストラクタ
	virtual ~TitleScene();

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

	void StarAnim2();

	// 星の移動処理
	void StarMove();

	// 画面切り替えアニメーション
	void Transition();
};
