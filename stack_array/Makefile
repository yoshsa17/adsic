SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

main:  $(OBJS)

$(OBJS): stack_array.h

clean:
	rm -f main *.o *~ tmp*

.PHONY: clean