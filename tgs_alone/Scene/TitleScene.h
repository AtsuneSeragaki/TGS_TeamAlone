#pragma once

#include "SceneBase.h"

#define PI    3.1415926535897932384626433832795f

class TitleScene : public SceneBase
{
private:
	int back_img;     // 背景画像 
	int logo_img;     // タイトルロゴ画像
	int ope_img;      // 操作説明画像
	int menu_img[8];  // メニュー画像
	int star_img[5];  // 星画像
	int tran_img;     // トランジション画像
	int deco_img[5];  // メニュー飾り画像
	int cloud_img;    // 雲画像 
	int se[2];        // 効果音
	int bgm;          // BGM
	int star_cnt;     // 星の回転用
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用
	bool rota_flg;    // 回転変数 false:プラス true:マイナス
	bool star_flg;    // 流れ星の表示 false:しない true:する
	int shoot_num;    // 表示する流れ星画像の番号
	int shoot_cnt;    // 流れ星を表示するまでの時間をカウント
	int shoot_x;      // 流れ星のX座標
	int shoot_y;      // 流れ星のY座標
	int cnt;          // フレームカウント

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

	// 星とかの動き
	void StarAnim2();

	// 星の移動処理
	void StarMove();

	// 画面切り替えアニメーション
	void Transition();

	// 流れ星アニメーション
	void ShootStarAnim();
};
