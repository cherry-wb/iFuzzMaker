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

// MainFrm.h : CMainFrame �N���X�̃C���^�[�t�F�C�X
//
#pragma once
#include "FixedDatas.h"
#include "FuzzCreateThread.h"

class CMainFrame : public CFrameWndEx
{
	
protected: // �V���A��������̂ݍ쐬���܂��B
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	CFixedDatas* GetFixedDatas();

// ����
public:

// �I�[�o�[���C�h
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	enum
	{
		STATUS_BAR_SEPARATOR = 0,
		STATUS_BAR_PROGRESS = 1,
		STATUS_BAR_SELECT = 2,
		STATUS_BAR_COUNT = 3,
	};

protected:  // �R���g���[�� �o�[�p�����o�[
	CMFCMenuBar       m_wndMenuBar;
	CMFCStatusBar     m_wndStatusBar;
	CMFCToolBarImages m_UserImages;

// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIndicatorCount(CCmdUI *pCmdUI);
	afx_msg void OnUpdateIndicatorSelect(CCmdUI *pCmdUI);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);

	//	�v���C�x�[�g���b�Z�[�W
	afx_msg LRESULT OnReadJpeg( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnReadGroup( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnCreateFuzzList( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnUpdateCount( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT OnThreadCtrl( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnThreadStatus( WPARAM wParam, LPARAM lParam );

	DECLARE_MESSAGE_MAP()

	BOOL ReadConfig();

	CFixedDatas m_FixedDatas;
	CFont m_FontGUI;

	CFuzzCreateThread m_FuzzCreateThread;

public:
	afx_msg void OnClose();
};


