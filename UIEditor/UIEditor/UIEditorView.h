
// UIEditorView.h : CUIEditorView 类的接口
//

#pragma once

#include "D3DInit.h"

class CUIEditorView : public CView
{
public:
	D3DInit *m_pD3DInit;

	CPoint m_movePoint;
	CPoint m_clickPoint;
	HWND m_hWnd;

protected: // 仅从序列化创建
	CUIEditorView();
	DECLARE_DYNCREATE(CUIEditorView)

// 特性
public:
	CUIEditorDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CUIEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // UIEditorView.cpp 中的调试版本
inline CUIEditorDoc* CUIEditorView::GetDocument() const
   { return reinterpret_cast<CUIEditorDoc*>(m_pDocument); }
#endif

