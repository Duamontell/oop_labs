@echo off

set PROGRAM="%~1"
set INPUT_FILE=tests/input.txt
set OUTPUT_FILE=tests/output.txt
set INPUT_FILE_1=tests/input1.txt
set OUTPUT_FILE_1=tests/output1.txt
set INPUT_FILE_2=tests/input2.txt
set OUTPUT_FILE_2=tests/output2.txt
set INPUT_FILE_3=tests/input3.txt
set OUTPUT_FILE_3=tests/output3.txt
set INPUT_FILE_4=tests/input4.txt
set OUTPUT_FILE_4=tests/output4.txt
set INPUT_FILE_5=tests/input5.txt
set OUTPUT_FILE_5=tests/output5.txt
set INPUT_FILE_6=tests/input6.txt
set OUTPUT_FILE_6=tests/output6.txt
set OUTPUT_FILE_7=tests/output7.txt
set OUTPUT_FILE_8=tests/output8.txt
set OUTPUT_FILE_9=tests/output9.txt

echo Test 1: Valid input
%PROGRAM% %INPUT_FILE% > result.txt
fc /B result.txt %OUTPUT_FILE% || goto err

echo Test 2: Valid input
%PROGRAM% %INPUT_FILE_1% > result.txt
fc result.txt %OUTPUT_FILE_1% || goto err

echo Test 3: Non-invertible
%PROGRAM% %INPUT_FILE_2% > result.txt
fc result.txt %OUTPUT_FILE_2% || goto err

echo Test 4: Invalid matrix format 
%PROGRAM% %INPUT_FILE_3% > result.txt
fc result.txt %OUTPUT_FILE_3% || goto err

echo Test 5: Invalid matrix
%PROGRAM% %INPUT_FILE_4% > result.txt
fc result.txt %OUTPUT_FILE_4% || goto err

echo Test 6: Invalid matrix format - Empty file
%PROGRAM% %INPUT_FILE_5% > result.txt
fc result.txt %OUTPUT_FILE_5% || goto err

echo Test 7: Valid input
%PROGRAM% %INPUT_FILE_6% > result.txt
fc result.txt %OUTPUT_FILE_6% || goto err

echo Test 8: Help command test
%PROGRAM% -h > result.txt
fc result.txt %OUTPUT_FILE_7% || goto err

echo Test 9: Invalid input - wrong numbers arguments
%PROGRAM% %INPUT_FILE_2% -h > result.txt
fc result.txt %OUTPUT_FILE_8% || goto err

echo Test 10: Invalid input - empty
%PROGRAM% > result.txt
fc result.txt %OUTPUT_FILE_9% || goto err

echo All tests passed
exit /B 0

:err 
echo Program testing failed!
exit /B 1