@echo off
echo -- Строка параметров: %*
echo -- Параметр 1: %1
echo -- Параметр 2: %2
echo -- Параметр 3: %3
set /a result = %1 %3 %2
echo %1 %3 %2 = %result%
pause