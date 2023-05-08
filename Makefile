SRC_DIR = src
GEN_DIR = gen
OBJ_DIR = obj
TEST_OUT_DIR = tests/out
BIN_DIR = bin
BIN_NAME = output
TEST = test_script.sh
OBJS = main tree

# Сборка, запуск и вывод кода завершения работы программы
all_file: build 
	sh start_file.sh
all_console: build 
	sh start_console.sh
# Сборка
build: makedir sintax lexer $(OBJS)
	gcc $(OBJ_DIR)/*.o -o $(BIN_DIR)/$(BIN_NAME)
# Создание папок
makedir: 
	mkdir -p $(BIN_DIR) $(OBJ_DIR) $(GEN_DIR)
# Транслирование файла из формата flex в файл на языке C и компиляция транслированного файла
lexer: lexer.h
	gcc $(GEN_DIR)/lexer.c -o $(OBJ_DIR)/lexer.o -c -std=gnu11
# Транслирование файла из формата flex в файл на языке C
lexer.h: 
	flex --header-file=$(GEN_DIR)/lexer.h -o $(GEN_DIR)/lexer.c $(SRC_DIR)/lexer.l
# Транслирование файла из формата bison в файл на языке C и компиляция транслированного файла
sintax:	lexer.h
	bison $(SRC_DIR)/sintax.y --defines=$(GEN_DIR)/sintax.h -o $(GEN_DIR)/sintax.c
	gcc $(GEN_DIR)/sintax.c -I$(GEN_DIR) -o $(OBJ_DIR)/sintax.o -c
# Создание объектных файлов из .с
$(OBJS):
	gcc $(SRC_DIR)/$@.c -I$(GEN_DIR) -c -o $(OBJ_DIR)/$@.o
# Запуск тестов
test: build
	sh $(TEST) $(BIN_DIR)/$(BIN_NAME)
# Удаление созданных папок
clear:
	rm -fr $(BIN_DIR) $(OBJ_DIR) $(GEN_DIR) $(TEST_OUT_DIR)



