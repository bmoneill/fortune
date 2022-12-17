include config.mk

all: fortune

fortune: fortune.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f fortune

install: all
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp fortune $(DESTDIR)$(PREFIX)/bin/fortune
	chmod 755 $(DESTDIR)$(PREFIX)/bin/fortune

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/bin/fortune

.PHONY: all clean install uninstall
