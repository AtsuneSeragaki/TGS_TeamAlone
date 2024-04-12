#pragma once

class Time
{
private:
	float time;       // 制限時間
	bool time_flg;     // 1秒減らすタイミングをカウント

public:
	Time();
	~Time();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理

	void SetTimeFlg(bool flg); // 制限時間を止めたり再開したりするフラグの設定
};