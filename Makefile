# компилятор
CC=gcc

# флаги
CFLAGS=-c -Wall -Werror 

# путь до объектных файлов
OBJDIR=builder/

# путь до исходников
SRCDIR=src/

# файлы исходников
FILES=board.c board_print_plain.c board_read.c board_validation.c main.c

# исходники
SRC=$(patsubst %.c, $(SRCDIR)%.c, $(FILES))

# объектные файлы
OBJ=$(patsubst %.c, $(OBJDIR)%.o, $(FILES))

# выходной файл
EXECUTABLE=bin/chessviz

.PHONY: clean

all: $(EXECUTABLE)
 
$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -o $@ $^

clean: 
	$(RM) $(OBJ) $(EXECUTABLE)
