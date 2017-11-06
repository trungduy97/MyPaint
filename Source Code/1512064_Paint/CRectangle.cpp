#include "stdafx.h"
#include "CRectangle.h"


CRectangle::CRectangle()
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop)
{
	//Lưu lại các thuộc tính để vẽ lại
	m_lefttop = lefttop;
	m_rightbot = rightbot;

	HDC hdc = GetDC(hwnd);
	m_pen = pen;
	SelectObject(hdc, m_pen);

	if (bSetRop == true)
		SetROP2(hdc, R2_MERGEPENNOT);

	SelectObject(hdc, GetStockObject(NULL_BRUSH)); //Trong suốt

	Rectangle(hdc, lefttop.x, lefttop.y, rightbot.x, rightbot.y);

	ReleaseDC(hwnd, hdc);
}

void CRectangle::ReDraw(HWND hwnd)
{
	Draw(hwnd, m_pen, m_lefttop, m_rightbot, false);
}

CShape* CRectangle::CreateNewShape()
{
	CShape* shape = new CRectangle;
	return shape;
}