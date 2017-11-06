﻿#include "stdafx.h"
#include "CCircle.h"


CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop)
{
	//Lưu các thuộc tính để vẽ lại
	m_lefttop = lefttop;
	m_rightbot = rightbot;
	m_pen = pen;

	HDC hdc = GetDC(hwnd);

	if (bSetRop == true)
		SetROP2(hdc, R2_MERGEPENNOT);
	SelectObject(hdc, pen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH)); //Trong suốt

	RECT a;
	a.left = min(lefttop.x, rightbot.x);
	a.top = min(lefttop.y, rightbot.y);
	a.right = max(lefttop.x, rightbot.x);
	a.bottom = max(lefttop.y, rightbot.y);

	int length = min(abs(rightbot.x - lefttop.x), abs(rightbot.y - lefttop.y));

	if (lefttop.x > rightbot.x)
	{
		a.left = a.right - length;
	}
	else
		a.right = a.left + length;

	if (rightbot.y < lefttop.y)
	{
		a.top = a.bottom - length;
	}
	else
	{
		a.bottom = a.top + length;
	}

	Ellipse(hdc, a.left, a.top, a.right, a.bottom);

	ReleaseDC(hwnd, hdc);
}

void CCircle::ReDraw(HWND hwnd)
{
	Draw(hwnd, m_pen, m_lefttop, m_rightbot, false);
}

CShape* CCircle::CreateNewShape()
{
	CShape* shape = new CCircle;
	return shape;
}
