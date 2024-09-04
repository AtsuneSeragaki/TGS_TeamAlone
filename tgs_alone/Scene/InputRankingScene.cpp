#include "InputRankingScene.h"
#include "../Utility/InputControl.h"
#include "../Object/Player.h"
#include "../Object/Theme.h"
#include "RankingScene.h"
#include "DxLib.h"

InputRankingScene::InputRankingScene():ranking(nullptr),level(0),combo(0),cursor_x(0),cursor_y(0),no_name(false),name_num(0),font(0),bgm(0), star_img(0), star_cnt(0),input_end(false), transition(0), tran_img(0), tran_flg(false),cnt(0)
{
	memset(name, NULL, (sizeof(char) * 6));

	for (int i = 0; i < 7; i++)
	{
		img[i] = 0;
	}

	for (int i = 0; i < 27; i++)
	{
		font_img[i] = 0;
	}

	for (int i = 0; i < 2; i++)
	{
		se[i] = 0;
	}
}

InputRankingScene::~InputRankingScene()
{
	// フォントデータの削除
	DeleteFontToHandle(font);

	// 画像データの削除
	DeleteGraph(star_img);

	for (int i = 0; i < 7; i++)
	{
		DeleteGraph(img[i]);
	}

	for (int i = 0; i < 27; i++)
	{
		DeleteGraph(font_img[i]);
	}

	DeleteGraph(tran_img);

	// 音データの削除
	DeleteSoundMem(se[0]);
	DeleteSoundMem(se[1]);
	DeleteSoundMem(bgm);
}

void InputRankingScene::Initialize()
{
	// 画像データの読み込み
	img[0] = LoadGraph("Resource/images/ranking/button1.png");
	img[1] = LoadGraph("Resource/images/ranking/button2.png");
	img[2] = LoadGraph("Resource/images/ranking/button3.png");
	img[3] = LoadGraph("Resource/images/ranking/input.png");
	img[4] = LoadGraph("Resource/images/ranking/noname.png");
	img[5] = LoadGraph("Resource/images/ranking/moji.png");
	img[6] = LoadGraph("Resource/images/ranking/cursor.png");

	star_img = LoadGraph("Resource/images/help/star.png");

	tran_img = LoadGraph("Resource/images/tansition/transition.png");

	LoadDivGraph("Resource/images/ranking/moji.png", 27, 9, 3, 73, 73, font_img);

	// 音データの読み込み
	se[0] = LoadSoundMem("Resource/sounds/title/move.mp3");
	se[1] = LoadSoundMem("Resource/sounds/title/ok.mp3");
	bgm = LoadSoundMem("Resource/sounds/title/bgm.mp3");

	// フォントデータの読み込み
	font = CreateFontToHandle("Segoe UI", 70, 7, DX_FONTTYPE_ANTIALIASING);

	// エラーチェック
	for (int i = 0; i < 7; i++)
	{
		if (img[i] == -1)
		{
			throw("img[%d]がありません",i);
		}
	}

	for (int i = 0; i < 27; i++)
	{
		if (font_img[i] == -1)
		{
			throw("font_img[%d]がありません", i);
		}
	}

	if (star_img == -1)
	{
		throw("Resource/images/help/star.pngがありません");
	}
	if (tran_img == -1)
	{
		throw("Resource/images/tansition/transition.pngがありません");
	}
	if (font == -1)
	{
		throw("Segoe UIがありません");
	}
	if (se[0] == -1)
	{
		throw("Resource/sounds/title/move.mp3がありません");
	}
	if (se[1] == -1)
	{
		throw("Resource/sounds/title/ok.mp3がありません");
	}
	if (bgm == -1)
	{
		throw("Resource/sounds/title/bgm.mp3がありません");
	}

	// BGMの音量設定
	ChangeVolumeSoundMem(100, bgm);

	// メモリの動的確保
	ranking = new RankingData;
	ranking->Initialize();

	// 変数の初期化
	level = Theme::theme_num - 2;
	combo = Player::combo;
	no_name = true;
	name_num = -1;
	star_cnt = 0;
	input_end = false;
	transition = -93;
	tran_flg = true;
	cnt = 0;
}

eSceneType InputRankingScene::Update()
{
	// BGMの再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// 星を回転させる
	StarAnim();

	if (no_name == true)
	{
		cnt++;

		if (cnt >= 70)
		{
			cnt = 0;
		}
	}
	else/* if (no_name == false && input_end == false)*/
	{
		cnt++;

		if (cnt >= 60)
		{
			cnt = 0;
		}
	}

	// 画面遷移用フラグ
	bool is_change = false;

	if (tran_flg == true)
	{
		if (RankingScene::to_ranking == true && transition <= -120)
		{
			Transition();
		}
		else if (RankingScene::to_ranking == true && transition > -120)
		{
			// ランキングに遷移
			return eSceneType::E_RANKING;
		}
		else if (transition <= 1943)
		{
			Transition();
		}
		else
		{
			tran_flg = false;
			transition = -1943;
		}
	}
	else
	{
		// 名前入力処理
		is_change = InputName();

		// シーン変更は可能か？
		if (is_change)
		{
			// BGMの再生を止める
			StopSoundMem(bgm);

			RankingScene::to_ranking = true;
			tran_flg = true;
		}
	}

	return GetNowScene();
}

void InputRankingScene::Draw() const
{
	// 背景の描画
	DrawGraph(0, 0, img[3], TRUE);

	// 星の描画
	DrawRotaGraph(100, 70, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1180, 70, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(100, 650, 1.0, PI / 180 * (-star_cnt * 2), star_img, TRUE);
	DrawRotaGraph(1180, 650, 1.0, PI / 180 * (star_cnt * 2), star_img, TRUE);

	if (cursor_y < 3)
	{
		// カーソルの描画
		DrawGraph(320 + cursor_x * 73, 250 + cursor_y * 73, img[6], TRUE);

		// OK,deleteの描画
		DrawGraph(0, -60, img[0], TRUE);
	}
	else
	{
		// OK,deleteの描画
		if (cursor_x == 0)
		{
			DrawGraph(0, -60, img[1], TRUE);
		}
		else
		{
			DrawGraph(0, -60, img[2], TRUE);
		}
	}

	// 文字(キーボード？)の描画
	DrawGraph(320, 250, img[5], TRUE);

	if (no_name == true)
	{// 名前が入力されていないとき

		if (cnt <= 35)
		{
			// 名前を入力してくださいの文字を描画
			DrawGraph(0, -37, img[4], TRUE);
		}
		
		/*DrawGraph(530 - 35, 63, font_img[0], TRUE);
		DrawGraph(590 - 35, 63, font_img[1], TRUE);
		DrawGraph(650 - 35, 63, font_img[2], TRUE);
		DrawGraph(710 - 35, 63, font_img[3], TRUE);
		DrawGraph(770 - 35, 63, font_img[4], TRUE);*/
	}
	else
	{
		/*for (int i = 0; i <= name_num; i++)
		{
			DrawFormatString(0 + i * 30, 0, 0x000000, "%d", (int)name[i]);
		}*/

		//DrawFormatString(0, 30, 0x000000, "%d", name_num);

		// 入力された名前を描画
		if (input_end == false)
		{	
			for (int i = 0; i <= name_num; i++)
			{
				DrawGraph((605 - (name_num * 30))+ i * 70, 63, font_img[(int)name[i] - 65], TRUE);
			}
			
			if (name_num < 4 && cnt <= 30)
			{
				/*DrawLine((605 - (name_num * 30)) + name_num * 70 + 75, 67, (605 - (name_num * 30)) + name_num * 70 + 75, 130, 0x000000);*/
				DrawBox((605 - (name_num * 30)) + name_num * 70 + 75, 67, (605 - (name_num * 30)) + name_num * 70 + 77, 130, 0x000000,TRUE);
			}

			//DrawFormatStringToHandle(630 - name_num * 30, 63, 0x000000, font, "%s", name);
		}
		else
		{
			for (int i = 0; i < name_num; i++)
			{
				DrawGraph((605 - ((name_num - 1) * 27)) + i * 70, 63, font_img[(int)name[i] - 65], TRUE);
			}

			//DrawFormatStringToHandle(630 - (name_num - 1) * 30, 63, 0x000000, font, "%s", name);
		}
	}

	if (tran_flg == true)
	{
		DrawGraph(transition, 0, tran_img, TRUE);
	}
}

void InputRankingScene::Finalize()
{
	// ランキングにデータを格納
	ranking->SetRankingData(level, combo, name);

	// 動的メモリの解放
	delete ranking;
}

eSceneType InputRankingScene::GetNowScene() const
{
	return eSceneType::E_INPUT_RANKING;
}

bool InputRankingScene::InputName()
{
	// カーソル操作処理
	if (InputControl::GetButtonDown(XINPUT_BUTTON_X))
	{// Xボタンを押した場合

		// 効果音を再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y == 0 && cursor_x == 0)
		{// 1列目の一番最初にカーソルがある場合、4列目の最後の位置に移動
			cursor_y = 3;
			cursor_x = 1;
		}
		else if (cursor_y == 1 && cursor_x == 0)
		{// 2列目の一番最初にカーソルがある場合、1列目の最後の位置に移動
			cursor_y--;
			cursor_x = 8;
		}
		else if (cursor_y == 2 && cursor_x == 0)
		{// 3列目の一番最初にカーソルがある場合、2列目の最後の位置に移動
			cursor_y--;
			cursor_x = 8;
		}
		else if (cursor_y == 3 && cursor_x == 0)
		{// 4列目の一番最初にカーソルがある場合、3列目の最後の位置に移動
			cursor_y--;
			cursor_x = 7;
		}
		else
		{// 上記以外は、左にカーソルを移動
			cursor_x--;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{// Bボタンを押した場合

		// 効果音を再生
		PlaySoundMem(se[0], DX_PLAYTYPE_BACK, TRUE);

		if (cursor_y == 0 && cursor_x == 8)
		{// 1列目の一番最後にカーソルがある場合、2列目の最初の位置に移動
			cursor_y++;
			cursor_x = 0;
		}
		else if (cursor_y == 1 && cursor_x == 8)
		{// 2列目の一番最後にカーソルがある場合、3列目の最初の位置に移動
			cursor_y++;
			cursor_x = 0;
		}
		else if (cursor_y == 2 && cursor_x == 7)
		{// 3列目の一番最後にカーソルがある場合、4列目の最初の位置に移動
			cursor_y++;
			cursor_x = 0;
		}
		else if (cursor_y == 3 && cursor_x == 1)
		{// 4列目の一番最後にカーソルがある場合、1列目の最初の位置に移動
			cursor_y = 0;
			cursor_x = 0;
		}
		else
		{// 上記以外は、右にカーソルを移動
			cursor_x++;
		}
	}

	// Aボタンを押した場合カーソル位置の文字を決定する
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{	
		if (cursor_y < 3)
		{// カーソルが1～3列目にある場合

			// 効果音を再生
			PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

			// 名前が5文字未満だったら
			if (name[4] == NULL)
			{
				if (no_name == true)
				{
					no_name = false;
				}
				
				// 名前を格納
				name[++name_num] = 'A' + cursor_x + (cursor_y * 9);

				cnt = 0;
			}
		}
		else if (cursor_y == 3)
		{// カーソルが4列目にある場合

			if (cursor_x == 0)
			{// カーソルがOKの位置にある場合

				// 効果音を再生
				PlaySoundMem(se[1], DX_PLAYTYPE_NORMAL, TRUE);
				
				if (no_name != true)
				{// 名前が入力されていたら

					// 名前の最後に\0を入れる
					name[++name_num] = '\0';
					input_end = true;

					return true;
				}
				else
				{
					return false;
				}
			}
			else if (cursor_x == 1)
			{
				// 効果音を再生
				PlaySoundMem(se[1], DX_PLAYTYPE_BACK, TRUE);

				// 入力された名前をひとつ消す
				name[name_num--] = NULL;

				cnt = 0;

				// 名前が入力されていなかったら
				if (name[0] == NULL)
				{
					no_name = true;
				}
			}
		}
	}

	return false;
}

void InputRankingScene::StarAnim()
{
	star_cnt++;

	// 180より大きくなったら0にする
	if (star_cnt > 180)
	{
		star_cnt = 0;
	}
}

void InputRankingScene::Transition()
{
	transition += 50;
}