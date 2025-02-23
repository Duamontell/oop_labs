@echo off

set PROGRAM="%~1"

:: Тесты 1-5 - обычная работа программы
echo Test 1: 25 15 3B3A
%PROGRAM% 25 15 3B3A > result.txt
echo 10E40> expected.txt
fc result.txt expected.txt || goto err

echo Test 2: 16 10 1F
%PROGRAM% 16 10 1F > result.txt
echo 31> expected.txt
fc result.txt expected.txt || goto err

echo Test 3: 36 2 A3
%PROGRAM% 36 2 A3 > result.txt
echo 101101011> expected.txt
fc result.txt expected.txt || goto err

echo Test 4: 6 27 431
%PROGRAM% 6 27 431 > result.txt
echo 61> expected.txt
fc result.txt expected.txt || goto err

echo Test 5: 3 9 -121
%PROGRAM% 3 9 -121 > result.txt
echo -17> expected.txt
fc result.txt expected.txt || goto err

:: Вводим одинаковые системы счисления
echo Test 6: 10 10 7
%PROGRAM% 10 10 7 > result.txt
(echo 7)> expected.txt
fc result.txt expected.txt || goto err

:: Тесты 7-13 - Неправильные входные данные
echo Test 7: 4 7 153
%PROGRAM% 4 7 153 > result.txt
echo Invalid input data!> expected.txt
fc /B result.txt expected.txt || goto err

echo Test 8: 29 5 DAFADFIOGFDLGP
%PROGRAM% 29 5 DAFADFIOGFDLGP > result.txt
echo Invalid input data!> expected.txt
fc result.txt expected.txt || goto err

echo Test 9: 37 12 78
%PROGRAM% 37 12 78 > result.txt
echo Invalid input data!> expected.txt
fc result.txt expected.txt || goto err

echo Test 10: 12 78
%PROGRAM% 12 78 > result.txt
echo Wrong number of arguments!> expected.txt
fc result.txt expected.txt || goto err

echo Test 11: 1F 7 6789
%PROGRAM% 1F 7 6789 > result.txt
echo Invalid input data!> expected.txt
fc result.txt expected.txt || goto err

echo Test 12: 18 32 67892315495924919301939
%PROGRAM% 18 32 67892315495924919301939 > result.txt
echo Invalid input data!> expected.txt
fc result.txt expected.txt || goto err

echo Test 13: Empty
%PROGRAM% > result.txt
echo Wrong number of arguments!> expected.txt
fc result.txt expected.txt || goto err

echo All tests passed
exit /B 0

:err 
echo Program testing failed!
exit /B 1