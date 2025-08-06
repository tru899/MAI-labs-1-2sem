CC = gcc
CFLAGS = -g -Wall -std=c99 -Werror
DEBUGGER = gdb
TARGET = deck.exe
SOURCES = deck.c main26.c

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

debug: $(TARGET)
	$(DEBUGGER) $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
