//================================================================================
//  独立行政法人情報処理推進機構 (IPA)
//  - Information-technology Promotion Agency, Japan -
//
//                                                    独立行政法人情報処理推進機構
//                                                   技術本部 セキュリティセンター
//                                                情報セキュリティ技術ラボラトリー
//
//      -- JPEG テスト支援ツール iFuzzMaker  --
//                                                                Date：2013/07/30
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

// FuzzCreateView.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "IFuzzMakerDoc.h"
#include "FuzzCreateView.h"
#include "AppMessage.h"
#include "MainFrm.h"

// CFuzzCreateView
IMPLEMENT_DYNCREATE(CFuzzCreateView, CTabChildView)

CFuzzCreateView::CFuzzCreateView()
	: CTabChildView(CFuzzCreateView::IDD)
{
	m_bDoDataExchange = FALSE;
}

CFuzzCreateView::~CFuzzCreateView()
{
}

void CFuzzCreateView::DoDataExchange(CDataExchange* pDX)
{
	CTabChildView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_OUTPUT_FOLDER_BROWSE, m_wndOutputFolderBrowse);
	DDX_Control(pDX, IDC_DISCRIPTION_EDIT, m_wndDiscriptionEdit);
	DDX_Control(pDX, IDC_CREATE_LOG_LIST, m_wndCreateLogList);
	DDX_Control(pDX, IDC_CREATE_PROGRESS, m_wndCreateProgress);
	DDX_Control(pDX, IDC_START_BUTTON, m_wndStartButton);
	DDX_Control(pDX, IDC_STOP_BUTTON, m_wndStopButton);
	DDX_Control(pDX, IDC_COUNT_STATIC, m_wndCountStatic);

	if( !m_bDoDataExchange )
	{
		m_bDoDataExchange = TRUE;
		m_wndOutputFolderBrowse.EnableFolderBrowseButton();
		m_wndOutputFolderBrowse.SetWindowText( ((CMainFrame*)AfxGetMainWnd())->GetFixedDatas()->GetAppConfig().GetFuzzOutputFolder() );
		m_wndDiscriptionEdit.SetLimitText(1024);
		m_wndCreateLogList.InitCtrl();
	}

	m_wndStopButton.EnableWindow( FALSE );
	m_wndCountStatic.SetWindowText( _T("") );
}

BEGIN_MESSAGE_MAP(CFuzzCreateView, CTabChildView)
	ON_BN_CLICKED(IDC_START_BUTTON, &CFuzzCreateView::OnClickedStartButton)
	ON_BN_CLICKED(IDC_STOP_BUTTON, &CFuzzCreateView::OnClickedStopButton)
	ON_MESSAGE(WM_APP_START_CREATE_FUZZ, OnStartCreateFuzz)
	ON_MESSAGE(WM_APP_END_CREATE_FUZZ, OnEndCreateFuzz)
	ON_MESSAGE(WM_APP_CREATE_FUZZ_STATUS, OnCreateFuzzStatus)
	ON_MESSAGE(WM_APP_EXIF_ANALYZED, OnExifAnalyzed)
	ON_MESSAGE(WM_APP_GROUP_DISP, OnGroupDisp)
	ON_COMMAND(ID_OP_CREATE_FUZZFILE, &CFuzzCreateView::OnOpCreateFuzzfile)
	ON_UPDATE_COMMAND_UI(ID_OP_CREATE_FUZZFILE, &CFuzzCreateView::OnUpdateOpCreateFuzzfile)
	ON_COMMAND(ID_OP_CANCEL_CREATE_FUZZFILE, &CFuzzCreateView::OnOpCancelCreateFuzzfile)
	ON_UPDATE_COMMAND_UI(ID_OP_CANCEL_CREATE_FUZZFILE, &CFuzzCreateView::OnUpdateOpCancelCreateFuzzfile)
END_MESSAGE_MAP()


// CFuzzCreateView 診断
#ifdef _DEBUG
void CFuzzCreateView::AssertValid() const
{
	CTabChildView::AssertValid();
}

#ifndef _WIN32_WCE
void CFuzzCreateView::Dump(CDumpContext& dc) const
{
	CTabChildView::Dump(dc);
}
#endif
#endif //_DEBUG

// CFuzzCreateView メッセージ ハンドラー
void CFuzzCreateView::OnInitialView()
{
	m_wndResizer.Hook(this,m_sizeInitWnd);
	
	m_wndResizer.SetAnchor( IDC_OUTPUT_FOLDER_BROWSE, ANCHOR_LEFT | ANCHOR_RIGHT| ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_DISCRIPTION_EDIT, ANCHOR_LEFT | ANCHOR_RIGHT| ANCHOR_TOP );
	m_wndResizer.SetAnchor( IDC_CREATE_LOG_LIST, ANCHOR_ALL );
	m_wndResizer.SetAnchor( IDC_COUNT_STATIC, ANCHOR_LEFT | ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_CREATE_PROGRESS, ANCHOR_LEFT | ANCHOR_RIGHT| ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_START_BUTTON, ANCHOR_RIGHT| ANCHOR_BOTTOM );
	m_wndResizer.SetAnchor( IDC_STOP_BUTTON, ANCHOR_RIGHT| ANCHOR_BOTTOM );

	m_wndResizer.InvokeOnResized();

}

BOOL CFuzzCreateView::OnUpdateStatusBar( int nTotal, int nChecked, int nSelected )
{
	BOOL bEnable = GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() && !GetDocument()->GetUserDatas()->GetFuzzCreateing();
	m_wndStartButton.EnableWindow( bEnable );
	m_wndStopButton.EnableWindow( GetDocument()->GetUserDatas()->GetFuzzCreateing() );
	return FALSE;
}

void CFuzzCreateView::OnClickedStartButton()
{
	CreateFuzzfile();
}

void CFuzzCreateView::OnClickedStopButton()
{
	CancelCreateFuzzfile();
}

LRESULT CFuzzCreateView::OnStartCreateFuzz( WPARAM wParam, LPARAM lParam )
{
	CString szBuffer;
	CSystemTime st;
	st.Get();
	szBuffer.Format( _T("%04d/%02d/%02d %02d:%02d:%02d.%03d"), 
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds );
	m_wndCreateLogList.InsertItem( 0, _T(""), CCreateLogList::ICON_INFO, NULL );
	m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_DATETIME, szBuffer );
	m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_STATUS, _T("処理開始") );

	return TRUE;
}

LRESULT CFuzzCreateView::OnEndCreateFuzz( WPARAM wParam, LPARAM lParam )
{
	CString szBuffer;
	CSystemTime st;
	st.Get();
	szBuffer.Format( _T("%04d/%02d/%02d %02d:%02d:%02d.%03d"), 
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds );
	m_wndCreateLogList.InsertItem( 0, _T(""), lParam?CCreateLogList::ICON_INFO:CCreateLogList::ICON_STATUS_END, NULL );
	m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_DATETIME, szBuffer );
	m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_STATUS, lParam?_T("処理中断"):_T("処理完了") );

	m_wndStartButton.EnableWindow( TRUE );
	m_wndStopButton.EnableWindow( FALSE );

	GetDocument()->GetUserDatas()->SetFuzzCreateing( FALSE );
	return TRUE;
}

LRESULT CFuzzCreateView::OnCreateFuzzStatus( WPARAM wParam, LPARAM lParam )
{
	int nItem = 0;
	CString szBuffer;
	LVFINDINFO info;
	CFuzzData *lpFuzzData = (CFuzzData*)lParam;
	switch(wParam)
	{
	case CREATE_FUZZ_STATUS_COUNTER:
		m_wndCreateProgress.SetPos( lpFuzzData->GetCounter()+1 );
		szBuffer.Format( _T("%d/%d"), lpFuzzData->GetCounter()+1, GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() );
		m_wndCountStatic.SetWindowText( szBuffer );
		m_wndCreateLogList.InsertItem( 0, _T(""), CCreateLogList::ICON_NONE, NULL );
		m_wndCreateLogList.SetItemData( 0, (DWORD_PTR)lpFuzzData );

		szBuffer.Format( _T("%04d/%02d/%02d %02d:%02d:%02d.%03d"), 
			lpFuzzData->GetCreateDateTime().wYear,
			lpFuzzData->GetCreateDateTime().wMonth,
			lpFuzzData->GetCreateDateTime().wDay,
			lpFuzzData->GetCreateDateTime().wHour,
			lpFuzzData->GetCreateDateTime().wMinute,
			lpFuzzData->GetCreateDateTime().wSecond,
			lpFuzzData->GetCreateDateTime().wMilliseconds );
		m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_DATETIME, szBuffer );
		m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_STATUS, _T("出力中") );

		switch(lpFuzzData->GetFuzzDataType())
		{
		case CFuzzData::FUZZDATA_TYPE_FIELDENTRY:
			m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_TAG, lpFuzzData->GetFealdEntryData()->GetTagID() );
			break;
		case CFuzzData::FUZZDATA_TYPE_SEGMENT:
			m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_TAG, lpFuzzData->GetSegmentItemData()->GetMarkerName() );
			break;
		case CFuzzData::FUZZDATA_TYPE_FILE:
			m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_TAG, _T("File") );
			break;
		}

		m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_PATTERN, lpFuzzData->GetPatternData()->GetDispName() );
		break;
	case CREATE_FUZZ_STATUS_FILE:
		SecureZeroMemory( &info, sizeof(LVFINDINFO) );
		info.flags = LVFI_PARAM;
		info.lParam = (LPARAM)lpFuzzData;
		nItem = m_wndCreateLogList.FindItem( &info, -1 );
		m_wndCreateLogList.SetItemImage( 0, CCreateLogList::ICON_CHECK );
		m_wndCreateLogList.SetItemText( nItem, CCreateLogList::COL_FILENAME, lpFuzzData->GetFileName() );
		m_wndCreateLogList.SetItemText( nItem, CCreateLogList::COL_STATUS, _T("完了") );
		break;
	case CREATE_FUZZ_STATUS_SKIP:
		m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_STATUS, _T("Skip") );
		m_wndCreateLogList.SetItemText( nItem, CCreateLogList::COL_FILENAME, _T("生成できないルール") );
		break;
	case CREATE_FUZZ_STATUS_FILE_ERROR:
		m_wndCreateLogList.SetItemImage( 0, CCreateLogList::ICON_STATUS_ERROR );
		m_wndCreateLogList.SetItemText( 0, CCreateLogList::COL_STATUS, _T("エラー") );
		break;
	}
	return TRUE;
}


void CFuzzCreateView::OnOpCreateFuzzfile()
{
	CreateFuzzfile();
}


void CFuzzCreateView::OnUpdateOpCreateFuzzfile(CCmdUI *pCmdUI)
{
	BOOL bEnable = GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() && !GetDocument()->GetUserDatas()->GetFuzzCreateing();
	m_wndStartButton.EnableWindow( bEnable );
	pCmdUI->Enable(bEnable);
}


void CFuzzCreateView::OnOpCancelCreateFuzzfile()
{
	CancelCreateFuzzfile();
}


void CFuzzCreateView::OnUpdateOpCancelCreateFuzzfile(CCmdUI *pCmdUI)
{
	m_wndStopButton.EnableWindow( GetDocument()->GetUserDatas()->GetFuzzCreateing() );
	pCmdUI->Enable( GetDocument()->GetUserDatas()->GetFuzzCreateing() );
}

BOOL CFuzzCreateView::CreateFuzzfile()
{
	CString szFolderName;
	CString szDiscription;

	m_wndOutputFolderBrowse.GetWindowText( szFolderName );

	if( !PathFileExists( szFolderName ) )
	{
		MessageBox( _T("フォルダーが存在しません"), _T("エラー"), MB_ICONHAND );
		return FALSE;
	}
	m_wndDiscriptionEdit.GetWindowText( szDiscription );

	GetDocument()->GetUserDatas()->SetDiscription( szDiscription );
	GetDocument()->GetUserDatas()->SetOutputFolder( szFolderName );
	GetDocument()->GetUserDatas()->GetCreateFuzzTime().Get();

	CString szCount;
	szCount.Format( _T("0/%d"), GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() );
	m_wndCountStatic.SetWindowText( szCount );
	m_wndCreateLogList.ClearList();

	m_wndCreateProgress.SetPos( 0 );
	m_wndCreateProgress.SetRange32( 0, GetDocument()->GetUserDatas()->GetCheckedFuzzDataCount() );
	m_wndCreateProgress.SetStep( 1 );

	m_wndStopButton.EnableWindow( TRUE );
	m_wndStartButton.EnableWindow( FALSE );

	AfxGetMainWnd()->PostMessage( WM_APP_THREAD_CTRL, THREAD_CTRL_START, (LPARAM)this->m_hWnd );

	GetDocument()->GetUserDatas()->SetFuzzCreateing( TRUE );
	return TRUE;
}

BOOL CFuzzCreateView::CancelCreateFuzzfile()
{
	AfxGetMainWnd()->PostMessage( WM_APP_THREAD_CTRL, THREAD_CTRL_CANCEL, NULL );
	return FALSE;
}

LRESULT CFuzzCreateView::OnExifAnalyzed( WPARAM wParam, LPARAM lParam )
{
	m_wndStartButton.EnableWindow( FALSE );
	m_wndStopButton.EnableWindow( FALSE );
	return TRUE;
}

LRESULT CFuzzCreateView::OnGroupDisp( WPARAM wParam, LPARAM lParam )
{
	m_wndStartButton.EnableWindow( FALSE );
	m_wndStopButton.EnableWindow( FALSE );
	return TRUE;
}
