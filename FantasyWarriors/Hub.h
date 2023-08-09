#pragma once
//include宣言
#include<iostream>
#include<Windows.h>
#include<wchar.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//ファイル読み込み
#include"Sub.h"

//ライブラリ
#pragma comment(lib,"winmm.lib")//音を鳴らすライブラリ

//画像制作　　スペシャルサンクス
//Yamada Kenzi 　　山田　健司　UI
//Takahashi Tubasa 高橋　翼　タイトルロゴ

#pragma region マクロ定義

#pragma region ウィンドウ情報
#define WND_W	800 //ウィンドウの幅(width)
#define WND_H	600 //ウィンドウの高さ(height)
#define CLASS_NAME "STG"//アプリケーション名
#define TITLE_NAME "FantasyWarriors"
#pragma endregion

#pragma region キャラ画像大きさ
#define VALKYRIE_SIZE 138,88

#define ASSASSIN_SIZE 100,59

#define MONK_SIZE	  82,60

#define SNIPER_SIZE 62,54

#define BANBIT_SIZE 48,51

#define KNIGHT_SIZE 100,55

#define ENEMY_CHAR 32,32

#define EXEPLOTION 32,32

#define SHOT_SIZE 32,32

#define BOSS_SIZE 140,93

#define CHAR_SIZE 64
//表示画像サイズ
#define CHARA_DC_SIZE 64,64
#pragma endregion 

#pragma region 画像xサイズ

#define VALKYRIE_X 138
#define VALKYRIE_REVERS_X 1378

#define ASSASSIN_X 100
#define ASSASSIN_REVERS_X 500

#define MONK_X 82
#define MONK_REVERS_X 410

#define SNIPER_X 62
#define SNIPER_REVERS_X 806

#define BANBIT_X 48
#define BANBIT_REVERS_X 464

#define KNIGHT_X 100
#define KNIGHT_REVERS_X 900

#define SHOT_X_SIZE 32
#define SHOT_REVERS_X 349

#define ENEMY_X_SIZE 32
#define ENEMY_REVERS_X 64

#define BOSS_X_SIZE 140
#define BOSS_REVERS_X 1680
#pragma endregion

#pragma region 画像yサイズ
#define VALKYRIE_Y 88
#define VALKYRIE_REVERS_Y 883

#define ASSASSIN_Y 59
#define ASSASSIN_REVERS_Y 354

#define MONK_Y 60
#define MONK_REVERS_Y 600

#define SNIPER_Y 54
#define SNIPER_REVERS_Y 432

#define BANBIT_Y 48
#define BANBIT_REVERS_Y 256

#define KNIGHT_Y 55
#define KNIGHT_REVERS_Y 660

#define SHOT_Y_SIZE 32
#define SHOT_REVERS_Y 354

#define SWORD_REVERS 49

#define ENEMY_Y_SIZE 32
#define ENEMY_REVERS_Y 161

#define BOSS_Y_SIZE 93
#define BOSS_REVERS_Y 466
#pragma endregion

#pragma region 最大値数
#define ENEMY_MAX 5
#define ENEMY_SHOT_MAX 15
#define SHOT_MAX 10
//文字送りの限度
#define TLN_MAX 100
#pragma endregion

#pragma region テキストボックス
#define MAIN_BOX 750,150  //memdc
#define MAIN_BOX_S 20,450 //hdc
#define MSGT 256
#define ENDMSGT 30
#pragma endregion 

//透過色(マクロ関数)
#define TRANSPARENT_COLOR RGB(0,255,0)	

//AIInterval
#define AIINTERVAL 10

//計算に使うπ
#define M_PI  3.14

#pragma endregion

#pragma region 列挙体
//背景数
enum ImageScrean
{
	Haikei,
	Zenmen,
	titlescene,
	titlelog,
	tutorial,
	blackwhite,
	endroll,
	backskill,
	Haikei2,
	Zenmen2,
	CharaSelHaikei,
	KO,
	Start,
	NotChara,
	NowSelect,
	Esc,

	Max
};
//キャラ画像枚数
enum ImageChara
{
	VALKYRIE,
	BOSS,
	ZAKO,
	ASSASSIN,
	MONK,
	SNIPER,
	BANBIT1,
	BANBIT2,
	KNIGHT,

	CMA
};
//弾画像枚数
enum ImageShot
{
	longshot,
	enemyatack,
	sword,
	spel,
	pet,

	SImax
};
//UI画像枚数
enum ImageUI
{
	hpgage,
	hpwaku,
	uispace,
	uscore,
	utime,
	uisel,
	uOkan,
	urank,
	ui9,
	ui10,
	ui11,
	ui12,
	ui13,
	ui14,
	ui15,
	ui16,
	ui17,

	uimax
};
//シーケンス
enum Scene {
	Title,
	Menu,
	Warriors,
	Result,
	Ending,
	Winning,
	WinningResult,
	CharaSelect,
	GameOver,

	MMax
};
//音楽数
enum BGM
{
	Op,
	Me,
	Bt,
	End,

	Ma
};
//アニメーション
enum Action
{
	//ヴァルキリー
	idle,
	work,
	attack1,
	attack2,
	die,
	hit,
	jumpup,
	jumpdown,
	skill,
	roll,

	//ボス
	bidle,
	bwork,
	batack1,
	bdie,
	batack2,

	//エネミー
	eatack,
	eidle,
	ejump,
	edie,
	ework,

	//アサシン
	aidle,
	arun,
	aattack1,
	aattack2,
	aattack3,
	ajump,
	ahit,
	ajumpdown,
	adie,

	//ムンク
	midle,
	mrun,
	mattack1,
	mattack2,
	mhit,
	mjumpup,
	mjumpdown,
	mseald,
	mattack3,
	mjumpattack,
	mguard,
	mdie,

	//スナイパー
	sidle,
	srun,
	sattack1,
	sattack2,
	shit,
	sseald,
	sjumpup,
	sjumpdown,
	sguard,
	sdie,

	//バンビット 
	baidle,
	barun,
	baattack,
	barespawn,
	bahit,
	badie,

	//ナイト
	kidle,
	krun,
	kattack1,
	kattack2,
	kattack3,
	kjumpup,
	kjumpdown,
	khit,
	kdie,
	kseald,
	kguard,
	kroll,

	//必殺技
	ult
};
//方向
enum Direction
{
	Right = 1,
	Left = -1
};
//キャラタイプ
enum Type
{
	Valkyrie,
	Assassin,
	Monk,
	Sniper,
	Banbit2,
	Banbit1,
	Knight,

	typemax
};
//interval種類
enum Interval
{
	hitinterval,
	shotinterval,
	jumpinterval,
	rollinterval,

	intervalmax
};
#pragma endregion

#pragma region 構造体

struct Chara
{
	int hp;
	int atk;
	int x, y;
	int dx;
	int cnt;
	int interval[intervalmax];
	bool die;
	Action act;
	Direction dir;
	Type typ;
};

typedef struct GameWindow
{
public:
	HWND hWnd;		//ウィンドウハンドル
	SIZE size;		//ウィンドウサイズ
	DWORD dwFPS;	//FPS値(Frame Per Secomd)
	HDC hScreenDC;	//デバイスコンテキスト
};

#pragma endregion

#pragma region プロトタイプ宣言
//メインで使うもののプロトタイプ宣言
DWORD WINAPI ThreadFunc(LPVOID vdlParam);
LRESULT CALLBACK WindowProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
//関数プロトタイプ宣言
void ValkyrieAI(Chara* ri, Chara* sh, Chara* pl);
void AssassinAI(Chara* ri, Chara* sh, Chara* pl);
void MonkAI(Chara* ri, Chara* sh, Chara* pl);
void BanbitAI(Chara* ri, Chara* sh, Chara* pl);
void SniperAI(Chara* ri, Chara* sh, Chara* pl);
void KnightAI(Chara* ri, Chara* sh, Chara* pl);
void WinningModeHitCheck(Chara* sh, Chara* pl1, Chara* pl2);
void RaivalExecute(Chara* ri, Chara* sh, Chara* pl);
void ValkyrieController(Chara* pl, Chara* sh);
void AssassinController(Chara* pl, Chara* sh);
void MonkController(Chara* pl, Chara* sh);
void SniperController(Chara* pl, Chara* sh);
void BanbitController(Chara* pl, Chara* sh);
void KnightController(Chara* pl, Chara* sh);
void SceneChenge(HDC hdc, HDC hMemDC, HBITMAP* hBack, int* Alpha, bool* AlphaF);
bool HitCheckUlt(int ax, int ay, int sizex, int sizey, int dx, int dy, int sizedx, int sizedy);
void TBltC(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int sizex, int sizey);
void TBltCS(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int sizex, int sizey);
void AlphaBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int a);
void AlphaBltSel(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y, int dy);
void AlphaBltResult(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int a, int y);
void AnimationMainChara(Chara* pl);
void AnimationBoss(Chara* bo,Chara* bsh);
void AnimationEnemy(Chara* en, Chara* esh);
void CheckIntervalPlayer(Chara* pl);
void CheckIntervalRaival(Chara* ri);
void TutorialCheckInterval(Chara* pl);
void PlayerExecute(Chara* pl, Chara* sh);
void PlayerShotExecute(Chara* sh, int max);
void PlayerShotHitCheckOnce(Chara* sh, Chara* bo, Chara* pl, int* Score);
void PlayerShotHitCheckSame(Chara* sh, Chara* en, Chara* pl, int* Score, int enmax);
void EnemyExecute(Chara* en, Chara* pl, int* beforshotx);
void EnemyShotExecute(Chara* esh, Chara* pl);
void BossExecute(Chara* bo, Chara* pl, Chara* bsh, int* beforx);
void BBltT(HDC hdc, HDC hMemDC, HBITMAP hBmp, int a);
void BBltTU(HDC hdc, HDC hMemDC, HBITMAP hBmp, int a);
void BGMPlay(int sn, HWND hWnd);
void BGMClose(int sn, HWND hWnd);
void BGMOpen(int sn,HWND hWnd);
void BGMCheck(int sn, HWND hWnd);
void BossDraw(Chara* bo,Chara* bsh, HDC hdc, HDC hMemDC, HBITMAP* hChar,HBITMAP* hShot);
void EnemyShotTiming(Chara* en, Chara* esh, int a);
void EnemyShotDrawPos(Chara* esh,Chara* pl, int a,int x);
void EnemyDraw(Chara* en,Chara* esh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hShot);
void EndingExecute(int* interval, int* Scene);
void EndingDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, int* Scene);
void WarrioersExecute(Chara* pl, Chara* en, Chara* sh, Chara* bo, Chara* bsh, Chara* esh, int* scene, int* Score);
void WarrioersDraw(Chara* pl, Chara* en, Chara* sh,Chara* bo,Chara* bsh , Chara* esh, HDC hdc, HDC hMemDC,HBITMAP* hChar, HBITMAP* hBack, HBITMAP* hShot);
bool HitCheck(int ax, int ay, int dx, int dy);
bool HitCheckB(int ax, int ay, int dx, int dy, int rdian);
void InitPlayer(Chara* pl, int num);
void InitShot(Chara* sh);
void InitEnemy(Chara* en);
void InitBoss(Chara* bo);
void InitRival(Chara* ri, int num);
void TutorialPlayerExecute(Chara* pl, Chara* sh);
void MenuExecute(int* Scene, Chara* pl, Chara* sh,int NowChara);
void MenuDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hChar, HBITMAP* hShot, Chara* pl, Chara* sh);
void PlayerDraw(Chara* pl, HDC hdc, HDC hMemDC,HBITMAP* hChar);
void ResultExecute(int* interval, int* Scene);
void ResultDraw(HDC hdc, HDC hMemDC, HBITMAP* hUi, HBITMAP* hStage, int* rank, int nowrank);
void PlayerShotDraw(Chara* sh, HDC hdc, HDC hMemDC, HBITMAP* hShot);
void TBltBTU(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y);
void TBltMap(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x);
void TBltUI9(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI10(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI11(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int z);
void TBltUI12(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y);

void TBltUI13(HDC hdc, HDC hMemDC, HBITMAP* hBmp);
void TBltE(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBlt2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int dx, int dy);
void TBltUI1(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI3(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI4(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int* Score);
void TBltUI5(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int* Score);
void TBltUI6(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltUI7(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltBoss(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltES(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltS(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltS2(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltS3(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltS4(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltSU(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z, int sx, int sy);
void TBltZ(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int i, int z);
void TBltLogo(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y);
void TBltEnd(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x);
void TBltGameOver(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int y);
void TBltUlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y);
void TitleExecute(int* nowScene,int* sel,int* interval);
void TitleDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hUi, int* sel, int* cnt,int scene);
void TAlphaB(HDC hdc, HDC hMemDC, HDC hWork, HBITMAP* hBmp);
void UiDraw(Chara* pl, int* Score, int* Time, HDC hdc, HDC hMemDC, HBITMAP* ui);
void WinningExecute(Chara* pl, Chara* sh, Chara* ri, Chara* rsh, int* scene, int NowChara, HDC hdc, HDC hMemDC, HBITMAP* hBack,bool* CharaF);
void GameOverDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hUi, int Scene);
void WinningDraw(Chara* pl, Chara* sh, Chara* bo, Chara* bsh, HDC hdc, HDC hMemDC, HBITMAP* hChar, HBITMAP* hBack, HBITMAP* hShot);
void WinningUI(Chara* pl, Chara* ri, HDC hdc, HDC hMemDC, HBITMAP* hUi);
void WinningResultDraw(HDC hdc, HDC hMemDC, HBITMAP* hUi, HBITMAP* hStage, int* rank, int nowrank);
void CharaSelectExecute(int* Scene, int* SelChara, int* interval, bool* CharaF, int* NowChara);
void CharaSelectDraw(HDC hdc, HDC hMemDC, HBITMAP* hStage, HBITMAP* hChar, int* SelChara, bool* CharaF, int* NowChara);
#pragma endregion