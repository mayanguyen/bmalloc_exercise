CFLAGS=-g
# -g includes debugging symbols

all: simplebtree bmemtest

simplebtree: simplebtree.o bmem.o
	gcc -o simplebtree simplebtree.o bmem.o

bmemtest: bmemtest.o bmem.o
	gcc -o bmemtest bmemtest.o bmem.o

test: simplebtree
	for i in {1..25}; do echo $$RANDOM; done | ./simplebtree

%.o:%.c
	gcc -c -o $@ $< $(CFLAGS)

# targets that don't depend on real file dependencies
.PHONY: clean test

# delete intermediate files
clean:
	$(RM) simplebtree *.o *~
