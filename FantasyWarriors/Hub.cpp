#define _CRT_SECURE_NO_WARNINGS
#include"Hub.h"

//関数
#pragma region テキスト関係

//フォント作成関数
HFONT Font(int w, int h, LPCTSTR fontName)
{
	HFONT hFont = CreateFont(
		h,//文字の大きさ
		w,//文字幅
		0,//角度
		0,//ベースライン角度
		FW_REGULAR, //太さ（太字；FW_BOLD)
		FALSE,
		FALSE,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		VARIABLE_PITCH | FF_ROMAN,
		fontName);
	if (hFont == NULL)
	{
		MessageBox(NULL,
			"文字フォントの作成に失敗",
			fontName, MB_OK);
	}
	return hFont;
}

//黒いテキストを表記する関数
void text(HDC hdc, int x, int y, const char* text)
{
	HFONT hFont = Font(22, 15, "FixedSys");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(0, 0, 0));
	TextOut(hdc, x, y, text, lstrlen(text));
	SetBkMode(hdc, TRANSPARENT);
}

//白いテキストを表記する関数
void whitetext(HDC hdc, int x, int y, const char* text)
{
	HFONT hFont = Font(22, 15, "FixedSys");
	SelectObject(hdc, hFont);
	SetTextColor(hdc, RGB(200, 200, 200));
	TextOut(hdc, x, y, text, lstrlen(text));
	SetBkMode(hdc, TRANSPARENT);
}

#pragma endregion

#pragma region 画像処理

//画面切り替え
void SceneChenge(HDC hdc,HDC hMemDC,HBITMAP* hBack,int* Alpha,bool* AlphaF)
{
	if (*AlphaF)*Alpha += 6;
	else if (!*AlphaF) *Alpha -= 6;
	AlphaBltResult(hdc, hMemDC, hBack, *Alpha, 600);
	if (*Alpha <= 0)*AlphaF = true;
	if (*Alpha >= 180)*AlphaF = false;
}

//画像の読み取り関数
bool ReadBmp(HBITMAP* hBmp, LPCTSTR FName)
{
	*hBmp = (HBITMAP)LoadImage(
		NULL,	//インスタンス番号（省略）
		FName,	//画像ファイル名
		IMAGE_BITMAP,	//ビットマップ画像
		0, 0,	//画像内の読み込み開始座標
		LR_LOADFROMFILE);	//ファイルから読み込む
	if (*hBmp == NULL)
	{
		MessageBox(NULL,
			"画像ファイルの読み込みに失敗",
			FName, MB_YESNO + MB_ICONEXCLAMATION);
		return false;

	}
	return true;
}

//画像表示関数
void BBlt(HDC hdc, HDC hMemDC, HBITMAP hBmp, int a)
{
	SelectObject(hMemDC, hBmp);
	BitBlt(hdc, a, 0, 1600, 600, hMemDC, 0, 0, SRCCOPY);
}
void BBltT(HDC hdc, HDC hMemDC, HBITMAP hBmp, int a)
{
	SelectObject(hMemDC, hBmp);
	BitBlt(hdc, a, 0, 800, 600, hMemDC, 0, 0, SRCCOPY);
}
void BBltTU(HDC hdc, HDC hMemDC, HBITMAP hBmp, int a)
{
	SelectObject(hMemDC, hBmp);
	BitBlt(hdc, 0, 0, 800, 600, hMemDC, a, 0, SRCCOPY);
}

//alpha
void AlphaBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int a)
{
	BLENDFUNCTION hBlack;
	hBlack.BlendOp = AC_SRC_OVER;
	hBlack.BlendFlags = 0;
	hBlack.SourceConstantAlpha = a;
	hBlack.AlphaFormat = 0;

	SelectObject(hMemDC, *hBmp);
	AlphaBlend(hdc, 130, 140, 540, 320, hMemDC, 0, 0, 540, 320, hBlack);
}
void AlphaBltSel(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y, int dy)
{
	BLENDFUNCTION hBlack;
	hBlack.BlendOp = AC_SRC_OVER;
	hBlack.BlendFlags = 0;
	hBlack.SourceConstantAlpha = 200;
	hBlack.AlphaFormat = 0;

	SelectObject(hMemDC, *hBmp);
	AlphaBlend(hdc, 160, y, 480, 50, hMemDC, 0, dy, 600, 50, hBlack);
}
void AlphaBltResult(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int a, int y)
{
	BLENDFUNCTION hBlack;
	hBlack.BlendOp = AC_SRC_OVER;
	hBlack.BlendFlags = 0;
	hBlack.SourceConstantAlpha = a;
	hBlack.AlphaFormat = 0;

	SelectObject(hMemDC, *hBmp);
	AlphaBlend(hdc, 0, 0, 800, 600, hMemDC, 0, y, 800, 600, hBlack);
}

//クロマキー
void TBltB(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, VALKYRIE_SIZE, TRANSPARENT_COLOR);
}
void TBltC(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z,int sizex,int sizey)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, sizex, sizey, TRANSPARENT_COLOR);
}
void TBltCS(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int sizex, int sizey)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 255,255, hMemDC, i, z, sizex, sizey, TRANSPARENT_COLOR);
}
void TBlt2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int dx, int dy)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 90, 50, hMemDC, i, z, dx, dy, TRANSPARENT_COLOR);
}
void TBltBTU(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 205, 10, 414, 264, hMemDC, x, y, VALKYRIE_SIZE, TRANSPARENT_COLOR);
}
void TBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, WND_W, WND_H, hMemDC, i, z, 420, 236, TRANSPARENT_COLOR);
}
void TBltUI1(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 330, 20, hMemDC, i, z, 1600, 112, TRANSPARENT_COLOR);
}
void TBltUI2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 340, 28, hMemDC, i, z, 1600, 163, TRANSPARENT_COLOR);
}
void TBltUI3(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 380, 80, hMemDC, i, z, 600, 50, TRANSPARENT_COLOR);
}
void TBltUI4(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int* Score)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 64, 32, hMemDC, i, z, 128, 64, TRANSPARENT_COLOR);

	int num = 0, tmp = *Score;
	for (int j = 0; j < 6; j++)
	{
		num = tmp % 10;
		TransparentBlt(hdc, x + (6 - j) * 32 + 100, y, 16, 32, hMemDC, num * 32, 64, 32, 64, TRANSPARENT_COLOR);
		tmp -= num;
		tmp /= 10;
	}
}
void TBltUI5(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int* Score)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 64, 32, hMemDC, i, z, 128, 64, TRANSPARENT_COLOR);
	int num = 0, tmp = *Score;
	for (int j = 0; j < 6; j++)
	{
		num = tmp % 10;
		TransparentBlt(hdc, x + (6 - j) * 32 + 100, y, 32, 32, hMemDC, num * 32, 64, 32, 64, TRANSPARENT_COLOR);
		tmp -= num;
		tmp /= 10;
	}
}
void TBltUI6(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 100, 100, hMemDC, i, z, 647, 618, TRANSPARENT_COLOR);
}
void TBltUI7(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 200, 60, hMemDC, i, z, 288, 144, TRANSPARENT_COLOR);
}
void TBltUI8(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 215, 60, hMemDC, i, z, 288, 144, TRANSPARENT_COLOR);
}
void TBltUI9(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 300, 90, hMemDC, i, z, 300, 100, TRANSPARENT_COLOR);
}
void TBltUI10(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 110, 90, hMemDC, i, z, 453, 340, TRANSPARENT_COLOR);
}
void TBltUI11(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y,int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 50, 45, hMemDC, 0, z, 184, 150, TRANSPARENT_COLOR);
}
void TBltUI12(HDC hdc, HDC hMemDC, HBITMAP* hBmp,int x,int y)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 200, 80, 400, 15, hMemDC, x, y, 350, 3, TRANSPARENT_COLOR);
}
void TBltUI13(HDC hdc, HDC hMemDC, HBITMAP* hBmp)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 10, 10, 180, 45, hMemDC,0, 0, 135, 30, TRANSPARENT_COLOR);
}
void TBltE(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, SHOT_SIZE, TRANSPARENT_COLOR);
}
void TBltBoss(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, BOSS_SIZE, hMemDC, i, z, BOSS_SIZE, TRANSPARENT_COLOR);
}
void TBltS(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, SHOT_SIZE, TRANSPARENT_COLOR);
}
void TBltS2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, 50, 32, TRANSPARENT_COLOR);
}
void TBltS3(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, 61, 46, TRANSPARENT_COLOR);
}
void TBltS4(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, CHARA_DC_SIZE, hMemDC, i, z, 36, 36, TRANSPARENT_COLOR);
}
void TBltSU(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z,int sx,int sy)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, sx,sy, hMemDC, i, z, 64,32, TRANSPARENT_COLOR);
}
void TBltZ(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, ENEMY_CHAR, hMemDC, i, z, ENEMY_CHAR, TRANSPARENT_COLOR);
}
void TBltES(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, y, 8, 8, hMemDC, i, z, ENEMY_CHAR, TRANSPARENT_COLOR);
}
void TBltMap(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, 0, 1600, 600, hMemDC, 0, 0, 1600, 600, TRANSPARENT_COLOR);
}
void TBltEnd(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 0, 0, 800, 600, hMemDC, x, 0, 800, 600, TRANSPARENT_COLOR);
}
void TBltGameOver(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 0, y, 800, 600, hMemDC, 0, 0, 800, 600, TRANSPARENT_COLOR);
}
void TBltLogo(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, 100, y, 600, 400, hMemDC, 0, 0, 600, 400, TRANSPARENT_COLOR);
}
void TBltUlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x,int y)
{
	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hdc, x, 135, 1600, 330, hMemDC, 0, y, 1600, 330, TRANSPARENT_COLOR);
}

//クロマキーアルファブレンド
void TAlphaB(HDC hdc, HDC hMemDC, HDC hWork, HBITMAP* hBmp)
{
	BLENDFUNCTION hBlack;
	hBlack.BlendOp = AC_SRC_OVER;
	hBlack.BlendFlags = 0;
	hBlack.SourceConstantAlpha = 125;
	hBlack.AlphaFormat = 0;

	SelectObject(hMemDC, *hBmp);
	TransparentBlt(hWork, 0, 0, CHARA_DC_SIZE, hMemDC, 0, 0, 50, 32, TRANSPARENT_COLOR);

	SelectObject(hWork, *hBmp);
	AlphaBlend(hdc, 130, 140, 540, 320, hWork, 0, 0, 540, 320, hBlack);
}

#pragma endregion

#pragma region 初期処理

//プレイヤー
void InitPlayer(Chara* pl,int num)
{
	pl->hp = 100; pl->x = WND_W / 6 - CHAR_SIZE / 2, pl->y = 450;
	pl->cnt = 0; pl->die = false; pl->dir = Right;
	pl->interval[jumpinterval] = 100; pl->interval[shotinterval] = 0;
	pl->interval[rollinterval] = 30; pl->interval[hitinterval] = 50;
	switch (num)
	{
	case Valkyrie:pl->typ = Valkyrie; pl->act = idle; break;
	case Assassin:pl->typ = Assassin; pl->act = aidle; break;
	case Monk:pl->typ = Monk; pl->act = midle; break;
	case Sniper:pl->typ = Sniper; pl->act = sidle; break;
	case Banbit1:pl->typ = Banbit1; pl->act = baidle; break;
	case Banbit2:pl->typ = Banbit2; pl->act = baidle; break;
	case Knight:pl->typ = Knight; pl->act = kidle; break;
	}

}

//ウイニングモードの敵
void InitRival(Chara* ri,int num)
{
	ri->hp = 350; ri->x = WND_W - 150, ri->y = 445;
	ri->cnt = 0; ri->die = false; ri->act = idle; ri->dir = Left;
	ri->interval[jumpinterval] = 100; ri->interval[shotinterval] = 0;
	ri->interval[rollinterval] = 30; ri->interval[hitinterval] = 70;
	switch (num)
	{
	case Valkyrie:ri->typ = Valkyrie; ri->act = idle; break;
	case Assassin:ri->typ = Assassin; ri->act = aidle; break;
	case Monk:ri->typ = Monk; ri->act = midle; break;
	case Sniper:ri->typ = Sniper; ri->act = sidle; break;
	case Banbit1:ri->typ = Banbit1; ri->act = baidle; break;
	case Banbit2:ri->typ = Banbit2; ri->act = baidle; break;
	case Knight:ri->typ = Knight; ri->act = kidle; break;
	}
}

//弾
void InitShot(Chara* sh)
{
	sh->y = -CHAR_SIZE, sh->y = WND_H; sh->dx = sh->dx;
	sh->cnt = 0; sh->die = false; sh->act = idle; sh->atk = 10;
	sh->interval[jumpinterval] = 80; sh->interval[shotinterval] = 50;
	sh->interval[rollinterval] = 30; sh->interval[hitinterval] = 50;
	sh->typ = Valkyrie;
}

//ウォリアーモードの敵
void InitEnemy(Chara* en)
{
	en->y = rand() % WND_H - 200, en->x = rand() % 1600 + 200; en->dx = en->x;
	en->cnt = 0; en->die = false; en->act = eidle; en->atk = 2; en->hp = 20;
	en->interval[jumpinterval] = 50; en->interval[shotinterval] = 50;
	en->interval[rollinterval] = 0; en->interval[hitinterval] = 20;
}

//ボス
void InitBoss(Chara* bo)
{
	bo->y = 505 - BOSS_Y_SIZE, bo->x = rand() % 1400 + 400; bo->dx = bo->x;
	bo->cnt = 0; bo->die = false; bo->act = bidle; bo->dir = Left; bo->atk = 0; bo->hp = 100;
	bo->interval[jumpinterval] = 30; bo->interval[shotinterval] = 50;
	bo->interval[rollinterval] = 30; bo->interval[hitinterval] = 50;
}

#pragma endregion

#pragma region 音楽関数

//音楽流す
void BGMPlay(int sn, HWND hWnd)
{
	CHAR wNum[3] = { NULL };//桁数
	_itoa_s(sn + 1, wNum, 10);
	CHAR FilePath[64] = " BGM";
	strcat_s(FilePath, wNum);
	CHAR str[128] = { NULL };
	strcat_s(str, "play");
	strcat_s(str, FilePath);
	strcat_s(str, " notify");
	mciSendString(str, NULL, 0, hWnd);
}

//音楽止める
void BGMClose(int sn, HWND hWnd)
{
	CHAR wNum[3] = { NULL };//桁数
	_itoa_s(sn + 1, wNum, 10);
	CHAR FilePath[64] = " BGM";
	strcat_s(FilePath, wNum);
	CHAR str[128] = { NULL };
	strcat_s(str, "close");
	strcat_s(str, FilePath);
	mciSendString(str, NULL, 0, hWnd);
}

//音楽ファイルを開く
void BGMOpen(int sn, HWND hWnd)
{
	CHAR Num[3] = { NULL };//桁数
	_itoa_s(sn + 1, Num, 10);
	CHAR filePath[64] = "open ";
	CHAR Body[64] = "素材/音楽/BGM";
	CHAR Body2[64] = ".mp3 alias BGM";
	strcat_s(filePath, Body);		//"open 素材/音楽/BGM"	
	strcat_s(filePath, Num);		//"open 素材/音楽/BGM(i)"	
	strcat_s(filePath, Body2);//"open 素材/音楽/BGM(i) alias BGM(i)"
	strcat_s(filePath, Num);
	mciSendString(filePath, NULL, 0, hWnd);
}

//現在なっている音楽が止まっていないかチェック
void BGMCheck(int sn, HWND hWnd)
{
	CHAR status[256] = { NULL };
	CHAR wNum[3] = { NULL };//桁数
	_itoa_s(sn + 1, wNum, 10);
	CHAR FilePath[64] = " BGM";
	strcat_s(FilePath, wNum);
	CHAR tmp[64] = { NULL };
	strcpy_s(tmp, FilePath);
	CHAR str[128] = { NULL };
	strcat_s(str, "status");
	strcat_s(str, FilePath);
	strcat_s(str, " mode");
	mciSendStringA(str, status, 255, hWnd);
	if (strcmp(status, "stopped") == 0)
	{
		CHAR second[128] = { NULL };
		strcat_s(second, "seek ");
		strcat_s(second, tmp);
		strcat_s(second, " to start");
		mciSendStringA(second, NULL, 0, hWnd);
		BGMPlay(sn, hWnd);
	}
}

#pragma endregion

#pragma region タイトル

//タイトル入力処理
void TitleExecute(int* nowScene, int* sel, int* interval)
{
	//キー入力
	if (*interval <= 0) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			switch (*sel)
			{
			case 0:
				*nowScene = Warriors;
				break;
			case 1:
				*nowScene = Winning;
				break;
			case 2:
				*nowScene = CharaSelect;
				break;
			case 3:
				*nowScene = Menu;
				break;
			}
			PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
			*interval = 30;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			*sel -= 1;
			if (*sel < 0)*sel = 0;
			PlaySoundA("素材/効果音/効果音6.wav", NULL, SND_ASYNC | SND_FILENAME);
			*interval = 30;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			*sel += 1;
			if (*sel > 3)*sel = 3;
			PlaySoundA("素材/効果音/効果音6.wav", NULL, SND_ASYNC | SND_FILENAME);
			*interval = 30;
		}
	}
	if (*interval > -1)*interval -= 1;
}

//タイトル描画
void TitleDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hUi, int* sel, int* cnt, int scene)
{
	static int count = -400;
	if (scene != Title)count = -400;
	BBltT(hdc, hMemDC, hStage[titlescene], 0);
	TBltLogo(hdc, hMemDC, &hStage[titlelog], count);
	for (int i = 0; i < 4; i++)
	{
		if (*sel == i)
		{
			AlphaBltSel(hdc, hMemDC, &hUi[uisel], 400 + (i * 50), 50);
		}
		else
		{
			AlphaBltSel(hdc, hMemDC, &hUi[uisel], 400 + (i * 50), 0);
		}
	}
	if(*sel == 0)text(hdc, 215, 414, "WARRIOERS START");
	else whitetext(hdc, 215, 414, "WARRIOERS START");
	if (*sel == 1)text(hdc, 240, 464, "WINNING START");
	else whitetext(hdc, 240, 464, "WINNING START");
	if (*sel == 2)text(hdc, 250, 514, "CHARA SELECT");
	else whitetext(hdc, 250, 514, "CHARA SELECT");
	if (*sel == 3)text(hdc, 305, 564, "TUTORIAL");
	else whitetext(hdc, 305, 564, "TUTORIAL");
	if (count < 0)count += 2;
}

#pragma endregion

#pragma region ゲームオーバー

//ゲームオーバー時の描画
void GameOverDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage,HBITMAP* hUi,int Scene)
{
	static int Alpha = 0;
	static int Time = -400;
	AlphaBltResult(hdc, hMemDC, &hStage[blackwhite], Alpha, 600);
	if (Alpha == 120) {
		TBltGameOver(hdc, hMemDC, &hUi[ui12], Time);
		if(Time < 0)Time += 4;
	}
	if (Alpha < 120)Alpha++;
	if (Alpha > 120)Alpha = 120;
	if (Scene != GameOver)
	{
		Alpha = 0;
		Time = -200;
	}
}

#pragma endregion

#pragma region チュートリアル

//チュートリアル中の入力処理
void MenuExecute(int* Scene, Chara* pl, Chara* sh,int NowChara)
{
	TutorialPlayerExecute(pl, sh);
	PlayerShotExecute(sh, SHOT_MAX);
	AnimationMainChara(pl);
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
		*Scene = Title;
	}
	if (*Scene != Menu)
	{
		InitPlayer(pl,NowChara);
		for (int i = 0; i < SHOT_MAX; i++)
		{
			InitShot(&sh[i]);
		}
	}
}

//チュートリアル画面の描画
void MenuDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hChar,HBITMAP* hShot,Chara* pl,Chara* sh)
{
	//背景描画
	BBlt(hdc, hMemDC, hStage[Haikei], (pl->x * -1));
	if (pl->act != ult) {
		//球描画
		PlayerShotDraw(sh, hdc, hMemDC, hShot);
		//Player描画
		PlayerDraw(pl, hdc, hMemDC, hChar);
		TBltMap(hdc, hMemDC, &hStage[Zenmen], (pl->x * -1));
		text(hdc, 10, 15, "GreenGauge = Jump");
		text(hdc, 10, 40, "BlueGauge = ULT");
	}
	//Ult時カットイン
	if (pl->act == ult)
	{
		whitetext(hdc, 10, 15, "GreenGauge = Jump");
		whitetext(hdc, 10, 40, "BlueGauge = ULT");
		AlphaBltResult(hdc, hMemDC, &hStage[blackwhite], 160, 600);
		PlayerDraw(pl, hdc, hMemDC, hChar);
		if (pl->cnt >= 72)PlayerShotDraw(sh, hdc, hMemDC, hShot);
		TBltMap(hdc, hMemDC, &hStage[Zenmen], (pl->x * -1));
		if (pl->cnt < 42)TBltUlt(hdc, hMemDC, &hStage[backskill], -1 * (30 * (pl->cnt / 2)), (330 * pl->typ));
	}
}

#pragma endregion

#pragma region ウォリアーモード

//Gameルールや仕様
void WarrioersExecute(Chara* pl, Chara* en, Chara* sh, Chara* bo, Chara* bsh, Chara* esh, int* scene, int* Score)
{
	//座標を背景に連動させるための変数
	static int beforshotx[ENEMY_MAX] = { 0 };
	static int beforx = 0;
	
	//プレイヤーの処理
	PlayerExecute(pl, sh);

	//死亡処理
	if (pl->die) {
		switch (pl->typ)
		{
		case Banbit1:
		case Banbit2:
			if (pl->cnt > 28)*scene = Result;
			pl->cnt++;
			break;
		case Monk:
		case Sniper:
			if (pl->cnt > 22)*scene = Result;
			pl->cnt++;
			break;
		default:
			if (pl->cnt > 22)*scene = Result;
			pl->cnt++;
			break;
		}
	}

	//プレイヤー弾の処理
	PlayerShotExecute(sh,SHOT_MAX);

	//弾のヒット判定
	PlayerShotHitCheckOnce(sh, bo,pl, Score);
	PlayerShotHitCheckSame(sh, en,pl, Score, ENEMY_MAX);
	
	//ULT時敵が動かないように
	if (pl->act != ult) {

		//敵の処理
		EnemyExecute(en, pl, beforshotx);

		//敵の弾の処理
		EnemyShotExecute(esh, pl);

		//BossAI及び敵の弾の挙動
		if (bo->interval[jumpinterval] == 0 && !bo->die)
		{
			int BossAi = rand() % 3;
			switch (BossAi)
			{
			case 0:
				bo->act = batack1;
				bo->atk = 30;
				break;
			case 1:
				//Bossのアクション
				bo->act = batack2;
				bo->atk = 15;
				//弾のアクション
				bsh->act = batack2;
				bsh->y = pl->y - 35;
				if (bo->dir == Right)beforx = pl->x - 20;
				if (bo->dir == Left)beforx = pl->x - 20;

				break;
			case 2:
				bo->act = bwork;
				bo->atk = 5;
				break;
			}
		}

		//ボスの処理
		BossExecute(bo, pl, bsh, &beforx);
	
		//アニメーション関数
		AnimationBoss(bo, bsh);
		AnimationEnemy(en, esh);
	}

	//ULTの関係のためここ
	AnimationMainChara(pl);

#pragma region 効果音

	static bool HpLow = false;

	//ロール時の効果音
	if (pl->cnt == 1 && pl->act == roll)
	{
		PlaySoundA("素材/効果音/効果音9.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	//HPが三割しか残っていないときの効果音
	if (HpLow == false && pl->hp < 30)
	{
		PlaySoundA("素材/効果音/効果音5.wav", NULL, SND_ASYNC | SND_FILENAME);
		HpLow = true;
	}

#pragma endregion

#pragma region その他処理

	//画像場所を背景につかせる
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!en[i].die)
		{
			en[i].dx = en[i].x - pl->x;
			EnemyShotDrawPos(esh,pl, i * 3, beforshotx[i]);
		}
	}
	bo->dx = bo->x - pl->x;
	if (bsh->act == batack2)bsh->x = pl->x;
	bsh->dx = beforx - (bsh->x - beforx);
	if (pl->interval[hitinterval] <= 0)pl->interval[hitinterval] = 50;

	//変数の初期化
	if (pl->die)
	{
		HpLow == false;
		beforx = 0;
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			beforshotx[i] = 0;
		}
	}

	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
		*scene = Title;
	}
#pragma endregion
}

//GameModeの画像摘出
void WarrioersDraw(Chara* pl, Chara* en, Chara* sh, Chara* bo, Chara* bsh, Chara* esh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hBack, HBITMAP* hShot)
{
	//背景描画
	BBlt(hdc, hMemDC, hBack[Haikei], (pl->x * -1));
	if (pl->act != ult) {
		//球描画
		PlayerShotDraw(sh, hdc, hMemDC, hShot);
		//Player描画
		PlayerDraw(pl, hdc, hMemDC, hChar);
	}
	//Enemy描画
	EnemyDraw(en, esh, hdc, hMemDC, hChar, hShot);
	//Boss描画
	BossDraw(bo, bsh, hdc, hMemDC, hChar, hShot);
	//前面透過画像
	if (pl->act != ult)	TBltMap(hdc, hMemDC, &hBack[Zenmen], (pl->x * -1));
	
	//Ult時カットイン
	if (pl->act == ult)
	{
		AlphaBltResult(hdc, hMemDC, &hBack[blackwhite], 160, 600);
		PlayerDraw(pl, hdc, hMemDC, hChar);
		if (pl->cnt >= 72)PlayerShotDraw(sh, hdc, hMemDC, hShot);
		TBltMap(hdc, hMemDC, &hBack[Zenmen], (pl->x * -1));
		if(pl->cnt<42)TBltUlt(hdc, hMemDC, &hBack[backskill],-1 * (30 * (pl->cnt / 2)),(330 * pl->typ));
	}
}

//UIの描画
void UiDraw(Chara* pl, int* Score, int* Time, HDC hdc, HDC hMemDC, HBITMAP* ui)
{
	TBltUI3(hdc, hMemDC, &ui[uispace], 0, 530, 0, 0);
	TBltUI1(hdc, hMemDC, &ui[hpgage], (int)(-5 - ((100 - (int)pl->hp) * 3.1)), 546, 0, 0);
	TBltUI2(hdc, hMemDC, &ui[hpwaku], -10, 540, 0, 0);
	if(Score != NULL)TBltUI4(hdc, hMemDC, &ui[uscore], 480, 40, 0, 0, Score);
	if(Time != NULL)TBltUI4(hdc, hMemDC, &ui[utime], 480, 10, 0, 0, Time);
	TBltUI8(hdc, hMemDC, &ui[ui9], (int)(0 - ((100 - (int)pl->interval[jumpinterval]) * 1.5)), 560, 10, 0);
	TBltUI7(hdc, hMemDC, &ui[ui9], -10, 560, 0, 144);
	TBltUI8(hdc, hMemDC, &ui[ui9], 180, 560, 220 - (int)pl->interval[shotinterval], 288);
	TBltUI7(hdc, hMemDC, &ui[ui9], 180, 560, 0, 432);
	TBltUI9(hdc, hMemDC, &ui[ui14], 500, 510, 0, 0);
	if(pl->interval[shotinterval]==220)
		TBltUI10(hdc, hMemDC, &ui[ui15], 400, 510, 0, 0);
	switch (pl->typ)
	{
	case Valkyrie:
		TBltUI9(hdc, hMemDC, &ui[ui13], 500, 510, 0, 0);
	case Assassin:
		TBltUI9(hdc, hMemDC, &ui[ui13], 500, 510, 0, 100);
		break;
	case Monk:
	case Sniper:
		TBltUI9(hdc, hMemDC, &ui[ui13], 500, 510, 0, 200);
		break;
	case Banbit1:
	case Banbit2:
		TBltUI9(hdc, hMemDC, &ui[ui13], 500, 510, 0, 300);
		break;
	case Knight:
		TBltUI9(hdc, hMemDC, &ui[ui13], 500, 510, 0, 400);
		break;
	}
}

#pragma endregion

#pragma region ゲームを遊ぶときに使う関数

#pragma region コントローラー

//女騎士
void ValkyrieController(Chara* pl, Chara* sh)
{
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != hit && pl->act != ult) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = work;
				if (pl->x < (WND_W - 32))pl->x += 2;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = work;
				if (pl->x > 0)pl->x -= 2;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (jKeyInterval >= 20) {
				if (pl->interval[jumpinterval] > 0) {
					pl->interval[jumpinterval] -= 26;
					pl->act = jumpup;
				}
				pl->cnt = 0;
				jKeyInterval = 0;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = attack1;
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = idle; sh[i].atk = 20;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			pl->act = attack2;
			if (KeyInterval >= 15) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 10;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true;  break;
					}
				}
			}
		}
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pl->act = skill;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = skill; sh[i].atk = 30;
						sh[i].x = pl->x; sh[i].y = (pl->y - 70); sh[i].die = true; break;
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (pl->interval[rollinterval] <= 0)
			{
				pl->interval[rollinterval] = 30;
				pl->act = roll;
				pl->cnt = 0;
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true;
							break;
						}
					}
				}
			}
		}
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

//暗殺者
void AssassinController(Chara* pl, Chara* sh)
{
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != ahit && pl->act != ult) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != roll) {
				if (pl->y == 450) {
					pl->act = arun;
					if (pl->x < (WND_W - 32))pl->x += 3;
				}
				else { if (pl->x < (WND_W - 32))pl->x += 4; }
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != roll) {
				if (pl->y == 450) {
					pl->act = arun;
					if (pl->x > 0)pl->x -= 3;
				}
				else { if (pl->x > 0)pl->x -= 4; }
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (jKeyInterval >= 20) {
				if (pl->interval[jumpinterval] > 0) {
					pl->interval[jumpinterval] -= 26;
					pl->act = ajump;
				}
				pl->cnt = 0;
				jKeyInterval = 0;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = aattack1;
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = idle; sh[i].atk = 15;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			pl->act = aattack2;
			if (KeyInterval >= 15) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 10;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pl->act = aattack3;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = skill; sh[i].atk = 20;
						sh[i].x = pl->x; sh[i].y = pl->y ; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
					}
				}
			}
		}
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

//僧侶
void MonkController(Chara* pl, Chara* sh)
{
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != mhit && pl->act != ult && pl->act != mguard) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = mrun;
				if (pl->x < (WND_W - 32))pl->x += 2;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = mrun;
				if (pl->x > 0)pl->x -= 2;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (jKeyInterval >= 20) {
				if (pl->interval[jumpinterval] > 0) {
					pl->interval[jumpinterval] -= 26;
					pl->act = mjumpup;
				}
				pl->cnt = 0;
				jKeyInterval = 0;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			pl->act = mseald; pl->cnt = 0;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = mattack1;
			
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = idle; sh[i].atk = 20;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			pl->act = mattack2;
			if (KeyInterval >= 15) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 10;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ; break;
					}
				}
			}
		}
		if (GetAsyncKeyState('C') & 0x8000)
		{
			if (pl->y == 450)pl->act = mattack3;
			else if (pl->y != 450)pl->act = mjumpattack;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					int max = 3;
					if (!sh[i].die) {
						if(pl->act != mjumpattack){
							sh[i].dir = pl->dir; sh[i].act = skill; sh[i].atk = 30;
							sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ; break;
						}
						else
						{
							sh[i].dir = pl->dir; sh[i].act = hit; sh[i].atk = 30; max--;
							sh[i].x = pl->x; sh[i].y = pl->y ; sh[i].die = true; sh[i].typ = pl->typ;
							if(max<=0)break;
						}
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (pl->interval[rollinterval] <= 0)
			{
				pl->interval[rollinterval] = 30;
				pl->act = mseald;
				pl->cnt = 0;
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
					}
				}
			}
		}
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

//狙撃者
void SniperController(Chara* pl, Chara* sh)
{
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != shit && pl->act != ult && pl->act != sguard) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = srun;
				if (pl->x < (WND_W - 32))pl->x += 4;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = srun;
				if (pl->x > 0)pl->x -= 4;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (jKeyInterval >= 20) {
				if (pl->interval[jumpinterval] > 0) {
					pl->interval[jumpinterval] -= 26;
					pl->act = sjumpup;
				}
				pl->cnt = 0;
				jKeyInterval = 0;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			pl->act = sseald; pl->cnt = 0;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = sattack1;
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = idle; sh[i].atk = 20;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			pl->act = sattack2;
			if (KeyInterval >= 15) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 10;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;  break;
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (pl->interval[rollinterval] <= 0)
			{
				pl->interval[rollinterval] = 30;
				pl->act = sseald;
				pl->cnt = 0;
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
					}
				}
			}
		}
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

//野盗
void BanbitController(Chara* pl, Chara* sh)
{
	static int RespawnMax = 3;
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != bahit && pl->act != ult && pl->act != barespawn) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = barun;
				if (pl->x < (WND_W - 32))pl->x += 2;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != roll) {
				if (pl->y == 450)pl->act = barun;
				if (pl->x > 0)pl->x -= 2;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = baattack;
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					int max = 3;
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 15; max--;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						if(max <= 0)break;
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
					}
				}
			}
		}
	}
	
	if (pl->die && RespawnMax > 0 &&pl->cnt >=25)
	{
		RespawnMax--;
		pl->die = false;
		pl->hp = 100;
		pl->cnt = 0;
		pl->act = barespawn;
		PlaySoundA("素材/効果音/回復.wav", NULL, SND_ASYNC | SND_FILENAME);
	}
	else if (pl->die)
	{
		pl->act = badie;
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

//騎士
void KnightController(Chara* pl, Chara* sh)
{
	//キー入力
	static int KeyInterval = 0;
	static int jKeyInterval = 20;
	if (!pl->die && pl->act != khit && pl->act != ult && pl->act != kguard) {
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
			pl->dir = Right;
			if (pl->act != kroll) {
				if (pl->y == 450)pl->act = krun;
				if (pl->x < (WND_W - 32))pl->x += 2;
			}
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
			pl->dir = Left;
			if (pl->act != kroll) {
				if (pl->y == 450)pl->act = krun;
				if (pl->x > 0)pl->x -= 2;
			}
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			pl->act = kseald; pl->cnt = 0;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
			}
		}
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			if (jKeyInterval >= 20) {
				if (pl->interval[jumpinterval] > 0) {
					pl->interval[jumpinterval] -= 26;
					pl->act = kjumpup;
				}
				pl->cnt = 0;
				jKeyInterval = 0;
			}
		}
		if (GetAsyncKeyState('Z') & 0x8000) {
			pl->act = kattack1;
			if (KeyInterval >= 30) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = idle; sh[i].atk = 20;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ;
						break;
					}
				}
			}
		}
		if (GetAsyncKeyState('C') & 0x8000)
		{
			pl->act = kattack2;
			if (KeyInterval >= 50) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = skill; sh[i].atk = 30;
						sh[i].x = pl->x; sh[i].y = (pl->y - 70); sh[i].die = true; sh[i].typ = pl->typ; break;
					}
				}
			}
		}
		if (GetAsyncKeyState('X') & 0x8000)
		{
			pl->act = kattack3;
			if (KeyInterval >= 15) {
				KeyInterval = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = pl->dir; sh[i].act = roll; sh[i].atk = 10;
						sh[i].x = pl->x; sh[i].y = pl->y; sh[i].die = true; sh[i].typ = pl->typ; break;
					}
				}
			}
		}
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (pl->interval[rollinterval] <= 0)
			{
				pl->interval[rollinterval] = 30;
				pl->act = kroll;
				pl->cnt = 0;
			}
		}
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (pl->interval[shotinterval] >= 220)
			{
				pl->act = ult;
				pl->interval[shotinterval] = 0;
				pl->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (pl->dir == Right) {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
						else {
							sh[i].dir = pl->dir; sh[i].act = ult; sh[i].atk = 100;
							sh[i].x = pl->x - 100; sh[i].y = pl->y - 90; sh[i].die = true; sh[i].typ = pl->typ;
							break;
						}
					}
				}
			}
		}
	}

	if (KeyInterval < 51)KeyInterval++;
	if (jKeyInterval < 21)jKeyInterval++;
}

#pragma endregion

#pragma region PLAYER関係
//プレイヤーのinterval処理
void CheckIntervalPlayer(Chara* pl)
{
	if (pl->y == 450)pl->interval[jumpinterval] += 2;
	if (pl->interval[jumpinterval] > 100)pl->interval[jumpinterval] = 100;
	if (pl->act == hit ||pl->act == ahit || pl->act == shit ||
		pl->act == mhit || pl->act == bahit ||
		pl->act == khit || pl->interval[hitinterval] != 50)
		pl->interval[hitinterval]--;
	if (pl->interval[shotinterval] > 220)pl->interval[shotinterval] = 220;
	if (pl->interval[rollinterval] > 0)pl->interval[rollinterval]--;
	//ULT使い放題プラン
	//if (pl->interval[shotinterval] < 220)pl->interval[shotinterval] +=15;
}

//チュートリアル中のinterval処理
void TutorialCheckInterval(Chara* pl)
{
	if (pl->y == 450)pl->interval[jumpinterval] += 2;
	if (pl->interval[jumpinterval] > 100)pl->interval[jumpinterval] = 100;
	if (pl->act == hit || pl->interval[hitinterval] != 50)pl->interval[hitinterval]--;
	if (pl->interval[shotinterval] > 220)pl->interval[shotinterval] = 220;
	if (pl->interval[rollinterval] > 0)pl->interval[rollinterval]--;
	//ULT使い放題プラン
	if (pl->interval[shotinterval] < 220)pl->interval[shotinterval] +=15;
}

//プレイヤー自体の処理
void PlayerExecute(Chara* pl, Chara* sh)
{
	//タイプ別コントローラー
	switch (pl->typ)
	{
	case Valkyrie:
		ValkyrieController(pl, sh);
		break;
	case Assassin:
		AssassinController(pl, sh);
		break;
	case Monk:
		MonkController(pl, sh);
		break;
	case Sniper:
		SniperController(pl, sh);
		break;
	case Banbit1:
		BanbitController(pl, sh);
		break;
	case Banbit2:
		BanbitController(pl, sh);
		break;
	case Knight:
		KnightController(pl, sh);
		break;
	}
	//インターバル処理
	CheckIntervalPlayer(pl);
}

//チュートリアル中のプレイヤーの処理
void TutorialPlayerExecute(Chara* pl, Chara* sh)
{
	//タイプ別コントローラー
	switch (pl->typ)
	{
	case Valkyrie:
		ValkyrieController(pl, sh);
		break;
	case Assassin:
		AssassinController(pl, sh);
		break;
	case Monk:
		MonkController(pl, sh);
		break;
	case Sniper:
		SniperController(pl, sh);
		break;
	case Banbit1:
		BanbitController(pl, sh);
		break;
	case Banbit2:
		BanbitController(pl, sh);
		break;
	case Knight:
		KnightController(pl, sh);
		break;
	}
	//インターバル処理
	TutorialCheckInterval(pl);
}

//プレイヤーのアニメーション処理
void AnimationMainChara(Chara* pl)
{
	switch (pl->typ)
	{
	case Valkyrie:
		switch (pl->act)
	{
	case idle:
		if (pl->cnt >= 10)pl->cnt = 0;
		pl->cnt++;
		break;
	case work:
		if (pl->cnt >= 14) { pl->act = idle; pl->cnt = 0; }
		pl->cnt++;
		break;
	case attack1:
		if (pl->cnt >= 14) {
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else { pl->act = jumpdown; pl->cnt = 0; }
		}
		if (pl->y != 450)
		{
			pl->y += 2; if (pl->y >= 450)pl->y = 450;
		}
		pl->cnt++;
		break;
	case attack2:
		if (pl->cnt >= 6) {
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else { pl->act = jumpdown; pl->cnt = 0;}
		}
		if (pl->y != 450)
		{
			pl->y += 2; if (pl->y >= 450)pl->y = 450;
		}
		pl->cnt++;
		break;
	case hit:
		if (pl->cnt >= 40) {
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else { pl->act = jumpdown; pl->cnt = 0; }
		}
		if (pl->y != 450)
		{
			pl->y += 2; if (pl->y >= 450)pl->y = 450;
		}
		pl->cnt++;
		break;
	case jumpup:
		if (pl->cnt >= 15 && pl->y >= 0) { pl->y -= 1; pl->act = jumpdown; }
		switch (pl->cnt)
		{
		case 0:
		case 1:
		case 2:
			pl->y -= 9;
			break;
		case 3:
			pl->y -= 7;
			break;
		case 4:
		case 5:
			pl->y -= 11;
			break;
		case 6:
		case 7:
		case 8:
			pl->y -= 8;
		case 9:
		case 10:
		case 11:
			pl->y -= 5;
			break;
		case 12:
		case 13:
		case 14:
			pl->y -= 2;
			break;
		}
		pl->cnt++;
		break;
	case jumpdown:
		if (pl->y < 450) {
			pl->cnt++;
			if (pl->cnt < 12)
				pl->y += 4;
			else if (pl->cnt >= 12)
				pl->y += 7;
		}
		else if (pl->y >= 450) {
			pl->y = 450;
			pl->act = idle;
			pl->cnt = 0;
		}
		break;
	case skill:
		if (pl->cnt >= 6) {
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else { pl->act = jumpdown; pl->cnt = 0; }
		}
		if (pl->y != 450)
		{
			pl->y += 2; if (pl->y >= 450)pl->y = 450;
		}
		pl->cnt++;
		break;
	case roll:
		if (pl->cnt <= 8)
		{
			if (pl->dir == Right)pl->x += 8;
			else pl->x -= 8;
			if (pl->x > (WND_W - 32))pl->x = WND_W - 32;
			else if (pl->x < 0)pl->x = 0;
			pl->cnt++;
		}
		else
		{
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else pl->act = jumpdown;
		}
		break;
	case ult:
		if (pl->cnt >= 87) {
			if (pl->y == 450) { pl->act = idle; pl->cnt = 0; }
			else { pl->act = jumpdown; pl->cnt = 0; }
		}
		pl->cnt++;
		break;
	}
		break;
	case Assassin:
		switch (pl->act)
		{
		case aidle:
			if (pl->cnt >= 12)pl->cnt = 0;
			pl->cnt++;
			break;
		case arun:
			if (pl->cnt >= 20) { pl->act = aidle; pl->cnt = 0; }
			pl->cnt++;
			break;
		case aattack1:
			if (pl->cnt >= 16) { 
				if (pl->y == 450) { pl->act = aidle; pl->cnt = 0; }
				else { pl->act = ajumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case aattack2:
			if (pl->cnt >= 16) {
				if (pl->y == 450) { pl->act = aidle; pl->cnt = 0; }
				else { pl->act = ajumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case aattack3:
			if (pl->cnt >= 16) {
				if (pl->y == 450) { pl->act = aidle; pl->cnt = 0; }
				else { pl->act = ajumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case ajump:
			if (pl->cnt >= 15 && pl->y >= 0) { pl->y -= 1; pl->act = ajumpdown; }
			switch (pl->cnt)
			{
			case 0:
			case 1:
			case 2:
				pl->y -= 10;
				break;
			case 3:
				pl->y -= 8;
				break;
			case 4:
			case 5:
				pl->y -= 11;
				break;
			case 6:
			case 7:
			case 8:
				pl->y -= 8;
			case 9:
			case 10:
			case 11:
				pl->y -= 7;
				break;
			case 12:
			case 13:
			case 14:
				pl->y -= 2;
				break;
			}
			pl->cnt++;
			break;
		case ajumpdown:
			if (pl->y < 450) {
				pl->cnt++;
				if (pl->cnt < 12)
					pl->y += 4;
				else if (pl->cnt >= 12)
					pl->y += 7;
			}
			else if (pl->y >= 450) {
				pl->y = 450;
				pl->act = aidle;
				pl->cnt = 0;
			}
			break;
		case ahit:
			if (pl->cnt >= 40) {
				if (pl->y == 450) { pl->act = aidle; pl->cnt = 0; }
				else { pl->act = ajumpdown; pl->cnt = 0; }
			}
			if (pl->dir == Right) { pl->x -= (pl->cnt % 3); if (pl->x < 0)pl->x = 0; }
			else { pl->x += (pl->cnt % 3); if (pl->x > WND_W - 64)pl->x = WND_W - 64;
			}
			if (pl->y != 450) pl->y += (pl->cnt % 3);
			pl->cnt++;
			break;
		case ult:
			if (pl->cnt >= 67) {
				if (pl->y == 450) { pl->act = aidle; pl->cnt = 0; }
				else { pl->act = ajumpdown; pl->cnt = 0; }
			}
			pl->cnt++;
			break;
		}
		break;
	case Monk:
		switch (pl->act)
		{
		case midle:
			if (pl->cnt >= 12)pl->cnt = 0;
			pl->cnt++;
			break;
		case mrun:
			if (pl->cnt >= 20) { pl->act = midle; pl->cnt = 0; }
			pl->cnt++;
			break;
		case mattack1:
			if (pl->cnt >= 20) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mattack2:
			if (pl->cnt >= 16) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mattack3:
			if (pl->cnt >= 15) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mjumpattack:
			if (pl->cnt >= 10) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				if (pl->dir == Right)pl->x += 3;
				else pl->x -= 3;
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mjumpup:
			if (pl->cnt >= 10 && pl->y >= 0) { pl->y -= 1; pl->act = mjumpdown; }
			switch (pl->cnt)
			{
			case 0:
			case 1:
			case 2:
				pl->y -= 15;
				break;
			case 3:
				pl->y -= 8;
				break;
			case 4:
			case 5:
				pl->y -= 15;
				break;
			case 6:
			case 7:
			case 8:
				pl->y -= 12;
			case 9:
			case 10:
			case 11:
				pl->y -= 5;
				break;
			case 12:
			case 13:
				pl->y -= 3;
				break;
			}
			pl->cnt++;
			break;
		case mjumpdown:
			if (pl->y < 450) {
				pl->cnt++;
				if (pl->cnt < 12)
					pl->y += 4;
				else if (pl->cnt >= 12)
					pl->y += 8;
			}
			else if (pl->y >= 450) {
				pl->y = 450;
				pl->act = midle;
				pl->cnt = 0;
			}
			break;
		case mhit:
			if (pl->cnt >= 36) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mseald:
			if (pl->cnt >= 4) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case mguard:
			if (pl->cnt >= 36) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case ult:
			if (pl->cnt >= 72) {
				if (pl->y == 450) { pl->act = midle; pl->cnt = 0; }
				else { pl->act = mjumpdown; pl->cnt = 0; }
			}
			pl->cnt++;
			break;
		}
		break;
	case Sniper:
		switch (pl->act)
		{
		case sidle:
			if (pl->cnt >= 18)pl->cnt = 0;
			if (pl->die)pl->act = sdie;
			pl->cnt++;
			break;
		case srun:
			if (pl->cnt >= 26) { pl->act = sidle; pl->cnt = 0; }
			pl->cnt++;
			break;
		case sattack1:
			if (pl->cnt >= 8) {
				if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
				else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case sattack2:
			if (pl->cnt >= 8) {
				if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
				else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case shit:
			if (pl->cnt >= 36) {
				if (pl->die)pl->act = sdie;
				if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
				else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case sseald:
			if (pl->cnt >= 12) {
				if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
				else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case sguard:if (pl->cnt >= 36) {
			if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
			else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
			  pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case sjumpup:
			if (pl->cnt >= 8 && pl->y >= 0) { pl->y -= 1; pl->act = sjumpdown; }
			switch (pl->cnt)
			{
			case 0:
			case 1:
			case 2:
				pl->y -= 15;
				break;
			case 3:
				pl->y -= 8;
				break;
			case 4:
			case 5:
				pl->y -= 15;
				break;
			case 6:
			case 7:
			case 8:
				pl->y -= 12;
			case 9:
			case 10:
			case 11:
				pl->y -= 5;
				break;
			case 12:
			case 13:
			case 14:
				pl->y -= 2;
				break;
			}
			pl->cnt++;
			break;
		case sjumpdown:
			if (pl->y < 450) {
				pl->cnt++;
				if (pl->cnt < 12)
					pl->y += 4;
				else if (pl->cnt >= 12)
					pl->y += 7;
			}
			else if (pl->y >= 450) {
				pl->y = 450;
				pl->act = sidle;
				pl->cnt = 0;
			}
			break;
		case ult:
			if (pl->cnt >= 54) {
				if (pl->y == 450) { pl->act = sidle; pl->cnt = 0; }
				else { pl->act = sjumpdown; pl->cnt = 0; }
			}
			pl->cnt++;
			break;
		case sdie:
			break;
		}
		break;
	case Banbit1:
	case Banbit2:
		switch (pl->act)
		{
		case baidle:
			if (pl->cnt >= 28)pl->cnt = 0;
			pl->cnt++;
			break;
		case barun:
			if (pl->cnt >= 28) { pl->act = baidle; pl->cnt = 0; }
			pl->cnt++;
			break;
		case baattack:
			if (pl->cnt >= 28) {
				 pl->act = baidle; pl->cnt = 0; 
			}
			pl->cnt++;
			break;
		case barespawn:
			if (pl->cnt >= 42) {
				pl->act = baidle; pl->cnt = 0; 
			}
			pl->cnt++;
			break;
		case bahit:
			if (pl->cnt >= 40) {
				pl->act = baidle; pl->cnt = 0; 
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case badie:
			break;
		case ult:
			if (pl->cnt >= 84) {
				pl->act = baidle; pl->cnt = 0; 
			}
			pl->cnt++;
			break;
		}
		break;
	case Knight:
		switch (pl->act)
		{
		case kidle:
			if (pl->cnt >= 21)pl->cnt = 0;
			pl->cnt++;
			break;
		case krun:
			if (pl->cnt >= 27) { pl->act = kidle; pl->cnt = 0; }
			pl->cnt++;
			break;
		case kattack1:
			if (pl->cnt >= 15) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case kattack2:
			if (pl->cnt >= 15) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case kattack3:
			if (pl->cnt >= 18) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case khit:
			if (pl->cnt >= 30) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case kdie:
			break;
		case kjumpup:
			if (pl->cnt >= 15 && pl->y >= 0) { pl->y -= 1; pl->act = kjumpdown; }
			switch (pl->cnt)
			{
			case 0:
			case 1:
			case 2:
				pl->y -= 9;
				break;
			case 3:
				pl->y -= 7;
				break;
			case 4:
			case 5:
				pl->y -= 11;
				break;
			case 6:
			case 7:
			case 8:
				pl->y -= 8;
			case 9:
			case 10:
			case 11:
				pl->y -= 5;
				break;
			case 12:
			case 13:
			case 14:
				pl->y -= 2;
				break;
			}
			pl->cnt++;
			break;
		case kjumpdown:
			if (pl->y < 450) {
				pl->cnt++;
				if (pl->cnt < 12)
					pl->y += 4;
				else if (pl->cnt >= 12)
					pl->y += 7;
			}
			else if (pl->y >= 450) {
				pl->y = 450;
				pl->act = kidle;
				pl->cnt = 0;
			}
			break;
		case kseald:
			if (pl->cnt >= 21) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case kguard:
			if (pl->cnt >= 12) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			if (pl->y != 450)
			{
				pl->y += 2; if (pl->y >= 450)pl->y = 450;
			}
			pl->cnt++;
			break;
		case kroll:
			if (pl->cnt <= 27)
			{
				if (pl->dir == Right)pl->x += 4;
				else pl->x -= 4;
				if (pl->x > (WND_W - 32))pl->x = WND_W - 32;
				else if (pl->x < 0)pl->x = 0;
				pl->cnt++;
			}
			else
			{
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else pl->act = kjumpdown;
			}
			break;
		case ult:
			if (pl->cnt >= 84) {
				if (pl->y == 450) { pl->act = kidle; pl->cnt = 0; }
				else { pl->act = kjumpdown; pl->cnt = 0; }
			}
			pl->cnt++;
			break;
		}
		break;
	}
}

//プレイヤーの描画
void PlayerDraw(Chara* pl, HDC hdc, HDC hMemDC, HBITMAP* hChar)
{
	switch (pl->typ)
	{
	case Valkyrie:
		switch (pl->act)
		{
	case hit:
		if (pl->dir == Right)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_X * (pl->cnt / 10),				//アニメーション
			(VALKYRIE_Y * (int)pl->act));			//どのアニメーションか
		else if (pl->dir == Left)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_REVERS_X - (VALKYRIE_X * (pl->cnt / 10)), //アニメーションのカウント 
			VALKYRIE_REVERS_Y + (VALKYRIE_Y * (int)pl->act)   //反転されたy軸の位置
		);
		break;
	case jumpup:
		if (pl->dir == Right)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_X * (pl->cnt / 5),				//アニメーション
			(VALKYRIE_Y * (int)pl->act));			//どのアニメーションか
		else if (pl->dir == Left)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_REVERS_X - (VALKYRIE_X * (pl->cnt / 5)), //アニメーションのカウント 
			VALKYRIE_REVERS_Y + (VALKYRIE_Y * (int)pl->act)   //反転されたy軸の位置
		);
		break;
	case jumpdown:
		if (pl->dir == Right)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_X * (pl->cnt % 4),				//アニメーション
			(VALKYRIE_Y * (int)pl->act));			//どのアニメーションか
		else if (pl->dir == Left)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_REVERS_X - (VALKYRIE_X * (pl->cnt % 4)), //アニメーションのカウント 
			VALKYRIE_REVERS_Y + (VALKYRIE_Y * (int)pl->act)   //反転されたy軸の位置
		);
		break;
	case ult:
		if (pl->dir == Right)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_X * ((pl->cnt-42) / 6),				//アニメーション
			177);			//どのアニメーションか
		else if (pl->dir == Left)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_REVERS_X - (VALKYRIE_X * ((pl->cnt - 42) / 6)), //アニメーションのカウント 
			1070   //反転されたy軸の位置
		);
		break; 
	default:
		if (pl->dir == Right)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_X * (pl->cnt / 2),				//アニメーション
			(VALKYRIE_Y * (int)pl->act));			//どのアニメーションか
		else if (pl->dir == Left)TBltB(hdc, hMemDC, &hChar[VALKYRIE], pl->x, pl->y,
			VALKYRIE_REVERS_X - (VALKYRIE_X * (pl->cnt / 2)), //アニメーションのカウント 
			VALKYRIE_REVERS_Y + (VALKYRIE_Y * (int)pl->act)   //反転されたy軸の位置
		);
		break;
		}
		break;
	case Assassin:
		switch (pl->act)
		{
		case ajump:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_X * (pl->cnt / 5),
				(ASSASSIN_Y * ((int)pl->act - Action::aidle)),
				ASSASSIN_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X - (ASSASSIN_X * (pl->cnt / 5)),
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * ((int)pl->act - Action::aidle)),
				ASSASSIN_SIZE);		 
			break;
		case ajumpdown:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_X * 2,
				(ASSASSIN_Y * 5),
				ASSASSIN_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X - (ASSASSIN_X * 2),
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * 5),
				ASSASSIN_SIZE);
			break;
		case ult:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_X * ((pl->cnt - 42) / 6),
			   (ASSASSIN_Y * ((int)Action::aattack1 - Action::aidle)),
				ASSASSIN_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X - (ASSASSIN_X * ((pl->cnt - 42) / 6)),
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * ((int)Action::aattack1 - Action::aidle)),
				ASSASSIN_SIZE);
			break;
		case ahit:
		case aattack2:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				0,
				(ASSASSIN_Y * 3),
				ASSASSIN_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X,
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * 3),
				ASSASSIN_SIZE);
			break;
		case aattack3:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				0,
				(ASSASSIN_Y * 4),
				ASSASSIN_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X,
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * 4),
				ASSASSIN_SIZE);
			break;
		default:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_X * (pl->cnt / 4),				
			   (ASSASSIN_Y * ((int)pl->act - Action::aidle)),
				ASSASSIN_SIZE);			
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[ASSASSIN], pl->x, pl->y,
				ASSASSIN_REVERS_X - (ASSASSIN_X * (pl->cnt / 4)), 
				ASSASSIN_REVERS_Y + (ASSASSIN_Y * ((int)pl->act - Action::aidle)),
				ASSASSIN_SIZE);
			break;
		}
		break;
	case Monk:
		switch (pl->act)
		{
		case mhit:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_X * (pl->cnt  / 18),
				(MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * (pl->cnt / 18)),
				MONK_REVERS_Y + (MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			break;
		case mguard:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_X * (pl->cnt / 15),
				(MONK_Y * ((int)Action::mseald - Action::midle)),
				MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * (pl->cnt / 18)),
				MONK_REVERS_Y + (MONK_Y * ((int)Action::mseald - Action::midle)),
				MONK_SIZE);
			break;
		case mjumpup:
		case mjumpattack:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_X * (pl->cnt / 7),
				(MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * (pl->cnt / 7)),
				MONK_REVERS_Y + (MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			break;
		case mjumpdown:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_X * (pl->cnt % 2),
				(MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * (pl->cnt % 2)),
				MONK_REVERS_Y + (MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			break;
		case ult:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_X * ((pl->cnt - 42) / 6),
				(MONK_Y * ((int)Action::mattack1 - Action::midle)),
				MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * ((pl->cnt - 42) / 6)),
				MONK_REVERS_Y + (MONK_Y * ((int)Action::mattack1 - Action::midle)),
				MONK_SIZE);
			break;
		default:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				 MONK_X * (pl->cnt / 4),
				(MONK_Y * ((int)pl->act - Action::midle)),
				 MONK_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[MONK], pl->x, pl->y,
				MONK_REVERS_X - (MONK_X * (pl->cnt / 4)),
				MONK_REVERS_Y + (MONK_Y * ((int)pl->act - Action::midle)),
				MONK_SIZE);
			break;
		}
		break;
	case Sniper:
		switch (pl->act)
		{
		case sjumpup:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt / 8),
				(SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt / 8)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			break;
		case sjumpdown:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt % 2),
				(SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt % 2)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			break;
		case srun:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt / 2),
				(SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt / 2)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			break;
		case shit:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt / 18),
				(SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt / 18)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			break;
		case sguard:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt / 18),
				(SNIPER_Y * ((int)Action::sseald - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt / 18)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)Action::sseald - Action::sidle)),
				SNIPER_SIZE);
			break;
		case ult:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * ((pl->cnt - 42) / 6),
				(SNIPER_Y * ((int)Action::sattack1 - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * ((pl->cnt - 42) / 6)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)Action::sattack1 - Action::sidle)),
				SNIPER_SIZE);
			break;
		default:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_X * (pl->cnt / 4),
				(SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[SNIPER], pl->x, pl->y,
				SNIPER_REVERS_X - (SNIPER_X * (pl->cnt / 4)),
				SNIPER_REVERS_Y + (SNIPER_Y * ((int)pl->act - Action::sidle)),
				SNIPER_SIZE);
			break;
		}
		break;
	case Banbit1:
		switch (pl->act)
		{
		case bahit:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y - 2,
				BANBIT_X * (pl->cnt % 2),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt % 2)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		case barespawn:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_X * (pl->cnt / 6),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt / 6)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		case ult:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_X * ((pl->cnt - 42) / 6),
			   (BANBIT_Y * ((int)Action::baattack - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_REVERS_X - (BANBIT_X * ((pl->cnt - 42) / 6)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)Action::baattack - Action::baidle)),
				BANBIT_SIZE);
			break;
		default:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y -2,
				BANBIT_X * (pl->cnt / 4),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT1], pl->x, pl->y - 2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt / 4)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		}
		break;
	case Banbit2:
		switch (pl->act)
		{
		case bahit:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_X * (pl->cnt % 2),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt % 2)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		case barespawn:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_X * (pl->cnt / 6),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt / 6)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		case ult:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_X * ((pl->cnt - 42) / 6),
				(BANBIT_Y * ((int)Action::baattack - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_REVERS_X - (BANBIT_X * ((pl->cnt - 42) / 6)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)Action::baattack - Action::baidle)),
				BANBIT_SIZE);
			break;
		default:
			if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_X * (pl->cnt / 4),
				(BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			else if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[BANBIT2], pl->x, pl->y - 2,
				BANBIT_REVERS_X - (BANBIT_X * (pl->cnt / 4)),
				BANBIT_REVERS_Y + (BANBIT_Y * ((int)pl->act - Action::baidle)),
				BANBIT_SIZE);
			break;
		}
		break;
	case Knight:
		switch (pl->act)
		{
		case khit:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_X * (pl->cnt / 10),
				(KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_REVERS_X - (KNIGHT_X * (pl->cnt / 10)),
				KNIGHT_REVERS_Y + (KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			break;
		case kjumpup:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_X * (pl->cnt / 5),
				(KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_REVERS_X - (KNIGHT_X * (pl->cnt / 5)),
				KNIGHT_REVERS_Y + (KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			break;
		case kjumpdown:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_X * (pl->cnt % 4),
				(KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_REVERS_X - (KNIGHT_X * (pl->cnt % 4)),
				KNIGHT_REVERS_Y + (KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			break;
		case ult:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_X * ((pl->cnt - 42) / 6),
				(KNIGHT_Y * ((int)Action::kattack3 - Action::kidle)),
				KNIGHT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_REVERS_X - (KNIGHT_X * ((pl->cnt - 42) / 6)),
				KNIGHT_REVERS_Y + (KNIGHT_Y * ((int)Action::kattack3 - Action::kidle)),
				KNIGHT_SIZE);
			break;
		default:
			if (pl->dir == Right)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_X * (pl->cnt / 3),
			   (KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			else if (pl->dir == Left)TBltC(hdc, hMemDC, &hChar[KNIGHT], pl->x, pl->y,
				KNIGHT_REVERS_X - (KNIGHT_X * (pl->cnt / 3)),
				KNIGHT_REVERS_Y + (KNIGHT_Y * ((int)pl->act - Action::kidle)),
				KNIGHT_SIZE);
			break;
		}
		break;
	}
}

#pragma region PLAYERSHOT関係

//弾自体の処理
void PlayerShotExecute(Chara* sh,int max)
{
	for (int i = 0; i < max; i++) {
		if (sh[i].die) {
			//それぞれの弾の動き
			switch (sh[i].typ)
			{
			case Valkyrie:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right)sh[i].x += 8;
					else sh[i].x -= 8;
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case roll:
					if (sh[i].cnt > 10)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 6; }
					else { sh[i].x -= 8; sh[i].y -= 6; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case skill:
					sh[i].cnt++;
					if (sh[i].cnt > 20) {
						if (sh[i].cnt == 21)PlaySoundA("素材/効果音/効果音13.wav", NULL, SND_ASYNC | SND_FILENAME);

						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y += 10; }
						else { sh[i].x -= 8; sh[i].y += 10; }
					}
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < -50) {
						InitShot(&sh[i]);
					}
					break;
				case ult:
					sh[i].cnt++;
					if(sh[i].cnt==42)PlaySoundA("素材/効果音/ボイス3.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			case Assassin:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right)sh[i].x += 8 ;
					else sh[i].x -= 8 ;
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case roll:
					if (sh[i].cnt > 10)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y += 4; }
					else { sh[i].x -= 8; sh[i].y += 4; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case skill:
					if (sh[i].cnt > 36)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { 
						sh[i].x += sh[i].cnt / 3;
					}
					else {
						sh[i].x += -1 * ((sh[i].cnt) / 3);
					}
					if (sh[i].cnt < 18)sh[i].y -= 2;
					else if(sh[i].cnt < 36)sh[i].y += 2;
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < -50) {
						InitShot(&sh[i]);
					}
					break;
				case ult:
					sh[i].cnt++;
					if (sh[i].cnt == 42)PlaySoundA("素材/効果音/ボイス7.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			case Monk:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) sh[i].x += 8;
					else sh[i].x -= 8; 
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case roll:
					if (sh[i].cnt > 10)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 15; }
					else { sh[i].x -= 8; sh[i].y -= 15; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case skill:
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 6; }
					else { sh[i].x -= 8; sh[i].y -= 6; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < -50) {
						InitShot(&sh[i]);
					}
					break;
				case hit:
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y +=3+ (i % 3) * 3; }
					else { sh[i].x -= 8; sh[i].y += 3 + ((i % 3) * 3); }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
				case ult:
					sh[i].cnt++;
					if (sh[i].cnt == 42)PlaySoundA("素材/効果音/ボイス5.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			case Sniper:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right)sh[i].x += 18;
					else sh[i].x -= 18;
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case roll:
					if (sh[i].cnt > 10)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 18; sh[i].y -= 8; }
					else { sh[i].x -= 18; sh[i].y -= 8; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case ult:
					sh[i].cnt++;
					if (sh[i].cnt == 42)PlaySoundA("素材/効果音/ボイス1.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			case Banbit1:
			case Banbit2:
				switch (sh[i].act)
				{
				case roll:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= (i % 3) * 3; }
					else { sh[i].x -= 8; sh[i].y -= (i % 3) * 3; }
					if (sh[i].x > 850 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case ult:
					sh[i].cnt++;
					if (sh[i].cnt == 42)PlaySoundA("素材/効果音/ボイス2.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			case Knight:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].cnt > 12)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right)sh[i].x += 10;
					else sh[i].x -= 10;
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case roll:
					if (sh[i].cnt > 10)sh[i].cnt = 0;
					sh[i].cnt++;
					if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 8; }
					else { sh[i].x -= 8; sh[i].y -= 8; }
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < 0) {
						InitShot(&sh[i]);
					}
					break;
				case skill:
					sh[i].cnt++;
					if (sh[i].cnt > 20) {
						if (sh[i].cnt == 21)PlaySoundA("素材/効果音/効果音13.wav", NULL, SND_ASYNC | SND_FILENAME);

						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y += 10; }
						else { sh[i].x -= 8; sh[i].y += 10; }
					}
					if (sh[i].x > 1600 || sh[i].x < 0 || sh[i].y>WND_H || sh[i].y < -50) {
						InitShot(&sh[i]);
					}
					break;
				case ult:
					sh[i].cnt++;
					if (sh[i].cnt == 42)PlaySoundA("素材/効果音/ボイス4.wav", NULL, SND_ASYNC | SND_FILENAME);
					if (sh[i].cnt > 72) {
						if (sh[i].dir == Right) { sh[i].x += 8; sh[i].y -= 1; }
						else { sh[i].x -= 8; sh[i].y -= 1; }
					}
					if (sh[i].x > 1600 || sh[i].x < -500) {
						InitShot(&sh[i]);
					}
					break;
				}
				break;
			}
		}
	}
}

//敵一体に対する当たり判定
void PlayerShotHitCheckOnce(Chara* sh, Chara* bo, Chara* pl, int* Score)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		//ボスへのヒット判定
		if (bo->interval[hitinterval] >= 50 && bo->die == false && sh[i].die == true) {
			//左向いているときの判定
			if (bo->dir == Left) {
				if (sh[i].act != ult)
				{
					if (HitCheck(sh[i].x , sh[i].y, bo->dx, bo->y +16))
					{
						bo->hp -= sh[i].atk;
						bo->act = hit;
						bo->cnt = 0;
						if (bo->hp <= 0)
						{
							PlaySoundA("素材/効果音/効果音15.wav", NULL, SND_ASYNC | SND_FILENAME);
							*Score += 1000;
							bo->act = bdie;
							bo->die = true;
						}
						else PlaySoundA("素材/効果音/効果音7.wav", NULL, SND_ASYNC | SND_FILENAME);
						switch (sh[i].act)
						{
						case skill:
							pl->interval[shotinterval] += 20;
							break;
						default:
							pl->interval[shotinterval] += 15;
							InitShot(&sh[i]);
							break;
						}
					}
				}
				else
				{
					if (HitCheckUlt(sh[i].x, sh[i].y,
						sh[i].x + ((SHOT_X_SIZE+ SHOT_X_SIZE) + (sh[i].cnt * 2)),
						sh[i].y + ((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2)),
						bo->dx, bo->y,
						bo->dx + BOSS_X_SIZE/2,
						bo->y + BOSS_Y_SIZE))
					{
						bo->hp -= sh[i].atk;
							bo->act = hit;
							bo->cnt = 0;
							if (bo->hp <= 0)
							{
								PlaySoundA("素材/効果音/効果音15.wav", NULL, SND_ASYNC | SND_FILENAME);
								*Score += 1000;
								bo->act = bdie;
								bo->die = true;
							}
					}
				}
			}
			//左向いているときの判定
			if (bo->dir == Right) {
				if (sh[i].act != ult) {
					if (HitCheck(sh[i].x + 16, sh[i].y, (bo->dx + 80), bo->y + 15))
					{
						bo->hp -= sh[i].atk;
						bo->act = hit;
						bo->cnt = 0;
						if (bo->hp <= 0)
						{
							PlaySoundA("素材/効果音/効果音15.wav", NULL, SND_ASYNC | SND_FILENAME);
							*Score += 1000;
							bo->act = bdie;
							bo->die = true;
						}
						else PlaySoundA("素材/効果音/効果音7.wav", NULL, SND_ASYNC | SND_FILENAME);
						switch (sh[i].act)
						{
						case skill:
							pl->interval[shotinterval] += 20;
							break;
						case ult:
							break;
						default:
							pl->interval[shotinterval] += 15;
							InitShot(&sh[i]);
							break;
						}
					}
				}
				else
				{
					if (HitCheckUlt(sh[i].x, sh[i].y,
						sh[i].x + ((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						sh[i].y + ((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2)),
						bo->dx, bo->y,
						bo->dx + BOSS_X_SIZE / 2,
						bo->y + BOSS_Y_SIZE))
					{
						bo->hp -= sh[i].atk;
						bo->act = hit;
						bo->cnt = 0;
						if (bo->hp <= 0)
						{
							PlaySoundA("素材/効果音/効果音15.wav", NULL, SND_ASYNC | SND_FILENAME);
							*Score += 1000;
							bo->act = bdie;
							bo->die = true;
						}
					}
				}
			}
		}
	}
}

//敵複数に対する当たり判定
void PlayerShotHitCheckSame(Chara* sh, Chara* en,Chara* pl,int* Score, int enmax)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		//敵へのヒット判定
		for (int j = 0; j < enmax; j++) {

			if (en[j].interval[hitinterval] >= 20 && en[j].die == false)
			{
				//右向いているときの判定
				if (en[j].dir == Right)
				{
					if (sh[i].act != ult) {
						if (HitCheck(sh[i].x + 16, sh[i].y + 16, en[j].dx + 5, en[j].y+5))
						{
							en[j].hp -= sh[i].atk;
							en[j].act = hit;
							en[j].cnt = 0;
							if (en[j].hp <= 0) {
								PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);
								*Score += 200;
								en[j].die = true;
							}
							else PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);

							en[j].interval[hitinterval]--;
							switch (sh[i].act)
							{
							case skill:
								pl->interval[shotinterval] += 15;
								break;
							case idle:
								pl->interval[shotinterval] += 10;
								break;
							default:
								pl->interval[shotinterval] += 8;
								InitShot(&sh[i]);
								break;
							}
						}
					}
					else {
						if (HitCheckUlt(sh[i].x, sh[i].y,
							sh[i].x + ((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
							sh[i].y + ((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2)),
							en[j].dx, en[j].y,
							en[j].dx + ENEMY_X_SIZE,
							en[j].y + ENEMY_Y_SIZE))
						{
							en[j].hp -= sh[i].atk;
							en[j].act = hit;
							en[j].cnt = 0;
							if (en[j].hp <= 0) {
								PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);
								*Score += 200;
								en[j].die = true;
							}
						}
					}
				}
				//左向いているときの判定
				else if (en[j].dir == Left)
				{
					if (sh[i].act != ult) {
						if (HitCheck(sh[i].x + 16, sh[i].y + 16, en[j].dx + 5, en[j].y + 5))
						{
							en[j].hp -= sh[i].atk;
							en[j].act = hit;
							en[j].cnt = 0;
							if (en[j].hp <= 0) {
								PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);
								*Score += 200;
								en[j].die = true;
							}
							else PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);

							en[j].interval[hitinterval]--;
							switch (sh[i].act)
							{
							case skill:
								pl->interval[shotinterval] += 15;
								break;
							case ult:
								break;
							case idle:
								pl->interval[shotinterval] += 10;
								break;
							default:
								pl->interval[shotinterval] += 8;
								InitShot(&sh[i]);
								break;
							}
						}
					}
					else
					{
					if (HitCheckUlt(sh[i].x, sh[i].y,
						sh[i].x + ((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						sh[i].y + ((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2)),
						en[j].dx, en[j].y,
						en[j].dx + ENEMY_X_SIZE,
						en[j].y + ENEMY_Y_SIZE))
						{
						en[j].hp -= sh[i].atk;
						en[j].act = hit;
						en[j].cnt = 0;
						if (en[j].hp <= 0) {
							PlaySoundA("素材/効果音/効果音8.wav", NULL, SND_ASYNC | SND_FILENAME);
							*Score += 200;
							en[j].die = true;
							}
						}
				
					}
				}
			}
		}
	}
}

//プレイヤーの弾の描画
void PlayerShotDraw(Chara* sh, HDC hdc, HDC hMemDC, HBITMAP* hShot)
{
	for (int i = 0; i < SHOT_MAX; i++) {
		if (sh[i].die) {
			switch (sh[i].typ)
			{
			case Valkyrie:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].dir == Left)TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (SHOT_X_SIZE * (sh[i].cnt / 2)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)		//メモリ画像のy開始位置
					);
					else TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_X_SIZE * (sh[i].cnt / 2),						//メモリ画像のx開始位置
						SHOT_Y_SIZE * (int)sh[i].act							//メモリ画像のy開始位置
					);
					break;
				case roll:
					if (sh[i].dir == Left)TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (40 * (sh[i].cnt / 2)),
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)
					);
					else TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						49 * (sh[i].cnt / 2),
						SHOT_Y_SIZE * (int)sh[i].act
					);
					break;
				case skill:
					if (sh[i].cnt <= 20) {
						TBltS4(hdc, hMemDC, &hShot[spel], sh[i].x, sh[i].y, 36 * (sh[i].cnt / 10), 0);
					}
					else
					{
						if (sh[i].dir == Right)
						{
							TBltS3(hdc, hMemDC, &hShot[sword], sh[i].x, sh[i].y, 0, 0);
						}
						else
						{
							TBltS3(hdc, hMemDC, &hShot[sword], sh[i].x, sh[i].y, 0, 46);
						}
					}
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			case Assassin:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].dir == Left)TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (SHOT_X_SIZE * (sh[i].cnt / 2)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)		//メモリ画像のy開始位置
					);
					else TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_X_SIZE * (sh[i].cnt / 2),						//メモリ画像のx開始位置
						SHOT_Y_SIZE * (int)sh[i].act							//メモリ画像のy開始位置
					);
					break;
				case roll:
					if (sh[i].dir == Left)TBltC(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y, 64, 128, 32, 32);
					else TBltC(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,64,128,32,32);
					break;
				case skill:
					if (sh[i].dir == Right)
					TBltC(hdc, hMemDC, &hShot[pet], sh[i].x, sh[i].y,96 * (sh[i].cnt / 12),53, 96, 53);
					else
						TBltC(hdc, hMemDC, &hShot[pet], sh[i].x, sh[i].y,
							96 * (sh[i].cnt / 12),
							0, 96, 53);
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			case Monk:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].dir == Left)TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (SHOT_X_SIZE * (sh[i].cnt / 2)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)		//メモリ画像のy開始位置
					);
					else TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_X_SIZE * (sh[i].cnt / 2),						//メモリ画像のx開始位置
						SHOT_Y_SIZE * (int)sh[i].act						//メモリ画像のy開始位置
					);
					break;
				case roll:
					TBltC(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y, 64, 128, 32, 32);
					break;
				case skill:
					TBltC(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y, 64, 128, 32, 32);
					break;
				case hit:
					TBltC(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y, 64, 128, 32, 32);
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			case Sniper:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].dir == Left)TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (SHOT_X_SIZE * (sh[i].cnt / 2)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)roll)		//メモリ画像のy開始位置
					);
					else TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_X_SIZE * (sh[i].cnt / 2),						//メモリ画像のx開始位置
						SHOT_Y_SIZE * (int)roll							//メモリ画像のy開始位置
					);
					break;
				case roll:
					if (sh[i].dir == Left)TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (40 * (sh[i].cnt / 2)),
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)
					);
					else TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						49 * (sh[i].cnt / 2),
						SHOT_Y_SIZE * (int)sh[i].act
					);
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			case Banbit2:
			case Banbit1:
				switch (sh[i].act)
				{
				case roll:
					if (sh[i].dir == Left)TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (40 * (sh[i].cnt / 2)),
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)
					);
					else TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						49 * (sh[i].cnt / 2),
						SHOT_Y_SIZE * (int)sh[i].act
					);
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			case Knight:
				switch (sh[i].act)
				{
				case idle:
					if (sh[i].dir == Left)TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (SHOT_X_SIZE * (sh[i].cnt / 2)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)		//メモリ画像のy開始位置
					);
					else TBltS(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_X_SIZE * (sh[i].cnt / 2),						//メモリ画像のx開始位置
						SHOT_Y_SIZE * (int)sh[i].act							//メモリ画像のy開始位置
					);
					break;
				case roll:
					if (sh[i].dir == Left)TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						SHOT_REVERS_X - (40 * (sh[i].cnt / 2)),
						SHOT_REVERS_Y + (SHOT_Y_SIZE * (int)sh[i].act)
					);
					else TBltS2(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						49 * (sh[i].cnt / 2),
						SHOT_Y_SIZE * (int)sh[i].act
					);
					break;
				case skill:
					if (sh[i].cnt <= 20) {
						TBltS4(hdc, hMemDC, &hShot[spel], sh[i].x, sh[i].y, 36 * (sh[i].cnt / 10), 0);
					}
					else
					{
						if (sh[i].dir == Right)
						{
							TBltS3(hdc, hMemDC, &hShot[sword], sh[i].x, sh[i].y, 0, 0);
						}
						else
						{
							TBltS3(hdc, hMemDC, &hShot[sword], sh[i].x, sh[i].y, 0, 46);
						}
					}
					break;
				case ult:
					if (sh[i].dir == Left)TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						317 - ((64) * (sh[i].cnt % 5)),	//メモリ画像のx開始位置
						SHOT_REVERS_Y + 224,												//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					else TBltSU(hdc, hMemDC, &hShot[longshot], sh[i].x, sh[i].y,
						(SHOT_X_SIZE + SHOT_X_SIZE) * (sh[i].cnt % 5),						//メモリ画像のx開始位置
						224,																//メモリ画像のy開始位置
						((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
						((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2))
					);
					break;
				}
				break;
			}
		}
	}
}

#pragma endregion

#pragma endregion

#pragma region ENEMY関係
//敵自体の処理
void EnemyExecute(Chara* en, Chara* pl, int* beforshotx)
{
	for (int i = 0; i < ENEMY_MAX; i++) {

		//プレイヤーが右にいてるか左にいてるか
		if (en[i].dx <= pl->x)en[i].dir = Right;
		else en[i].dir = Left;

		//敵AIの作成
		if (en[i].interval[jumpinterval] >= 50) {
			int EnemyAi = rand() % 3;
			switch (EnemyAi)
			{
			case 0:
				en[i].act = ework;
				break;
			case 1:
				en[i].act = eatack;
				en[i].atk = 2;
				beforshotx[i] = en[i].x;
				break;
			case 2:
				en[i].act = ejump;
				break;
			}
		}

		//範囲外に行った時の処理
		if (en[i].dx > 1600 || en[i].y > WND_H || en[i].dx < 0 || en[i].y < 0)
		{
			InitEnemy(&en[i]);
		}

		//敵のプレイヤーへのヒット判定
		if (pl->act != barespawn&& pl->act != kroll && pl->act != khit && pl->act != ahit && pl->act != mhit && pl->act != shit && pl->act != bahit) {
			if (pl->act != mguard && pl->act != sguard && pl->act != kguard && pl->act != roll && pl->act != hit && pl->interval[hitinterval] == 50 && pl->die == false)
			{
				if (HitCheck(en[i].dx, en[i].y, pl->x, pl->y))
				{
					if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
					{
						pl->hp -= en[i].atk;
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = hit;
							break;
						case Assassin:
							pl->act = ahit;
							break;
						case Monk:
							pl->act = mhit;
							break;
						case Sniper:
							pl->act = shit;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = bahit;
							break;
						case Knight:
							pl->act = khit;
							break;
						}
					}
					else {
						switch (pl->typ)
						{
						case Knight:
							pl->hp -= (en[i].atk / 3);
							pl->interval[shotinterval] += 10;
							pl->act = kguard;
							break;
						case Monk:
							pl->hp -= (en[i].atk / 2);
							pl->cnt = 0;
							pl->act = mguard;
							break;
						case Sniper:
							pl->hp -= (en[i].atk / 2);
							pl->cnt = 0;
							pl->act = sguard;
							break;
						}
					}
					pl->cnt = 0;
					if (pl->hp <= 0) {
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = die;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = badie;
							break;
						case Knight:
							pl->act = kdie;
							break;
						}
						pl->die = true;
						pl->cnt = 0;
					}
					PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
				}
			}
		}
		
		//死亡処理
		if (en[i].die)
		{
			en[i].cnt++;
			if (en[i].cnt > 15)
			{
				InitEnemy(&en[i]);
			}
		}

		//攻撃を食らってからの無敵時間
		if (en[i].interval[hitinterval] < 20)en[i].interval[hitinterval]--;
		if (en[i].interval[hitinterval] <= 0)en[i].interval[hitinterval] = 20;

		//AIの次の読み込みまでのデクリメント
		en[i].interval[jumpinterval]--;
	}

}

//敵のアニメーション
void AnimationEnemy(Chara* en, Chara* esh)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (en[i].act)
		{
		case ework:
			if (en[i].cnt >= 90) { en[i].act = eidle; en[i].cnt = 0; }
			en[i].cnt++;
			if (en[i].dir == Right) { en[i].dx += 2; en[i].x += 2; }
			else { en[i].dx -= 2; en[i].x -= 2; }
			break;
		case eatack:
			if (en[i].cnt == 0)
			{
				for (int j = i * 3; j < (i*3) + 3; j++)
				{
					InitShot(&esh[j]);
				}
			}
			if (en[i].cnt >= 60) { en[i].act = eidle; en[i].cnt = 0; }
			en[i].cnt++;
			break;
		case eidle:
			if (en[i].cnt >= 60) {
				en[i].cnt = 0;
				if (en[i].interval[jumpinterval] <= 0)en[i].interval[jumpinterval] = 50;
			}
			en[i].cnt++;
			break;
		case ejump:
			if (en[i].cnt >= 30) { en[i].act = eatack; en[i].cnt = 0; }
			if (en[i].cnt < 15)
			{
				en[i].y -= 12;
				if (en[i].dir == Right) { en[i].dx -= 4; en[i].x -= 4; }
				else { en[i].dx += 4; en[i].x += 4; }
			}
			else if (en[i].cnt > 15) {
				en[i].y += 12;
				if (en[i].dir == Right) { en[i].dx -= 4; en[i].x -= 4; }
				else { en[i].dx += 4; en[i].x += 4; }
			}
			en[i].cnt++;
			break;
		case hit:
			if (en[i].cnt >= 20) { en[i].act = eatack; en[i].cnt = 0; }
			en[i].cnt++;
			break;
		}
	}

#pragma region 敵の弾の発生
	if (en[0].act == eatack)
		EnemyShotTiming(&en[0], esh, 0);
	if (en[1].act == eatack)
		EnemyShotTiming(&en[1], esh, 3);
	if (en[2].act == eatack)
		EnemyShotTiming(&en[2], esh, 6);
	if (en[3].act == eatack)
		EnemyShotTiming(&en[3], esh, 9);
	if (en[4].act == eatack)
		EnemyShotTiming(&en[4], esh, 12);
#pragma endregion

}

//敵の描画(弾も含める)
void EnemyDraw(Chara* en, Chara* esh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hShot)
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (esh[i].die)TBltE(hdc, hMemDC, &hShot[longshot], esh[i].dx, esh[i].y, 0, 64);
	}
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (!en[i].die) {
			if (en[i].dir == Left)
				TBltZ(hdc, hMemDC, &hChar[ZAKO], en[i].dx, en[i].y,
					ENEMY_REVERS_X - ((ENEMY_X_SIZE - 1) * ((int)en[i].cnt / 30)),
					ENEMY_REVERS_Y + (ENEMY_Y_SIZE * (en[i].act - (int)Action::eatack))
				);
			else if (en[i].dir == Right)
				TBltZ(hdc, hMemDC, &hChar[ZAKO], en[i].dx, en[i].y,
					ENEMY_X_SIZE * (en[i].cnt / 30),
					ENEMY_Y_SIZE * (en[i].act - (int)Action::eatack)
				);
		}
		if (en[i].act == hit) {
			if (en[i].dir == Right)TBltZ(hdc, hMemDC, &hChar[ZAKO], en[i].dx, en[i].y, 0, 97);
			else TBltZ(hdc, hMemDC, &hChar[ZAKO], en[i].dx, en[i].y, ENEMY_REVERS_X, ENEMY_REVERS_Y + 97);
			if (en[i].die)TBltE(hdc, hMemDC, &hShot[longshot], en[i].dx, en[i].y, SHOT_X_SIZE * (en[i].cnt / 2), 32 * 4);
		}
	}
}

//敵の弾自体の処理
void EnemyShotExecute(Chara* esh, Chara* pl)
{
	for (int i = 0; i < ENEMY_SHOT_MAX; i++)
	{
		if (esh[i].die) {

			//敵の弾の挙動
			if (esh[i].dir == Left) { esh[i].x -= (6 + (i % 3) * 3); esh[i].y += 4; }
			else { esh[i].x += (6 + (i % 3) * 3); esh[i].y += 4; }
			
			//敵の弾のプレイヤーへのヒット判定
			if (pl->act != barespawn && pl->act != kroll && pl->act != khit && pl->act != ahit && pl->act != mhit && pl->act != shit && pl->act != bahit) {
				if (pl->act != mguard &&pl->act != sguard && pl->act != kguard && pl->act != roll && pl->act != hit && pl->interval[hitinterval] == 50 && pl->die == false)
				{
					if (HitCheck(esh[i].dx, esh[i].y, pl->x, pl->y))
					{
						if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
						{
							pl->hp -= esh[i].atk;
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = hit;
								break;
							case Assassin:
								pl->act = ahit;
								break;
							case Monk:
								pl->act = mhit;
								break;
							case Sniper:
								pl->act = shit;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = bahit;
								break;
							case Knight:
								pl->act = khit;
								break;
							}
						}
						else {
							switch (pl->typ)
							{
							case Knight:
								pl->hp -= (esh[i].atk / 3);
								pl->interval[shotinterval] += 10;
								pl->act = kguard;
								break;
							case Monk:
								pl->hp -= (esh[i].atk / 2);
								pl->cnt = 0;
								pl->act = mguard;
								break;
							case Sniper:
								pl->hp -= (esh[i].atk / 2);
								pl->cnt = 0;
								pl->act = sguard;
								break;
							}
						}
						pl->cnt = 0;
						if (pl->hp <= 0) {
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = die;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = badie;
								break;
							case Knight:
								pl->act = kdie;
								break;
							}
							pl->die = true;
							pl->cnt = 0;
						}
						PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
				}
			}
			
			//画面外に出たときの初期化
			if (esh[i].dx > 1600 || esh[i].y > WND_H || esh[i].dx < 0 || esh[i].y < 0)
			{
				InitShot(&esh[i]);
			}
		}
	}
}

//敵の弾の発生タイミング
void EnemyShotTiming(Chara* en, Chara* esh, int a)
{
	if (en->cnt == 10) {
		esh[a].die = true; esh[a].dir = en->dir;
		esh[a].atk = en->atk;
		esh[a].x = en->x; esh[a].y = en->y + 10;
	}
	else if (en->cnt == 30) {
		esh[a + 1].die = true; esh[a + 1].dir = en->dir;
		esh[a].atk = en->atk;
		esh[a + 1].x = en->x; esh[a + 1].y = en->y + 10;
	}
	else if (en->cnt == 50) {
		esh[a + 2].die = true; esh[a + 2].dir = en->dir;
		esh[a].atk = en->atk;
		esh[a + 2].x = en->x; esh[a + 2].y = en->y + 10;
	}
}

//敵の弾の描画場所
void EnemyShotDrawPos(Chara* esh,Chara* pl, int a, int x)
{
	if (esh[a].die) {
		esh[a].dx = esh[a].x  - pl->x;
	}
	if (esh[a + 1].die) {
		esh[a + 1].dx = esh[a + 1].x  - pl->x;
	}
	if (esh[a + 2].die) {
		esh[a + 2].dx = esh[a + 2].x  - pl->x;
	}
}

#pragma endregion

#pragma region BOSS関係

//Boss自体の処理
void BossExecute(Chara* bo, Chara* pl, Chara* bsh, int* beforx)
{
	//プレイヤーが右にいてるか左にいてるか
	if (bo->dx + 40 <= pl->x)bo->dir = Left;
	else bo->dir = Right;

	//プレイヤーへの当たり判定
	if (pl->act != barespawn && pl->act != kroll && pl->act != khit && pl->act != ahit && pl->act != mhit && pl->act != shit && pl->act != bahit) {
		if (pl->act != mguard &&pl->act != sguard && pl->act != kguard && pl->act != roll && pl->act != hit && pl->interval[hitinterval] == 50 && pl->die == false) {
			//右向き
			if (bo->dir == Right) {
				//剣を振り下ろす攻撃右
				if (bo->act == batack1 && bo->cnt > 31 && bo->cnt < 65) {
					if (HitCheckB(bo->dx, bo->y + 10, pl->x, pl->y, 80))
					{
						if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
						{
							pl->hp -= bo->atk;
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = hit;
								break;
							case Assassin:
								pl->act = ahit;
								break;
							case Monk:
								pl->act = mhit;
								break;
							case Sniper:
								pl->act = shit;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = bahit;
								break;
							case Knight:
								pl->act = khit;
								break;
							}
						}
						else {
							switch (pl->typ)
							{
							case Knight:
								pl->hp -= (bo->atk / 3);
								pl->interval[shotinterval] += 10;
								pl->act = kguard;
								break;
							case Monk:
								pl->hp -= (bo->atk / 2);
								pl->cnt = 0;
								pl->act = mguard;
								break;
							case Sniper:
								pl->hp -= (bo->atk / 2);
								pl->cnt = 0;
								pl->act = sguard;
								break;
							}
						}
						pl->cnt = 0;
						if (pl->hp <= 0) {
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = die;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = badie;
								break;
							case Knight:
								pl->act = kdie;
								break;
							}
							pl->die = true;
							pl->cnt = 0;
						}
						PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
				}
				//通常時の当たり判定
				if (HitCheck(bo->dx + 80, bo->y + 10, pl->x, pl->y))
				{
					if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
					{
						pl->hp -= bo->atk;
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = hit;
							break;
						case Assassin:
							pl->act = ahit;
							break;
						case Monk:
							pl->act = mhit;
							break;
						case Sniper:
							pl->act = shit;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = bahit;
							break;
						case Knight:
							pl->act = khit;
							break;
						}
					}
					else {
						switch (pl->typ)
						{
						case Knight:
							pl->hp -= (bo->atk / 3);
							pl->interval[shotinterval] += 10;
							pl->act = kguard;
							break;
						case Monk:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = mguard;
							break;
						case Sniper:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = sguard;
							break;
						}
					}
					pl->cnt = 0;
					if (pl->hp <= 0) {
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = die;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = badie;
							break;
						case Knight:
							pl->act = kdie;
							break;
						}
						pl->die = true;
						pl->cnt = 0;
					}
					PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
				}
			}
			//左向き
			else if (bo->dir == Left)
			{
				//剣を振り下ろす攻撃左
				if (bo->act == batack1 && bo->cnt > 31 && bo->cnt < 65) {
					if (HitCheckB(bo->dx + 40, bo->y + 10, pl->x, pl->y, 80))
					{
						if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
						{
							pl->hp -= bo->atk;
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = hit;
								break;
							case Assassin:
								pl->act = ahit;
								break;
							case Monk:
								pl->act = mhit;
								break;
							case Sniper:
								pl->act = shit;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = bahit;
								break;
							case Knight:
								pl->act = khit;
								break;
							}
						}
						else {
							switch (pl->typ)
							{
							case Knight:
								pl->hp -= (bo->atk / 3);
								pl->interval[shotinterval] += 10;
								pl->act = kguard;
								break;
							case Monk:
								pl->hp -= (bo->atk / 2);
								pl->cnt = 0;
								pl->act = mguard;
								break;
							case Sniper:
								pl->hp -= (bo->atk / 2);
								pl->cnt = 0;
								pl->act = sguard;
								break;
							}
						}
						pl->cnt = 0;
						if (pl->hp <= 0) {
							switch (pl->typ)
							{
							case Valkyrie:
								pl->act = die;
								break;
							case Banbit1:
							case Banbit2:
								pl->act = badie;
								break;
							case Knight:
								pl->act = kdie;
								break;
							}
							pl->die = true;
							pl->cnt = 0;
						}
						PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
					}
				}
				//通常時の当たり判定
				if (HitCheck((bo->dx), bo->y + 10, pl->x, pl->y))
				{
					if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
					{
						pl->hp -= bo->atk;
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = hit;
							break;
						case Assassin:
							pl->act = ahit;
							break;
						case Monk:
							pl->act = mhit;
							break;
						case Sniper:
							pl->act = shit;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = bahit;
							break;
						case Knight:
							pl->act = khit;
							break;
						}
					}
					else {
						switch (pl->typ)
						{
						case Knight:
							pl->hp -= (bo->atk / 3);
							pl->interval[shotinterval] += 10;
							pl->act = kguard;
							break;
						case Monk:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = mguard;
							break;
						case Sniper:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = sguard;
							break;
						}
					}
					pl->cnt = 0;
					if (pl->hp <= 0) {
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = die;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = badie;
							break;
						case Knight:
							pl->act = kdie;
							break;
						}
						pl->die = true;
						pl->cnt = 0;
					}
					PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
				}
			}
			//次元からくる手の攻撃判定
			if (bsh->cnt > 64 && bsh->cnt < 88)
			{
				if (HitCheck((bsh->dx + 30), bo->y + 10, pl->x, pl->y))
				{
					if (pl->act != kseald && pl->act != mseald && pl->act != sseald)
					{
						pl->hp -= bo->atk;
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = hit;
							break;
						case Assassin:
							pl->act = ahit;
							break;
						case Monk:
							pl->act = mhit;
							break;
						case Sniper:
							pl->act = shit;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = bahit;
							break;
						case Knight:
							pl->act = khit;
							break;
						}
					}
					else {
						switch (pl->typ)
						{
						case Knight:
							pl->hp -= (bo->atk / 3);
							pl->interval[shotinterval] += 10;
							pl->act = kguard;
							break;
						case Monk:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = mguard;
							break;
						case Sniper:
							pl->hp -= (bo->atk / 2);
							pl->cnt = 0;
							pl->act = sguard;
							break;
						}
					}
					pl->cnt = 0;
					if (pl->hp <= 0) {
						switch (pl->typ)
						{
						case Valkyrie:
							pl->act = die;
							break;
						case Banbit1:
						case Banbit2:
							pl->act = badie;
							break;
						case Knight:
							pl->act = kdie;
							break;
						}
						pl->die = true;
						pl->cnt = 0;
					}
					PlaySoundA("素材/効果音/効果音2.wav", NULL, SND_ASYNC | SND_FILENAME);
				}
			}
		}
	}
	
	//死亡アニメーション
	if (bo->die)
	{
		if (bo->cnt > 96)InitBoss(bo);
	}

	//AIが動くまでのタイマー
	bo->interval[jumpinterval]--;

	//攻撃を食らってから次の攻撃を食らうまでの無敵時間
	if (bo->act == hit || bo->interval[hitinterval] < 50)bo->interval[hitinterval]--;
	if (bo->interval[hitinterval] < 0)bo->interval[hitinterval] = 50;

}

//Bossのアニメーション
void AnimationBoss(Chara* bo, Chara* bsh)
{
	switch (bo->act)
	{
	case bwork:
		if (bo->cnt >= 64) { bo->act = bidle; bo->cnt = 0; }
		bo->cnt++;
		if (bo->dir == Right) { bo->dx -= 4; bo->x -= 4; }
		else { bo->dx += 4; bo->x += 4; }
		break;
	case batack1:
		if (bo->cnt >= 80) { bo->act = bidle; bo->cnt = 0; }
		bo->cnt++;
		break;
	case batack2:
		if (bo->cnt >= 72) { bo->act = bidle; bo->cnt = 0; }
		bo->cnt++;
		break;
	case bdie:
		bo->cnt++;
		break;
	case bidle:
		if (bo->cnt >= 64) {
			bo->cnt = 0;
			if (bo->interval[jumpinterval] <= 0) bo->interval[jumpinterval] = 30;
		}
		bo->cnt++;
		break;
	case hit:
		if (bo->cnt >= 30) { bo->cnt = 0; bo->act = batack1; bo->atk = 30; }
		bo->cnt++;
		break;
	}
	if (bsh->act == batack2)
	{
		if (bsh->cnt >= 128) { bsh->act = bidle; bsh->cnt = 0; }
		bsh->cnt++;
	}
}

//Bossの描画
void BossDraw(Chara* bo, Chara* bsh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hShot)
{
	if (bo->act == hit)
	{
		if (bo->dir == Left)
			TBltBoss(hdc, hMemDC, &hChar[BOSS], bo->dx, bo->y,
				BOSS_REVERS_X,
				BOSS_Y_SIZE * 3
			);
		else if (bo->dir == Right)
			TBltBoss(hdc, hMemDC, &hChar[BOSS], bo->dx, bo->y,
				0,
				BOSS_REVERS_Y + (BOSS_Y_SIZE * 3)
			);
	}
	else
	{
		if (bo->dir == Left)
			TBltBoss(hdc, hMemDC, &hChar[BOSS], bo->dx, bo->y,
				BOSS_REVERS_X - (BOSS_X_SIZE * (int)(bo->cnt / 8)),
				BOSS_Y_SIZE * ((int)bo->act - (int)Action::bidle)
			);
		else if (bo->dir == Right)
			TBltBoss(hdc, hMemDC, &hChar[BOSS], bo->dx, bo->y,
				BOSS_X_SIZE * (bo->cnt / 8),
				BOSS_REVERS_Y + (BOSS_Y_SIZE * ((int)bo->act - (int)Action::bidle))
			);
	}
	if (bsh->act == batack2)
		TBltBoss(hdc, hMemDC, &hShot[enemyatack], bsh->dx, bsh->y,
			BOSS_X_SIZE * (bsh->cnt / 8), 0);

}

#pragma endregion

#pragma region RIVAL関係

//敵女騎士
void ValkyrieAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL;

	if (!ri->die && ri->act != hit && ri->act != ult && aiinterval>=AIINTERVAL) {
		int actAi = rand() % 4;
		switch (actAi)
		{
		case 0:
			if (pl->y == ri->y) {
			ri->act = attack1;
			if (KIntervalva >= 15) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = idle; sh[i].atk = 8;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;
						break;
					}
				}
			}
		}
			break;
		case 1:
			if (pl->y < ri->y)
		{
			ri->act = attack2;
			if (KIntervalva >= 15) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 5;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;  break;
					}
				}
			}
		}
			break;
		case 2:
			if (pl->y > ri->y)
		{
			ri->act = skill;
			if (KIntervalva >= 30) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = skill; sh[i].atk = 12;
						sh[i].x = ri->x; sh[i].y = (ri->y - 70); sh[i].die = true; break;
					}
				}
			}
		}
			break;
		case 3:
			if (ri->interval[shotinterval] >= 220)
		{
			if (ri->interval[shotinterval] >= 220)
			{
				ri->act = ult;
				ri->interval[shotinterval] = 0;
				ri->cnt = 0;
				PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						if (ri->dir == Right) {
							sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50;
							sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
							break;
						}
						else {
							sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50;
							sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
							break;
						}
					}
				}
			}
		}
			break;
		}
		int moveAi = rand() % 4;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
				if (ri->dir == Right)
				{
					if (ri->act != roll)
					{
						if (ri->y == 450)ri->act = work;
						if (ri->act == work)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 2;
						}
						else
						{
							if (ri->x < (WND_W - 32))
								ri->x += 4;
						}
					}
				}
				break;
			case 1:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != roll) {
						if (ri->y == 450)ri->act = work;
						if (ri->act == work)
						{
							if (ri->x > 0)
								ri->x -= 2;
						}
						else
						{
							if (ri->x > 0)
								ri->x -= 4;
						}
					}
				}
				break;
			case 2:
				if (pl->y < ri->y)
				{
					if (jKeyIntervalva >= 20) {
						if (ri->interval[jumpinterval] > 0) {
							ri->interval[jumpinterval] -= 26;
							ri->act = jumpup;
						}
						ri->cnt = 0;
						jKeyIntervalva = 0;
					}
				}
				break;
			case 3:
				if ((pl->x - ri->x) >= 50 || -50 >= (pl->x - ri->x))
				{
					if (ri->interval[rollinterval] <= 0)
					{
						ri->interval[rollinterval] = 30;
						if (ri->dir == Right)ri->dir = Left;
						else ri->dir = Left;
						ri->act = roll;
						ri->cnt = 0;
					}
				}
				break;
			}
		}
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 51)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵暗殺者
void AssassinAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL;

	if (!ri->die && ri->act != ahit && ri->act != ult && aiinterval >= AIINTERVAL) {
		int actAi = rand() % 4;
		switch (actAi)
		{
		case 0:
			if (pl->y == ri->y) {
				ri->act = aattack1;
				if (KIntervalva >= 20) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = idle; sh[i].atk = 5; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;
							break;
						}
					}
				}
			}
			break;
		case 1:
			if (pl->y > ri->y)
			{
				ri->act = aattack2;
				if (KIntervalva >= 15) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 3; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;  break;
						}
					}
				}
			}
			break;
		case 2:
			ri->act = aattack3;
			if (KIntervalva >= 20) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = skill; sh[i].atk = 7; sh[i].typ = ri->typ;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true; break;
					}
				}
			}
			break;
		case 3:
			if (ri->interval[shotinterval] >= 220)
			{
				if (ri->interval[shotinterval] >= 220)
				{
					ri->act = ult;
					ri->interval[shotinterval] = 0;
					ri->cnt = 0;
					PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							if (ri->dir == Right) {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
							else {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		int moveAi = rand() % 5;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
			case 3:
				if (ri->dir == Right)
				{
					if (ri->act != roll)
					{
						if (ri->y == 450)ri->act = arun;
						if (ri->act == arun)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 4;
						}
						else
						{
							if (ri->x < (WND_W - 82))
								ri->x += 50;
						}
					}
				}
				break;
			case 1:
			case 4:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != roll) {
						if (ri->y == 450)ri->act = arun;
						if (ri->act == arun)
						{
							if (ri->x > 0)
								ri->x -= 4;
						}
						else
						{
							if (ri->x > 50)
								ri->x -= 50;
						}
					}
				}
				break;
			case 2:
				if (jKeyIntervalva >= 20) {
					if (ri->interval[jumpinterval] > 0) {
						ri->interval[jumpinterval] -= 26;
						ri->act = ajump;
					}
					ri->cnt = 0;
					jKeyIntervalva = 0;
				}
				break;
			
			}
		}
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 51)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵僧侶
void MonkAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL;

	if (!ri->die && ri->act != mhit && ri->act != ult && aiinterval >= AIINTERVAL && ri->act != mseald && ri->act != mguard) {
		int actAi = rand() % 4;
		switch (actAi)
		{
		case 0:
			ri->act = mattack1;
			if (KIntervalva >= 30) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = idle; sh[i].atk = 8; sh[i].typ = ri->typ;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;
						break;
					}
				}
			}
			break;
		case 1:
			if (pl->y < ri->y && pl->x - ri->x >= 50&& pl->x - ri->x <= -50)
			{
				ri->act = mattack2;
				if (KIntervalva >= 15) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 3; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;  break;
						}
					}
				}
			}
			break;
		case 2:
			if (ri->y == 450 && ri->y - pl->y <= 50 && ri->y - pl->y >= 150)ri->act = mattack3;
			else if (ri->y != 450 && ri->y < pl->y)ri->act = mjumpattack;
			if (KIntervalva >= 50) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					int max = 3;
					if (!sh[i].die) {
						if (ri->act != mjumpattack) {
							sh[i].dir = ri->dir; sh[i].act = skill; sh[i].atk = 10;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true; sh[i].typ = ri->typ; break;
						}
						else
						{
							sh[i].dir = ri->dir; sh[i].act = hit; sh[i].atk = 10; max--;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true; sh[i].typ = ri->typ;
							if (max <= 0)break;
						}
					}
				}
			}
			break;
		case 3:
			if (ri->interval[shotinterval] >= 220)
			{
				if (ri->interval[shotinterval] >= 220)
				{
					ri->act = ult;
					ri->interval[shotinterval] = 0;
					ri->cnt = 0;
					PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							if (ri->dir == Right) {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
							else {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		int moveAi = rand() % 5;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
				if (ri->dir == Right)
				{
					if (ri->act != roll)
					{
						if (ri->y == 450)ri->act = mrun;
						if (ri->act == mrun)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 2;
						}
						else
						{
							if (ri->x < (WND_W - 32))
								ri->x += 8;
						}
					}
				}
				break;
			case 1:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != roll) {
						if (ri->y == 450)ri->act = mrun;
						if (ri->act == mrun)
						{
							if (ri->x > 0)
								ri->x -= 2;
						}
						else
						{
							if (ri->x > 4)
								ri->x -= 8;
						}
					}
				}
				break;
			case 2:
				if (jKeyIntervalva >= 20) {
					if (ri->interval[jumpinterval] > 0) {
						ri->interval[jumpinterval] -= 26;
						ri->act = mjumpup;
					}
					ri->cnt = 0;
					jKeyIntervalva = 0;
				}
				break;
			case 3:
			case 4:
				ri->act = mseald;
				break;
			}
			if (ri->dir == Left) {
				if (ri->act == mrun)
				{
					if (ri->x > 0)
						ri->x -= 12;
				}
				else if (ri->act == mjumpup || ri->act == mjumpdown)
				{
					if (ri->x > 0)
						ri->x -= 8;
				}
			}	
			if (ri->dir == Right) {
				if (ri->act == mrun)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 12;
				}
				else if (ri->act == mjumpup || ri->act == mjumpdown)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 8;
				}
			}
		}
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 51)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵狙撃手
void SniperAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL;

	if (!ri->die && ri->act != shit && ri->act != ult && aiinterval >= AIINTERVAL && ri->act !=sguard &&ri->act != sseald)
	{
		int actAi = rand() % 3;
		switch (actAi)
		{
		case 0:
			if (pl->y == ri->y) {
				ri->act = sattack1;
				if (KIntervalva >= 11) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = idle; sh[i].atk = 40;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true; sh[i].typ = ri->typ;
							break;
						}
					}
				}
			}
			break;
		case 1:
			if (pl->y < ri->y)
			{
				ri->act = sattack2;
				if (KIntervalva >= 11) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 15; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;  break;
						}
					}
				}
			}
			break;
		case 2:
			if (ri->interval[shotinterval] >= 220)
			{
				if (ri->interval[shotinterval] >= 220)
				{
					ri->act = ult;
					ri->interval[shotinterval] = 0;
					ri->cnt = 0;
					PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							if (ri->dir == Right) {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
							else {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		int moveAi = rand() % 4;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
				if (ri->dir == Right)
				{
					if (ri->act != roll)
					{
						if (ri->y == 450)ri->act = srun;
						if (ri->act == srun)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 6;
						}
						if (pl->x - ri->x < 50)
							ri->x = WND_W-32;
					}
				}
				break;
			case 1:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != roll) {
						if (ri->y == 450)ri->act = srun;
						if (ri->act == srun)
						{
							if (ri->x > 0)
								ri->x -= 6;
						}
						if (ri->x - pl->x < 50)
							ri->x = 0;
					}
				}
				break;
			case 2:
				if (pl->y < ri->y)
				{
					if (jKeyIntervalva >= 20) {
						if (ri->interval[jumpinterval] > 0) {
							ri->interval[jumpinterval] -= 26;
							ri->act = sjumpup;
						}
						ri->cnt = 0;
						jKeyIntervalva = 0;
					}
				}
				break;
			case 3:
				ri->act = sseald;
				break;
			}
		}
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 30)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵野盗
void BanbitAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL; static int RespawnMax = 1;

	if (!ri->die && ri->act != bahit && ri->act != ult && aiinterval >= AIINTERVAL) {
		int actAi = rand() % 2;
		switch (actAi)
		{
		case 0:
			ri->act = baattack;
			if (KIntervalva >= 30) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					int max = 3;
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 10; max--;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true; sh[i].typ = ri->typ;
						if (max <= 0)break;
					}
				}
			}
			break;
		case 1:
			if (ri->interval[shotinterval] >= 220)
			{
				if (ri->interval[shotinterval] >= 220)
				{
					ri->act = ult;
					ri->interval[shotinterval] = 0;
					ri->cnt = 0;
					PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							if (ri->dir == Right) {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
							else {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		int moveAi = rand() % 2;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
				if (ri->dir == Right)
				{
					if (ri->act != roll)
					{
						if (ri->y == 450)ri->act = barun;
						if (ri->act == barun)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 2;
						}
						else
						{
							if (ri->x < (WND_W - 32))
								ri->x += 4;
						}
					}
				}
				break;
			case 1:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != roll) {
						if (ri->y == 450)ri->act = barun;
						if (ri->act == barun)
						{
							if (ri->x > 0)
								ri->x -= 2;
						}
						else
						{
							if (ri->x > 0)
								ri->x -= 4;
						}
					}
				}
				break;
			}
			if (ri->dir == Left) {
				if (ri->act == barun)
				{
					if (ri->x > 0)
						ri->x -= 12;
				}
				else if (ri->act == mjumpup || ri->act == mjumpdown)
				{
					if (ri->x > 0)
						ri->x -= 8;
				}
			}
			if (ri->dir == Right) {
				if (ri->act == barun)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 12;
				}
				else if (ri->act == mjumpup || ri->act == mjumpdown)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 8;
				}
			}
		}
	}
	if (ri->die && RespawnMax > 0 && ri->cnt >= 25 &&ri->typ == Banbit1)
	{
		RespawnMax--;
		ri->die = false;
		ri->hp = 150;
		ri->cnt = 0;
		ri->act = barespawn;
	}
	else if (ri->die)
	{
		ri->act = badie;
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 51)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵騎士
void KnightAI(Chara* ri, Chara* sh, Chara* pl)
{
	static int KIntervalva = 0;
	static int jKeyIntervalva = 20;
	static int aiinterval = AIINTERVAL;

	if (!ri->die && ri->act != khit && ri->act != ult && aiinterval >= AIINTERVAL && ri->act != kguard && ri->act != kseald) 
	{
		int actAi = rand() % 4;
		switch (actAi)
		{
		case 0:
			ri->act = kattack1;
			if (KIntervalva >= 15) {
				KIntervalva = 0;
				PlaySoundA("素材/効果音/効果音11.wav", NULL, SND_ASYNC | SND_FILENAME);
				for (int i = 0; i < SHOT_MAX; i++)
				{
					if (!sh[i].die) {
						sh[i].dir = ri->dir; sh[i].act = idle; sh[i].atk = 8; sh[i].typ = ri->typ;
						sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;
						break;
					}
				}
			}
			break;
		case 1:
			if (pl->y < ri->y)
			{
				ri->act = kattack2;
				if (KIntervalva >= 15) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音12.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = roll; sh[i].atk = 5; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = ri->y; sh[i].die = true;  break;
						}
					}
				}
			}
			break;
		case 2:
			if (pl->y > ri->y)
			{
				ri->act = kattack3;
				if (KIntervalva >= 15) {
					KIntervalva = 0;
					PlaySoundA("素材/効果音/効果音14.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							sh[i].dir = ri->dir; sh[i].act = skill; sh[i].atk = 10; sh[i].typ = ri->typ;
							sh[i].x = ri->x; sh[i].y = (ri->y - 70); sh[i].die = true; break;
						}
					}
				}
			}
			break;
		case 3:
			if (ri->interval[shotinterval] >= 220)
			{
				if (ri->interval[shotinterval] >= 220)
				{
					ri->act = ult;
					ri->interval[shotinterval] = 0;
					ri->cnt = 0;
					PlaySoundA("素材/効果音/Ult.wav", NULL, SND_ASYNC | SND_FILENAME);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						if (!sh[i].die) {
							if (ri->dir == Right) {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
							else {
								sh[i].dir = ri->dir; sh[i].act = ult; sh[i].atk = 50; sh[i].typ = ri->typ;
								sh[i].x = ri->x - 100; sh[i].y = ri->y - 90; sh[i].die = true;
								break;
							}
						}
					}
				}
			}
			break;
		}
		int moveAi = rand() % 12;
		if (ri->act != ult)
		{
			switch (moveAi)
			{
			case 0:
				if (ri->dir == Right)
				{
					if (ri->act != kroll)
					{
						if (ri->y == 450)ri->act = krun;
						if (ri->act == krun)
						{
							if (ri->x < (WND_W - 32))
								ri->x += 12;
						}
						else
						{
							if (ri->x < (WND_W - 32))
								ri->x += 15;
						}
					}
				}
				break;
			case 1:
				if (ri->dir == Left)
				{
					ri->dir = Left;
					if (ri->act != kroll) {
						if (ri->y == 450)ri->act = krun;
						if (ri->act == krun)
						{
							if (ri->x > 0)
								ri->x -= 12;
						}
						else
						{
							if (ri->x > 0)
								ri->x -= 15;
						}
					}
				}
				break;
			case 2:
			case 7:
			case 8:
			case 9:
				if (jKeyIntervalva >= 20) {
					if (ri->interval[jumpinterval] > 0) {
						ri->interval[jumpinterval] -= 26;
						ri->act = kjumpup;
					}
					ri->cnt = 0;
					jKeyIntervalva = 0;
				}
				break;
			case 3:
			case 10:
			case 11:
				if ((pl->x - ri->x) >= 50 || -50 >= (pl->x - ri->x))
				{
					if (ri->interval[rollinterval] <= 0)
					{
						ri->interval[rollinterval] = 30;
						if (ri->dir == Right)ri->dir = Left;
						else ri->dir = Left;
						ri->act = kroll;
						ri->cnt = 0;
					}
				}
				break;
			case 4:
			case 5:
			case 6:
				if (ri->act != krun) {
					ri->act = kseald; ri->cnt = 0;
					if (KIntervalva >= 50) {
						KIntervalva = 0;
					}
				}
				break;
			}
			if (ri->dir == Left) {
				if (ri->act == krun)
				{
					if (ri->x > 0)
						ri->x -= 12;
				}
				else if (ri->act == kjumpup || ri->act == kjumpdown)
				{
					if (ri->x > 0)
						ri->x -= 8;
				}
			}
			if (ri->dir == Right) {
				if (ri->act == krun)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 12;
				}
				else if (ri->act == kjumpup || ri->act == kjumpdown)
				{
					if (ri->x < (WND_W - 32))
						ri->x += 8;
				}
			}
		}
	}
	aiinterval--;
	if (aiinterval <= 0)aiinterval = AIINTERVAL;
	if (KIntervalva < 51)KIntervalva++;
	if (jKeyIntervalva < 21)jKeyIntervalva++;
}

//敵のinterval処理
void CheckIntervalRaival(Chara* ri)
{
	if (ri->y == 450)ri->interval[jumpinterval] += 2;
	if (ri->interval[jumpinterval] > 100)ri->interval[jumpinterval] = 100;
	if (ri->act == hit || ri->interval[hitinterval] != 70
		||ri->act == ahit|| ri->act == shit|| ri->act == mhit||
		ri->act == bahit|| ri->act == khit)
		ri->interval[hitinterval]--;
	if (ri->interval[shotinterval] > 220)ri->interval[shotinterval] = 220;
	if (ri->interval[rollinterval] > 0)ri->interval[rollinterval]--;
	//ULT使い放題プラン
	//if (pl->interval[shotinterval] < 220)pl->interval[shotinterval] +=15;
}

//ライバルの動きの処理
void RaivalExecute(Chara* ri, Chara* sh ,Chara* pl)
{
	//タイプ別AI
	switch (ri->typ)
	{
	case Valkyrie:
		ValkyrieAI(ri,sh,pl);
		break;
	case Assassin:
		AssassinAI(ri, sh, pl);
		break;
	case Monk:
		MonkAI(ri,sh,pl);
		break;
	case Sniper:
		SniperAI(ri,sh,pl);
		break;
	case Banbit1:
		BanbitAI(ri,sh,pl);
		break;
	case Banbit2:
		BanbitAI(ri,sh,pl);
		break;
	case Knight:
		KnightAI(ri,sh,pl);
		break;
	}

	//インターバル処理
	CheckIntervalRaival(ri);
}

//WinningにおけるHitCheck
void WinningModeHitCheck(Chara* sh, Chara* pl1, Chara* pl2)
{
	for (int i = 0; i < SHOT_MAX; i++)
	{
		if (pl1->act != barespawn && pl1->act != kroll && pl1->act != khit && pl1->act != ult &&
			pl1->act != ahit && pl1->act != mhit && pl1->act != shit && pl1->act != bahit &&
			pl1->act != mguard && pl1->act != sguard && pl1->act != kguard && pl1->act != roll &&
			pl1->act != hit &&pl1->die != true)
		{
			if (pl1->interval[hitinterval] == 50 || pl1->interval[hitinterval] == 70) {

				if (!pl1->die && sh[i].die)
				{
					if (sh[i].act != ult)
					{
						if (HitCheck(sh[i].x + 16, sh[i].y + 16, pl1->x + 16, pl1->y + 16))
						{
							if (pl1->act != kseald && pl1->act != mseald && pl1->act != sseald)
							{
								pl1->hp -= sh[i].atk;
								switch (pl1->typ)
								{
								case Valkyrie:
									pl1->act = hit;
									break;
								case Assassin:
									pl1->act = ahit;
									break;
								case Monk:
									pl1->act = mhit;
									break;
								case Sniper:
									pl1->act = shit;
									break;
								case Banbit1:
								case Banbit2:
									pl1->act = bahit;
									break;
								case Knight:
									pl1->act = khit;
									break;
								}
							}
							else {
								switch (pl1->typ)
								{
								case Knight:
									pl1->hp -= (sh[i].atk / 3);
									pl1->interval[shotinterval] += 10;
									pl1->act = kguard;
									break;
								case Monk:
									pl1->hp -= (sh[i].atk / 2);
									pl1->cnt = 0;
									pl1->act = mguard;
									break;
								case Sniper:
									pl1->hp -= (sh[i].atk / 2);
									pl1->cnt = 0;
									pl1->act = sguard;
									break;
								}
							}
							pl1->cnt = 0;
							if (pl1->hp < 0) {
								switch (pl1->typ)
								{
								case Valkyrie:
									pl1->act = die;
									break;
								case Banbit1:
								case Banbit2:
									pl1->act = badie;
									break;
								case Knight:
									pl1->act = kdie;
									break;
								}
								pl1->die = true;
								pl1->cnt = 0;
							}
							else PlaySoundA("素材/効果音/効果音7.wav", NULL, SND_ASYNC | SND_FILENAME);
							switch (sh[i].act)
							{
							case skill:
								pl2->interval[shotinterval] += 20;
								break;
							default:
								pl2->interval[shotinterval] += 15;
								InitShot(&sh[i]);
								break;
							}
						}
					}
					else
					{
						if (HitCheckUlt(sh[i].x, sh[i].y,
							sh[i].x + ((SHOT_X_SIZE + SHOT_X_SIZE) + (sh[i].cnt * 2)),
							sh[i].y + ((SHOT_Y_SIZE + 64) + (sh[i].cnt * 2)),
							pl1->x, pl1->y,
							pl1->x + 64,
							pl1->y + 64))
						{
							if (pl1->act != kseald && pl1->act != mseald && pl1->act != sseald)
							{
								pl1->hp -= sh[i].atk;
								switch (pl1->typ)
								{
								case Valkyrie:
									pl1->act = hit;
									break;
								case Assassin:
									pl1->act = ahit;
									break;
								case Monk:
									pl1->act = mhit;
									break;
								case Sniper:
									pl1->act = shit;
									break;
								case Banbit1:
								case Banbit2:
									pl1->act = bahit;
									break;
								case Knight:
									pl1->act = khit;
									break;
								}
							}
							else {
								switch (pl1->typ)
								{
								case Knight:
									pl1->hp -= (sh[i].atk / 3);
									pl1->interval[shotinterval] += 10;
									pl1->act = kguard;
									break;
								case Monk:
									pl1->hp -= (sh[i].atk / 2);
									pl1->cnt = 0;
									pl1->act = mguard;
									break;
								case Sniper:
									pl1->hp -= (sh[i].atk / 2);
									pl1->cnt = 0;
									pl1->act = sguard;
									break;
								}
							}
							pl1->cnt = 0;
							if (pl1->hp < 0) {
								switch (pl1->typ)
								{
								case Valkyrie:
									pl1->act = die;
									break;
								case Banbit1:
								case Banbit2:
									pl1->act = badie;
									break;
								case Knight:
									pl1->act = kdie;
									break;
								}
								pl1->die = true;
								pl1->cnt = 0;
							}
							else PlaySoundA("素材/効果音/効果音7.wav", NULL, SND_ASYNC | SND_FILENAME);
							if (pl1->hp < 0)
							{
								PlaySoundA("素材/効果音/効果音15.wav", NULL, SND_ASYNC | SND_FILENAME);
								pl1->act = bdie;
								pl1->die = true;
							}
						}
					}
				}
			}
		}
	}
}

#pragma endregion

//当たり判定の計算
bool HitCheck(int ax, int ay, int dx, int dy)
{
	double a, b, c, r1, r2;
	a = (double)dy - (double)ay;
	b = (double)dx - (double)ax;
	c = sqrt(a * a + b * b);
	r1 = 30 / 2;
	r2 = 30 / 2;
	if (c <= r1 + r2)
	{
		return true;
	}
	return false;
}
bool HitCheckB(int ax, int ay, int dx, int dy, int rdian)
{
	double a, b, c, r1, r2;
	a = (double)dy - (double)ay;
	b = (double)dx - (double)ax;
	c = sqrt(a * a + b * b);
	r1 = 64 / 2;
	r2 = rdian / 2;
	if (c <= r1 + r2)
	{
		return true;
	}
	return false;
}
bool HitCheckUlt(int ax, int ay,int sizex,int sizey, int dx, int dy, int sizedx,int sizedy)
{
	//当たり判定のif文を書くところ
	if (dx <= sizex && ax <= dx && dy <= sizey && ay <= dy)
	{
		return true;
	}
	else if (sizedx <= sizex && ax <= sizedx && dy <= sizey && ay <= dy)
	{
			return true;
	}	
	return false;
}
#pragma endregion

#pragma region ウイニングモード

//勝ち抜き戦モード処理
void WinningExecute(Chara* pl, Chara* sh, Chara* ri, Chara* rsh, int* scene ,int NowChara,HDC hdc, HDC hMemDC, HBITMAP* hBack,bool* CharaF)
{
	static int RivalChara = Valkyrie; static bool RaivalChenge = false;
	static int StartTimer = 0;
	if (StartTimer >= 100) {
		if (pl->x < ri->x) ri->dir = Left;
		else ri->dir = Right;
		PlayerExecute(pl, sh);

		//死亡処理
		if (pl->hp < 0)pl->die = true;
		if (ri->hp < 0)ri->die = true;
		if (pl->die) {
			switch (pl->typ)
			{
			case Banbit1:
			case Banbit2:
				if (pl->cnt > 28) {
					*scene = GameOver;
				}
				pl->cnt++;
				break;
			default:
				if (pl->cnt > 22) {
					*scene = GameOver;
				}
				pl->cnt++;
				break;
			}
		}
		if (ri->die)
		{
			switch (RivalChara)
			{
			case Assassin:
				ri->act = adie;
				break;
			case Monk:
				ri->act = mdie;
				break;
			case Sniper:
				ri->act = sdie;
				break;
			default:
				break;
			}
			if (RivalChara == typemax)
			{
				if (ri->cnt > 22) {
					*scene = WinningResult;
				}
				ri->cnt++;
			}
			else
			{

				if (ri->cnt > 140)
				{
					InitPlayer(pl, NowChara);
					InitRival(ri, RivalChara);
					for (int i = 0; i < SHOT_MAX; i++)
					{
						InitShot(&sh[i]);
					}
					for (int i = 0; i < ENEMY_SHOT_MAX; i++)
					{
						InitShot(&rsh[i]);
					}
					StartTimer = 0;
					RaivalChenge = false;
				}
				if (!RaivalChenge) {
					CharaF[RivalChara] = true;
					RivalChara++;
					RaivalChenge = true;
				}
				ri->cnt++;
				if(ri->cnt == 35)PlaySoundA("素材/効果音/KO.wav", NULL, SND_ASYNC | SND_FILENAME);
				if(ri->cnt > 30 &&81 > ri->cnt)AlphaBltResult(hdc, hMemDC, &hBack[blackwhite], (ri->cnt - 30) * 5, 600);
				if(ri->cnt>80)AlphaBltResult(hdc, hMemDC, &hBack[blackwhite],255, 600);
				TBltEnd(hdc, hMemDC, &hBack[KO], 0);
			}
		}
		RaivalExecute(ri, rsh, pl);

		PlayerShotExecute(sh, SHOT_MAX);

		PlayerShotExecute(rsh, ENEMY_SHOT_MAX);

		WinningModeHitCheck(sh, ri, pl);
		WinningModeHitCheck(rsh, pl, ri);

		AnimationMainChara(pl);
		AnimationMainChara(ri);

		if (pl->interval[hitinterval] <= 0)pl->interval[hitinterval] = 50;
		if (ri->interval[hitinterval] <= 0)ri->interval[hitinterval] = 70;
	}
	if (StartTimer < 100) {
		StartTimer++;
		if(StartTimer == 85)PlaySoundA("素材/効果音/Start.wav", NULL, SND_ASYNC | SND_FILENAME);
		if(StartTimer>20)TBltEnd(hdc, hMemDC, &hBack[Start], 0);
	}
	if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		RivalChara = Valkyrie; RaivalChenge = false; StartTimer = 0;
		PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
		*scene = Title;
	}
	if(*scene != Winning){ RivalChara = Valkyrie; RaivalChenge = false; StartTimer = 0; }
}

//勝ち抜き戦の時の描画
void WinningDraw(Chara* pl, Chara* sh, Chara* ri, Chara* rsh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hBack, HBITMAP* hShot)
{
	BBlt(hdc, hMemDC, hBack[Haikei2], (pl->x * -1));
	//球描画
	PlayerShotDraw(sh, hdc, hMemDC, hShot);
	//Player描画
	PlayerDraw(pl, hdc, hMemDC, hChar);
	//球描画
	PlayerShotDraw(rsh, hdc, hMemDC, hShot);
	//Player描画
	PlayerDraw(ri, hdc, hMemDC, hChar);

	TBltMap(hdc, hMemDC, &hBack[Zenmen2], (pl->x * -1));
}

//プレイヤーと敵のUI
void WinningUI(Chara* pl, Chara* ri, HDC hdc, HDC hMemDC, HBITMAP* hUi)
{
	if(pl->interval[hitinterval] == 50)
		TBltUI11(hdc, hMemDC, &hUi[ui16], pl->x+5, pl->y - 50, 0);
	else TBltUI11(hdc, hMemDC, &hUi[ui16], pl->x + 5, pl->y - 50, 450 * (pl->interval[hitinterval] % 2));
	if(ri->interval[hitinterval]==70)
		TBltUI11(hdc, hMemDC, &hUi[ui16], ri->x+10, ri->y - 50, 150);
	else TBltUI11(hdc, hMemDC, &hUi[ui16], ri->x + 10, ri->y - 50, 150 * (1 + ri->interval[hitinterval] % 2));
	TBltUI12(hdc, hMemDC, &hUi[ui17], 0, 0);
	TBltUI12(hdc, hMemDC, &hUi[ui17], 350 - ri->hp, 3);
}
#pragma endregion

#pragma region ウイニング結果

//リザルト中の描画処理
void WinningResultDraw(HDC hdc, HDC hMemDC, HBITMAP* hUi, HBITMAP* hStage, int* rank, int nowrank)
{
	bool rankincheck = false; int tmp = 0;
	BBltT(hdc, hMemDC, hStage[titlescene], 0);
	AlphaBltResult(hdc, hMemDC, &hStage[blackwhite], 150, 600);
	for (int i = 0; i < 5; i++)
	{
		if ((nowrank - 1) == i) {
			TBltUI3(hdc, hMemDC, &hUi[uispace], 185, 25 + (i * 100), 0, 0);
			rankincheck = true;
			tmp = i;
		}
		TBltUI5(hdc, hMemDC, &hUi[ui11], 200, 50 + (i * 100), 0, 0, rank);
		if (i >= 0 && i < 3)TBlt2(hdc, hMemDC, &hUi[uOkan], 100, 45 + (i * 100), 488 * i, 0, 488, 273);
		rank++;
	}
	if (rankincheck)TBltUI6(hdc, hMemDC, &hUi[urank], 600, 10 + (tmp * 100), 0, 0);
}

#pragma endregion

#pragma region キャラクターセレクト

//キャラクター選択中の進行
void CharaSelectExecute(int* Scene, int* SelChara, int* interval,bool* CharaF,int* NowChara)
{
	//キー入力
	if (*interval <= 0) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			if (CharaF[*SelChara]) { 
				*NowChara = *SelChara;
				PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
			}
			else
			{

			}
			*interval = 30;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			if (*SelChara < (int)Type::Knight)*SelChara += 1;
			PlaySoundA("素材/効果音/効果音6.wav", NULL, SND_ASYNC | SND_FILENAME);
			if (*SelChara > (int)Type::typemax)*SelChara = Type::typemax - 1;
			*interval = 30;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			*SelChara -= 1;
			PlaySoundA("素材/効果音/効果音6.wav", NULL, SND_ASYNC | SND_FILENAME);
			if (*SelChara < 0)*SelChara = 0;
			*interval = 30;
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			PlaySoundA("素材/効果音/効果音3.wav", NULL, SND_ASYNC | SND_FILENAME);
			*Scene = Title;
			*interval = 30;
		}
	}
	if (*interval > -1)*interval -= 1;
}

//キャラクター選択中の描画
void CharaSelectDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hChar, int* SelChara,bool*CharaF,int* NowChara)
{
	if (CharaF[*SelChara])
	{
		BBltTU(hdc, hMemDC, hStage[CharaSelHaikei], *SelChara * 800);
		switch (*SelChara)
		{
		case Valkyrie:
			TBltCS(hdc, hMemDC, &hChar[VALKYRIE], 290, 150,0,0,VALKYRIE_SIZE);
			break;
		case Assassin:
			TBltCS(hdc, hMemDC, &hChar[ASSASSIN], 290, 150,0,0,ASSASSIN_SIZE);
			break;
		case Monk:
			TBltCS(hdc, hMemDC, &hChar[MONK], 290, 150,0,0,MONK_SIZE);
			break;
		case Sniper:
			TBltCS(hdc, hMemDC, &hChar[SNIPER], 290, 150,0,0,SNIPER_SIZE);
			break;
		case Banbit1:
			TBltCS(hdc, hMemDC, &hChar[BANBIT1], 290, 150,0,0,BANBIT_SIZE);
			break;
		case Banbit2:
			TBltCS(hdc, hMemDC, &hChar[BANBIT2], 290, 150,0,0,BANBIT_SIZE);
			break;
		case Knight:
			TBltCS(hdc, hMemDC, &hChar[KNIGHT], 290, 150,0,0,KNIGHT_SIZE);
			break;
		}
		if (*SelChara == *NowChara)
		{
			SelectObject(hMemDC, hStage[NowSelect]);
			TransparentBlt(hdc, 360, 130, 80, 80, hMemDC, 0, 0, 640, 640, TRANSPARENT_COLOR);
		}
	}
	else BBltTU(hdc, hMemDC, hStage[NotChara], 0);
	TBltUI13(hdc, hMemDC, &hStage[Esc]);
}

#pragma endregion

#pragma region ウォリアー結果

//リザルト中の入力処理
void ResultExecute(int* interval, int* Scene)
{
	if (*interval <= 0) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			*Scene = Ending;
			PlaySoundA("素材/効果音/効果音4.wav", NULL, SND_ASYNC | SND_FILENAME);
			*interval = 30;
		}
	}
	if (*interval > -1)*interval -= 1;
}

//リザルト中の描画処理
void ResultDraw(HDC hdc, HDC hMemDC, HBITMAP* hUi, HBITMAP* hStage, int* rank, int nowrank)
{
	bool rankincheck = false; int tmp = 0;
	BBltT(hdc, hMemDC, hStage[titlescene], 0);
	AlphaBltResult(hdc, hMemDC, &hStage[blackwhite], 150, 600);
	for (int i = 0; i < 5; i++)
	{
		if ((nowrank - 1) == i) {
			TBltUI3(hdc, hMemDC, &hUi[uispace], 185, 25 + (i * 100), 0, 0);
			rankincheck = true;
			tmp = i;
		}
		TBltUI5(hdc, hMemDC, &hUi[ui10], 200, 50 + (i * 100), 0, 0, rank);
		if (i >= 0 && i < 3)TBlt2(hdc, hMemDC, &hUi[uOkan], 100, 45 + (i * 100), 488 * i, 0, 488, 273);
		rank++;
	}
	if (rankincheck)TBltUI6(hdc, hMemDC, &hUi[urank], 600, 10 + (tmp * 100), 0, 0);
}

#pragma endregion

#pragma region エンディング

//エンディング中の入力処理
void EndingExecute(int* interval, int* Scene)
{
	if (*interval <= 0) {
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		{
			PlaySoundA("素材/効果音/効果音4.wav", NULL, SND_ASYNC | SND_FILENAME);
			*Scene = Title;
			*interval = 30;
		}
	}
	if (*interval > -1)*interval -= 1;
}

//エンディング中の描画処理
void EndingDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, int* Scene)
{
	static int count = 0;
	BBltT(hdc, hMemDC, hStage[titlescene], 0);
	AlphaBltResult(hdc, hMemDC, &hStage[blackwhite], 75, 0);
	if (count <= 600)count++;

	if (count >= 600)
		TBltEnd(hdc, hMemDC, &hStage[endroll], 2400);
	else if (count >= 400)
		TBltEnd(hdc, hMemDC, &hStage[endroll], 1600);
	else if (count >= 200)
		TBltEnd(hdc, hMemDC, &hStage[endroll], 800);
	else
		TBltEnd(hdc, hMemDC, &hStage[endroll], 0);

	if (*Scene == Title)
	{
		count = 0;
	}
}

#pragma endregion