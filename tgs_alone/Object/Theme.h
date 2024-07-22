#pragma once

#define THEME_MAX 20

class Theme
{
private:
	int sound;  // 音データ
	int img[4]; // お題画像
	int level_img[10]; // レベル数字画像のデータ
	bool theme_flg;    // お題の生成フラグ
	int 

public:
	static int theme[THEME_MAX]; // お題 
	static int theme_num;        // お題の数

public:

	// コンストラクタ
	Theme();

	// デストラクタ
	~Theme();

	// 初期化処理
	void Initialize();  

	// 更新処理
	void Update();  

	// 描画処理
	void Draw();

	// 終了時処理
	void Finalize();   

	// お題のデータを返す
	int GetTheme(int num) { return theme[num]; } 

	// お題の数を返す
	int GetThemeNum() { return theme_num; } 

	// お題設定中かどうか
	bool GetThemeFlg() { return theme_flg; } 

	// お題の数を増やす
	void SetThemeNum() { theme_num++; } 

	// お題の生成フラグを設定
	void SetThemeFlg(bool flg) { theme_flg = flg; }  
};