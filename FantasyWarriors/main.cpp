#define _CRT_SECURE_NO_WARNINGS
#include"Hub.h"
#include"Sub.h"
#include"resource.h"

HDC BuffaDC;
static int nowScene = Title;
static int backScene = nowScene;

//メインから飛ぶ処理
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)	//メッセージに対応した情報
	//変数の宣言
{
	HDC hdc;
	PAINTSTRUCT  ps;
	static GameWindow gameWnd;//ゲームウィンドウ構造体
	DWORD	dwID;	//スレッドID
	HBITMAP hBMP;	//ビットマップハンドル
	//HRESULT hRlt;	//関数復帰値

	//ここがマルチバイトの場合はwcharにする（大き目の箱を用意している）
	//メッセージ別の処理
	switch (uMsg)
	{
	case WM_CREATE:
		gameWnd.hWnd = hWnd;
		gameWnd.size.cx = WND_W;
		gameWnd.size.cy = WND_H;
		gameWnd.dwFPS = 60;

		hdc = GetDC(hWnd);
		gameWnd.hScreenDC = CreateCompatibleDC(hdc);
		hBMP = CreateCompatibleBitmap(hdc, WND_W, WND_H);
		SelectObject(gameWnd.hScreenDC, hBMP);
		ReleaseDC(hWnd, hdc);

		//初期BGM
		BGMOpen(nowScene, hWnd);
		BGMPlay(nowScene, hWnd);

		//スレッドに飛ばす
		CreateThread(NULL, 0, ThreadFunc, (LPVOID)&gameWnd, 0, &dwID);
		
		break;

	case WM_TIMER:	//何かキーを押したとき
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_PAINT:	//表示するとき（最初とWindowsが更新されたとき）
	{
		hdc = BeginPaint(hWnd, &ps);//表示開始
		BitBlt(hdc, 0, 0, WND_W, WND_H, BuffaDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
		return 0;
	case WM_DESTROY:	//Windowが終了されたとき
		//===終了処理＝＝//
		PostQuitMessage(0);
		return 0;	//Windowに戻る
	}

	//メインに返す情報
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//非同期処理
DWORD WINAPI ThreadFunc(LPVOID vdlParam)	//voidにポインタをつけるLPVOID
{
	GameWindow* gw = (GameWindow*)vdlParam;

	DWORD frame = 0,
		beforTime = timeGetTime();

	HDC hdc = CreateCompatibleDC(gw->hScreenDC);

#pragma region 変数

	int Score = 0;
	int Time = 6000;
	int WinningTime = 0;
	int SelChara = Valkyrie;
	int NowChara = Valkyrie;
	int MenuSel = 0;
	int DrowCount = 0;
	int page = 0;
	int KeyInterval = 30;
	int ranking[6] = { 0 };
	int Winningrank[6] = { 999999,999999,999999,999999,999999,999999, };
	int nowrank = 10;
	int Alpha = 180;
	bool rakingread = false;
	bool AlphaF = false;
	bool CharaF[Type::typemax] = { true,true,true,false,false,false,false };
	FILE* fp = fopen("xxx.dat", "ab");
	fclose(fp);
	fp = fopen("Chara.dat", "ab");
	fclose(fp);
	fp = fopen("Time.dat", "ab");
	fclose(fp);

#pragma endregion

//ランキング及びキャラ所得の初期化

//下記３行をコメントアウトでランキングを記録する
	
	//Warriors
	/*fp = fopen("xxx.dat", "wb");
	fwrite(&ranking, sizeof(int), 5, fp);
	fclose(fp);*/

	//Winning
	/*fp = fopen("Time.dat", "wb");
	fwrite(&Winningrank	, sizeof(int), 5, fp);
	fclose(fp);*/

	//キャラクター開放情報のリセット
	/*fp = fopen("Chara.dat", "wb");
	fwrite(&CharaF, sizeof(bool), 6, fp);
	fclose(fp);*/
	
	//キャラクター開放情報の読み込み
	fp = fopen("Chara.dat", "rb");
	fread(&CharaF, sizeof(bool), 7, fp);
	fclose(fp);

//初期処理
#pragma region キャラクター及び弾の初期化

	//キャラ
	Chara pl;
	Chara en[ENEMY_MAX];
	Chara bo;
	Chara ri;
	InitPlayer(&pl,NowChara);
	InitBoss(&bo);
	InitRival(&ri, Valkyrie);
	for (int i = 0; i < ENEMY_MAX; i++) {
		InitEnemy(&en[i]);
	}
	//弾
	Chara sh[SHOT_MAX];
	Chara esh[ENEMY_SHOT_MAX];
	Chara bsh;
	for (int i = 0; i < SHOT_MAX; i++) {
		InitShot(&sh[i]);
	}
	for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
		InitShot(&esh[i]);
	}
	InitShot(&bsh);
	
#pragma endregion 

//画像読み込み
#pragma region 画像データ

	HBITMAP hBack[ImageScrean::Max];  
	HBITMAP hChar[ImageChara::CMA];
	HBITMAP hShot[ImageShot::SImax];
	HBITMAP hUi[ImageUI::uimax];

	for (int i = 0; i < (int)ImageScrean::Max; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "素材/背景/背景";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hBack[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageChara::CMA; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "素材/キャラ/キャラ";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hChar[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageShot::SImax; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "素材/攻撃/攻撃";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hShot[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageUI::uimax; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "素材/UI/UI";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hUi[i], wStr) == false)return 0;
	}

#pragma endregion

//ダブルバッファ生成
	HBITMAP hBmp = CreateCompatibleBitmap(gw->hScreenDC, WND_W, WND_H);
	BuffaDC = CreateCompatibleDC(gw->hScreenDC);
	SelectObject(BuffaDC, hBmp);

//この中を繰り返す
	while (true)
	{
		DWORD nowTime = timeGetTime(),						//現在の時間を取得
			idealTime = (DWORD)(frame * (1000.0F / gw->dwFPS)),
			progress = nowTime - beforTime;

		if (idealTime > progress) Sleep(idealTime - progress);
		
		//シーケンス
		if (!AlphaF) {
			switch (nowScene)
			{
			case Title:
				TitleExecute(&nowScene, &MenuSel, &KeyInterval);
				TitleDraw(BuffaDC, gw->hScreenDC, hBack, hUi, &MenuSel, &DrowCount, backScene);
				break;
			case Menu:
				MenuExecute(&nowScene,&pl,sh,NowChara);
				MenuDraw(BuffaDC, gw->hScreenDC, hBack, hChar,hShot,&pl,sh);
				UiDraw(&pl, NULL, NULL, BuffaDC, gw->hScreenDC, hUi);
				break;
			case Warriors:
				WarrioersExecute(&pl, en, sh, &bo, &bsh, esh, &nowScene, &Score);
				WarrioersDraw(&pl, en, sh, &bo, &bsh, esh, BuffaDC, gw->hScreenDC, hChar, hBack, hShot);
				UiDraw(&pl, &Score, &Time, BuffaDC, gw->hScreenDC, hUi);
				Time--; if (Time < 0)nowScene = Result;
				break;
			case Result:
				ResultExecute(&KeyInterval, &nowScene);
				ResultDraw(BuffaDC, gw->hScreenDC, hUi, hBack, ranking, nowrank);
				break;
			case Ending:
				EndingExecute(&KeyInterval, &nowScene);
				EndingDraw(BuffaDC, gw->hScreenDC, hBack, &nowScene);
				break;
			case Winning:
				WinningDraw(&pl, sh, &ri, esh, BuffaDC, gw->hScreenDC, hChar, hBack, hShot);
				WinningUI(&pl, &ri, BuffaDC, gw->hScreenDC, hUi);
				UiDraw(&pl, NULL, NULL, BuffaDC, gw->hScreenDC, hUi);
				WinningExecute(&pl, sh, &ri, esh, &nowScene,NowChara,BuffaDC, gw->hScreenDC,hBack,CharaF);
				WinningTime++;
				break;
			case WinningResult:
				ResultExecute(&KeyInterval, &nowScene);
				WinningResultDraw(BuffaDC, gw->hScreenDC, hUi, hBack, Winningrank, nowrank);
				break;
			case CharaSelect:
				CharaSelectExecute(&nowScene, &SelChara, &KeyInterval, CharaF, &NowChara);
				CharaSelectDraw(BuffaDC, gw->hScreenDC, hBack, hChar, &SelChara, CharaF,&NowChara);
				break;
			case GameOver:
				ResultExecute(&KeyInterval, &nowScene);
				GameOverDraw(BuffaDC, gw->hScreenDC, hBack, hUi, nowScene);
				break;
			}
		}

		//シーン切り替え時の処理
		if (backScene != nowScene)
		{
			switch (backScene)
			{
			case Warriors:

				Time = 6000;
				InitPlayer(&pl, NowChara);
				InitBoss(&bo);
				InitShot(&bsh);
				for (int i = 0; i < ENEMY_MAX; i++) {
					InitEnemy(&en[i]);
				}
				for (int i = 0; i < SHOT_MAX; i++) {
					InitShot(&sh[i]);
				}
				for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
					InitShot(&esh[i]);
				}
				//ランキングの読み込みとソート処理
				if (!rakingread) {
					nowrank = Score;

					fp = fopen("xxx.dat", "rb");
					fread(&ranking, sizeof(int), 5, fp);
					fclose(fp);

					Score = nowrank;
					ranking[5] = Score;
					for (int i = 5; i > 0; i--) {
						if (ranking[i - 1] < ranking[i]) {
							int tmp = ranking[i];
							ranking[i] = ranking[i - 1];
							ranking[i - 1] = tmp;
							nowrank = i;
						}
					}

					fp = fopen("xxx.dat", "wb");
					fwrite(&ranking, sizeof(int), 5, fp);
					fclose(fp);

					rakingread = true;
				}
				break;
			case Result:
				Score = 0;
				nowrank = 10;
				DrowCount = 0;
				break;
			case Title:
				Score = 0;
				rakingread = false;
				break;
			case Ending:
				Score = 0;
				nowrank = 10;
				DrowCount = 0;
				MenuSel = 0;
				rakingread = false;
				break;
			case Winning:
				if (nowScene == WinningResult)
				{
					if (!rakingread) {
						nowrank = WinningTime;

						fp = fopen("Time.dat", "rb");
						fread(&Winningrank, sizeof(int), 5, fp);
						fclose(fp);

						WinningTime = nowrank;
						Winningrank[5] = WinningTime / 100;
						for (int i = 0; i < 6; i++) {
							for (int j = i + 1; j < 6; ++j) {
								if (Winningrank[i] > Winningrank[j]) {
									int tmp = Winningrank[i];
									Winningrank[i] = Winningrank[j];
									Winningrank[j] = tmp;
									nowrank = i;
								}
							}
						}

						fp = fopen("Time.dat", "wb");
						fwrite(&Winningrank, sizeof(int), 5, fp);
						fclose(fp);

						fp = fopen("Chara.dat", "wb");
						fwrite(&CharaF, sizeof(bool), 7, fp);
						fclose(fp);

						rakingread = true;
					}
				}
				InitPlayer(&pl, NowChara);
				InitRival(&ri, 0);
				for (int i = 0; i < SHOT_MAX; i++) {
					InitShot(&sh[i]);
				}
				for (int i = 0; i < ENEMY_SHOT_MAX; i++) {
					InitShot(&esh[i]);
				}
				break;
			case WinningResult:
				WinningTime = 0;
				nowrank = 10;
				DrowCount = 0;
				rakingread = false;
			case CharaSelect:
				MenuSel = 0;
				InitPlayer(&pl, NowChara);
				break;
			default:
				MenuSel = 0;
				DrowCount = 0;
				page = 0;
				rakingread = false;
				break;
			}
		}

		InvalidateRect(gw->hWnd, NULL, false);

		if (progress >= 1000)
		{
			beforTime = nowTime;		//現在の時間で更新する
			frame = 0;
		}

		frame++;
	}

	return TRUE;
}

//ウィンドウを作る	こいつが最初に始まる
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE, PSTR,int)
{
	WNDCLASS  wc;										//Windowsクラス
	HWND      hWnd;										//windowsハンドル
	MSG		  msg;										//Windowメッセージ
	DWORD     ProcessAffinityMask;						//CPUを指定
	HANDLE    hProcess;									//プロセスハンドル
	DWORD     errnum;									//エラーNo
	BOOL      ret;										//関数復帰値

	timeBeginPeriod(1);

	//自信のプロセスハンドルを取得
	hProcess = GetCurrentProcess();

	//自信を動作させるCPUを指定する
	ProcessAffinityMask = 1;
	ret = SetProcessAffinityMask(hProcess, ProcessAffinityMask);
	if (!ret) { errnum = GetLastError(); return 0; }

	//Windows（ウィンドウの情報）の登録
	wc.style = CS_HREDRAW | CS_VREDRAW;					//縦軸と横軸の再描画
	wc.lpfnWndProc = WindowProc;						//ウィンドウズ関数名
	wc.cbClsExtra = 0;									//使いません	拡張機能
	wc.cbWndExtra = 0;									//使いません	拡張機能
	wc.hInstance = hInstance;							//インスタンス番号
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//アイコン（デフォルトにする）
	wc.hCursor = NULL;									//カーソル（デフォルトを使用）
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//背景色
	wc.lpszMenuName = NULL;								//メニューなし
	wc.lpszClassName = CLASS_NAME;						//アプリケーション名
	//WindowsくらすをWindowsに登録する
	if (RegisterClass(&wc) == false)
	{
		//エラーメッセージの表示
		MessageBox(NULL,
			"ウィンドウズクラスの登録に失敗",
			"エラーメッセージ", MB_YESNO + MB_ICONEXCLAMATION);
		return 0;
	}
	//Windowsの作成
	hWnd = CreateWindow(
		CLASS_NAME,				//アプリケーション名
		TITLE_NAME,		//タイトル
		WS_OVERLAPPEDWINDOW,	//普通のWindow
		100, 100,				//表示する位置のｘ、ｙ座標
		WND_W,WND_H,				//Windowの幅、高さ
		NULL,					//親ウィンドウハンドル（自分が親なのでなし）
		NULL,					//メニューの設定（使わない）
		hInstance,				//インスタンス番号
		NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL,
			"ウィンドウズの作成に失敗",
			"エラーメッセージ", MB_YESNO + MB_ICONEXCLAMATION);
		return 0;
	}
	RECT rc, rw;
	GetWindowRect(hWnd, &rw);
	GetClientRect(hWnd, &rc);

	int nw = (rw.right - rw.left) - (rc.right - rc.left)+WND_W;
	int nh = (rw.bottom - rw.top) - (rc.bottom - rc.top) + WND_H;

	SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_COMPOSITED);

	SetWindowPos(hWnd, 0, 0, 0, nw, nh, SWP_NOMOVE | SWP_NOZORDER);
	//ウィンドウを表示
	ShowWindow(hWnd, SW_SHOW);			//SW_HIDE隠す
	UpdateWindow(hWnd);
	//メッセージループ（Windowが閉じられるまでループ）
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		//BGM
		if (backScene != nowScene)
		{
			if (nowScene != Menu) {
				BGMClose(backScene, hWnd);
				BGMOpen(nowScene, hWnd);
				BGMPlay(nowScene, hWnd);
			}
		}
		else BGMCheck(nowScene, hWnd);

		backScene = nowScene;

		//Window関数に送る
		DispatchMessage(&msg);
	}

	timeEndPeriod(1);

	return 0;
}