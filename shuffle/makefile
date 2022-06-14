SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

fisher:
	gcc -o fisher_yates_shuffle.o fisher_yates_shuffle.c
	./fisher_yates_shuffle.o

clean:
	rm -f $(OBJS) *.o *~ tmp* *.out

.PHONY: clean