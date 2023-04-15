Репозиторий для лаборатоных работ по Проектированию компиляторов.

Самсонова Валерия, М8О-107М-22.

Организация папок в проекте:

В папке src лежит основной код.
В папке tests/in лежат тесты.
В папке tests/samp лежат результаты тестов для сравнения их с теми, что сгенерирует программа.

Перед сборкой нужно перейти в папку с проектом 
cd ПУТЬ_ДO_ПАПКИ_НА_ВАШЕЙ_МАШИНЕ/compiler_design

===============Запуск программы (чтение с консоли)===============

make all_console

===============Запуск программы (чтение из файла)===============

Запустит программу с заранее выбранным файлом
make all_file
Чтобы выбрать другой файл, нужно открыть start_file.sh и в строке "bin/output tests/in/correct_test.txt" заменить "tests/in/correct_test.txt" на путь к файлу, котрый хотите открыть

===============Запуск программы (чтение из файла) (алтернативный вариант)===============

make build
Перед запуском "FILE_NAME" надо заменить на путь до файла
bin/output FILE_NAME
echo $?

===============Тест===============

Вывод тестов лежит в папке tests/out
make test

===============Чистка проекта от лишнего===============

make clean
