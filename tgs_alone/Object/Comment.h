#pragma once

class Comment
{
private:
	bool disp_flg; // 表示するかしないかのフラグ
	int com_num;   // 表示するコメントの種類
	int p_num;     // プレイヤーが正解した数
	int t_num;     // お題の数
	int cnt;       // 表示時間カウント用

public:
	Comment();
	~Comment();

	void Initialize();  // 初期化処理
	void Update();      // 更新処理
	void Draw();        // 描画処理
	void Finalize();    // 終了時処理

	// フラグの設定
	void SetDispFlg(bool flg) { disp_flg = flg; }

	// プレイヤーとお題の数の設定
	void SetNum(int p, int t) { p_num = p, t_num = t; }

	// どのコメントを出すか決める
	void SetComNum();  
};