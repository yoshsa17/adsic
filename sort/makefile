SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=.o)

merge:
	gcc -o merge_sort.o merge_sort.c
	./merge_sort.o

quick:
	gcc -o quick_sort.o quick_sort.c
	./quick_sort.o

clean:
	rm -f $(OBJS) *.o *~ tmp* *.out

.PHONY: clean