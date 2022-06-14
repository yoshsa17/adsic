SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

stack_array:
	gcc -o stack_array.o stack_array.c
	./stack_array.o

stack_linkedlist:
	gcc -o stack_linkedlist.o stack_linkedlist.c
	./stack_linkedlist.o

clean:
	rm -f $(OBJS) *.o *~ tmp*

.PHONY: clean