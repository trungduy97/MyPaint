#pragma once

#include "resource.h"
#include <Windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <windowsx.h>
#include "CLine.h"
#include "CRectangle.h"
#include "CPolygon.h"
#include "CEllipse.h"
#include "CSquare.h"
#include "CCircle.h"
#include <CommCtrl.h>
#pragma comment(lib, "ComCtl32.lib")

#include <vector>
using namespace std;

ATOM MyRegisterClass(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
//------------------------------------------------------------------

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND);
void OnLButtonDown(HWND, BOOL, int, int, UINT);
void OnMouseMove(HWND, int, int, UINT);
void OnLButtonUp(HWND, int, int, UINT);