#pragma once

#include "SceneBase.h"
#include "../Object/Player.h"
#include "../Object/Time.h"
#include "../Object/Theme.h"
#include "../Object/Comment.h"

#define PI    3.1415926535897932384626433832795f

class GameMainScene : public SceneBase
{
private:
	int img[8];       // 画像データ
	int pause_img[8]; // ポーズ画面の画像
	int tran_img;     // トランジション画像
	int button[3];    // 操作説明画像
	int star_img[5];  // 星画像
	int sound[6];     // 音データ
	int se[2];        // 効果音
	int begin_time;   // 開始までのカウントダウン
	int begin_cnt;    // カウントダウンまでのカウントダウン
	int draw_cnt;     // お題の設定を数フレーム後に
	bool timeup_flg;  // 時間0かどうかのフラグ
	int timeup_cnt;   // タイムアップのアニメーション用
	bool pause;       // ポーズフラグ
	int pause_cursor; // ポーズ画面のカーソル
	bool tran_flg;    // 画面遷移 false:しない true:する
	int transition;   // トランジションの値保存用
	bool restart;     // やり直し false:しない true:する
	int cnt;          // フレームカウント
	bool goal;        // すべてクリア false:してない true: した
	int shoot_num;    // 表示する流れ星画像の番号
	int shoot_cnt;    // 流れ星を表示するまでの時間をカウント
	int shoot_x;      // 流れ星のX座標
	int shoot_y;      // 流れ星のY座標
	int shoot_x2;     // 流れ星2のX座標
	int shoot_y2;     // 流れ星2のY座標
	int shoot_ran;    // 流れ星の表示位置をランダムに取る 
	int shoot_ran2;   // 流れ星2の表示位置をランダムに取る 
	bool star_flg;    // 流れ星の表示 false:しない true:する
	
    Player* player;   // プレイヤーのオブジェクト
	Time* time;       // 制限時間のオブジェクト
	Theme* theme;     // お題のオブジェクト
	Comment* comment; // コメントのオブジェクト

public:

	// コンストラクタ
	GameMainScene();

	// デストラクタ
	virtual ~GameMainScene();

	// 初期化処理
	virtual void Initialize() override;

	// 更新処理
	virtual eSceneType Update() override;

	// 描画処理
	virtual void Draw() const override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーン情報
	virtual eSceneType GetNowScene() const override;

	// タイムアップアニメーション
	void TimeupAnim(); 

	// 画面切り替えアニメーション
	void Transition();

	// ポーズ中の操作説明のボタンのアニメーション
	void OpeAnim();

	// 流れ星アニメーション
	void ShootStarAnim();

	// 流れ星の表示位置の設定
	void SetStarPos();
};