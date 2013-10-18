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


// IFuzzMaker.cpp : アプリケーションのクラス動作を定義します。
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
	// 標準のファイル基本ドキュメント コマンド
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()

// CIFuzzMakerApp コンストラクション
CIFuzzMakerApp::CIFuzzMakerApp()
{
	m_bHiColorIcons = TRUE;

	// 再起動マネージャーをサポートします
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// アプリケーションが共通言語ランタイム サポート (/clr) を使用して作成されている場合:
	//     1) この追加設定は、再起動マネージャー サポートが正常に機能するために必要です。
	//     2) 作成するには、プロジェクトに System.Windows.Forms への参照を追加する必要があります。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 下のアプリケーション ID 文字列を一意の ID 文字列で置換します。推奨される
	// 文字列の形式は CompanyName.ProductName.SubProduct.VersionInformation です
	SetAppID(_T("IFuzzMaker.AppID.NoVersion"));

	// TODO: この位置に構築用コードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

// 唯一の CIFuzzMakerApp オブジェクトです。
CIFuzzMakerApp theApp;

// CIFuzzMakerApp 初期化
BOOL CIFuzzMakerApp::InitInstance()
{
	// アプリケーション マニフェストが visual スタイルを有効にするために、
	// ComCtl32.dll Version 6 以降の使用を指定する場合は、
	// Windows XP に InitCommonControlsEx() が必要です。さもなければ、ウィンドウ作成はすべて失敗します。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// アプリケーションで使用するすべてのコモン コントロール クラスを含めるには、
	// これを設定します。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	// OLE ライブラリを初期化します。
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit コントロールを使用するには AfxInitRichEdit2() が必要です	
	AfxInitRichEdit2();

	// 標準初期化
	// これらの機能を使わずに最終的な実行可能ファイルの
	// サイズを縮小したい場合は、以下から不要な初期化
	// ルーチンを削除してください。
	// 設定が格納されているレジストリ キーを変更します。
	// TODO: 会社名または組織名などの適切な文字列に
	// この文字列を変更してください。
	SetRegistryKey(_T("IPA"));
	LoadStdProfileSettings(10);  // 標準の INI ファイルのオプションをロードします (MRU を含む)

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// アプリケーション用のドキュメント テンプレートを登録します。ドキュメント テンプレート
	//  はドキュメント、フレーム ウィンドウとビューを結合するために機能します。
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CIFuzzMakerDoc),
		RUNTIME_CLASS(CMainFrame),       // メイン SDI フレーム ウィンドウ
		RUNTIME_CLASS(CIFuzzMakerView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// DDE、file open など標準のシェル コマンドのコマンド ラインを解析します。
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// コマンド ラインで指定されたディスパッチ コマンドです。アプリケーションが
	// /RegServer、/Register、/Unregserver または /Unregister で起動された場合、False を返します。
	if( cmdInfo.m_nShellCommand == CCommandLineInfo::FileOpen && !PathFileExists( cmdInfo.m_strFileName ) )
	{
		MessageBox( NULL, _T("ファイルが見つかりません"), _T("エラー"), MB_ICONERROR );
		return FALSE;
	}

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// メイン ウィンドウが初期化されたので、表示と更新を行います。
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

int CIFuzzMakerApp::ExitInstance()
{
	//TODO: 追加したリソースがある場合にはそれらも処理してください
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CIFuzzMakerApp メッセージ ハンドラー

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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

// ダイアログを実行するためのアプリケーション コマンド
void CIFuzzMakerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CIFuzzMakerApp のカスタマイズされた読み込みメソッドと保存メソッド

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

// CIFuzzMakerApp メッセージ ハンドラー





