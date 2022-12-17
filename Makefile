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

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp fortune $(DESTDIR)$(PREFIX)/bin/fortune
	chmod 755 $(DESTDIR)$(PREFIX)/bin/fortune

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin/fortune

.PHONY: all clean install uninstall
