#!/bin/bash
IN_DIR="tests/in"
OUT_DIR="tests/out"
SAMP_DIR="tests/samp"
CORRECT_TEST_NAME=correct_test.txt
INCORRECT_TEST_NAME=incorrect_test.txt
BIN=$1

# Создание папки для результатов тестов
mkdir -p $OUT_DIR

# Корректный тест
echo "===================\nStart of correct test."
$BIN "$IN_DIR/$CORRECT_TEST_NAME" > "$OUT_DIR/$CORRECT_TEST_NAME.out"
if [ `echo $?` != 0 ]
then
    echo "ERROR, $BIN $IN_DIR/$CORRECT_TEST_NAME"
    continue
fi
diff -q "$OUT_DIR/$CORRECT_TEST_NAME.out" "$SAMP_DIR/$CORRECT_TEST_NAME.samp"
if [ `echo $?` != 0 ]
then
    echo "ERROR, diff -q "$OUT_DIR/$CORRECT_TEST_NAME.out" "$SAMP_DIR/$CORRECT_TEST_NAME.samp""
else
    echo "Test passed successfully."
fi

# Некорректный тест
echo "===================\nStart of incorrect test."
$BIN "$IN_DIR/$INCORRECT_TEST_NAME" > "$OUT_DIR/$INCORRECT_TEST_NAME.out"
if [ `echo $?` != 0 ]
then
    echo "ERROR, $BIN $IN_DIR/$INCORRECT_TEST_NAME"
    continue
fi
diff -q "$OUT_DIR/$INCORRECT_TEST_NAME.out" "$SAMP_DIR/$INCORRECT_TEST_NAME.samp"
if [ `echo $?` != 0 ]
then
    echo "ERROR, diff -q "$OUT_DIR/$INCORRECT_TEST_NAME.out" "$SAMP_DIR/$INCORRECT_TEST_NAME.samp""
else
    echo "Test passed successfully."
fi