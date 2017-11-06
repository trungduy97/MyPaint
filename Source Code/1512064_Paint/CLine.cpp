#include "stdafx.h"
#include "CLine.h"


CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop)
{
	//Lưu lại các thuộc tính để vẽ lại
	m_lefttop = lefttop;
	m_rightbot = rightbot;

	HDC hdc = GetDC(hwnd);

	if (bSetRop == true)
		SetROP2(hdc, R2_MERGEPENNOT);

	m_pen = pen;
	SelectObject(hdc, m_pen);

	MoveToEx(hdc, lefttop.x, lefttop.y, NULL);
	LineTo(hdc, rightbot.x, rightbot.y);

	ReleaseDC(hwnd, hdc);
}

void CLine::ReDraw(HWND hwnd)
{
	Draw(hwnd, m_pen, m_lefttop, m_rightbot, false);
}

CShape* CLine::CreateNewShape()
{
	CShape* shape = new CLine;
	return shape;
}