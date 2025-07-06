# Makefile for modular shell

CC = gcc
CFLAGS = -Wall -g
OBJS = main.o parser.o builtins.o executor.o
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
