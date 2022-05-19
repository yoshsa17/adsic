SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

main:  $(OBJS)

$(OBJS): linkedlist.h

clean:
	rm -f main *.o *~ tmp*

.PHONY: clean