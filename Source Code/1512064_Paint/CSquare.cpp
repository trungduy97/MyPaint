#include "stdafx.h"
#include "CShape.h"


CShape::CShape()
{
	m_pen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
}


CShape::~CShape()
{
}
