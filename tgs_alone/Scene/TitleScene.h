﻿#pragma once

#include "SceneBase.h"

#define PI    3.1415926535897932384626433832795f

class TitleScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int ope_img[4];   // 操作説明画像
	int menu_img[8];  // メニュー画像
	int star_img[6];  // 星画像
	int tran_img;     // トランジション画像
	int cloud_img;    // 雲画像
	int se[2];        // 効果音
	int bgm;          // BGM
	int star_cnt;     // 星の回転用
	int star_cnt2;     // 星の回転用
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用
	bool rota_flg;    // 回転変数 false:プラス true:マイナス
	bool star_flg;    // 流れ星の表示 false:しない true:する
	int cnt;          // フレームカウント
	int shoot_num;    // 表示する流れ星画像の番号
	int shoot_cnt;    // 流れ星を表示するまでの時間をカウント
	int shoot_x;      // 流れ星のX座標
	int shoot_y;      // 流れ星のY座標
	int shoot_x2;     // 流れ星2のX座標
	int shoot_y2;     // 流れ星2のY座標
	int shoot_ran;    // 流れ星の表示位置をランダムに取る 
	int shoot_ran2;   // 流れ星2の表示位置をランダムに取る 
	int char_y;       // キャラクターのY座標
	bool move_flg;    // キャラクターの移動 false:下 true:上
	bool pos_flg;     // キャラクターの表示位置 false:左 true:右
	int char_stay;    // キャラクターをある位置で止める

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

	// メニューカーソルの横にある画像の動き
	void CursorAnim();

	// 星の移動処理
	void StarMove();

	// 画面切り替えアニメーション
	void Transition();

	// 流れ星アニメーション
	void ShootStarAnim();

	// 流れ星の表示位置の設定
	void SetStarPos();

	// キャラクターのY座標変更
	void SetCharY();

	// 操作説明のボタンのアニメーション
	void OpeAnim();
};
