default: main

cc = gcc
CFLAGS = -O3 -fopenmp

pi_omp: pi_omp.o
	$(CC) $(CFLAGS) pi_omp.o -o pi_omp

pi_omp.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o pi_omp.o

serial: pi.o
	$(CC) $(CFLAGS) pi.o -o pi

pi.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o pi.o

clean:
	rm -rf ./*.o pi_omp pi

run: pi_omp
	./pi_omp

run_serial: pi
	./pi
