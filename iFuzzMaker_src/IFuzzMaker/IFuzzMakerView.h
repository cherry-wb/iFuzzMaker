//================================================================================
//  �Ɨ��s���@�l��񏈗����i�@�\ (IPA)
//  - Information-technology Promotion Agency, Japan -
//
//                                                    �Ɨ��s���@�l��񏈗����i�@�\
//                                                   �Z�p�{�� �Z�L�����e�B�Z���^�[
//                                                ���Z�L�����e�B�Z�p���{���g���[
//
//      -- JPEG �e�X�g�x���c�[�� iFuzzMaker  --
//                                                                Date�F2013/07/30
//--------------------------------------------------------------------------------
//  Copyright (c) 2013, IPA, Japan.
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//      * Redistributions of source code must retain the above copyright
//        notice, this list of conditions and the following disclaimer.
//      * Redistributions in binary form must reproduce the above copyright
//        notice, this list of conditions and the following disclaimer in the
//        documentation and/or other materials provided with the distribution.
//      * Neither the name of the IPA nor the
//        names of its contributors may be used to endorse or promote products
//        derived from this software without specific prior written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//==============================================================================

// IFuzzMakerView.h : CIFuzzMakerView �N���X�̃C���^�[�t�F�C�X
//
#pragma once

#include "resource.h"
#include "WndResizer.h"
#include "JpegSelView.h"
#include "ExifSelView.h"
#include "SegmentItemSelView.h"
#include "PatternSelView.h"
#include "FuzzSelView.h"
#include "FuzzCreateView.h"

#define ID_TAB		1000

class CIFuzzMakerView : public CFormView
{
protected: // �V���A��������̂ݍ쐬���܂��B
	CIFuzzMakerView();
	DECLARE_DYNCREATE(CIFuzzMakerView)

public:
	enum{ IDD = IDD_IFUZZMAKER_FORM };

// ����
public:
	CIFuzzMakerDoc* GetDocument() const;

// ����
public:

// �I�[�o�[���C�h
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialUpdate(); // �\�z��ɏ��߂ČĂяo����܂��B

// ����
public:
	virtual ~CIFuzzMakerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	enum
	{
		TAB_JPEG_SEL,
		TAB_EXIF_SEL,
		TAB_SEGMENT_ITEM_SEL,
		TAB_PATTERN_SEL,
		TAB_FUZZ_SEL,
		TAB_FUZZ_CREATE,
	};

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnTabChange( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnTabChangeing( WPARAM wParam, LPARAM lParam );
	afx_msg void OnOpAnalysisJpeg();
	afx_msg void OnUpdateOpAnalysisJpeg(CCmdUI *pCmdUI);
	afx_msg void OnOpReadPattern();
	afx_msg void OnUpdateOpReadPattern(CCmdUI *pCmdUI);
	afx_msg void OnOpViewFuzzlist();
	afx_msg void OnUpdateOpViewFuzzlist(CCmdUI *pCmdUI);
	afx_msg void OnOpCreateFuzzfile();
	afx_msg void OnUpdateOpCreateFuzzfile(CCmdUI *pCmdUI);
	afx_msg void OnOpCancelCreateFuzzfile();
	afx_msg void OnUpdateOpCancelCreateFuzzfile(CCmdUI *pCmdUI);
	afx_msg LRESULT OnStartCreateFuzz( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEndCreateFuzz( WPARAM wParam, LPARAM lParam );

	CMFCTabCtrl	m_wndTabCtrl;
	CWndResizer m_wndResizer;
	CJpegSelView* m_lpJpegSelView;
	CExifSelView* m_lpExifSelView;
	CSegmentItemSelView* m_lpSegmentItemSelView;
	CPatternSelView* m_lpPatternSelView;
	CFuzzSelView* m_lpFuzzSelView;
	CFuzzCreateView* m_lpFuzzCreateView;

	CImageList m_ImageList;

public:
};

#ifndef _DEBUG  // IFuzzMakerView.cpp �̃f�o�b�O �o�[�W����
inline CIFuzzMakerDoc* CIFuzzMakerView::GetDocument() const
   { return reinterpret_cast<CIFuzzMakerDoc*>(m_pDocument); }
#endif

