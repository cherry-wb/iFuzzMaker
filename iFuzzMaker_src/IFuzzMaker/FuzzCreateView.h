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

#pragma once

#include "TabChildView.h"
#include "WndResizer.h"
#include "FileBrowseCtrl.h"
#include "CreateLogList.h"

// CFuzzCreateView �t�H�[�� �r���[
class CFuzzCreateView : public CTabChildView
{
	DECLARE_DYNCREATE(CFuzzCreateView)

protected:
	CFuzzCreateView();           // ���I�����Ŏg�p����� protected �R���X�g���N�^�[
	virtual ~CFuzzCreateView();

public:
	enum { IDD = IDD_FUZZ_CREATE_VIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	virtual void OnInitialView();
	virtual BOOL OnUpdateStatusBar( int nTotal, int nChecked, int nSelected );

	DECLARE_MESSAGE_MAP()
	afx_msg void OnClickedStartButton();
	afx_msg void OnClickedStopButton();
	afx_msg void OnOpCreateFuzzfile();
	afx_msg void OnUpdateOpCreateFuzzfile(CCmdUI *pCmdUI);
	afx_msg void OnOpCancelCreateFuzzfile();
	afx_msg void OnUpdateOpCancelCreateFuzzfile(CCmdUI *pCmdUI);
	afx_msg LRESULT OnStartCreateFuzz( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnEndCreateFuzz( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnCreateFuzzStatus( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnExifAnalyzed( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnGroupDisp( WPARAM wParam, LPARAM lParam );

	BOOL m_bDoDataExchange;

	BOOL CreateFuzzfile();
	BOOL CancelCreateFuzzfile();

	CWndResizer m_wndResizer;
	CFileBrowseCtrl m_wndOutputFolderBrowse;
	CEdit m_wndDiscriptionEdit;
	CCreateLogList m_wndCreateLogList;
	CProgressCtrl m_wndCreateProgress;
	CStatic m_wndCountStatic;
	CMFCButton m_wndStartButton;
	CMFCButton m_wndStopButton;

};


