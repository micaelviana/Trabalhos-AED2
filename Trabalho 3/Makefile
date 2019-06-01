output: main.o arquivo.o arvore_id.o
	gcc main.o arquivo.o arvore_id.o -o output

main.o: main.c
	gcc -O -c main.c -Wall

arquivo.o: arquivo.h arquivo.c
	gcc -O -c arquivo.c -Wall

arvore_id.o: arvore_id.h arvore_id.c
	gcc -O -c arvore_id.c -Wall

clean:
	rm *.o