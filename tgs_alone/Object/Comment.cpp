#include "Comment.h"
#include "Player.h"
#include "Theme.h"
#include "DxLib.h"

Comment::Comment():disp_flg(false),com_num(0),p_num(0),t_num(0),cnt(0),font(0),font2(0), transparency(0),char_num(0),char_flg(false),com_img(0)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			char_img[i][j] = 0;
		}
	}
}

Comment::~Comment()
{
}

void Comment::Initialize()
{
	// 画像データの読み込み
	char_img[0][0] = LoadGraph("Resource/images/main/comment/char1-9.png");
	char_img[0][1] = LoadGraph("Resource/images/main/comment/char1-8.png");
	char_img[0][2] = LoadGraph("Resource/images/main/comment/char1-7.png");
	char_img[0][3] = LoadGraph("Resource/images/main/comment/char1-6.png");
	char_img[0][4] = LoadGraph("Resource/images/main/comment/char1-5.png");
	char_img[0][5] = LoadGraph("Resource/images/main/comment/char1.png");
	char_img[0][6] = LoadGraph("Resource/images/main/comment/char1-4.png");
	char_img[0][7] = LoadGraph("Resource/images/main/comment/char1-3.png");
	char_img[0][8] = LoadGraph("Resource/images/main/comment/char1-2.png");
	char_img[0][9] = LoadGraph("Resource/images/main/comment/char1-1.png");

	char_img[1][0] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][1] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][2] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][3] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][4] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][5] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][6] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][7] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][8] = LoadGraph("Resource/images/main/comment/char2.png");
	char_img[1][9] = LoadGraph("Resource/images/main/comment/char2.png");

	char_img[2][0] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][1] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][2] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][3] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][4] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][5] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][6] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][7] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][8] = LoadGraph("Resource/images/main/comment/char3.png");
	char_img[2][9] = LoadGraph("Resource/images/main/comment/char3.png");

	char_img[3][0] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][1] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][2] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][3] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][4] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][5] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][6] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][7] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][8] = LoadGraph("Resource/images/main/comment/char4.png");
	char_img[3][9] = LoadGraph("Resource/images/main/comment/char4.png");

	char_img[4][0] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][1] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][2] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][3] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][4] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][5] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][6] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][7] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][8] = LoadGraph("Resource/images/main/comment/char5.png");
	char_img[4][9] = LoadGraph("Resource/images/main/comment/char5.png");
	
	com_img = LoadGraph("Resource/images/main/comment/hukidasi.png");

	// フォントデータの読み込み
	font = CreateFontToHandle("Segoe UI", 40, 7, DX_FONTTYPE_ANTIALIASING);
	font2 = CreateFontToHandle("Segoe UI", 30, 7, DX_FONTTYPE_ANTIALIASING);

	// エラーチェック
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (char_img[i][j] == -1)
			{
				throw("char_img[%d][%d]がありません", i,j);
			}
		}
	}

	if (com_img == -1)
	{
		throw("Resource/images/main/comment/hukidasi.pngがありません");
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
	//disp_flg = false;
	disp_flg = true;
	t_num = 0;
	p_num = 0;
	cnt = 0;
	com_num = -1;
	transparency = 255;
	char_num = 0;
	char_flg = false;
}

void Comment::Update()
{
	// コメント表示フラグがtrueだったら
	if (disp_flg == true)
	{
		cnt++;
		
		if (char_flg == false)
		{
			char_num++;

			if (char_num == 9)
			{
				char_flg = true;
			}
		}
		else
		{

			if (char_num <= 6)
			{
				char_num--;
			}
		}

		// cntが50より大きかったら
		if (cnt > 71)
		{
			cnt = 0;
			//disp_flg = false;
			char_flg = false;
			char_num = 0;
		}
	}
	/*else
	{
		if (transparency != 0)
		{
			transparency = 0;
		}
	}*/
}

void Comment::Draw()
{
	if (disp_flg == true)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, transparency);

		// キャラクターを描画
		DrawGraph(0, 0, com_img, TRUE);

		DrawGraph(340, 250, char_img[0][7], TRUE);
		DrawStringToHandle(SB_X, SB_Y, "Genius!", 0x000000, font);

		// コメントを描画
		switch (com_num)
		{
		case 0:
			DrawGraph(360 - char_num * 3, 270, char_img[0][7], TRUE);
			DrawStringToHandle(SB_X, SB_Y , "Genius!", 0x000000, font);
			break;

		case 1:
			DrawGraph(360, 280, char_img[0][char_num], TRUE);
			DrawStringToHandle(SB_X - 15, SB_Y, "Excellent!", 0x000000, font);
			break;

		case 2:
			DrawGraph(360, 280, char_img[2][char_num], TRUE);
			DrawStringToHandle(SB_X + 15, SB_Y, "Great!", 0x000000, font);
			break;

		case 3:
			DrawGraph(360, 280, char_img[1][char_num], TRUE);
			DrawStringToHandle(SB_X + 30, SB_Y, "Nice!", 0x000000, font);
			break;

		case 4:
			DrawGraph(360, 280, char_img[0][char_num], TRUE);
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
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			DeleteGraph(char_img[i][j]);
		}
	}

	DeleteGraph(com_img);
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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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

		break;

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