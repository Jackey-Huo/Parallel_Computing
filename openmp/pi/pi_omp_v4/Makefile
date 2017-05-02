default: main

cc = g++
CFLAGS = -O3 -fopenmp

pi_omp: pi_omp.o
	$(CC) $(CFLAGS) pi_omp.o -o pi_omp

pi_omp.o: main.c
	$(CC) $(CFLAGS) -c main.c -o pi_omp.o

serial: pi.o
	$(CC) $(CFLAGS) pi.o -o pi

pi.o: main.c
	$(CC) $(CFLAGS) -c main.c -o pi.o

clean:
	rm -rf ./*.o pi_omp pi

run: pi_omp
	./pi_omp

run_serial: pi
	./pi
