#define _CRT_SECURE_NO_WARNINGS
#include"Hub.h"
#include"Sub.h"
#include"resource.h"

HDC BuffaDC;
static int nowScene = Title;
static int backScene = nowScene;

//���C�������ԏ���
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)	//���b�Z�[�W�ɑΉ��������
	//�ϐ��̐錾
{
	HDC hdc;
	PAINTSTRUCT  ps;
	static GameWindow gameWnd;//�Q�[���E�B���h�E�\����
	DWORD	dwID;	//�X���b�hID
	HBITMAP hBMP;	//�r�b�g�}�b�v�n���h��
	//HRESULT hRlt;	//�֐����A�l

	//�������}���`�o�C�g�̏ꍇ��wchar�ɂ���i�傫�ڂ̔���p�ӂ��Ă���j
	//���b�Z�[�W�ʂ̏���
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

		//����BGM
		BGMOpen(nowScene, hWnd);
		BGMPlay(nowScene, hWnd);

		//�X���b�h�ɔ�΂�
		CreateThread(NULL, 0, ThreadFunc, (LPVOID)&gameWnd, 0, &dwID);
		
		break;

	case WM_TIMER:	//�����L�[���������Ƃ�
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;
	case WM_PAINT:	//�\������Ƃ��i�ŏ���Windows���X�V���ꂽ�Ƃ��j
	{
		hdc = BeginPaint(hWnd, &ps);//�\���J�n
		BitBlt(hdc, 0, 0, WND_W, WND_H, BuffaDC, 0, 0, SRCCOPY);
		EndPaint(hWnd, &ps);
	}
		return 0;
	case WM_DESTROY:	//Window���I�����ꂽ�Ƃ�
		//===�I����������//
		PostQuitMessage(0);
		return 0;	//Window�ɖ߂�
	}

	//���C���ɕԂ����
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//�񓯊�����
DWORD WINAPI ThreadFunc(LPVOID vdlParam)	//void�Ƀ|�C���^������LPVOID
{
	GameWindow* gw = (GameWindow*)vdlParam;

	DWORD frame = 0,
		beforTime = timeGetTime();

	HDC hdc = CreateCompatibleDC(gw->hScreenDC);

#pragma region �ϐ�

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

//�����L���O�y�уL���������̏�����

//���L�R�s���R�����g�A�E�g�Ń����L���O���L�^����
	
	//Warriors
	/*fp = fopen("xxx.dat", "wb");
	fwrite(&ranking, sizeof(int), 5, fp);
	fclose(fp);*/

	//Winning
	/*fp = fopen("Time.dat", "wb");
	fwrite(&Winningrank	, sizeof(int), 5, fp);
	fclose(fp);*/

	//�L�����N�^�[�J�����̃��Z�b�g
	/*fp = fopen("Chara.dat", "wb");
	fwrite(&CharaF, sizeof(bool), 6, fp);
	fclose(fp);*/
	
	//�L�����N�^�[�J�����̓ǂݍ���
	fp = fopen("Chara.dat", "rb");
	fread(&CharaF, sizeof(bool), 7, fp);
	fclose(fp);

//��������
#pragma region �L�����N�^�[�y�ђe�̏�����

	//�L����
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
	//�e
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

//�摜�ǂݍ���
#pragma region �摜�f�[�^

	HBITMAP hBack[ImageScrean::Max];  
	HBITMAP hChar[ImageChara::CMA];
	HBITMAP hShot[ImageShot::SImax];
	HBITMAP hUi[ImageUI::uimax];

	for (int i = 0; i < (int)ImageScrean::Max; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "�f��/�w�i/�w�i";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hBack[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageChara::CMA; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "�f��/�L����/�L����";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hChar[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageShot::SImax; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "�f��/�U��/�U��";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hShot[i], wStr) == false)return 0;
	}
	for (int i = 0; i < (int)ImageUI::uimax; i++)
	{
		CHAR wNum[3] = { NULL };
		_itoa_s(i + 1, wNum, 10);
		CHAR wStr[64] = "�f��/UI/UI";
		strcat_s(wStr, wNum);
		strcat_s(wStr, ".bmp");
		if (ReadBmp(&hUi[i], wStr) == false)return 0;
	}

#pragma endregion

//�_�u���o�b�t�@����
	HBITMAP hBmp = CreateCompatibleBitmap(gw->hScreenDC, WND_W, WND_H);
	BuffaDC = CreateCompatibleDC(gw->hScreenDC);
	SelectObject(BuffaDC, hBmp);

//���̒����J��Ԃ�
	while (true)
	{
		DWORD nowTime = timeGetTime(),						//���݂̎��Ԃ��擾
			idealTime = (DWORD)(frame * (1000.0F / gw->dwFPS)),
			progress = nowTime - beforTime;

		if (idealTime > progress) Sleep(idealTime - progress);
		
		//�V�[�P���X
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

		//�V�[���؂�ւ����̏���
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
				//�����L���O�̓ǂݍ��݂ƃ\�[�g����
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
			beforTime = nowTime;		//���݂̎��ԂōX�V����
			frame = 0;
		}

		frame++;
	}

	return TRUE;
}

//�E�B���h�E�����	�������ŏ��Ɏn�܂�
int WINAPI WinMain(HINSTANCE hInstance,	HINSTANCE, PSTR,int)
{
	WNDCLASS  wc;										//Windows�N���X
	HWND      hWnd;										//windows�n���h��
	MSG		  msg;										//Window���b�Z�[�W
	DWORD     ProcessAffinityMask;						//CPU���w��
	HANDLE    hProcess;									//�v���Z�X�n���h��
	DWORD     errnum;									//�G���[No
	BOOL      ret;										//�֐����A�l

	timeBeginPeriod(1);

	//���M�̃v���Z�X�n���h�����擾
	hProcess = GetCurrentProcess();

	//���M�𓮍삳����CPU���w�肷��
	ProcessAffinityMask = 1;
	ret = SetProcessAffinityMask(hProcess, ProcessAffinityMask);
	if (!ret) { errnum = GetLastError(); return 0; }

	//Windows�i�E�B���h�E�̏��j�̓o�^
	wc.style = CS_HREDRAW | CS_VREDRAW;					//�c���Ɖ����̍ĕ`��
	wc.lpfnWndProc = WindowProc;						//�E�B���h�E�Y�֐���
	wc.cbClsExtra = 0;									//�g���܂���	�g���@�\
	wc.cbWndExtra = 0;									//�g���܂���	�g���@�\
	wc.hInstance = hInstance;							//�C���X�^���X�ԍ�
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//�A�C�R���i�f�t�H���g�ɂ���j
	wc.hCursor = NULL;									//�J�[�\���i�f�t�H���g���g�p�j
	wc.hbrBackground = (HBRUSH)COLOR_BACKGROUND + 1;	//�w�i�F
	wc.lpszMenuName = NULL;								//���j���[�Ȃ�
	wc.lpszClassName = CLASS_NAME;						//�A�v���P�[�V������
	//Windows���炷��Windows�ɓo�^����
	if (RegisterClass(&wc) == false)
	{
		//�G���[���b�Z�[�W�̕\��
		MessageBox(NULL,
			"�E�B���h�E�Y�N���X�̓o�^�Ɏ��s",
			"�G���[���b�Z�[�W", MB_YESNO + MB_ICONEXCLAMATION);
		return 0;
	}
	//Windows�̍쐬
	hWnd = CreateWindow(
		CLASS_NAME,				//�A�v���P�[�V������
		TITLE_NAME,		//�^�C�g��
		WS_OVERLAPPEDWINDOW,	//���ʂ�Window
		100, 100,				//�\������ʒu�̂��A�����W
		WND_W,WND_H,				//Window�̕��A����
		NULL,					//�e�E�B���h�E�n���h���i�������e�Ȃ̂łȂ��j
		NULL,					//���j���[�̐ݒ�i�g��Ȃ��j
		hInstance,				//�C���X�^���X�ԍ�
		NULL);
	if (hWnd == NULL)
	{
		MessageBox(NULL,
			"�E�B���h�E�Y�̍쐬�Ɏ��s",
			"�G���[���b�Z�[�W", MB_YESNO + MB_ICONEXCLAMATION);
		return 0;
	}
	RECT rc, rw;
	GetWindowRect(hWnd, &rw);
	GetClientRect(hWnd, &rc);

	int nw = (rw.right - rw.left) - (rc.right - rc.left)+WND_W;
	int nh = (rw.bottom - rw.top) - (rc.bottom - rc.top) + WND_H;

	SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_COMPOSITED);

	SetWindowPos(hWnd, 0, 0, 0, nw, nh, SWP_NOMOVE | SWP_NOZORDER);
	//�E�B���h�E��\��
	ShowWindow(hWnd, SW_SHOW);			//SW_HIDE�B��
	UpdateWindow(hWnd);
	//���b�Z�[�W���[�v�iWindow��������܂Ń��[�v�j
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

		//Window�֐��ɑ���
		DispatchMessage(&msg);
	}

	timeEndPeriod(1);

	return 0;
}