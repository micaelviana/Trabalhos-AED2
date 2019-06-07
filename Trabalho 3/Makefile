output: main.o arquivo.o arvore_id.o arvore_sem_id.o hash.o
	gcc main.o arquivo.o arvore_id.o arvore_sem_id.o hash.o -o output

main.o: main.c
	gcc -c main.c -Wall

arquivo.o: arquivo.h arquivo.c
	gcc -c arquivo.c -Wall

arvore_id.o: arvore_id.h arvore_id.c
	gcc -c arvore_id.c -Wall

arvore_sem_id.o: arvore_sem_id.h arvore_sem_id.c
	gcc -c arvore_sem_id.c -Wall

hash.o: hash.h hash.c
	gcc -c hash.c -Wall

clean:
	rm *.o