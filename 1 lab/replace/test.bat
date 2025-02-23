@echo off
chcp 1251 > nul

setlocal

set PROGRAM=replace.exe
set INPUT_FILE=input1.txt
set OUTPUT_FILE=output1.txt
set INPUT_FILE_2=input2.txt
set OUTPUT_FILE_2=output2.txt
set INPUT_FILE_3=input3.txt
set OUTPUT_FILE_3=output3.txt

%PROGRAM% "%INPUT_FILE%" "%OUTPUT_FILE%" "ma" "mama"

echo ���� 1: ma mama - mama delala pelmeni
echo ��������: mamamama delala pelmeni
type "%OUTPUT_FILE%"
echo.


%PROGRAM% "%INPUT_FILE_2%" "%OUTPUT_FILE_2%" "1231234" "XYZ"

echo ���� 2: 1231234 XYZ - 12312312345
echo ��������: 123XYZ5
type "%OUTPUT_FILE_2%"
echo.

%PROGRAM% "%INPUT_FILE_3%" "%OUTPUT_FILE_3%" "" "tam"

echo ���� 3: "" tam - tut text
echo ��������: tut text
type "%OUTPUT_FILE_3%"
echo.

echo ���� 4: hello EOF
echo ��������: ERROR
echo hello | %PROGRAM%
echo.

endlocal

echo ���� 5: ���������� �� ����������
echo ��������: 
echo "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>"    
echo ���������:
replace.exe -h
echo.

echo ���� 6: ���������� ���������� ���������� (3)
echo ��������: ERROR
replace.exe "test" "test" 
echo.

echo ���� 7: ���������� ���������� ���������� (4)
echo ��������: ERROR
replace.exe "test" "test" "test"
echo.

echo ���� 8: ������������ �������� �������� �����
echo ��������: ERROR
replace.exe "test" "test" "test" "test"
echo.

echo ���� 9: ������������ �������� ��������� �����
echo ��������: ERROR
replace.exe "%INPUT_FILE%" "test" "test" "test"
echo.

pause
