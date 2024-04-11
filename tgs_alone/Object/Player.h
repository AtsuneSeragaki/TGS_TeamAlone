#pragma once

class Player
{
private:
	int image[4];      // 画僧データ
	int sound;         // 音データ

public:
	Player();
	~Player();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理
};