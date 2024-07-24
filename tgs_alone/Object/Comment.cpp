#include "Comment.h"
#include "Player.h"
#include "Theme.h"
#include "DxLib.h"

Comment::Comment():disp_flg(false),com_num(0),p_num(0),t_num(0),cnt(0),font(0),font2(0), transparency(0)
{
	for (int i = 0; i < 7; i++)
	{
		char_img[i] = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		com_img[i] = 0;
	}
}

Comment::~Comment()
{
}

void Comment::Initialize()
{
	// 画像データの読み込み
	//char_img[0] = LoadGraph("Resource/images/main/comment/char1.png");
	char_img[0] = LoadGraph("Resource/images/main/comment/char1.png");
	char_img[1] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[2] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[3] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[4] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[5] = LoadGraph("Resource/images/main/comment/fchar.png");
	char_img[6] = LoadGraph("Resource/images/main/comment/char7.png");
	
	//com_img[0] = LoadGraph("Resource/images/main/comment/comment1.png");
	com_img[0] = LoadGraph("Resource/images/main/comment/hukidasi.png");

	com_img[1] = LoadGraph("Resource/images/main/comment/comment2.png");
	com_img[2] = LoadGraph("Resource/images/main/comment/comment3.png");
	com_img[3] = LoadGraph("Resource/images/main/comment/comment4.png");
	com_img[4] = LoadGraph("Resource/images/main/comment/comment5.png");

	// フォントデータの読み込み
	font = CreateFontToHandle("Segoe UI", 40, 7, DX_FONTTYPE_ANTIALIASING);
	font2 = CreateFontToHandle("Segoe UI", 30, 7, DX_FONTTYPE_ANTIALIASING);

	// エラーチェック
	for (int i = 0; i < 7; i++)
	{
		if (char_img[i] == -1)
		{
			throw("char_img[%d]がありません", i);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (com_img[i] == -1)
		{
			throw("com_img[%d]がありません", i);
		}
	}

	if (font == -1)
	{
		throw("Segoe UIがありません");
	}
	if (font2 == -1)
	{
		throw("Segoe UIがありません");
	}

	// 変数の初期化
	disp_flg = false;
	t_num = 0;
	p_num = 0;
	cnt = 0;
	com_num = -1;
	transparency = 0;
}

void Comment::Update()
{
	// コメント表示フラグがtrueだったら
	if (disp_flg == true)
	{
		cnt++;

		// cntが50より大きかったら
		if (cnt > 71)
		{
			cnt = 0;
			disp_flg = false;
		}
	}
	else
	{
		if (transparency != 0)
		{
			transparency = 0;
		}
	}
}

void Comment::Draw()
{
	if (disp_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);

		// キャラクターを描画
		DrawGraph(0, 0, com_img[0], TRUE);

		// コメントを描画
		switch (com_num)
		{
		case 0:
			DrawGraph(360, 300, char_img[5], TRUE);
			DrawStringToHandle(SB_X, SB_Y , "Genius!", 0x000000, font);
			break;

		case 1:
			DrawGraph(360, 300, char_img[5], TRUE);
			DrawStringToHandle(SB_X - 15, SB_Y, "Excellent!", 0x000000, font);
			break;

		case 2:
			DrawGraph(360, 300, char_img[5], TRUE);
			DrawStringToHandle(SB_X + 15, SB_Y, "Great!", 0x000000, font);
			break;

		case 3:
			DrawGraph(360, 300, char_img[5], TRUE);
			DrawStringToHandle(SB_X + 30, SB_Y, "Nice!", 0x000000, font);
			break;

		case 4:
			DrawGraph(360, 300, char_img[5], TRUE);
			DrawStringToHandle(SB_X - 25, SB_Y + 5, "You can do it!", 0x000000, font2);
			break;
			
		default:
			break;
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Comment::Finalize()
{
	// フォントデータの削除
	DeleteFontToHandle(font);
	DeleteFontToHandle(font2);

	// 画像データの削除
	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(char_img[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		DeleteGraph(com_img[i]);
	}
}

void Comment::SetComNum()
{
	// プレイヤーが間違えた数によって表示するコメントの種類を変える
	// お題の数によって条件を変える
	switch (t_num)
	{
	case 3:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 3)
		{
			com_num = 2;
		}
		else
		{
			com_num = 4;
		}

	case 4:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 3)
		{
			com_num = 2;
		}
		else
		{
			com_num = 4;
		}

	case 5:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 2)
		{
			com_num = 2;
		}
		else if (p_num < 5)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 6:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 6)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 7:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 7)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 8:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 8)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 9:

		if (p_num == 0)
		{
			com_num = 1;
		}
		else if (p_num < 7)
		{
			com_num = 2;
		}
		else if (p_num < 9)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 10:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 5)
		{
			com_num = 1;
		}
		else if (p_num < 8)
		{
			com_num = 2;
		}
		else if (p_num < 10)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 11:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 4)
		{
			com_num = 1;
		}
		else if (p_num < 9)
		{
			com_num = 2;
		}
		else if (p_num < 11)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 12:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 12)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 13:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 6)
		{
			com_num = 2;
		}
		else if (p_num < 12)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 14:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 14)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 15:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 15)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 16:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 5)
		{
			com_num = 2;
		}
		else if (p_num < 16)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 17:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 3)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 17)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 18:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 18)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 19:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 19)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	case 20:

		if (p_num == 0)
		{
			com_num = 0;
		}
		else if (p_num < 2)
		{
			com_num = 1;
		}
		else if (p_num < 4)
		{
			com_num = 2;
		}
		else if (p_num < 20)
		{
			com_num = 3;
		}
		else
		{
			com_num = 4;
		}

	default:
		break;
	}
	
}

void Comment::FadeInOut(bool flg)
{
	if (flg == false)
	{
		if (transparency <= 230)
		{
			transparency += 25;
		}
		else
		{
			transparency = 255;
		}
	}
	else
	{
		if (transparency >= 13)
		{
			transparency -= 13;
		}
		else
		{
			transparency = 0;
		}
	}
}