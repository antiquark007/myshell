# Makefile for modular shell with readline and prompt

CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lreadline
OBJS = main.o parser.o builtins.o executor.o prompt.o history.o
TARGET = myshell

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET)
