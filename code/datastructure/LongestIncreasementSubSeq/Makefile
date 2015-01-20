
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
OBJS+=$(patsubst %.cc, %.o, $(wildcard *.cc))

all:$(OBJS)

%.o:%.cc
	gcc -o $@ $^ -g -Wall -DDEBUG

clean:
	rm -rf $(OBJS)
