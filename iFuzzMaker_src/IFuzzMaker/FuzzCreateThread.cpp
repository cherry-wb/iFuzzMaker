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

// FuzzCreateThread.cpp : 実装ファイル
//

#include "stdafx.h"
#include "IFuzzMaker.h"
#include "FuzzCreateThread.h"
#include "AppMessage.h"
#include <locale.h>

// CFuzzCreateThread
IMPLEMENT_DYNCREATE(CFuzzCreateThread, CWinThread)

CFuzzCreateThread::CFuzzCreateThread()
{
	m_bAutoDelete = FALSE;

	m_hMainWnd = NULL;
	m_hCounterWnd = NULL;
	m_bCancel = FALSE;

	m_lpUserDatas = NULL;
	m_lpFixedDatas = NULL;
}

CFuzzCreateThread::~CFuzzCreateThread()
{
	m_lpUserDatas = NULL;
}

BOOL CFuzzCreateThread::InitInstance()
{
	m_bCancel = FALSE;
	return TRUE;
}

int CFuzzCreateThread::ExitInstance()
{
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CFuzzCreateThread, CWinThread)
END_MESSAGE_MAP()

// CFuzzCreateThread メッセージ ハンドラー
int CFuzzCreateThread::Run()
{

	if( m_lpUserDatas )
	{
		int nOutputCount = 1;
		int nCheckCount = 0;
		CString szFileName;
		CString szFilePath;

		m_ReportArray.RemoveAll();

		//	出力先フォルダ
		m_szOutputFolder.Format( _T("%s\\%04d%02d%02d%02d%02d%02d%03d\\"), 
								m_lpUserDatas->GetOutputFolder(), 
								m_lpUserDatas->GetCreateFuzzTime().wYear,
								m_lpUserDatas->GetCreateFuzzTime().wMonth,
								m_lpUserDatas->GetCreateFuzzTime().wDay,
								m_lpUserDatas->GetCreateFuzzTime().wHour,
								m_lpUserDatas->GetCreateFuzzTime().wMinute,
								m_lpUserDatas->GetCreateFuzzTime().wSecond,
								m_lpUserDatas->GetCreateFuzzTime().wMilliseconds );

		if( SHCreateDirectoryEx( NULL, m_szOutputFolder, NULL ) == ERROR_SUCCESS )
		{
			//	ログファイル Open
			LogOpen();

			for( int nFuzzData=0; nFuzzData<m_lpUserDatas->GetFuzzDataArray().GetSize(); nFuzzData++ )
			{
				if( m_bCancel )
					break;

				CFuzzData* lpFuzzData = m_lpUserDatas->GetFuzzDataArray().GetAt( nFuzzData );
				if( !lpFuzzData->GetCheck() )
					continue;

				lpFuzzData->GetCreateDateTime().Get();
				lpFuzzData->SetCounter( nCheckCount );
				szFileName.Format( _T("%08d.jpg"), nOutputCount );
				szFilePath.Format( _T("%s%s"), m_szOutputFolder, szFileName );
				lpFuzzData->SetFileName( szFileName );
				lpFuzzData->SetFilePath( szFilePath );
				nCheckCount++;

				PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_COUNTER, (LPARAM)lpFuzzData );

				//	どの部分を書き替えるのか
				CPatternData *lpPatternData = lpFuzzData->GetPatternData();
				CFealdEntryData *lpFealdEntryData = lpFuzzData->GetFealdEntryData();
				CSegmentItemData *lpSegmentItemData = lpFuzzData->GetSegmentItemData();

				CTagData *lpTagData = NULL;
				if( lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_TAG ||
					lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_TYPE ||
					lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_COUNT ||
					lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_VALUE ||
					lpPatternData->GetFuzzArea() == CPatternData::FUZZAREA_OFFSET)
				{
					if( !lpFealdEntryData->GetTagDataArray()->GetSize() )
					{
						continue;
					}
					lpTagData = lpFealdEntryData->GetTagDataArray()->GetAt(0);
				}

				int nReWritePos = 0;
				int nReWriteSize = 0;

				switch(lpPatternData->GetFuzzArea())
				{
				case CPatternData::FUZZAREA_TAG:
					nReWritePos = lpFealdEntryData->GetOffset();
					nReWriteSize = 2;
					break;
				case CPatternData::FUZZAREA_TYPE:
					nReWritePos = lpFealdEntryData->GetOffset() + 2;
					nReWriteSize = 2;
					break;
				case CPatternData::FUZZAREA_COUNT:
					nReWritePos = lpFealdEntryData->GetOffset() + 4;
					nReWriteSize = 4;
					break;
				case CPatternData::FUZZAREA_VALUE:
					nReWritePos = lpTagData->GetOffset();
					nReWriteSize = lpTagData->GetSize();
					break;
				case CPatternData::FUZZAREA_OFFSET:
					nReWritePos = lpFealdEntryData->GetOffset() + 8;
					nReWriteSize = 4;
					break;
				case CPatternData::FUZZAREA_SEGMENT:
					nReWritePos = lpSegmentItemData->GetOffset();
					nReWriteSize = lpSegmentItemData->GetSize();
					break;
				case CPatternData::FUZZAREA_FILE:
					nReWritePos = lpPatternData->GetFilePos()<0||lpPatternData->GetFilePos()>m_lpUserDatas->GetReadBufferArray().GetSize()?m_lpUserDatas->GetReadBufferArray().GetSize():lpPatternData->GetFilePos();
					nReWriteSize = 1;
					break;
				}

				//	繰り返し回数
				int nRepeatCount = lpPatternData->GetRepeat();
				//	ファズデータのサイズ
				int nFizzDataSize = lpPatternData->GetBinaryDataArray()->GetSize();

				//	何回繰り返せるか計算
				nRepeatCount = 1;
				if( lpPatternData->GetRepeat() == 0 )
				{
					nRepeatCount = nReWriteSize / nFizzDataSize;
					if( nRepeatCount == 0 )
					{
						PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_SKIP, (LPARAM)lpFuzzData );
						continue;
					}
				}
				int nFuzzBufferSize = nFuzzBufferSize = nFizzDataSize * nRepeatCount;

				switch(lpPatternData->GetWriteMode())
				{
				case CPatternData::WRITEMODE_REPLACE:
					//	置換の場合
					TRACE( _T("Mode[置換] nReWritePos[%d] nReWriteSize[%d] nFuzzBufferSize[%d]\n"),nReWritePos, nReWriteSize, nFuzzBufferSize );
					break;
				case CPatternData::WRITEMODE_OVERWRITE:
					//	上書の場合
					nReWriteSize = nFuzzBufferSize;
					TRACE( _T("Mode[上書] nReWritePos[%d] nReWriteSize[%d] nFuzzBufferSize[%d]\n"),nReWritePos, nReWriteSize, nFuzzBufferSize );
					break;
				case CPatternData::WRITEMODE_INSERT:
					//	挿入の場合
					nReWriteSize = 0;
					TRACE( _T("Mode[挿入] nReWritePos[%d] nReWriteSize[%d] nFuzzBufferSize[%d]\n"),nReWritePos, nReWriteSize, nFuzzBufferSize );
					break;
				}

				CUCharArray FuzzBufferArray;
				FuzzBufferArray.SetSize( nFuzzBufferSize );
				unsigned char *lpFuzzBuffer = FuzzBufferArray.GetData();

				for( int nRepeat=0; nRepeat<nRepeatCount; nRepeat++ )
				{
					CopyMemory( &lpFuzzBuffer[nRepeat*nFizzDataSize], lpPatternData->GetBinaryDataArray()->GetData(), nFizzDataSize );
				}

				if( WriteFuzz( nReWritePos, nReWriteSize, &m_lpUserDatas->GetReadBufferArray(), &FuzzBufferArray, lpFuzzData ) )
				{
					PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_FILE, (LPARAM)lpFuzzData );
				}
				nOutputCount++;

				LogWrite( lpFuzzData );
			}
			//	ログファイル Close
			LogClose();
		}else{
			PostMessage( m_hMainWnd, WM_APP_THREAD_STATUS, THREAD_STATUS_MAKEFOLDER_ERROR, NULL );
		}
	}

	PostMessage( m_hMainWnd, WM_APP_THREAD_STATUS, THREAD_STATUS_END, m_bCancel );
	PostQuitMessage(0);
	m_hThread = NULL;
	return CWinThread::Run();

}

void CFuzzCreateThread::Cancel()
{
	m_bCancel = TRUE;
	WaitForSingleObject( m_hThread, INFINITE );
}

BOOL CFuzzCreateThread::CreateThread( HWND hMainWnd, HWND hCounterWnd, CFixedDatas* lpFixedDatas, CUserDatas* lpUserDatas )
{
	m_hMainWnd = hMainWnd;
	m_hCounterWnd = hCounterWnd;
	m_lpUserDatas = lpUserDatas;
	m_lpFixedDatas = lpFixedDatas;
	BOOL bRet = CWinThread::CreateThread();
	if( !bRet )
		PostMessage( m_hMainWnd, WM_APP_THREAD_STATUS, THREAD_STATUS_CREATE_ERROR, NULL );
	return bRet;
}

BOOL CFuzzCreateThread::WriteFuzz( int nReWritePos, int nReWriteSize, CReadBufferArray* lpReadBufferArray, CUCharArray *lpFuzzBufferArray, CFuzzData* lpFuzzData )
{
	CString szErrorMessage;
	CFile lf;
	CFileException ex;
	if( !lf.Open( lpFuzzData->GetFilePath(), CFile::modeWrite | CFile::modeCreate | CFile::typeBinary, &ex ) )
	{
		ex.GetErrorMessage( szErrorMessage.GetBufferSetLength(256), 255 );
		lpFuzzData->SetErrorMessage( szErrorMessage );
		PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_FILE_ERROR, (LPARAM)lpFuzzData );
		return FALSE;
	}
	TRY{
		lf.Write( lpReadBufferArray->GetData(), nReWritePos );
		lf.Write( lpFuzzBufferArray->GetData(), lpFuzzBufferArray->GetSize() );

		if( nReWritePos+nReWriteSize < lpReadBufferArray->GetSize() )
			lf.Write( (lpReadBufferArray->GetData()+nReWritePos+nReWriteSize), lpReadBufferArray->GetSize()-(nReWritePos+nReWriteSize) );
	}CATCH( CFileException, e )
	{
		e->GetErrorMessage( szErrorMessage.GetBufferSetLength(256), 255 );
		lpFuzzData->SetErrorMessage( szErrorMessage );
		PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_FILE_ERROR, (LPARAM)lpFuzzData );
		return FALSE;
	}CATCH( CException, e )
	{
		e->GetErrorMessage( szErrorMessage.GetBufferSetLength(256), 255 );
		lpFuzzData->SetErrorMessage( szErrorMessage );
		PostMessage( m_hCounterWnd, WM_APP_CREATE_FUZZ_STATUS, CREATE_FUZZ_STATUS_FILE_ERROR, (LPARAM)lpFuzzData );
		return FALSE;
	}
	END_CATCH
	return TRUE;
}

BOOL CFuzzCreateThread::LogOpen()
{
	CFileException ex;
	CString szFileName;
	CString szBuffer;

	_tsetlocale( LC_ALL, _T("japanese") );

	szFileName.Format( _T("%sTestData.log"), m_szOutputFolder );
	if( !m_flTestDataLog.Open( szFileName, CFile::modeCreate | CFile::modeWrite, &ex ) )
	{
		return FALSE;
	}

	szBuffer.Format( _T("元ファイル名\t%s\n"), m_lpUserDatas->GetJpegFileName() );
	m_flTestDataLog.WriteString( szBuffer );
	m_flTestDataLog.Flush();

	szBuffer.Format( _T("出力日時\t%04d/%02d/%02d %02d:%02d:%02d.%03d\n"), 
					m_lpUserDatas->GetCreateFuzzTime().wYear,
					m_lpUserDatas->GetCreateFuzzTime().wMonth,
					m_lpUserDatas->GetCreateFuzzTime().wDay,
					m_lpUserDatas->GetCreateFuzzTime().wHour,
					m_lpUserDatas->GetCreateFuzzTime().wMinute,
					m_lpUserDatas->GetCreateFuzzTime().wSecond,
					m_lpUserDatas->GetCreateFuzzTime().wMilliseconds );
	m_flTestDataLog.WriteString( szBuffer );
	m_flTestDataLog.Flush();

	szBuffer.Format( _T("備考\t%s\n\n"), m_lpUserDatas->GetDiscription() );
	m_flTestDataLog.WriteString( szBuffer );
	m_flTestDataLog.Flush();

	szBuffer.Format( _T("マーカー/タグ\t名称\t書換モード\t変更箇所\tルール名\t説明\tファイル名\n"), m_lpUserDatas->GetDiscription() );
	m_flTestDataLog.WriteString( szBuffer );
	m_flTestDataLog.Flush();

	return TRUE;
}

BOOL CFuzzCreateThread::LogWrite( CFuzzData *lpFuzzData )
{
	CString szBuffer;
	CString szTagID;
	CString szTagName;
	CString szWriteMode;
	CString szFuzzArea;

	switch(lpFuzzData->GetFuzzDataType())
	{
	case CFuzzData::FUZZDATA_TYPE_FIELDENTRY:
		szTagID = lpFuzzData->GetFealdEntryData()->GetTagID();
		if( lpFuzzData->GetFealdEntryData()->GetFealdEntryInfo() )
			szTagName = lpFuzzData->GetFealdEntryData()->GetFealdEntryInfo()->GetTagName();
		else
			szTagName = _T("Unknown");
		break;
	case CFuzzData::FUZZDATA_TYPE_SEGMENT:
		szTagID = lpFuzzData->GetSegmentItemData()->GetMarkerName();
		if( lpFuzzData->GetSegmentItemData()->GetSegmentItemInfo() )
			szTagName = lpFuzzData->GetSegmentItemData()->GetSegmentItemInfo()->GetItemName();
		else
			szTagName = _T("Unknown");
		break;
	case CFuzzData::FUZZDATA_TYPE_FILE:
		szTagID = _T("File");
		if( lpFuzzData->GetPatternData()->GetFieldKey()==_T("-1") )
			szTagName = _T("- ファイル末尾");
		else
			szTagName.Format( _T("%s Byte -"), lpFuzzData->GetPatternData()->GetFieldKey() );
		break;
	}

	switch(lpFuzzData->GetPatternData()->GetWriteMode())
	{
	case CPatternData::WRITEMODE_REPLACE:
		szWriteMode = _T("置換");
		break;
	case CPatternData::WRITEMODE_OVERWRITE:
		szWriteMode = _T("上書");
		break;
	case CPatternData::WRITEMODE_INSERT:
		szWriteMode = _T("挿入");
		break;
	}

	switch(lpFuzzData->GetPatternData()->GetFuzzArea())
	{
	case CPatternData::FUZZAREA_TAG:
		szFuzzArea = _T("タグ");
		break;
	case CPatternData::FUZZAREA_TYPE:
		szFuzzArea = _T("タイプ");
		break;
	case CPatternData::FUZZAREA_COUNT:
		szFuzzArea = _T("カウント");
		break;
	case CPatternData::FUZZAREA_VALUE:
		szFuzzArea = _T("値");
		break;
	case CPatternData::FUZZAREA_OFFSET:
		szFuzzArea = _T("オフセット");
		break;
	case CPatternData::FUZZAREA_SEGMENT:
		szFuzzArea = _T("セグメント要素");
		break;
	case CPatternData::FUZZAREA_FILE:
		szFuzzArea = _T("ファイル位置指定");
		break;
	}

	szBuffer.Format( _T("%s\t%s\t%s\t%s\t%s\t%s\t%s\n"),
					szTagID,
					szTagName,
					szWriteMode,
					szFuzzArea,
					lpFuzzData->GetPatternData()->GetDispName(),
					lpFuzzData->GetPatternData()->GetDescription(),
					lpFuzzData->GetFileName() );
	m_flTestDataLog.WriteString( szBuffer );
	m_flTestDataLog.Flush();

	return TRUE;
}

BOOL CFuzzCreateThread::LogClose()
{
	m_flTestDataLog.Flush();
	m_flTestDataLog.Close();
	return TRUE;
}
