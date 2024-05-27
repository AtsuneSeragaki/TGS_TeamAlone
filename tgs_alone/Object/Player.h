#pragma once

#define INPUT_MAX 20
#define PI    3.1415926535897932384626433832795f

class Player
{
private:
	int sound[2];    // 音データ
	int img[4][5];      // 画像データ
	//int mis_img[5];
	int mis_img;
	int mistake_flg[INPUT_MAX]; // 間違えた時のアニメーションフラグ
	int  mistake_cnt; // 間違えた時のアニメーションカウント
	int mis_data[INPUT_MAX]; // プレイヤーが間違えたものを保存
	int cnt;
	int player_anim[INPUT_MAX];
	
public:
	int input[INPUT_MAX]; // プレイヤーが入力したデータを保存
	int input_draw[INPUT_MAX]; // プレイヤーが入力したデータを表示したかどうか
	bool input_flg;   // プレイヤーの入力ができるかどうか
	bool button_flg;  // プレイヤーの入力があるかどうか

public:
	Player();
	~Player();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理

	int GetPlayerInputData(int num) { return input[num]; }  // プレイヤーが入力したデータを返す
	void ResetPlayerInput(int num) { input[num] = -1; }    // プレイヤーの入力データをリセット
	bool GetPlayerInput() { return input_flg; }  // プレイヤーの入力状態を返す
	void SetPlayerInput(bool flg) { input_flg = flg; }  // プレイヤーの入力状態の設定
	bool GetButtonInput() { return button_flg; }  // プレイヤーの入力状態を返す
	void SetButtonInput(bool flg) { button_flg = flg; }  // プレイヤーの入力状態の設定
	void SetPlayerAnim(); // 当たった数設定
	int GetInputDraw(int num) { return input_draw[num]; }  // プレイヤーが入力したデータを表示したか返す
	void  ResetInputDraw(int num) { input_draw[num] = -1; }  // プレイヤーの入力データ表示をリセット
	void SetPlayerMis(int num,int button) { mis_data[num] = button; }  // プレイヤーの入力状態の設定
	void ResetPlayerAnim(); // プレイヤーが当たった時のボタンの動き
};