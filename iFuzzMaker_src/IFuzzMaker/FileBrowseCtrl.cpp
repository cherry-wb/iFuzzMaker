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

// FileBrowseCtrl.cpp : �����t�@�C��
//

#include "stdafx.h"

#include "IFuzzMaker.h"
#include "FileBrowseCtrl.h"


// CFileBrowseCtrl
CFileBrowseCtrl::CFileBrowseCtrl()
{
	m_bBrowse = FALSE;
}

CFileBrowseCtrl::~CFileBrowseCtrl()
{
}

BEGIN_MESSAGE_MAP(CFileBrowseCtrl, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()


// CFileBrowseCtrl ���b�Z�[�W �n���h���[
void CFileBrowseCtrl::OnBrowse()
{
	ASSERT_VALID(this);
	ENSURE(GetSafeHwnd() != NULL);

	switch (m_Mode)
	{
	case BrowseMode_Folder:
		if (afxShellManager != NULL)
		{
			CString strFolder;
			GetWindowText(strFolder);
			CString strResult;
			if( afxShellManager->BrowseForFolder(strResult, this, strFolder,_T("�o�͐�̑I��"),BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE) )
			{
				m_bBrowse = TRUE;
				SetWindowText(strResult);
				SetModify(TRUE);
				OnAfterUpdate();
			}
		}
		else
		{
			ASSERT(FALSE);
		}
		break;

	case BrowseMode_File:
		{
			CString strFile;
			GetWindowText(strFile);

			if (!strFile.IsEmpty())
			{
				TCHAR fname [_MAX_FNAME];

				_tsplitpath_s(strFile, NULL, 0, NULL, 0, fname, _MAX_FNAME, NULL, 0);

				CString strFileName = fname;
				strFileName.TrimLeft();
				strFileName.TrimRight();

				if (strFileName.IsEmpty())
				{
					strFile.Empty();
				}

				const CString strInvalidChars = _T("*?<>|");
				if (strFile.FindOneOf(strInvalidChars) >= 0)
				{
					if (!OnIllegalFileName(strFile))
					{
						SetFocus();
						return;
					}
				}
			}

			CFileDialog dlg(TRUE, !m_strDefFileExt.IsEmpty() ? (LPCTSTR)m_strDefFileExt : (LPCTSTR)NULL, strFile, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT |OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR, !m_strFileFilter.IsEmpty() ? (LPCTSTR)m_strFileFilter : (LPCTSTR)NULL, NULL);
			if( strFile.IsEmpty() )
				dlg.GetOFN().lpstrInitialDir = m_szDirectory;
			if( dlg.DoModal() == IDOK )
			{
				m_bBrowse = TRUE;
				SetWindowText(dlg.GetPathName());
				SetModify(TRUE);
				OnAfterUpdate();
			}

			if (GetParent() != NULL)
			{
				GetParent()->RedrawWindow(NULL, NULL, RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
			}
		}
		break;
	}

	SetFocus();
}


BOOL CFileBrowseCtrl::IsBrowse( BOOL bReset )
{
	BOOL bBrowse = m_bBrowse;
	if( bReset )
		m_bBrowse = FALSE;

	return bBrowse;
}

void CFileBrowseCtrl::SetInitDirectory()
{
	CString szFilename;
	GetWindowText( szFilename );
	SetInitDirectory( szFilename );
}

void CFileBrowseCtrl::SetInitDirectory( CString szPath )
{
	CString szDir = szPath;
	m_szDirectory = szDir;
}
