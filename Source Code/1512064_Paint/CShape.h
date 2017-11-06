#pragma once
#include <Windows.h>

class CShape
{
protected:
	POINT m_lefttop;
	POINT m_rightbot;
	HPEN m_pen;
public:
	CShape();
	~CShape();
	virtual void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE) = 0;
	virtual void ReDraw(HWND hwnd) = 0;
	virtual CShape* CreateNewShape() = 0;
};

