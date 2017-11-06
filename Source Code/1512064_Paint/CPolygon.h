#pragma once

#include <vector>
using namespace std;

#include "CShape.h"
#include "CLine.h"

class CPolygon :
	public CShape
{
	vector<CLine*> m_Lines;
public:
	CPolygon();
	~CPolygon();

	void Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop = TRUE);
	void ReDraw(HWND hwnd);
	CShape* CreateNewShape();
	POINT GetFirst();
	POINT GetLast();
};

bool operator==(const POINT& p1, const POINT& p2);
\