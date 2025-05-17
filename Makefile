CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
BIN = calias

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

install: $(BIN)
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BIN) $(DESTDIR)$(BINDIR)
	chmod +x $(DESTDIR)$(BINDIR)/$(BIN)
	@echo "✅ Installed $(BIN) to $(DESTDIR)$(BINDIR)"
	@echo "⚙️  Running postinstall as user: $(SUDO_USER)"
	@sudo -u $(SUDO_USER) sh scripts/postinstall.sh || true

uninstall:
	rm -f $(DESTDIR)$(BINDIR)/$(BIN)
	@echo "❌ Uninstalled $(BIN) from $(DESTDIR)$(BINDIR)"

clean:
	rm -f src/*.o $(BIN)

run: all
	./$(BIN)

