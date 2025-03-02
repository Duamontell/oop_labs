@echo off

set PROGRAM="%~1"
set INPUT_FILE=tests/input.txt
set OUTPUT_FILE=tests/output.txt
set OUTPUT_TO_INPUT_FILE=tests/outputToInput.txt

set INPUT_FILE_1=tests/input1.txt
set OUTPUT_FILE_1=tests/output1.txt
set OUTPUT_TO_INPUT_FILE_1=tests/outputToInput1.txt

set INPUT_FILE_2=tests/input2.txt
set OUTPUT_FILE_2=tests/output2.txt

set INPUT_FILE_3=tests/input3.txt
set OUTPUT_FILE_3=tests/output3.txt

set INPUT_FILE_4=tests/input4.txt
set OUTPUT_FILE_4=tests/output4.txt
set OUTPUT_TO_INPUT_FILE_4=tests/outputToInput4.txt


echo Test 1: Crypt input - 1
%PROGRAM% crypt %INPUT_FILE% result.txt 132
fc result.txt %OUTPUT_FILE% || goto err

echo Test 2: Decrypt input - 1
%PROGRAM% decrypt %OUTPUT_FILE% result.txt 132
fc result.txt %OUTPUT_TO_INPUT_FILE% || goto err

echo Test 3: Crypt input - 2
%PROGRAM% crypt %INPUT_FILE_1% result.txt 15
fc result.txt %OUTPUT_FILE_1% || goto err

echo Test 4: Decrypt input - 2
%PROGRAM% decrypt %OUTPUT_FILE_1% result.txt 15
fc result.txt %OUTPUT_TO_INPUT_FILE_1% || goto err

echo Test 5: Wrong numbers arguments
%PROGRAM% %INPUT_FILE_2% result.txt 99 > result.txt
fc result.txt %OUTPUT_FILE_2% || goto err

echo Test 6: Wrong key
%PROGRAM% crypt %INPUT_FILE_3% %OUTPUT_FILE_3% 1D > result.txt
fc result.txt wrongKey.txt || goto err

echo Test 7: Empty file
%PROGRAM% crypt %INPUT_FILE_4% %OUTPUT_FILE_4% 167 > result.txt
fc result.txt %OUTPUT_FILE_4% || goto err


echo All tests passed
exit /B 0

:err 
echo Program testing failed!
exit /B 1