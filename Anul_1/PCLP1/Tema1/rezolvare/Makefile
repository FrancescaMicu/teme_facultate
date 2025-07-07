CFLAGS = -Wall -Werror

.PHONY:	clean run-task1 run-task2 	

run: exe 
	./main

exe: fct.h fct.c main.c
	gcc fct.c main.c $(CFLAGS) -o main

clean:
	rm -f main