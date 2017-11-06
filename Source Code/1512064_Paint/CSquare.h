#pragma once
#include "CShape.h"
class CSquare : public CShape
{
public:
	CSquare();
	~CSquare();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
};