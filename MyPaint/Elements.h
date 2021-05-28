#pragma once
#include <afx.h>
#include <vector>

//Element
class CElement :public CObject
{
protected:
	int m_PenWith; // Pen thickness
	COLORREF m_Color; // Elemet color
	CRect m_EnclosingRect; // Rectangle describing element
public:
	virtual ~CElement();
	virtual void Draw(CDC* pDC) {}

	CRect GetBoundRect() const;

protected:
	CElement(); // What would prevent a call from outside the class
};


//Line
class CLine :public CElement
{
public:
	virtual ~CLine(void);
	
	virtual void Draw(CDC* pDC);
	
	CLine(const CPoint& start, const CPoint& end, COLORREF aColor, int aWidth);

protected:
	CPoint m_StartPoint;
	CPoint m_EndPoint;

protected:
	CLine(void);
};


//Rectangle
class CRectangle :public CElement
{
public:
	~CRectangle(void);

	virtual void Draw(CDC*pDC);

	CRectangle(const CPoint& start, const CPoint end, COLORREF aColor, int aWidth);

protected:
	CRectangle(void);
};


//Circle
class CCircle :public CElement
{
public:
	~CCircle(void);
	virtual void Draw(CDC*pDC);

	CCircle(const CPoint&Start, const CPoint& end, COLORREF aColor, int aWidth);


protected:
	CCircle(void);
};


//Curve
class CCurve :public CElement
{
public:
	~CCurve(void);
	virtual void Draw(CDC*pDC);

	CCurve(const CPoint& First, const CPoint& Second, COLORREF aColor, int aWidth);
	void AddSegment(const CPoint&point); // Add segment to curve
	std::vector<CPoint> m_Points; //Curve points
	

protected:
	CCurve(void);
};

