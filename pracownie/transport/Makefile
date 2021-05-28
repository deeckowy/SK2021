FILES = transport.cpp main.cpp utils.cpp inits.cpp
OBJS = transport.o inits.o utils.o main.o

all: transport

transport: $(FILES)
	g++ -c -O3 -Wall -Werror -Wextra $(FILES)
	g++ -o transport $(OBJS)

distclean:
	rm $(OBJS) transport

clean:
	rm $(OBJS)
