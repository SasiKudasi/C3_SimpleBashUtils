#bin\bash

make all
i=0
suc=0
fail=0
#TEST 1
i=$((i+1))
cat test.txt > 1
./s21_cat test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 2
i=$((i+1))

cat -b test.txt > 1
./s21_cat -b test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -b test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 3
i=$((i+1))

cat -b test.txt > 1
./s21_cat --number-nonblank test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat --number-nonblank test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 4
i=$((i+1))

cat -e test.txt > 1
./s21_cat -e test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -e test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 5
i=$((i+1))

cat -n test.txt > 1
./s21_cat -n test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -n test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi


#TEST 6
i=$((i+1))

cat -s test.txt > 1
./s21_cat -s test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -s test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 7
i=$((i+1))

cat -t test.txt > 1
./s21_cat -t test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -t test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 8
i=$((i+1))

cat -n test.txt > 1
./s21_cat --number test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat --number test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 9
i=$((i+1))

cat -s test.txt > 1
./s21_cat --squeeze-blank test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat --squeeze-blank test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 10
i=$((i+1))

cat -v test.txt > 1
./s21_cat -v test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -v test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

#TEST 11
i=$((i+1))
cat -k test.txt > 1
./s21_cat -k test.txt > 2
valgrind --tool=memcheck --leak-check=yes  ./s21_cat -k test.txt
diff 1 2

if [ $? -eq  0 ]
then
    echo "Test $i: SUCCESS"
    suc=$((suc+1))
else
    echo "Test $i: FAIL"
    fail=$((fail+1))
fi

echo "SUCCESS $suc/$i"
echo "FAIL $fail/$i"

