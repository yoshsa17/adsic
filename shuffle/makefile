SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

fisher:
	gcc -o fisher_yates_shuffle fisher_yates_shuffle.c
	./fisher_yates_shuffle

clean:
	rm -f fisher_yates_shuffle *.o *~ tmp* *.out

.PHONY: clean