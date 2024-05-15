#pragma once

class Time
{
private:
	bool time_flg;     // 1秒減らすタイミングをカウント
	int img_b[10];       // 画像データ
	int img_r[10];       // 画像データ

public:
	float time;       // 制限時間
	float time2[5];

public:
	Time();
	~Time();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理

	void SetTimeFlg(bool flg) { time_flg = flg; } // 制限時間を止めたり再開したりするフラグの設定
	float GetTime() { return time; } // 制限時間を返す
	void SetTime() { time -= 1.0f; } // 制限時間から一秒マイナス
};