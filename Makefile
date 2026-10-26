CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = src/GuillarteD.c src/GuillarteDFunc.c
TARGET = bin/QuizGame.exe

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	$(CC) $(CFLAGS) $(SRC) -o bin/GuillarteD.exe

run: $(TARGET)
	./$(TARGET)

test: tests/test_runner.c src/GuillarteDFunc.c
	$(CC) $(CFLAGS) tests/test_runner.c src/GuillarteDFunc.c -o tests/test_runner.exe
	./tests/test_runner.exe

clean:
	-powershell -Command "Remove-Item -Force -ErrorAction SilentlyContinue bin/*.exe, tests/*.exe, *.txt.txt"

.PHONY: all run test clean
