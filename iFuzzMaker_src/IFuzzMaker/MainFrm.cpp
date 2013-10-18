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


// MainFrm.cpp : CMainFrame クラスの実装
//

#include "stdafx.h"
#include "IFuzzMaker.h"

#include "MainFrm.h"
#include "IFuzzMakerView.h"
#include "IFuzzMakerDoc.h"
#include "AppMessage.h"

#include "AppConfigLoader.h"
#include "SegmentInfoLoader.h"
#include "SegmentItemInfoLoader.h"
#include "ImageFileDirectoryInfoLoader.h"
#include "FealdEntryInfoLoader.h"
#include "TagTypeInfoLoader.h"
#include "PatternGroupInfoLoader.h"
#include "PatternInfoLoader.h"

#include "JpegAnalyzer.h"
#include "ExifAnalyzer.h"
#include "SegmentAnalyzer.h"
#include "FileReader.h"

#include "EndianConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_WM_SETTINGCHANGE()
	ON_WM_GETMINMAXINFO()

	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_COUNT, &CMainFrame::OnUpdateIndicatorCount)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_SELECT, &CMainFrame::OnUpdateIndicatorSelect)

	ON_MESSAGE(WM_APP_READ_JPEG, OnReadJpeg)
	ON_MESSAGE(WM_APP_READ_GROUP, OnReadGroup)
	ON_MESSAGE(WM_APP_CREATE_FUZZ_LIST, OnCreateFuzzList)
	ON_MESSAGE(WM_APP_UPDATE_COUNT, OnUpdateCount)
	ON_MESSAGE(WM_APP_THREAD_CTRL, OnThreadCtrl)
	ON_MESSAGE(WM_APP_THREAD_STATUS, OnThreadStatus)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ステータス ライン インジケーター
	ID_INDICATOR_PROGRESS,
	ID_INDICATOR_SELECT,
	ID_INDICATOR_COUNT,
};

// CMainFrame コンストラクション/デストラクション
CMainFrame::CMainFrame()
{
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT lf;
	SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), &lf, 0);
	CMFCMenuBar::SetMenuFont(&lf);
	m_FontGUI.CreateFontIndirect(&lf);

	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// 固定値に基づいてビジュアル マネージャーと visual スタイルを設定します
	OnApplicationLook(theApp.m_nAppLook);

	if (!m_wndMenuBar.Create(this))
	{
		TRACE0("メニュー バーを作成できませんでした\n");
		return -1;      // 作成できませんでした。
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	// アクティブになったときメニュー バーにフォーカスを移動しない
	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("ステータス バーの作成に失敗しました。\n");
		return -1;      // 作成できない場合
	}
	
	m_wndStatusBar.SetPaneWidth(STATUS_BAR_SEPARATOR, 200);
	m_wndStatusBar.SetPaneWidth(STATUS_BAR_PROGRESS, 80);
	m_wndStatusBar.SetPaneWidth(STATUS_BAR_SELECT, 35);
	m_wndStatusBar.SetPaneWidth(STATUS_BAR_COUNT, 80);
	m_wndStatusBar.EnablePaneDoubleClick();

	DockPane(&m_wndMenuBar);

	ReadConfig();

	return 0;
}

// CMainFrame 診断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame メッセージ ハンドラー
void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
	}
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);


}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

BOOL CMainFrame::ReadConfig()
{
	POSITION pos = NULL;
	CString szKey;

	CAppConfigLoader AppConfigLoader;
	if( !AppConfigLoader.LoadConfig( m_FixedDatas.GetAppConfig() ) )
		return FALSE;

	CSegmentInfoLoader SegmentInfoLoader;
	if( !SegmentInfoLoader.LoadText( m_FixedDatas.GetAppConfig().GetSegmentFileName(), &m_FixedDatas.GetSegmentInfoMap() ) )
		return FALSE;

	pos = m_FixedDatas.GetSegmentInfoMap().GetStartPosition();
	CSegmentInfo *lpSegmentInfo = NULL;
	while(pos)
	{
		m_FixedDatas.GetSegmentInfoMap().GetNextAssoc( pos, szKey, lpSegmentInfo );
		if( lpSegmentInfo->IsAnalysisSegment() )
		{
			CSegmentItemInfoLoader SegmentItemInfoLoader;
			SegmentItemInfoLoader.LoadText( lpSegmentInfo->GetSegmentItemInfoFileName(), lpSegmentInfo->GetSegmentItemInfoArray(), &m_FixedDatas.GetSegmentItemInfoMap() );
		}
	}

	CImageFileDirectoryInfoLoader ImageFileDirectoryInfoLoader;
	if( !ImageFileDirectoryInfoLoader.LoadText( m_FixedDatas.GetAppConfig().GetIfdFileName(), &m_FixedDatas.GetImageFileDirectoryInfoMap() ) )
		return FALSE;

	pos = m_FixedDatas.GetImageFileDirectoryInfoMap().GetStartPosition();
	CImageFileDirectoryInfo *lpImageFileDirectoryInfo = NULL;

	while(pos)
	{
		m_FixedDatas.GetImageFileDirectoryInfoMap().GetNextAssoc( pos, szKey, lpImageFileDirectoryInfo );

		CFealdEntryInfoLoader FealdEntryInfoLoader;
		if( !FealdEntryInfoLoader.LoadText( lpImageFileDirectoryInfo->GetFealdEntryInfoFileName(), lpImageFileDirectoryInfo->GetFealdEntryInfoMap() ) )
			return FALSE;
	}

	CTagTypeInfoLoader TagTypeInfoLoader;
	if( !TagTypeInfoLoader.LoadText( m_FixedDatas.GetAppConfig().GetTagTypeFileName(), &m_FixedDatas.GetTagTypeInfoMap() ) )
		return FALSE;

	CFileReader FileReader;
	CReadBufferArray ReadBufferArray;

	return TRUE;
}

CFixedDatas* CMainFrame::GetFixedDatas()
{
	return &m_FixedDatas;
}

LRESULT CMainFrame::OnReadJpeg( WPARAM wParam, LPARAM lParam )
{
	int nSegmentCount = 0;
	CSegmentData *lpSegmentData = NULL;
	CSegmentInfo *lpSegmentInfo = NULL;

	CFileReader FileReader;
	CJpegAnalyzer JpegAnalyzer;
	CUserDatas* lpUserDatas = ((CIFuzzMakerDoc*)GetActiveDocument())->GetUserDatas();
	
	lpUserDatas->GetReadBufferArray().RemoveAll();
	if( !FileReader.ReadFile( lpUserDatas->GetJpegFileName(), lpUserDatas->GetReadBufferArray() ) )
	{
		//	エラー
		return FALSE;
	}

	//	Jpeg解析
	lpUserDatas->GetSegmentDataArray().RemoveAllWithDelete();
	if( !JpegAnalyzer.Analyze( lpUserDatas->GetReadBufferArray(), m_FixedDatas.GetSegmentInfoMap(), lpUserDatas->GetSegmentDataArray() ) )
		return FALSE;

	//	Exif解析
	for(nSegmentCount=0; nSegmentCount<lpUserDatas->GetSegmentDataArray().GetSize(); nSegmentCount++ )
	{
		lpSegmentData = lpUserDatas->GetSegmentDataArray().GetAt( nSegmentCount );
		if( lpSegmentData )
		{
			lpSegmentInfo = lpSegmentData->GetSegmentInfo();
			if( lpSegmentInfo )
			{
				if( lpSegmentInfo->GetMarker() == _T("FFE1") )
				{
					CExifAnalyzer ExifAnalyzer;
					ExifAnalyzer.Analyze( lpUserDatas->GetReadBufferArray().GetSize(), lpSegmentData, &m_FixedDatas.GetImageFileDirectoryInfoMap(), &m_FixedDatas.GetTagTypeInfoMap() );
				}
				if( lpSegmentInfo->IsAnalysisSegment() )
				{
					CSegmentAnalyzer SegmentAnalyzer;
					SegmentAnalyzer.Analyze( lpUserDatas->GetReadBufferArray().GetSize(), lpSegmentData );
				}
			}
		}
	}

	SendMessageToDescendants( WM_APP_EXIF_ANALYZED, NULL, NULL );

	return TRUE;
}

LRESULT CMainFrame::OnReadGroup( WPARAM wParam, LPARAM lParam )
{
	int nGroupCount = 0;
	CUserDatas* lpUserDatas = ((CIFuzzMakerDoc*)GetActiveDocument())->GetUserDatas();

	lpUserDatas->GetPatternGroupDataArray().RemoveAllWithDelete();

	CPatternGroupInfoLoader PatternGroupInfoLoader;
	CPatternGroupInfoArray PatternGroupInfoArray;
	if( !PatternGroupInfoLoader.LoadText( lpUserDatas->GetGroupFileName(), &PatternGroupInfoArray ) )
		return FALSE;

	for( nGroupCount=0; nGroupCount<PatternGroupInfoArray.GetSize(); nGroupCount++ )
	{
		CPatternGroupInfo *lpPatternGroupInfo = PatternGroupInfoArray.GetAt( nGroupCount );
		CPatternInfoLoader PatternInfoLoader;
		if( !PatternInfoLoader.LoadText( lpPatternGroupInfo->GetFileName(), lpPatternGroupInfo->GetPatternInfoArray() ) )
		{
		}
	}

	for( nGroupCount=0; nGroupCount<PatternGroupInfoArray.GetSize(); nGroupCount++ )
	{
		CPatternGroupInfo *lpPatternGroupInfo = PatternGroupInfoArray.GetAt( nGroupCount );
		if( lpPatternGroupInfo->GetDispFlag() )
		{
			CPatternGroupData* lpPatternGroupData = NULL;
			lpUserDatas->GetPatternGroupDataArray().AddWithNew( lpPatternGroupData );
			lpPatternGroupData->SetDispName( lpPatternGroupInfo->GetDispName() );

			for(int nPatternInfoCnt=0; nPatternInfoCnt<lpPatternGroupInfo->GetPatternInfoArray()->GetSize(); nPatternInfoCnt++ )
			{
				CPatternInfo* lpPatternInfo = lpPatternGroupInfo->GetPatternInfoArray()->GetAt(nPatternInfoCnt);
				CPatternData* lpPatternData = NULL;
				CReadBufferArray BinaryDataArray;

				CStringA szValue = CT2A(lpPatternInfo->GetValue());
				BYTE nDecValueByte = 0;
				unsigned short nDecValueShort = 0;
				unsigned int nDecValueInteger = 0;
				unsigned char* lpBuffer = NULL;

				if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_TEXT )
				{
					//
					BinaryDataArray.SetSize( szValue.GetLength() * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*szValue.GetLength()], szValue.GetBuffer(), szValue.GetLength() );
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_DEC_8 )
				{
					nDecValueByte = (BYTE)strtoul( szValue, NULL, 10 );
					BinaryDataArray.SetSize( sizeof(nDecValueByte) * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*sizeof(nDecValueByte)], &nDecValueByte, sizeof(nDecValueByte) );
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_DEC_16_LITTLE )
				{
					nDecValueShort = (unsigned short)strtoul( szValue, NULL, 10 );
					nDecValueShort = CEndianConverter::ConvertToShort( (unsigned char*)&nDecValueShort, FALSE );
					BinaryDataArray.SetSize( sizeof(nDecValueShort) * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*sizeof(nDecValueShort)], &nDecValueShort, sizeof(nDecValueShort) );
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_DEC_16_BIG )
				{
					nDecValueShort = (unsigned short)strtoul( szValue, NULL, 10 );
					nDecValueShort = CEndianConverter::ConvertToShort( (unsigned char*)&nDecValueShort, TRUE );
					BinaryDataArray.SetSize( sizeof(nDecValueShort) * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*sizeof(nDecValueShort)], &nDecValueShort, sizeof(nDecValueShort) );
					}

				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_DEC_32_LITTLE )
				{
					nDecValueInteger = (unsigned int)strtoul( szValue, NULL, 10 );
					nDecValueInteger = CEndianConverter::ConvertToInteger( (unsigned char*)&nDecValueInteger, FALSE );
					BinaryDataArray.SetSize( sizeof(nDecValueInteger) * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*sizeof(nDecValueInteger)], &nDecValueInteger, sizeof(nDecValueInteger) );
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_DEC_32_BIG )
				{
					nDecValueInteger = (unsigned int)strtoul( szValue, NULL, 10 );
					nDecValueInteger = CEndianConverter::ConvertToInteger( (unsigned char*)&nDecValueInteger, TRUE );
					BinaryDataArray.SetSize( sizeof(nDecValueInteger) * (!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()) );
					lpBuffer = BinaryDataArray.GetData();
					for( int nRepeat=0; nRepeat<(!lpPatternInfo->GetRepeat()?1:lpPatternInfo->GetRepeat()); nRepeat++ )
					{
						CopyMemory( &lpBuffer[nRepeat*sizeof(nDecValueInteger)], &nDecValueInteger, sizeof(nDecValueInteger) );
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_HEX )
				{
					//
					BinaryDataArray.SetSize( (int)(szValue.GetLength()/2) );
					for( int cCnt=0; cCnt<(int)(szValue.GetLength()/2); cCnt++ )
					{
						unsigned int nVal = strtol( szValue.Mid( cCnt*2, 2 ),NULL,16 );
						BinaryDataArray.SetAt(cCnt, nVal);
					}
				}else if( lpPatternInfo->GetDataType() == CPatternData::DATATYPE_BIN )
				{
					//
					CFileReader fl;
					if( !fl.ReadFile( lpPatternInfo->GetFileName(), BinaryDataArray ) )
						continue;
				}
				lpPatternGroupData->GetPatternDataArray()->AddWithNew( lpPatternData );

				lpPatternData->SetCheck( lpPatternInfo->GetSelectFlag() );
				lpPatternData->SetDispName( lpPatternInfo->GetDispName() );
				lpPatternData->SetDataType( lpPatternInfo->GetDataType() );
				lpPatternData->SetValue( lpPatternInfo->GetValue() );
				lpPatternData->SetRepeat( lpPatternInfo->GetRepeat() );
				lpPatternData->SetWriteMode( lpPatternInfo->GetWriteMode() );
				lpPatternData->SetFuzzArea( lpPatternInfo->GetFuzzArea() );
				lpPatternData->SetSearchField( lpPatternInfo->GetSearchField() );
				lpPatternData->SetFieldKey( lpPatternInfo->GetFieldKey() );
				lpPatternData->SetDescription( lpPatternInfo->GetDescription() );
				lpPatternData->SetBinaryDataArray( BinaryDataArray );

				if( lpPatternInfo->GetFuzzArea() == CPatternData::FUZZAREA_FILE )
				{
					TCHAR* endptr = NULL;
					int nFilePos = _tcstol( lpPatternInfo->GetFieldKey(), &endptr, 10 );
					if( _tcslen(endptr) )
						continue;
					lpPatternData->SetFilePos( nFilePos );
				}

				if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TAG ||
					lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TYPE ||
					lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_SEGMENT )
				{
					POSITION pos = NULL;
					CString szKey;
					CImageFileDirectoryInfo *lpImageFileDirectoryInfo = NULL;
					CFealdEntryInfo* lpFealdEntryInfo = NULL;
					CSegmentItemInfo* lpSegmentItemInfo = NULL;
					CTagTypeInfo* lpTagTypeInfo = NULL;
					int nFieldKey = 0;

					switch(lpPatternData->GetSearchField())
					{
					case CPatternData::SEARCHFIELD_TAG:
						pos = m_FixedDatas.GetImageFileDirectoryInfoMap().GetStartPosition();
						while(pos)
						{
							m_FixedDatas.GetImageFileDirectoryInfoMap().GetNextAssoc( pos, szKey, lpImageFileDirectoryInfo );
							if( lpImageFileDirectoryInfo->GetFealdEntryInfoMap()->Lookup( lpPatternData->GetFieldKey(), lpFealdEntryInfo ) )
								break;
						}
						break;
					case CPatternData::SEARCHFIELD_TYPE:
						nFieldKey = _tstol(lpPatternData->GetFieldKey());
						m_FixedDatas.GetTagTypeInfoMap().Lookup( nFieldKey, lpTagTypeInfo );
						break;
					case CPatternData::SEARCHFIELD_SEGMENT:
						m_FixedDatas.GetSegmentItemInfoMap().Lookup( lpPatternData->GetFieldKey(), lpSegmentItemInfo );
						break;
					}
					lpPatternData->SetFealdEntryInfo( lpFealdEntryInfo );
					lpPatternData->SetTagTypeInfo( lpTagTypeInfo );
					lpPatternData->SetSegmentItemInfo( lpSegmentItemInfo );
				}
			}
		}
	}

	SendMessageToDescendants( WM_APP_GROUP_DISP, NULL, NULL );

	return TRUE;
}

LRESULT CMainFrame::OnCreateFuzzList( WPARAM wParam, LPARAM lParam )
{
	CUserDatas* lpUserDatas = ((CIFuzzMakerDoc*)GetActiveDocument())->GetUserDatas();

	CFealdEntryDataArray CheckedFealdEntryDataArray;
	CSegmentItemDataArray CheckedSegmentItemDataArray;
	CPatternDataArray CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_COUNT];

	CheckedFealdEntryDataArray.SetAutoDelete( FALSE );
	CheckedSegmentItemDataArray.SetAutoDelete( FALSE );
	CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FIELDENTRY].SetAutoDelete( FALSE );
	CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_SEGMENT].SetAutoDelete( FALSE );
	CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FILE].SetAutoDelete( FALSE );

	lpUserDatas->GetFuzzDataArray().RemoveAllWithDelete();

	for( int nSegmentData=0; nSegmentData<lpUserDatas->GetSegmentDataArray().GetSize(); nSegmentData++ )
	{
		CSegmentData* lpSegmentData = lpUserDatas->GetSegmentDataArray().GetAt(nSegmentData);
		//	選択されているタグ取得
		for( int nExifData=0; nExifData<lpSegmentData->GetExifDataArray()->GetSize(); nExifData++ )
		{
			CExifData* lpExifData = lpSegmentData->GetExifDataArray()->GetAt(nExifData);
			for( int nImageFileDirectoryData=0; nImageFileDirectoryData<lpExifData->GetImageFileDirectoryDataArray()->GetSize(); nImageFileDirectoryData++ )
			{
				//bListGroup = FALSE;
				CImageFileDirectoryData* lpImageFileDirectoryData = lpExifData->GetImageFileDirectoryDataArray()->GetAt(nImageFileDirectoryData);
				for( int nFealdEntryData=0; nFealdEntryData<lpImageFileDirectoryData->GetFealdEntryDataArray()->GetSize(); nFealdEntryData++ )
				{
					CFealdEntryData* lpFealdEntryData = lpImageFileDirectoryData->GetFealdEntryDataArray()->GetAt(nFealdEntryData);
					{
						if( lpFealdEntryData->GetCheck() )
						{
							CheckedFealdEntryDataArray.Add( lpFealdEntryData );
						}
					}
				}
			}
		}
		//	選択されているセグメントパターンを取得
		if( lpSegmentData->GetSegmentInfo() && lpSegmentData->GetSegmentInfo()->IsAnalysisSegment() )
		{
			for( int nSegmentItemData=0; nSegmentItemData<lpSegmentData->GetSegmentItemDataArray()->GetSize(); nSegmentItemData++ )
			{
				CSegmentItemData *lpSegmentItemData = lpSegmentData->GetSegmentItemDataArray()->GetAt( nSegmentItemData );
				if( lpSegmentItemData->GetCheck() )
				{
					CheckedSegmentItemDataArray.Add( lpSegmentItemData );
				}
			}
		}
	}

	//	選択されているパターンを取得
	for( int nPatternGroupData=0; nPatternGroupData<lpUserDatas->GetPatternGroupDataArray().GetSize(); nPatternGroupData++ )
	{
		CPatternGroupData* lpPatternGroupData = lpUserDatas->GetPatternGroupDataArray().GetAt( nPatternGroupData );
		for( int nPatternData=0; nPatternData<lpPatternGroupData->GetPatternDataArray()->GetSize(); nPatternData++ )
		{
			CPatternData* lpPatternData = lpPatternGroupData->GetPatternDataArray()->GetAt(nPatternData);
			if( lpPatternData->GetCheck() )
			{
				if( lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_SEGMENT )
					CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_SEGMENT].Add( lpPatternData );
				else if( lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_FILE )
					CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FILE].Add( lpPatternData );
				else
					CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FIELDENTRY].Add( lpPatternData );
			}
		}
	}

	for( int nFealdEntryData=0; nFealdEntryData<CheckedFealdEntryDataArray.GetSize(); nFealdEntryData++ )
	{
		CFealdEntryData* lpFealdEntryData = CheckedFealdEntryDataArray.GetAt( nFealdEntryData );
		for( int nPatternData=0; nPatternData<CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FIELDENTRY].GetSize(); nPatternData++ )
		{
			CPatternData* lpPatternData = CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FIELDENTRY].GetAt( nPatternData );
			//	タグ指定あり
			if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TAG )
			{
				if( lpPatternData->GetFieldKey() != lpFealdEntryData->GetTagID() )
				{
					continue;
				}
			}
			//	タイプ指定あり
			if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_TYPE )
			{
				if( _tstol(lpPatternData->GetFieldKey()) != lpFealdEntryData->GetType() )
				{
					continue;
				}
			}
			CFuzzData* lpFuzzData = NULL;
			lpUserDatas->GetFuzzDataArray().AddWithNew( lpFuzzData );
			lpFuzzData->SetFuzzDataType( CFuzzData::FUZZDATA_TYPE_FIELDENTRY );
			lpFuzzData->SetFealdEntryData( lpFealdEntryData );
			lpFuzzData->SetPatternData( lpPatternData );

		}
	}

	for( int nSegmentItemData=0; nSegmentItemData<CheckedSegmentItemDataArray.GetSize(); nSegmentItemData++ )
	{
		CSegmentItemData *lpSegmentItemData = CheckedSegmentItemDataArray.GetAt( nSegmentItemData );
		for( int nPatternData=0; nPatternData<CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_SEGMENT].GetSize(); nPatternData++ )
		{
			CPatternData* lpPatternData = CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_SEGMENT].GetAt( nPatternData );
			//	指定あり
			if( lpPatternData->GetSearchField() == CPatternData::SEARCHFIELD_SEGMENT )
			{
				if( lpPatternData->GetFieldKey() != lpSegmentItemData->GetSegmentItemInfo()->GetItemTag() )
				{
					continue;
				}
			}
			CFuzzData* lpFuzzData = NULL;
			lpUserDatas->GetFuzzDataArray().AddWithNew( lpFuzzData );
			lpFuzzData->SetFuzzDataType( CFuzzData::FUZZDATA_TYPE_SEGMENT );
			lpFuzzData->SetSegmentItemData( lpSegmentItemData );
			lpFuzzData->SetPatternData( lpPatternData );
		}
	}

	for( int nPatternData=0; nPatternData<CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FILE].GetSize(); nPatternData++ )
	{
		CPatternData* lpPatternData = CheckedPatternDataArray[CFuzzData::FUZZDATA_TYPE_FILE].GetAt( nPatternData );

		CFuzzData* lpFuzzData = NULL;
		lpUserDatas->GetFuzzDataArray().AddWithNew( lpFuzzData );
		lpFuzzData->SetFuzzDataType( CFuzzData::FUZZDATA_TYPE_FILE );
		lpFuzzData->SetPatternData( lpPatternData );
	}

	SendMessageToDescendants( WM_APP_FUZZ_LIST_DISP, NULL, NULL );

	return TRUE;
}

LRESULT CMainFrame::OnUpdateCount( WPARAM wParam, LPARAM lParam )
{
	if( wParam )
	{
		CString szBuffer;
		szBuffer.Format( _T("%d"), HIWORD(lParam) );
		m_wndStatusBar.SetPaneText( STATUS_BAR_SELECT, szBuffer );
		szBuffer.Format( _T("%d/%d"), LOWORD(lParam), wParam );
		m_wndStatusBar.SetPaneText( STATUS_BAR_COUNT, szBuffer );
	}else{
		m_wndStatusBar.SetPaneText( STATUS_BAR_SELECT, _T("") );
		m_wndStatusBar.SetPaneText( STATUS_BAR_COUNT, _T("") );
	}
	return TRUE;
}

LRESULT CMainFrame::OnThreadCtrl( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
	{
	case THREAD_CTRL_START:
		SendMessageToDescendants( WM_APP_START_CREATE_FUZZ, NULL, NULL );
		m_FuzzCreateThread.CreateThread( this->m_hWnd, (HWND)lParam, &m_FixedDatas, ((CIFuzzMakerDoc*)GetActiveDocument())->GetUserDatas() );
		break;
	case THREAD_CTRL_CANCEL:
		m_FuzzCreateThread.Cancel();
		break;
	}
	return TRUE;
}

LRESULT CMainFrame::OnThreadStatus( WPARAM wParam, LPARAM lParam )
{
	switch( wParam )
	{
	case THREAD_STATUS_CREATE_ERROR:
		SendMessageToDescendants( WM_APP_END_CREATE_FUZZ, NULL, NULL );
		break;
	case THREAD_STATUS_MAKEFOLDER_ERROR:
		SendMessageToDescendants( WM_APP_END_CREATE_FUZZ, NULL, lParam );
		break;
	case THREAD_STATUS_END:
		SendMessageToDescendants( WM_APP_END_CREATE_FUZZ, NULL, lParam );
		break;
	}
	return TRUE;
}

void CMainFrame::OnUpdateIndicatorCount(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

void CMainFrame::OnUpdateIndicatorSelect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable( TRUE );
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.dwExStyle &= ~(WS_EX_CLIENTEDGE|WS_EX_WINDOWEDGE|WS_EX_STATICEDGE); 

	return CFrameWndEx::PreCreateWindow(cs);
}


void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 480;
	lpMMI->ptMinTrackSize.y = 320;

	CFrameWndEx::OnGetMinMaxInfo(lpMMI);
}

void CMainFrame::OnClose()
{
	CUserDatas* lpUserDatas = ((CIFuzzMakerDoc*)GetActiveDocument())->GetUserDatas();
	if( lpUserDatas->GetFuzzCreateing() )
	{
		return;
	}
	CFrameWndEx::OnClose();
}
