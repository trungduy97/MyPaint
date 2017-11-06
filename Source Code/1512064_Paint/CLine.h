#pragma once

#include "CShape.h"

class CLine : public CShape
{
public:
	CLine();
	~CLine();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
	POINT GetLefttop() { return m_lefttop; };
};

