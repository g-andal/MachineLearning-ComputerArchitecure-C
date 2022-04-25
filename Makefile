CC=cc
CFLAGS=-g -Wall -Werror -fsanitize=address
ml: ml.o
	$(CC) $(CFLAGS) -o $@ $^
ml.o: ml.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f -r list
	rm -f -r *.o
	clear