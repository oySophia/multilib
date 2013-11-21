CC = gcc
CFLAGS = -g -Wall -fPIC

ALL = test0 test1 test2 test3 test4
all: $(ALL)

#"$@" means the dynamic variable:destinations' values, "$<" the reliable destination values
test%: test%.o
	$(CC) $(CFLAGS) -o $@ $< ../*.o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

clean:
	rm -f *.o $(ALL)
