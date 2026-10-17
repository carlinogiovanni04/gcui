CC = clang
CFLAGS = -fsanitize=address -Wall -Wextra -Werror
LDFLAGS = -lSDL3 -lSDL3_ttf
INCLUDE = include/
SRC = examples/example.c
OUT = bin/gcui_test

SDL_VER = 3.4.16
SDL_TTF_VER = 3.2.2
VENDOR = vendor
SDL_PREFIX = $(VENDOR)/SDL3-$(SDL_VER)/x86_64-w64-mingw32
SDL_TTF_PREFIX = $(VENDOR)/SDL3_ttf-$(SDL_TTF_VER)/x86_64-w64-mingw32
MINGW_CC = x86_64-w64-mingw32-gcc
MINGW_CFLAGS = -Wall -Wextra -Werror
MINGW_CPPFLAGS = -I$(SDL_PREFIX)/include -I$(SDL_TTF_PREFIX)/include
MINGW_LDFLAGS = -L$(SDL_PREFIX)/lib -L$(SDL_TTF_PREFIX)/lib -lSDL3 -lSDL3_ttf
OUT_WIN = bin/gcui_test.exe

all: $(OUT)
$(OUT):
	mkdir -p bin/
	$(CC) $(SRC) $(CFLAGS) -I$(INCLUDE) -o $(OUT) $(LDFLAGS)

windows: vendor-sdl
	mkdir -p bin/
	$(MINGW_CC) $(SRC) $(MINGW_CFLAGS) -I$(INCLUDE) $(MINGW_CPPFLAGS) -o $(OUT_WIN) $(MINGW_LDFLAGS)
	cp $(SDL_PREFIX)/bin/SDL3.dll $(SDL_TTF_PREFIX)/bin/SDL3_ttf.dll bin/

vendor-sdl:
	mkdir -p $(VENDOR)
	if [ ! -d $(SDL_PREFIX) ]; then \
		curl -sL -o $(VENDOR)/sdl3-mingw.tar.gz https://github.com/libsdl-org/SDL/releases/download/release-$(SDL_VER)/SDL3-devel-$(SDL_VER)-mingw.tar.gz && \
		tar xzf $(VENDOR)/sdl3-mingw.tar.gz -C $(VENDOR) && \
		rm $(VENDOR)/sdl3-mingw.tar.gz; \
	fi
	if [ ! -d $(SDL_TTF_PREFIX) ]; then \
		curl -sL -o $(VENDOR)/sdl3_ttf-mingw.tar.gz https://github.com/libsdl-org/SDL_ttf/releases/download/release-$(SDL_TTF_VER)/SDL3_ttf-devel-$(SDL_TTF_VER)-mingw.tar.gz && \
		tar xzf $(VENDOR)/sdl3_ttf-mingw.tar.gz -C $(VENDOR) && \
		rm $(VENDOR)/sdl3_ttf-mingw.tar.gz; \
	fi

clean:
	rm -rf bin/
