#pragma once
#include "CShape.h"
class CEllipse :
	public CShape
{
public:
	CEllipse();
	~CEllipse();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
};