CC = gcc  #refer to the compile commands
CFLAGS = -g -Wall -fPIC#the gcc's options.

ALL = gf_table.o w4.o w8.o w16.o w32.o w64.o common.o #w128.o #the destination, we just want the .obj files
all: $(ALL)

clean:
	rm -f *.o $(ALL)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c
#the above command is to complie *.c files
gf_table.o: multilib.h gf_table.h
w4.o: multilib.h gf_table.h w_x.h
w8.o: multilib.h gf_table.h w_x.h
w16.o: multilib.h gf_table.h w_x.h
w32.o: multilib.h gf_table.h w_x.h
w64.o: multilib.h gf_table.h w_x.h
common.o: multilib.h common.h
#w128.o: multilib.h gf_table.h w_x.h
