include config.mk

BIN=fortune

SRC=fortune.c

all: $(BIN)

$(BIN): $(SRC)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	rm -f $(wildcard src/*.o) $(BIN)
