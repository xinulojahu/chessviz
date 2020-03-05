all: main.c
	gcc -g -Wall main.c -o main 

clean:
	$(RM) main
