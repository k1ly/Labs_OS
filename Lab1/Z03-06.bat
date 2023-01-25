@echo off
echo -- Строка параметров: %*
echo -- Режим: %1
echo -- Файл: %2

if not "%1" == "" goto checkFileName
echo ---+ %0 режим файл
echo ---++ %0 режим = {создать, удалить}
echo ---++ %0 файл = имя файла
goto exit

:checkFileName
if not "%2" == "" goto executeCreate
echo ---+ не задано имя файла
goto exit

:executeCreate
if not "%1" == "создать" goto executeDelete
if exist %2 (
echo ---+ файл %2 уже существует
) else (
break > %2
echo  ---+ файл %2 создан!
)
goto exit

:executeDelete
if not "%1" == "удалить" goto invalidCommand
if exist %2 (
del %2
echo ---+ файл %2 удален!
) else (
echo  ---+ файл %2 не найден
)
goto exit

:invalidCommand
echo ---+ режим задан некорректно

:exit
echo end
pause