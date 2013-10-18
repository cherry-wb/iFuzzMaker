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
#include "ConfigLoader.h"

CConfigLoader::CConfigLoader(void)
{
}


CConfigLoader::~CConfigLoader(void)
{
}

void CConfigLoader::SetFileName( CString szFileName )
{
	m_szFileName = szFileName;
}

CString CConfigLoader::GetFileName()
{
	return m_szFileName;
}

BOOL CConfigLoader::LoadConfig( CString szFileName )
{
	if( szFileName.GetLength() > 0 )
		m_szFileName = szFileName;

	int nLen = 0;
	int nBufferLen = 0;
	CString szBuffer;
	CString szWork;
	CString szSection;
	CString szKey;
	CString szValue;
	CMapStringToString *lpKeyMap = NULL;

	TCHAR* lpBuffer = szBuffer.GetBufferSetLength(4096);
	szValue.GetBufferSetLength(2048);
	m_SectionMap.RemoveAllWithDelete();
	nBufferLen = GetPrivateProfileString( NULL, NULL, NULL, lpBuffer, szBuffer.GetLength(), m_szFileName );

	//	セクションリスト作成
	for( nLen=0; nLen<nBufferLen; nLen++ )
	{
		if(lpBuffer[nLen]==0x00)
			break;
		szWork = &lpBuffer[nLen];
		m_SectionMap.SetAtWithNew( szWork );
		nLen += szWork.GetLength();
	}

	//	セクションごとにキーを追加
	POSITION pos = m_SectionMap.GetStartPosition();
	while( pos )
	{
		lpKeyMap = NULL;
		m_SectionMap.GetNextAssoc( pos, szSection, lpKeyMap );

		nBufferLen = GetPrivateProfileString( szSection, NULL, NULL, lpBuffer, szBuffer.GetLength(), m_szFileName );
		for( nLen=0; nLen<nBufferLen; nLen++ )
		{
			if(lpBuffer[nLen]==0x00)
				break;
			szKey = &lpBuffer[nLen];
			GetPrivateProfileString( szSection, szKey, NULL, szValue.GetBuffer(), szBuffer.GetLength(), m_szFileName );

			lpKeyMap->SetAt( szKey, szValue );
			nLen += szKey.GetLength();
		}
	}

	return TRUE;
}

BOOL CConfigLoader::SaveConfig( CString szFileName )
{
	if( szFileName.GetLength() > 0 )
		m_szFileName = szFileName;

	CString szSection;
	CString szKey;
	CString szValue;

	POSITION posSection = NULL;
	POSITION posKey = NULL;

	posSection = m_SectionMap.GetStartPosition();
	while(posSection)
	{
		CMapStringToString *lpKeyMap = NULL;
		m_SectionMap.GetNextAssoc( posSection, szSection, lpKeyMap );
		posKey = lpKeyMap->GetStartPosition();
		while(posKey)
		{
			lpKeyMap->GetNextAssoc( posKey, szKey, szValue );
			WritePrivateProfileString( szSection, szKey, szValue, m_szFileName );
		}
	}

	return TRUE;
}

BOOL CConfigLoader::SaveConfig( CString szSection, CString szFileName )
{
	if( szFileName.GetLength() > 0 )
		m_szFileName = szFileName;

	CString szKey;
	CString szValue;
	POSITION posKey = NULL;

	CMapStringToString *lpKeyMap = NULL;
	if( m_SectionMap.Lookup( szSection, lpKeyMap ) )
	{
		posKey = lpKeyMap->GetStartPosition();
		while(posKey)
		{
			lpKeyMap->GetNextAssoc( posKey, szKey, szValue );
			WritePrivateProfileString( szSection, szKey, szValue, m_szFileName );
		}
	}

	return TRUE;
}

BOOL CConfigLoader::SetValue( CString szSection, CString szKey, CString szValue )
{
	CMapStringToString *lpKeyMap = NULL;
	if( !m_SectionMap.Lookup( szSection, lpKeyMap ) )
		lpKeyMap = m_SectionMap.SetAtWithNew( szSection );
	lpKeyMap->SetAt( szKey, szValue );

	return TRUE;
}

BOOL CConfigLoader::GetValue( CString szSection, CString szKey, CString &szValue )
{
	CMapStringToString *lpKeyMap = NULL;
	if( m_SectionMap.Lookup( szSection, lpKeyMap ) )
		return lpKeyMap->Lookup( szKey,szValue );
	return FALSE;
}

BOOL CConfigLoader::SetValue( CString szSection, CString szKey, long lValue )
{
	CString szValue;
	szValue.Format( _T("%d"), lValue );
	return SetValue( szSection, szKey, szValue );
}

BOOL CConfigLoader::GetValue( CString szSection, CString szKey, long &lValue )
{
	CString szValue;
	lValue = 0;
	BOOL bRet = GetValue( szSection, szKey, szValue );
	lValue = _tstol(szValue);
	return bRet;
}

BOOL CConfigLoader::SetValue( CString szSection, CString szKey, int nValue )
{
	CString szValue;
	szValue.Format( _T("%d"), nValue );
	return SetValue( szSection, szKey, szValue );
}

BOOL CConfigLoader::GetValue( CString szSection, CString szKey, int &nValue )
{
	CString szValue;
	nValue = 0;
	BOOL bRet = GetValue( szSection, szKey, szValue );
	nValue = _tstol(szValue);
	return bRet;
}
