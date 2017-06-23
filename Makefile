FLAGS =-Wall -Wextra -Werror -pedantic
CC=gcc $(FLAGS)
OBJECTS= banhammer banhammer.o aes.o ll.o bf.o hash.o lex.yy.o

.PHONY:	all
all:	banhammer.c aes.c ll.c bf.c hash.c
	gcc -c banhammer.c
	$(CC) -c aes.c ll.c bf.c hash.c
	flex words.l
	gcc -c lex.yy.c
	$(CC) -g -o  $(OBJECTS) -lfl
.PHONY: make
make:
	gcc -c banhammer.c
	$(CC) -c aes.c ll.c bf.c hash.c
	flex words.l
	gcc -c lex.yy.c
	$(CC) -g -o  $(OBJECTS) -lfl
.PHONY: clean
clean:
	rm $(OBJECTS)
