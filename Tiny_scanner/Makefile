CC = gcc
TARGET = 20191574


all : $(TARGET)

$(TARGET) :
	$(CC) -c main.c
	$(CC) -c util.c
	lex tiny.l
	$(CC) -c lex.yy.c
	$(CC) -g -o 20191574 main.o util.o lex.yy.o -ll


