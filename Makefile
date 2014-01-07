CC=gcc

bin:
	mkdir -p bin

bin/nat: bin src/nat.c src/bigint.c include/bigint.h
	$(CC) -Iinclude -std=c11 src/nat.c src/bigint.c -o bin/nat

bin/fib: bin src/fib.c src/bigint.c include/bigint.h
	$(CC) -Iinclude -std=c11 src/fib.c src/bigint.c -o bin/fib