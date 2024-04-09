CC = gcc
CFLAGS = -Wall -Wextra

all: main 3CNFSAT A_to_B independente_set_from_A

independente_set_from_A: independente_set_from_A.o
	$(CC) $(CFLAGS) independente_set_from_A.o -o indep_a

independente_set_from_A.o: independente_set_from_A.c
	$(CC) $(CFLAGS) -c independente_set_from_A.c

A_to_B: A_to_B.o
	$(CC) $(CFLAGS) A_to_B.o -o a_b

A_to_B.o: A_to_B.c
	$(CC) $(CFLAGS) -c A_to_B.c

3CNFSAT: 3CNFSAT.o
	$(CC) $(CFLAGS) 3CNFSAT.o -o sat

3CNFSAT.o: 3CNFSAT.c
	$(CC) $(CFLAGS) -c 3CNFSAT.c

main: main.o
	$(CC) $(CFLAGS) main.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -rf *.o main
