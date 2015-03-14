CFLAGS= -g -std=c99 -lpthread
COMPILE = $(CC) $(CFLAGS)

OBJS=$(patsubst %.c, %.o, $(wildcard *.c))

all:cacu

cacu:$(OBJS)
	gcc -o cacu $^ $(CFLAGS)

%.o:%.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS)
