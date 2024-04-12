#pragma once

#define THEME_MAX 15

class Theme
{
private:
	int theme_img[4]; // お題画像
	int theme[THEME_MAX];  // お題 
	bool theme_flg;   // お題を出すか出さないかフラグ
	int theme_num;    // お題の数

public:
	Theme();
	~Theme();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理
};