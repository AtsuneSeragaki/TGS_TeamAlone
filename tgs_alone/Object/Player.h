#pragma once

#define INPUT_MAX 20
#define PI    3.1415926535897932384626433832795f

class Player
{
private:
	int sound[2];    // 音データ
	int img[4][5];      // 画像データ
	int combo_img[10];
	int mis_img[4];
	int comment[2];
	int mcom_cnt[INPUT_MAX];
	int com_cnt[INPUT_MAX];
	int correct[INPUT_MAX];
	int player_anim[INPUT_MAX];
	int mis_anim[INPUT_MAX];
	int mistake_flg[INPUT_MAX]; // 間違えた時のアニメーションフラグ
	int mis_data[INPUT_MAX]; // プレイヤーが間違えたものを保存
	int mistake_cnt; // 間違えた時のアニメーションカウント
	int mis_anim2[INPUT_MAX];
	int cnt;
	int mis_y[INPUT_MAX];
	int effect_img[2];
	int effect[INPUT_MAX];

public:
	int input[INPUT_MAX]; // プレイヤーが入力したデータを保存
	bool input_draw[INPUT_MAX]; // プレイヤーが入力したデータを表示したかどうか
	bool mis_draw[INPUT_MAX]; // プレイヤーが入力したデータを表示したかどうか
	bool input_flg;   // プレイヤーの入力ができるかどうか
	bool button_flg;  // プレイヤーの入力があるかどうか
	static int combo; // 連続で当たった数保存用
	static int correct_num;  // プレイヤーが正解した数
	static int mis_num;  // プレイヤーが間違えた数

public:
	Player();
	~Player();

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// 終了時処理
	void Finalize();

	// ボタンが落ちる演出
	void FallAnim();
	// MisYの設定
	void SetMisY();
	// プレイヤーの情報を初期化
	void ResetPlayerState();
	// プレイヤーの入力とお題の比較 
	void Comparison();
	// 当たった数設定
	void SetPlayerAnim();
	// コメントの表示時間
	void SetCom();
	// ミスコメントの表示時間
	void SetMisCom();
	// プレイヤーの入力状態を返す
	bool GetPlayerInput() { return input_flg; } 
	// プレイヤーの入力状態の設定
	void SetPlayerInput(bool flg) { input_flg = flg; }  
	// プレイヤーが入力したデータを表示したか返す
	bool GetInputDraw(int num) { return input_draw[num]; }  
};