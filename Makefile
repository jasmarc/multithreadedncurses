CC = gcc
CFLAGS = -g -Wall -pthread -lncurses -L/usr/lib
EXEC = nc

$(EXEC):
	$(CC) $(CFLAGS) -o $(EXEC) main.c
clean:
	-rm $(EXEC)
	-rm *.exe
test:
	$(CC) $(CFLAGS) -o test test.c
cleantest:
	-rm test
	-rm *.exe