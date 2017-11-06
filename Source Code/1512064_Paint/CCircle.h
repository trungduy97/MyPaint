#pragma once
#include "CShape.h"
class CCircle :
	public CShape
{
public:
	CCircle();
	~CCircle();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
};