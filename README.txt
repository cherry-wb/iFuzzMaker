================================================================================
  独立行政法人情報処理推進機構 (IPA)
  - Information-technology Promotion Agency, Japan -

                                                    独立行政法人情報処理推進機構
                                                   技術本部 セキュリティセンター
                                                情報セキュリティ技術ラボラトリー

      -- JPEG テスト支援ツール iFuzzMaker  --
                                                                Date：2013/07/30
--------------------------------------------------------------------------------
  Copyright (c) 2013, IPA, Japan
  All rights reserved.
================================================================================

【0. はじめに】
  この README ファイルは、iFuzzMaker の概要や動作環境などを記載しています。以下
  は記載内容です。
    1.  iFuzzMaker について
    2.  動作環境
    3.  ファイル構成
    4.  インストール
    5.  アンインストール
    6.  操作方法
    7.  利用条件
    8.  免責事項
    9.  著作権
    10. 改造および再配布条件
    11. コンパイル環境
    12. FAQ
    13. お問い合わせ先


【1. iFuzzMaker について】
  「JPEG テスト支援ツール『iFuzzMaker』」（以下 iFuzzMaker）は、「JPEG画像を読み
  込む機能」を持つ製品に対するセキュリティテスト「ファジング」に使えるツールです。
  製品の「JPEG画像を読み込む機能」に脆弱性が存在すると、問題を起こすデータ（例え
  ば極端に長い文字列）を持つ JPEG 画像を読み込んだ場合、製品の動作に問題（製品そ
  のものの強制終了、最悪の場合、ウイルスへの感染や外部からの遠隔操作）が生じてし
  まいます。この脆弱性を作りこまないためには、製品出荷前に、このような JPEG 画像
  （テストデータ）を読み込ませて、製品の動作に問題が生じないかを確認するセキュリ
  ティテスト「ファジング」が有効です。この「iFuzzMaker」では、ファジングで使うテ
  ストデータを作ることができます。

  iFuzzMaker は IPA のウェブページからダウンロードできます。
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/index.html


【2. 動作環境】
  IPA にて iFuzzMaker の動作を確認した環境です。
    OS      ：Windows XP SP3(32bit)
              Windows 7 SP1(32bit)
    CPU     ：1GHz以上のx86互換プロセッサ
    メモリ  ：1GB以上の空きメモリ
    HDD     ：1GB以上の空き領域


【3. ファイル構成】
  以下は iFuzzMaker のファイル構成です（抜粋）。

.\
│  BSD-License.txt                  … BSD のライセンス条項
│  CPOL.htm                         … CPOL のライセンス条項
│  iFuzzMaker_agreement.pdf         … 利用規約
│  iFuzzMaker_manual.pdf            … 操作手順書
│  README.txt                       … このファイル
│  LICENSE.txt                      … LICENSE ファイル
│  
├─iFuzzMaker                       … iFuzzMaker の実行モジュール一式
│  │  iFuzzMaker.exe               … iFuzzMaker 本体
│  │  iFuzzMaker.config            … iFuzzMaker の設定ファイル
│  │  IPA-SAMPLE.JPG               … サンプル JPEG ファイル
│  │  RegDel.bat                   … アンインストール用バッチファイル
│  │  
│  ├─Data
│  │      TagType.txt              … タグタイプ定義ファイル
│  │      IFDList.txt              … IFDリスト定義ファイル
│  │      Segments.txt             … セグメント情報ファイル
│  │      SOF0-Param.txt           … セグメント構造情報ファイル
│  │      SOF0.txt                 … セグメント構造情報ファイル
│  │      ExifIFD.txt              … タグ情報ファイル
│  │      GPSInfoIFD.txt           … タグ情報ファイル
│  │      Interoperability.txt     … タグ情報ファイル
│  │      TIFFRev60.txt            … タグ情報ファイル
│  │      
│  ├─Fuzz                         … テストデータの出力先フォルダ
│  │      
│  └─TestRule
│      │  sample-TestRule-List.txt … テストデータ生成ルールリスト定義ファイル
│      │  
│      └─List
│              sample-TestRule1.txt … サンプルテストデータ生成ルールファイル
│              sample-TestRule2.txt … サンプルテストデータ生成ルールファイル
│              sample-TestRule3.txt … サンプルテストデータ生成ルールファイル
│  
│  
└─iFuzzMaker_src                   … iFuzzMaker のソースコード一式
    │  
  （略）※ ソースコードを含めた iFuzzMaker のファイル構成は LICENSE.txt に掲載し
           ています

【4. インストール】
  1. iFuzzMaker の実行モジュール一式が入っている「iFuzzMaker」フォルダを、任意の
     フォルダへコピーします（例 C:\ipa\iFuzzMakerなど）


【5. アンインストール】
  1. iFuzzMaker をインストールしたフォルダ（例 C:\ipa\iFuzzMakerなど）内にある 
     RegDel.bat を起動します。
  2. iFuzzMaker をインストールした「iFuzzMaker」フォルダを、フォルダごと削除しま
     す。


【6. 操作方法】
  iFuzzMaker の操作方法は操作手順書（iFuzzMaker_manual.pdf）をご参照ください。


【7. 利用条件】
  iFuzzMaker（ツール本体、ソースコード、関連する全てのドキュメント等を含む）をご
  利用いただくには、「JPEG テスト支援ツール『iFuzzMaker』利用規約」（以下 利用規
  約）への同意が必要です。なお、iFuzzMaker は、BSD License（The BSD 3-Clause 
  License *1）および CPOL（The Code Project Open License *2）が定める条件の下で
  配布されていますので、BSD License および CPOL の内容もご確認ください。

  ・iFuzzMaker の利用規約は「iFuzzMaker_agreement.pdf」に記載しています。
  ・BSD License が定めるライセンス条件および免責事項については「BSD-License.txt」
    に記載しています。
  ・CPOL が定めるライセンス条件および免責事項については「CPOL.htm」に記載してい
    ます。

    *1) The BSD 3-Clause License
        http://opensource.org/licenses/BSD-3-Clause
    *2) The Code Project Open License
        http://www.codeproject.com/info/cpol10.aspx


【8. 免責事項】
  iFuzzMaker の免責事項は利用規約の第 6 条に記載しています。


【9. 著作権】
  iFuzzMakerの著作権は、BSD License 及び CPOL が定める条件の下で IPA が保有して
  おり、国際条約及び著作権法により保護されています。


【10. 改造および再配布条件】
  iFuzzMaker は BSD License と CPOL のライセンス条項の下、改造や再配布を許可して
  います。利用規約の内容に反しない限り、再配布および改造することが出来ます。
  なお、iFuzzMaker が適用するライセンスの詳細については「LICENSE.txt」をご確認く
  ださい。


【11. コンパイル環境】
  IPA にて動作を確認しているコンパイル環境です。
    OS      ：Windows XP SP3(32bit)
              Windows 7 SP1(32bit)
    開発言語：Microsoft Visual Studio 2010 Visual C++（MFCを使用）


【12. FAQ】
  IPA のウェブサイトに iFuzzMaker の FAQ を掲載しています。iFuzzMaker の FAQ に
  ついてはウェブサイトをご覧ください。
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/faq.html


【13. お問い合わせ先】
  IPA のウェブサイトに iFuzzMaker の問い合わせ先を掲載しています。お手数ですが、
  指定の「お問い合わせ様式」をダウンロードしていただき、必要事項をご記入のうえお
  問い合わせください。
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/index.html


                                                                            以上
