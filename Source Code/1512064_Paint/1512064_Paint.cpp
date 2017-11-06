// 1512064_Paint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1512064_Paint.h"

#define MAX_LOADSTRING 100

#define SHAPE_MODEL_LINE			0
#define SHAPE_MODEL_RECTANGLE		1
#define SHAPE_MODEL_POLYGON			2
#define SHAPE_MODEL_ELLIPSE			3
#define SHAPE_MODEL_SQUARE			4
#define SHAPE_MODEL_CIRCLE			5

// Global Variables:
HINSTANCE g_hInst;

HWND g_hwnd;

//C: Mảng các hình đã vẽ
vector <CShape*> g_Shapes;
//C: Các thông số về đối tượng đang được vẽ
BOOL g_bDrawStarted = FALSE; //Bắt đầu vẽ hay chưa
BOOL g_bPolygon = FALSE;

//C: Tọa độ
POINT g_lefttop;
POINT g_rightbot;
HPEN g_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

vector <CShape*> g_ShapeModels;
int g_iCurShapeType = SHAPE_MODEL_LINE;

BOOL g_bPolygonHasLine = FALSE;

TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY1512064_PAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1512064_PAINT));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1512064_PAINT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY1512064_PAINT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   g_hInst = hInstance; // Store instance handle in our global variable

   g_hwnd = CreateWindowEx(0, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_SIZEBOX,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
	   NULL, NULL, hInstance, NULL);

   if (!g_hwnd)
   {
	   return FALSE;
   }

   ShowWindow(g_hwnd, SW_SHOW);
   UpdateWindow(g_hwnd);
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, OnLButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, OnMouseMove);
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
		break;
	}

	return 0;
}

/**********************************************/

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	//C: Tạo ra các mẫu đối tượng cơ bản
	g_ShapeModels.push_back(new CLine);
	g_ShapeModels.push_back(new CRectangle);
	g_ShapeModels.push_back(new CPolygon);
	g_ShapeModels.push_back(new CEllipse);
	g_ShapeModels.push_back(new CSquare);
	g_ShapeModels.push_back(new CCircle);

	CheckMenuItem(GetMenu(hwnd), ID_SHAPE_LINE, MF_CHECKED);
	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtrl, UINT codeNotify)
{
	HMENU hMenu = GetMenu(hwnd);
	UINT state;
	switch (id)
	{
	case ID_FILE_NEW: //C: Tạp bảng vẽ mới 
		for (int i = g_Shapes.size() - 1; i >= 0; --i)
		{
			delete g_Shapes[i];
			g_Shapes.pop_back();
		}
		InvalidateRect(hwnd, NULL, TRUE);
		break; //-------------------------------------------------

	case IDM_EXIT:
		DestroyWindow(hwnd);
		break; //-------------------------------------------------
	case ID_SHAPE_LINE:
		g_iCurShapeType = SHAPE_MODEL_LINE;
		g_bPolygon = FALSE;
		g_bDrawStarted = FALSE;
		state = GetMenuState(hMenu, ID_SHAPE_LINE, MF_BYCOMMAND);
		if (state == MF_CHECKED)
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
		}
		else
		{
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);
		}
		break;

	case ID_SHAPE_RECTANGLE:
		g_iCurShapeType = SHAPE_MODEL_RECTANGLE;
		g_bPolygon = FALSE;
		g_bDrawStarted = FALSE;
		state = GetMenuState(hMenu, ID_SHAPE_RECTANGLE, MF_BYCOMMAND);
		if (state == MF_CHECKED)
		{
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
		}
		else
		{
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);
		}
		break;

	case ID_SHAPE_POLYGON:
		g_iCurShapeType = SHAPE_MODEL_POLYGON;
		g_bPolygon = TRUE;
		state = GetMenuState(hMenu, ID_SHAPE_POLYGON, MF_BYCOMMAND);
		if (state == MF_CHECKED)
		{
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);
		}
		else
		{
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
		}
		break;
	case ID_SHAPE_ELLIPSE:
		g_iCurShapeType = SHAPE_MODEL_ELLIPSE;
		g_bPolygon = FALSE;
		g_bDrawStarted = FALSE;
		state = GetMenuState(hMenu, ID_SHAPE_ELLIPSE, MF_BYCOMMAND);
		if (state == MF_CHECKED)
		{
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_UNCHECKED);
		}
		else
		{
			CheckMenuItem(hMenu, ID_SHAPE_ELLIPSE, MF_CHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_LINE, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_POLYGON, MF_UNCHECKED);
			CheckMenuItem(hMenu, ID_SHAPE_RECTANGLE, MF_UNCHECKED);
		}
		break;
	}
}

void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	HDC			hdc;
	hdc = BeginPaint(hwnd, &ps);

	for (int i = 0; i < g_Shapes.size(); ++i)
	{
		g_Shapes[i]->ReDraw(hwnd);
	}
	EndPaint(hwnd, &ps);
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	//C: Nếu chưa bắt đầu vẽ thì tạo ra một hình mới
	if (g_bDrawStarted == FALSE)
		g_Shapes.push_back(g_ShapeModels[g_iCurShapeType]->CreateNewShape());

	g_bDrawStarted = TRUE;

	if (g_bPolygon)
	{
		if (fDoubleClick)
		{
			//POINT first = ((CPolygon*)g_Shapes[g_Shapes.size() - 1])->GetFirst();

			g_Shapes[g_Shapes.size() - 1]->Draw(hwnd, g_pen, g_lefttop, g_rightbot, FALSE);

			g_bPolygonHasLine = FALSE;
			g_bDrawStarted = FALSE;
			InvalidateRect(hwnd, NULL, TRUE);
		}
		else if (g_bPolygonHasLine)
		{
			g_Shapes[g_Shapes.size() - 1]->Draw(hwnd, g_pen, g_lefttop, g_rightbot, FALSE);
		}
	}

	g_lefttop.x = x;
	g_lefttop.y = y;

	g_rightbot.x = x;
	g_rightbot.y = y;
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (g_bDrawStarted == TRUE)
	{
		int iIndex = g_Shapes.size();

		if (g_bPolygon == FALSE)
			g_Shapes[iIndex - 1]->Draw(hwnd, g_pen, g_lefttop, g_rightbot);

		g_rightbot.x = x;
		g_rightbot.y = y;

		if (g_bPolygon == FALSE)
			g_Shapes[iIndex - 1]->Draw(hwnd, g_pen, g_lefttop, g_rightbot);
	}
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (g_bDrawStarted == FALSE)
		return;

	int iIndex = g_Shapes.size();
	g_Shapes[iIndex - 1]->Draw(hwnd, g_pen, g_lefttop, g_rightbot, FALSE);
	
	if (g_bPolygon == FALSE)
		g_bDrawStarted = FALSE;
	else
	{
		g_lefttop.x = x;
		g_lefttop.y = y;
		g_bPolygonHasLine = TRUE;
	}
	InvalidateRect(hwnd, NULL, TRUE);
}