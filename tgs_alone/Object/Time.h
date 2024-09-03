#pragma once

#define TIME_Y 105   // 時間(秒)の描画位置Y座標
#define TIME_X 475   // 時間(秒)の描画位置X座標

class Time
{
private:
	bool time_flg;     // 1秒減らすタイミングをカウント
	int img_b[11];     // 画像データ
	int img_r[11];     // 画像データ
	int plus_img[3];      // 時間プラス画像
	bool add_flg;      // 追加する時間表示（false:しない true:する）
	int add_time;      // 追加する時間
	int add_cnt;       // 追加する時間表示の時間
	int transparency;      // 画像の透明度を保存用

public:
	int time;    // 制限時間(秒)
	int time2;   // 制限時間(ミリ秒)
	float time3; // バーの値

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

	// 追加する時間と表示フラグの設定
	void SetAddTime(bool flg, int num);

	// フェードアウトとフェードインさせる（false:フェードイン true:フェードアウト ）
	void FadeInOut(bool flg);

};