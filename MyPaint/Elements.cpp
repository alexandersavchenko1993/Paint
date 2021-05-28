#include "stdafx.h"
#include "Elements.h"
#include <cmath>

//Element
CElement::CElement()
{
}

CElement::~CElement()
{
}

CRect CElement::GetBoundRect() const
{
	// Item to store the bounding box
	CRect boundingRect(m_EnclosingRect);

	// Extend rectangle to pen width
	boundingRect.InflateRect(m_PenWith, m_PenWith);
	return CRect();
}


//Line
CLine::CLine()
{
}


CLine::~CLine()
{
}

void CLine::Draw(CDC * pDC)
{
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWith, m_Color))
	{
		AfxMessageBox(_T("Failed to create a line drawing pen"), MB_OK);
		AfxAbort();
	}

	// Select pen tool
	CPen* OldPen = pDC->SelectObject(&aPen);

	//Draw line
	pDC->MoveTo(m_StartPoint);
	pDC->LineTo(m_EndPoint);

	//Restore old pen
	pDC->SelectObject(OldPen);

}

CLine::CLine(const CPoint & start, const CPoint & end, COLORREF aColor, int aWidth) :m_StartPoint(start), m_EndPoint(end)
{
	m_PenWith = aWidth;
	m_Color = aColor;

	// Set Bounding Rectangle
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();
}


//Rectangle
CRectangle::CRectangle()
{
}

CRectangle::~CRectangle()
{
}

void CRectangle::Draw(CDC * pDC)
{
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWith, m_Color))
	{
		AfxMessageBox(_T("Failed to create a rectangle drawing pen"), MB_OK);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);

	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//Draw Rectangle
	pDC->Rectangle(m_EnclosingRect);

	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

CRectangle::CRectangle(const CPoint & start, const CPoint end, COLORREF aColor, int aWidth)
{
	m_PenWith = aWidth;
	m_Color = aColor;
	
	m_EnclosingRect = CRect(start, end);
	m_EnclosingRect.NormalizeRect();

}


//Circle
CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(CDC * pDC)
{
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWith, m_Color))
	{
		AfxMessageBox(_T("Failed to create a ellipse drawing pen"), MB_OK);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);// Select pen tool

	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//Draw Ellipse
	pDC->Ellipse(m_EnclosingRect);

	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

CCircle::CCircle(const CPoint & start, const CPoint & end, COLORREF aColor, int aWidth)
{
	//Calculate radius
	long radius = static_cast<long> (sqrt(static_cast<double>((end.x - start.x)*(end.x - start.x) + (end.y - end.y)*(end.y - end.y))));
	//Calculate rectangle arround circle
	m_EnclosingRect = CRect(start.x - radius, start.y - radius, start.x + radius, start.y + radius);
	//Normilize rectangle
	m_EnclosingRect.NormalizeRect();

	m_PenWith = aWidth;
	m_Color = aColor;
}


//Curve
CCurve::CCurve()
{
}


CCurve::~CCurve()
{
}

void CCurve::Draw(CDC * pDC)
{
	CPen aPen;
	if (!aPen.CreatePen(PS_SOLID, m_PenWith, m_Color))
	{
		AfxMessageBox(_T("Failed to create a curve drawing pen"), MB_OK);
		AfxAbort();
	}

	CPen* pOldPen = pDC->SelectObject(&aPen);

	//Draw Curve
	pDC->MoveTo(m_Points[0]);
	for (size_t i = 1; i < m_Points.size(); ++i) 
		pDC->LineTo(m_Points[i]);

	pDC->SelectObject(pOldPen);
}

CCurve::CCurve(const CPoint & First, const CPoint & Second, COLORREF aColor, int aWidth)
{
	m_Points.push_back(First);
	m_Points.push_back(Second);
	m_Color = aColor;
	
	m_PenWith = aWidth;
	m_EnclosingRect = CRect(min(First.x, Second.x), 
		min(First.y, Second.y), 
		min(First.x, Second.x), 
		min(First.y, Second.y));
}

void CCurve::AddSegment(const CPoint & point)
{
	//Add point to the end of curve
	m_Points.push_back(point);

	//Change rectangle around the curve
	m_EnclosingRect = CRect(min(point.x, m_EnclosingRect.left),
		min(point.y, m_EnclosingRect.top),
		max(point.x, m_EnclosingRect.right),
		max(point.y, m_EnclosingRect.bottom));
}
