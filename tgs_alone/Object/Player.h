#pragma once

#define INPUT_MAX 10

class Player
{
private:
	int sound;         // 音データ

public:
	int input[INPUT_MAX]; // プレイヤーが入力したデータを保存
	bool input_flg;  // プレイヤーの入力があるかどうか

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
	void SetPlayerInput() { input_flg = false; }  // プレイヤーの入力状態の設定
};