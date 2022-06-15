SRCS=$(wildcard *.c)  
OBJS=$(SRCS:.c=)

merge:
	gcc -o merge_sort merge_sort.c
	./merge_sort

quick:
	gcc -o quick_sort quick_sort.c
	./quick_sort

clean:
	rm -f ${OBJS} *.o *~ tmp* *.out

.PHONY: clean