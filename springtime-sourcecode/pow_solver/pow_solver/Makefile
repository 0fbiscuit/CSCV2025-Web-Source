CC = gcc
CFLAGS = -O3 -march=native -Wall
LDFLAGS = -lssl -lcrypto

pow_solver: pow_solver.c
	$(CC) $(CFLAGS) -o pow_solver pow_solver.c $(LDFLAGS)

clean:
	rm -f pow_solver

.PHONY: clean