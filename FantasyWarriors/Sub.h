#pragma once
#pragma comment(lib, "Msimg32.lib")	//TBlt使用の際必要
#ifndef _SUB_
#define _SUB_
#include"Hub.h"

#pragma region プロトタイプ宣言
//関数のプロトタイプ宣言
void MTBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, BLENDFUNCTION Bfunk, int px, int py, int sx, int sy);
void text(HDC hdc, int x, int y,const char* text);
void whitetext(HDC hdc, int x, int y, const char* text);
bool ReadBmp(HBITMAP* hBmp, LPCTSTR FName);
void BBlt(HDC hdc, HDC hMemDC, HBITMAP hBmp,int a);
void TBltB(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y,int i, int z);
void TransBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int gx, int gy);
#pragma endregion
#endif // !_SUB_
