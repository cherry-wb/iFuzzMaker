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


// IFuzzMaker.cpp : �A�v���P�[�V�����̃N���X������`���܂��B
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "IFuzzMaker.h"
#include "MainFrm.h"

#include "IFuzzMakerDoc.h"
#include "IFuzzMakerView.h"
#include "afxwin.h"

#include "ImageStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIFuzzMakerApp
BEGIN_MESSAGE_MAP(CIFuzzMakerApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CIFuzzMakerApp::OnAppAbout)
	// �W���̃t�@�C����{�h�L�������g �R�}���h
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

// CIFuzzMakerApp �R���X�g���N�V����
CIFuzzMakerApp::CIFuzzMakerApp()
{
	m_bHiColorIcons = TRUE;

	// �ċN���}�l�[�W���[���T�|�[�g���܂�
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// �A�v���P�[�V���������ʌ��ꃉ���^�C�� �T�|�[�g (/clr) ���g�p���č쐬����Ă���ꍇ:
	//     1) ���̒ǉ��ݒ�́A�ċN���}�l�[�W���[ �T�|�[�g������ɋ@�\���邽�߂ɕK�v�ł��B
	//     2) �쐬����ɂ́A�v���W�F�N�g�� System.Windows.Forms �ւ̎Q�Ƃ�ǉ�����K�v������܂��B
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ���̃A�v���P�[�V���� ID ���������ӂ� ID ������Œu�����܂��B���������
	// ������̌`���� CompanyName.ProductName.SubProduct.VersionInformation �ł�
	SetAppID(_T("IFuzzMaker.AppID.NoVersion"));

	// TODO: ���̈ʒu�ɍ\�z�p�R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

// �B��� CIFuzzMakerApp �I�u�W�F�N�g�ł��B
CIFuzzMakerApp theApp;

// CIFuzzMakerApp ������
BOOL CIFuzzMakerApp::InitInstance()
{
	// �A�v���P�[�V���� �}�j�t�F�X�g�� visual �X�^�C����L���ɂ��邽�߂ɁA
	// ComCtl32.dll Version 6 �ȍ~�̎g�p���w�肷��ꍇ�́A
	// Windows XP �� InitCommonControlsEx() ���K�v�ł��B�����Ȃ���΁A�E�B���h�E�쐬�͂��ׂĎ��s���܂��B
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �A�v���P�[�V�����Ŏg�p���邷�ׂẴR���� �R���g���[�� �N���X���܂߂�ɂ́A
	// �����ݒ肵�܂��B
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE ���C�u���������������܂��B
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit �R���g���[�����g�p����ɂ� AfxInitRichEdit2() ���K�v�ł�	
	AfxInitRichEdit2();

	// �W��������
	// �����̋@�\���g�킸�ɍŏI�I�Ȏ��s�\�t�@�C����
	// �T�C�Y���k���������ꍇ�́A�ȉ�����s�v�ȏ�����
	// ���[�`�����폜���Ă��������B
	// �ݒ肪�i�[����Ă��郌�W�X�g�� �L�[��ύX���܂��B
	// TODO: ��Ж��܂��͑g�D���Ȃǂ̓K�؂ȕ������
	// ���̕������ύX���Ă��������B
	SetRegistryKey(_T("IPA"));
	LoadStdProfileSettings(10);  // �W���� INI �t�@�C���̃I�v�V���������[�h���܂� (MRU ���܂�)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// �A�v���P�[�V�����p�̃h�L�������g �e���v���[�g��o�^���܂��B�h�L�������g �e���v���[�g
	//  �̓h�L�������g�A�t���[�� �E�B���h�E�ƃr���[���������邽�߂ɋ@�\���܂��B
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIFuzzMakerDoc),
		RUNTIME_CLASS(CMainFrame),       // ���C�� SDI �t���[�� �E�B���h�E
		RUNTIME_CLASS(CIFuzzMakerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE�Afile open �ȂǕW���̃V�F�� �R�}���h�̃R�}���h ���C������͂��܂��B
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// �R�}���h ���C���Ŏw�肳�ꂽ�f�B�X�p�b�` �R�}���h�ł��B�A�v���P�[�V������
	// /RegServer�A/Register�A/Unregserver �܂��� /Unregister �ŋN�����ꂽ�ꍇ�AFalse ��Ԃ��܂��B
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen && !PathFileExists( cmdInfo.m_strFileName ) )
	{
		MessageBox( NULL, _T("�t�@�C����������܂���"), _T("�G���["), MB_ICONERROR );
		return FALSE;
	}

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// ���C�� �E�B���h�E�����������ꂽ�̂ŁA�\���ƍX�V���s���܂��B
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CIFuzzMakerApp::ExitInstance()
{
	//TODO: �ǉ��������\�[�X������ꍇ�ɂ͂������������Ă�������
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CIFuzzMakerApp ���b�Z�[�W �n���h���[

// �A�v���P�[�V�����̃o�[�W�������Ɏg���� CAboutDlg �_�C�A���O
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

// ����
protected:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_wndProductName;
	CStatic m_wndProductVersion;
	CStatic m_wndCopyright;

	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PRODUCTNAME_STATIC, m_wndProductName);
	DDX_Control(pDX, IDC_PRODUCTVERSION_STATIC, m_wndProductVersion);
	DDX_Control(pDX, IDC_COPYRIGHT_STATIC, m_wndCopyright);
	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()
#pragma comment(lib, "version.lib")

BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString szModuleName;
	int nRet = ::GetModuleFileName( NULL, szModuleName.GetBufferSetLength(_MAX_PATH+1), _MAX_PATH );

	DWORD dwZero = 0;
	DWORD dwVerInfoSize = GetFileVersionInfoSize( szModuleName, &dwZero );
	if(dwVerInfoSize == 0) {
		return FALSE;
	}

	CString szBuff;

	CArray<unsigned char>	BlockDataArray;
	BlockDataArray.SetSize( dwVerInfoSize+1 );

	unsigned char *pBlock = BlockDataArray.GetData();
	GetFileVersionInfo( szModuleName, dwZero, dwVerInfoSize, pBlock );

	void *pvVersion = NULL;
	UINT VersionLen = 0;

	
	if(VerQueryValue( pBlock, TEXT("\\StringFileInfo\\041104b0\\FileDescription"), &pvVersion, &VersionLen )){
		szBuff.Format( _T("%s\n") , pvVersion);
		m_wndProductName.SetWindowText( szBuff );
	}
	
	if(VerQueryValue( pBlock, TEXT("\\StringFileInfo\\041104b0\\ProductVersion"), &pvVersion, &VersionLen )){
		szBuff.Format( _T("Version. %s\n") , pvVersion);
		m_wndProductVersion.SetWindowText( szBuff );
	}
	
	if(VerQueryValue(pBlock, TEXT("\\StringFileInfo\\041104b0\\LegalCopyright"), &pvVersion, &VersionLen)){
		szBuff.Format( _T("%s\n") , pvVersion);
		m_wndCopyright.SetWindowText( szBuff );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
}


BOOL CAboutDlg::OnEraseBkgnd(CDC* pDC)
{
	CRect rectClient;
	GetClientRect(rectClient);
	pDC->FillRect( rectClient, &afxGlobalData.brBarFace );

	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	if ( nCtlColor == CTLCOLOR_STATIC || nCtlColor == CTLCOLOR_BTN )
	{ 
		CString szBuffer;
		TCHAR* lpBuffer = szBuffer.GetBufferSetLength(256);
		if(lpBuffer)
		{
			if( GetClassName(pWnd->GetSafeHwnd(), lpBuffer, 255) > 0 )
			{

				if( szBuffer.Compare( _T("Static") ) == 0 ||
					szBuffer.Compare( _T("Button") ) == 0 ||
					szBuffer.Compare( _T("msctls_trackbar32") ) == 0 )
				{
					CRect rectClient;
					pWnd->GetClientRect(rectClient);
					pDC->FillRect( rectClient, &afxGlobalData.brBarFace );
					pDC->SetBkMode(TRANSPARENT);
					return(HBRUSH) GetStockObject(HOLLOW_BRUSH);
				}
			}
		}
	} 
	return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}

// �_�C�A���O�����s���邽�߂̃A�v���P�[�V���� �R�}���h
void CIFuzzMakerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIFuzzMakerApp �̃J�X�^�}�C�Y���ꂽ�ǂݍ��݃��\�b�h�ƕۑ����\�b�h

void CIFuzzMakerApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);

	bNameValid = strName.LoadString(IDS_LIST_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_LIST_POPUP);

}

void CIFuzzMakerApp::LoadCustomState()
{
}

void CIFuzzMakerApp::SaveCustomState()
{
}

// CIFuzzMakerApp ���b�Z�[�W �n���h���[





