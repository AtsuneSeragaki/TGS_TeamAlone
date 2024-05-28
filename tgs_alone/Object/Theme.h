#pragma once

#define THEME_MAX 20

class Theme
{
private:
	int sound;       // 音データ
	int img[4]; // お題画像
	int level_img[10];
	bool theme_flg;   // お題の生成フラグ

public:
	static int theme[THEME_MAX];  // お題 
	static int theme_num;    // お題の数

public:
	Theme();
	~Theme();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理

	int GetTheme(int num) { return theme[num]; } // お題のデータを返す
	int GetThemeNum() { return theme_num; } // お題の数を返す
	bool GetThemeFlg() { return theme_flg; } // お題設定中かどうか
	void SetThemeNum() { theme_num++; } // お題の数を増やす
	void SetThemeFlg(bool flg) { theme_flg = flg; }  // お題の生成フラグを設定
};