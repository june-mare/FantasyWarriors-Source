#pragma once
#pragma comment(lib, "Msimg32.lib")	//TBlt�g�p�̍ەK�v
#ifndef _SUB_
#define _SUB_
#include"Hub.h"

#pragma region �v���g�^�C�v�錾
//�֐��̃v���g�^�C�v�錾
void MTBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, BLENDFUNCTION Bfunk, int px, int py, int sx, int sy);
void text(HDC hdc, int x, int y,const char* text);
void whitetext(HDC hdc, int x, int y, const char* text);
bool ReadBmp(HBITMAP* hBmp, LPCTSTR FName);
void BBlt(HDC hdc, HDC hMemDC, HBITMAP hBmp,int a);
void TBltB(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y,int i, int z);
void TransBlt(HDC hdc, HDC hMemDC, HBITMAP* hBmp, int x, int y, int gx, int gy);
#pragma endregion
#endif // !_SUB_
