#pragma once

#define TIME_Y 105   // 時間(秒)の描画位置Y座標
#define TIME_X 475   // 時間(秒)の描画位置X座標

class Time
{
private:
	bool time_flg;     // 1秒減らすタイミングをカウント
	int img_b[11];     // 画像データ
	int img_r[11];     // 画像データ

public:
	int time;   // 制限時間(秒)
	int time2;  // 制限時間(ミリ秒)

public:

	// コンストラクタ
	Time();

	// デストラクタ
	~Time();

	// 初期化処理
	void Initialize();  

	// 更新処理
	void Update();   

	// 描画処理
	void Draw();   

	// 終了時処理
	void Finalize();   

	// 制限時間を止めたり再開したりするフラグの設定
	void SetTimeFlg(bool flg) { time_flg = flg; } 

	// 制限時間を返す
	int GetTime() { return time; } 

	// 制限時間から1秒マイナス
	void SetTime() { time--; } 
};