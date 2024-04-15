CC = gcc

all: main 3CNFSAT A_to_B B_to_A

B_to_A: B_to_A.c
	$(CC) B_to_A.c -o B_to_A

A_to_B: A_to_B.c
	$(CC) A_to_B.c -o A_to_B

3CNFSAT: 3CNFSAT.c
	$(CC) 3CNFSAT.c -o 3CNFSAT

main: main.c
	$(CC) main.c -o main

clean:
	rm -rf *.o main A_to_B B_to_A 3CNFSAT
