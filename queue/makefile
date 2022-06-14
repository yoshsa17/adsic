SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

queue_array:
	gcc -o queue_array.o queue_array.c
	./queue_array.o

queue_linkedlist:
	gcc -o queue_linkedlist.o queue_linkedlist.c
	./queue_linkedlist.o

clean:
	rm -f $(OBJS) *.o *~ tmp*

.PHONY: clean