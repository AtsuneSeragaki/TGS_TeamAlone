#pragma once

#define SB_X 30   // 吹き出しのX座標
#define SB_Y 520  // 吹き出しのY座標

class Comment
{
private:
	int char_img[7];  // キャラクター画像用
	int com_img[5];   // 吹き出し画像用
	int font;         // フォント用
	int font2;        // サイズ違いのフォント用
	bool disp_flg;    // コメントを表示するかしないかのフラグ
	int com_num;      // 表示するコメントの種類
	int p_num;        // プレイヤーが間違えた数
	int t_num;        // お題の数
	int cnt;          // 表示時間カウント用

public:

	// コンストラクタ
	Comment();

	// デストラクタ
	~Comment();

	// 初期化処理
	void Initialize();  

	// 更新処理
	void Update();

	// 描画処理
	void Draw();  

	// 終了時処理
	void Finalize();

	// フラグの設定
	void SetDispFlg(bool flg) { disp_flg = flg; }

	// プレイヤーとお題の数の設定
	void SetNum(int p, int t) { p_num = p, t_num = t; }

	// どのコメントを出すか決める
	void SetComNum();  
};