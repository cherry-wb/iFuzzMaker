================================================================================
  �Ɨ��s���@�l��񏈗����i�@�\ (IPA)
  - Information-technology Promotion Agency, Japan -

                                                    �Ɨ��s���@�l��񏈗����i�@�\
                                                   �Z�p�{�� �Z�L�����e�B�Z���^�[
                                                ���Z�L�����e�B�Z�p���{���g���[

      -- JPEG �e�X�g�x���c�[�� iFuzzMaker  --
                                                                Date�F2013/07/30
--------------------------------------------------------------------------------
  Copyright (c) 2013, IPA, Japan
  All rights reserved.
================================================================================

�y0. �͂��߂Ɂz
  ���� README �t�@�C���́AiFuzzMaker �̊T�v�⓮����Ȃǂ��L�ڂ��Ă��܂��B�ȉ�
  �͋L�ړ��e�ł��B
    1.  iFuzzMaker �ɂ���
    2.  �����
    3.  �t�@�C���\��
    4.  �C���X�g�[��
    5.  �A���C���X�g�[��
    6.  ������@
    7.  ���p����
    8.  �Ɛӎ���
    9.  ���쌠
    10. ��������эĔz�z����
    11. �R���p�C����
    12. FAQ
    13. ���₢���킹��


�y1. iFuzzMaker �ɂ��āz
  �uJPEG �e�X�g�x���c�[���wiFuzzMaker�x�v�i�ȉ� iFuzzMaker�j�́A�uJPEG�摜��ǂ�
  ���ދ@�\�v�������i�ɑ΂���Z�L�����e�B�e�X�g�u�t�@�W���O�v�Ɏg����c�[���ł��B
  ���i�́uJPEG�摜��ǂݍ��ދ@�\�v�ɐƎ㐫�����݂���ƁA�����N�����f�[�^�i�Ⴆ
  �΋ɒ[�ɒ���������j������ JPEG �摜��ǂݍ��񂾏ꍇ�A���i�̓���ɖ��i���i��
  �̂��̂̋����I���A�ň��̏ꍇ�A�E�C���X�ւ̊�����O������̉��u����j�������Ă�
  �܂��܂��B���̐Ǝ㐫����肱�܂Ȃ����߂ɂ́A���i�o�בO�ɁA���̂悤�� JPEG �摜
  �i�e�X�g�f�[�^�j��ǂݍ��܂��āA���i�̓���ɖ�肪�����Ȃ������m�F����Z�L����
  �e�B�e�X�g�u�t�@�W���O�v���L���ł��B���́uiFuzzMaker�v�ł́A�t�@�W���O�Ŏg���e
  �X�g�f�[�^����邱�Ƃ��ł��܂��B

  iFuzzMaker �� IPA �̃E�F�u�y�[�W����_�E�����[�h�ł��܂��B
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/index.html


�y2. ������z
  IPA �ɂ� iFuzzMaker �̓�����m�F�������ł��B
    OS      �FWindows XP SP3(32bit)
              Windows 7 SP1(32bit)
    CPU     �F1GHz�ȏ��x86�݊��v���Z�b�T
    ������  �F1GB�ȏ�̋󂫃�����
    HDD     �F1GB�ȏ�̋󂫗̈�


�y3. �t�@�C���\���z
  �ȉ��� iFuzzMaker �̃t�@�C���\���ł��i�����j�B

.\
��  BSD-License.txt                  �c BSD �̃��C�Z���X����
��  CPOL.htm                         �c CPOL �̃��C�Z���X����
��  iFuzzMaker_agreement.pdf         �c ���p�K��
��  iFuzzMaker_manual.pdf            �c ����菇��
��  README.txt                       �c ���̃t�@�C��
��  LICENSE.txt                      �c LICENSE �t�@�C��
��  
����iFuzzMaker                       �c iFuzzMaker �̎��s���W���[���ꎮ
��  ��  iFuzzMaker.exe               �c iFuzzMaker �{��
��  ��  iFuzzMaker.config            �c iFuzzMaker �̐ݒ�t�@�C��
��  ��  IPA-SAMPLE.JPG               �c �T���v�� JPEG �t�@�C��
��  ��  RegDel.bat                   �c �A���C���X�g�[���p�o�b�`�t�@�C��
��  ��  
��  ����Data
��  ��      TagType.txt              �c �^�O�^�C�v��`�t�@�C��
��  ��      IFDList.txt              �c IFD���X�g��`�t�@�C��
��  ��      Segments.txt             �c �Z�O�����g���t�@�C��
��  ��      SOF0-Param.txt           �c �Z�O�����g�\�����t�@�C��
��  ��      SOF0.txt                 �c �Z�O�����g�\�����t�@�C��
��  ��      ExifIFD.txt              �c �^�O���t�@�C��
��  ��      GPSInfoIFD.txt           �c �^�O���t�@�C��
��  ��      Interoperability.txt     �c �^�O���t�@�C��
��  ��      TIFFRev60.txt            �c �^�O���t�@�C��
��  ��      
��  ����Fuzz                         �c �e�X�g�f�[�^�̏o�͐�t�H���_
��  ��      
��  ����TestRule
��      ��  sample-TestRule-List.txt �c �e�X�g�f�[�^�������[�����X�g��`�t�@�C��
��      ��  
��      ����List
��              sample-TestRule1.txt �c �T���v���e�X�g�f�[�^�������[���t�@�C��
��              sample-TestRule2.txt �c �T���v���e�X�g�f�[�^�������[���t�@�C��
��              sample-TestRule3.txt �c �T���v���e�X�g�f�[�^�������[���t�@�C��
��  
��  
����iFuzzMaker_src                   �c iFuzzMaker �̃\�[�X�R�[�h�ꎮ
    ��  
  �i���j�� �\�[�X�R�[�h���܂߂� iFuzzMaker �̃t�@�C���\���� LICENSE.txt �Ɍf�ڂ�
           �Ă��܂�

�y4. �C���X�g�[���z
  1. iFuzzMaker �̎��s���W���[���ꎮ�������Ă���uiFuzzMaker�v�t�H���_���A�C�ӂ�
     �t�H���_�փR�s�[���܂��i�� C:\ipa\iFuzzMaker�Ȃǁj


�y5. �A���C���X�g�[���z
  1. iFuzzMaker ���C���X�g�[�������t�H���_�i�� C:\ipa\iFuzzMaker�Ȃǁj���ɂ��� 
     RegDel.bat ���N�����܂��B
  2. iFuzzMaker ���C���X�g�[�������uiFuzzMaker�v�t�H���_���A�t�H���_���ƍ폜����
     ���B


�y6. ������@�z
  iFuzzMaker �̑�����@�͑���菇���iiFuzzMaker_manual.pdf�j�����Q�Ƃ��������B


�y7. ���p�����z
  iFuzzMaker�i�c�[���{�́A�\�[�X�R�[�h�A�֘A����S�Ẵh�L�������g�����܂ށj����
  ���p���������ɂ́A�uJPEG �e�X�g�x���c�[���wiFuzzMaker�x���p�K��v�i�ȉ� ���p�K
  ��j�ւ̓��ӂ��K�v�ł��B�Ȃ��AiFuzzMaker �́ABSD License�iThe BSD 3-Clause 
  License *1�j����� CPOL�iThe Code Project Open License *2�j����߂�����̉���
  �z�z����Ă��܂��̂ŁABSD License ����� CPOL �̓��e�����m�F���������B

  �EiFuzzMaker �̗��p�K��́uiFuzzMaker_agreement.pdf�v�ɋL�ڂ��Ă��܂��B
  �EBSD License ����߂郉�C�Z���X��������іƐӎ����ɂ��ẮuBSD-License.txt�v
    �ɋL�ڂ��Ă��܂��B
  �ECPOL ����߂郉�C�Z���X��������іƐӎ����ɂ��ẮuCPOL.htm�v�ɋL�ڂ��Ă�
    �܂��B

    *1) The BSD 3-Clause License
        http://opensource.org/licenses/BSD-3-Clause
    *2) The Code Project Open License
        http://www.codeproject.com/info/cpol10.aspx


�y8. �Ɛӎ����z
  iFuzzMaker �̖Ɛӎ����͗��p�K��̑� 6 ���ɋL�ڂ��Ă��܂��B


�y9. ���쌠�z
  iFuzzMaker�̒��쌠�́ABSD License �y�� CPOL ����߂�����̉��� IPA ���ۗL����
  ����A���ۏ��y�ђ��쌠�@�ɂ��ی삳��Ă��܂��B


�y10. ��������эĔz�z�����z
  iFuzzMaker �� BSD License �� CPOL �̃��C�Z���X�����̉��A������Ĕz�z��������
  ���܂��B���p�K��̓��e�ɔ����Ȃ�����A�Ĕz�z����щ������邱�Ƃ��o���܂��B
  �Ȃ��AiFuzzMaker ���K�p���郉�C�Z���X�̏ڍׂɂ��ẮuLICENSE.txt�v�����m�F��
  �������B


�y11. �R���p�C�����z
  IPA �ɂē�����m�F���Ă���R���p�C�����ł��B
    OS      �FWindows XP SP3(32bit)
              Windows 7 SP1(32bit)
    �J������FMicrosoft Visual Studio 2010 Visual C++�iMFC���g�p�j


�y12. FAQ�z
  IPA �̃E�F�u�T�C�g�� iFuzzMaker �� FAQ ���f�ڂ��Ă��܂��BiFuzzMaker �� FAQ ��
  ���Ă̓E�F�u�T�C�g���������������B
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/faq.html


�y13. ���₢���킹��z
  IPA �̃E�F�u�T�C�g�� iFuzzMaker �̖₢���킹����f�ڂ��Ă��܂��B���萔�ł����A
  �w��́u���₢���킹�l���v���_�E�����[�h���Ă��������A�K�v���������L���̂�����
  �₢���킹���������B
    https://www.ipa.go.jp/security/vuln/iFuzzMaker/index.html


                                                                            �ȏ�
