@echo off
echo -- ��ப� ��ࠬ��஢: %*
echo -- �����: %1
echo -- ����: %2

if not "%1" == "" goto checkFileName
echo ---+ %0 ०�� 䠩�
echo ---++ %0 ०�� = {ᮧ����, 㤠����}
echo ---++ %0 䠩� = ��� 䠩��
goto exit

:checkFileName
if not "%2" == "" goto executeCreate
echo ---+ �� ������ ��� 䠩��
goto exit

:executeCreate
if not "%1" == "ᮧ����" goto executeDelete
if exist %2 (
echo ---+ 䠩� %2 㦥 �������
) else (
break > %2
echo  ---+ 䠩� %2 ᮧ���!
)
goto exit

:executeDelete
if not "%1" == "㤠����" goto invalidCommand
if exist %2 (
del %2
echo ---+ 䠩� %2 㤠���!
) else (
echo  ---+ 䠩� %2 �� ������
)
goto exit

:invalidCommand
echo ---+ ०�� ����� �����४⭮

:exit
echo end
pause