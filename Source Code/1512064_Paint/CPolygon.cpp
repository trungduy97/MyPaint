#include "stdafx.h"
#include "CPolygon.h"


CPolygon::CPolygon()
{
}


CPolygon::~CPolygon()
{
}


void CPolygon::Draw(HWND hwnd, HPEN pen, POINT lefttop, POINT rightbot, bool bSetRop)
{
	m_Lines.push_back(new CLine);
	m_Lines[m_Lines.size() - 1]->Draw(hwnd, pen, lefttop, rightbot);
}

void CPolygon::ReDraw(HWND hwnd)
{
	for (int i = 0; i < m_Lines.size(); ++i)
		m_Lines[i]->ReDraw(hwnd);
}

CShape* CPolygon::CreateNewShape()
{
	CShape* shape = new CPolygon;
	return shape;
}

bool operator==(const POINT& p1, const POINT& p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y))
		return true;
	else
		return false;
}

POINT CPolygon::GetFirst()
{
	return m_Lines[0]->GetLefttop();
}
