
OBJS=$(patsubst %.c, %.o, $(wildcard *.c))
OBJS+=$(patsubst %.cc, %.o, $(wildcard *.cc))

all:$(OBJS)

%.o:%.cc
	g++ -o $@ $^ -g -DDEBUG

clean:
	rm -rf $(OBJS)
