TARGET = river
CC=gcc
OBJS = \
  lex.yy.o\
  y.tab.o\
  main.o\
  interface.o\
  create.o\
  execute.o\
  eval.o\
  string.o\
  string_pool.o\
  util.o\
  native.o\
  error.o\
  error_message.o\
  ./memory/mem.o\
  ./debug/dbg.o
CFLAGS = -c -g -Wall -Wswitch-enum -ansi -pedantic -DDEBUG
INCLUDES = \

$(TARGET):$(OBJS)
	cd ./memory; $(MAKE);
	cd ./debug; $(MAKE);
	$(CC) $(OBJS) -o $@ -lm
clean:
	rm -f *.o lex.yy.c y.tab.c y.tab.h *~
