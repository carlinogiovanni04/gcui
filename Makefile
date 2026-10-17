CC = clang
CFLAGS = -fsanitize=address -Wall -Wextra -Werror
LDFLAGS = -lSDL3 -lSDL3_ttf
INCLUDE = include/
SRC = examples/example.c
OUT = bin/gcui_test

all: $(OUT)
$(OUT):
	mkdir -p bin/
	$(CC) $(SRC) $(CFLAGS) -I$(INCLUDE) -o $(OUT) $(LDFLAGS)

clean:
	rm -rf bin/
