#pragma once
#include "CShape.h"
class CRectangle : public CShape
{
public:
	CRectangle();
	~CRectangle();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
};

