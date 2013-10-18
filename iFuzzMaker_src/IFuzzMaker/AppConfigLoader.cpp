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

#include "StdAfx.h"
#include "AppConfigLoader.h"


CAppConfigLoader::CAppConfigLoader(void)
{
}


CAppConfigLoader::~CAppConfigLoader(void)
{
}

BOOL CAppConfigLoader::LoadConfig( CAppConfig &AppConfig )
{
	CString szModuleFilePath;
	CString szConfigFileName;

#ifdef _DEBUG
	GetCurrentDirectory( MAX_PATH, szModuleFilePath.GetBufferSetLength(MAX_PATH+1) );
#else
	GetModuleFileName(NULL,szModuleFilePath.GetBufferSetLength(MAX_PATH+1),MAX_PATH);
	PathRemoveFileSpec( szModuleFilePath.GetBuffer() );
#endif
	PathCombine( szConfigFileName.GetBufferSetLength(MAX_PATH+1), szModuleFilePath, APP_CONFIG_FILE_NAME );
	SetCurrentDirectory( szModuleFilePath );

	if( !CConfigLoader::LoadConfig( szConfigFileName ) )
		return FALSE;

	TCHAR *lpFilePart = NULL;
	CString szFullPath;
	CString szWork;
	CString szValue;

	szWork.GetBufferSetLength(1024);

	GetValue( _T("DATA"), _T("SEGMENT"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	AppConfig.SetSegmentFileName( szValue );

	GetValue( _T("DATA"), _T("IFD"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	AppConfig.SetIfdFileName( szValue );

	GetValue( _T("DATA"), _T("TAGTYPE"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	AppConfig.SetTagTypeFileName( szValue );

	GetValue( _T("BROWS"), _T("JPEGSELFOLDER"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	GetFullPathName( szValue, MAX_PATH, szFullPath.GetBufferSetLength( MAX_PATH+1 ), &lpFilePart );
	AppConfig.SetJpegSelFolder( szFullPath );

	GetValue( _T("BROWS"), _T("PATTERNSELFOLDER"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	GetFullPathName( szValue, MAX_PATH, szFullPath.GetBufferSetLength( MAX_PATH+1 ), &lpFilePart );
	AppConfig.SetPatternSelFolder( szFullPath );

	GetValue( _T("BROWS"), _T("FUZZOUTPUTFOLDER"), szValue );
	szValue.Replace( _T("<APPPATH>"), szModuleFilePath );
	GetFullPathName( szValue, MAX_PATH, szFullPath.GetBufferSetLength( MAX_PATH+1 ), &lpFilePart );
	AppConfig.SetFuzzOutputFolder( szFullPath );

	return TRUE;
}
