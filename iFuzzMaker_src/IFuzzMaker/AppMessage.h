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

#pragma once

#define WM_APP_READ_JPEG			WM_APP + 0x0001
#define WM_APP_EXIF_ANALYZED		WM_APP + 0x0002
#define WM_APP_EXIF_SELECT			WM_APP + 0x0003
#define WM_APP_READ_GROUP			WM_APP + 0x0004
#define WM_APP_GROUP_DISP			WM_APP + 0x0005
#define WM_APP_CREATE_FUZZ_LIST		WM_APP + 0x0006
#define WM_APP_FUZZ_LIST_DISP		WM_APP + 0x0007
#define WM_APP_UPDATE_COUNT			WM_APP + 0x0008

enum
{
	THREAD_CTRL_START,
	THREAD_CTRL_CANCEL,
};
#define WM_APP_THREAD_CTRL			WM_APP + 0x0009

enum
{
	THREAD_STATUS_CREATE_ERROR,
	THREAD_STATUS_MAKEFOLDER_ERROR,
	THREAD_STATUS_END,
};
#define WM_APP_THREAD_STATUS		WM_APP + 0x000A

enum
{
	CREATE_FUZZ_STATUS_COUNTER,
	CREATE_FUZZ_STATUS_FILE,
	CREATE_FUZZ_STATUS_SKIP,
	CREATE_FUZZ_STATUS_FILE_ERROR,
};
#define WM_APP_CREATE_FUZZ_STATUS	WM_APP + 0x000B

#define WM_APP_START_CREATE_FUZZ	WM_APP + 0x000C
#define WM_APP_END_CREATE_FUZZ		WM_APP + 0x000D

