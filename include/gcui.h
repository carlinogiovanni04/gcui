#ifndef GCUI_H
#define GCUI_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t GCU8;
typedef uint16_t GCU16;
typedef uint32_t GCU32;
typedef uint64_t GCU64;

typedef int8_t GCI8;
typedef int16_t GCI16;
typedef int32_t GCI32;
typedef int64_t GCI64;

typedef float GCF32;
typedef double GCF64;

typedef size_t GCUSIZE;
typedef uintptr_t GCUPTR;

typedef GCI32 GCB32;

#define GC_TRUE (GCB32)1
#define GC_FALSE (GCB32)0
#define GC_ASSERT(c)                                                           \
  if (!(c)) {                                                                  \
    printf("ASSERTION FAILED - %s:%d", __FILE__, __LINE__);                    \
    exit(1);                                                                   \
  }
#define GC_KB(n) ((GCUSIZE)(n) * 1024u)
#define GC_MB(n) ((GCUSIZE)(n) * 1024u * 1024u)
#define GC_GB(n) ((GCUSIZE)(n) * 1024u * 1024u * 1024u)

#define GC_DT_MAX (GCF32)0.1f

typedef struct {
  void *base;
  GCUPTR capacity;
  GCUPTR used;
} GCARENA;

static inline GCARENA *gc_arena_create(GCUPTR size) {
  GCARENA *result = (GCARENA *)malloc(sizeof(GCARENA));
  result->base = malloc(size);
  result->capacity = size;
  result->used = 0;
  return result;
}

static inline void *gc_arena_push(GCARENA *arena, GCUPTR size) {
  GC_ASSERT(arena);
  GC_ASSERT(size <= arena->capacity - arena->used);

  void *result = (char *)arena->base + arena->used;
  arena->used += size;
  return result;
}

static inline void gc_arena_pop(GCARENA *arena, GCUPTR size) {
  GC_ASSERT(arena);
  GC_ASSERT(size <= arena->used);

  arena->used -= size;
}

static inline void gc_arena_clear(GCARENA *arena) {
  GC_ASSERT(arena);

  arena->used = 0;
}

static inline void gc_arena_destroy(GCARENA *arena) {
  free(arena->base);
  free(arena);
}

typedef struct {
  GCU8 *data;
  GCUSIZE size;
} GCSTRING8;

static inline GCSTRING8 *gc_str8_create(GCARENA *arena, const char *cStr) {
  GC_ASSERT(arena);
  GC_ASSERT(cStr);

  GCUSIZE len = strlen(cStr);
  GCSTRING8 *result = (GCSTRING8 *)gc_arena_push(arena, sizeof(GCSTRING8));
  result->size = len;
  result->data = (GCU8 *)gc_arena_push(arena, len + 1);
  memcpy(result->data, cStr, len + 1);

  return result;
}

typedef struct {
  GCU32 x, y;
} GCVEC2U32;

typedef struct {
  GCF32 x, y, w, h;
} GCRECT;

typedef struct {
  GCU8 r, g, b, a;
} GCCOLOR;

static inline GCCOLOR gc_color(GCU8 r, GCU8 g, GCU8 b, GCU8 a) {
  GCCOLOR c = {r, g, b, a};
  return c;
}

typedef GCI32 GCKEY;

#define GC_KEY_COUNT 512

#define GC_KEY_A ((GCKEY)4)
#define GC_KEY_B ((GCKEY)5)
#define GC_KEY_C ((GCKEY)6)
#define GC_KEY_D ((GCKEY)7)
#define GC_KEY_E ((GCKEY)8)
#define GC_KEY_F ((GCKEY)9)
#define GC_KEY_G ((GCKEY)10)
#define GC_KEY_H ((GCKEY)11)
#define GC_KEY_I ((GCKEY)12)
#define GC_KEY_J ((GCKEY)13)
#define GC_KEY_K ((GCKEY)14)
#define GC_KEY_L ((GCKEY)15)
#define GC_KEY_M ((GCKEY)16)
#define GC_KEY_N ((GCKEY)17)
#define GC_KEY_O ((GCKEY)18)
#define GC_KEY_P ((GCKEY)19)
#define GC_KEY_Q ((GCKEY)20)
#define GC_KEY_R ((GCKEY)21)
#define GC_KEY_S ((GCKEY)22)
#define GC_KEY_T ((GCKEY)23)
#define GC_KEY_U ((GCKEY)24)
#define GC_KEY_V ((GCKEY)25)
#define GC_KEY_W ((GCKEY)26)
#define GC_KEY_X ((GCKEY)27)
#define GC_KEY_Y ((GCKEY)28)
#define GC_KEY_Z ((GCKEY)29)

#define GC_KEY_1 ((GCKEY)30)
#define GC_KEY_2 ((GCKEY)31)
#define GC_KEY_3 ((GCKEY)32)
#define GC_KEY_4 ((GCKEY)33)
#define GC_KEY_5 ((GCKEY)34)
#define GC_KEY_6 ((GCKEY)35)
#define GC_KEY_7 ((GCKEY)36)
#define GC_KEY_8 ((GCKEY)37)
#define GC_KEY_9 ((GCKEY)38)
#define GC_KEY_0 ((GCKEY)39)

#define GC_KEY_RETURN ((GCKEY)40)
#define GC_KEY_ESCAPE ((GCKEY)41)
#define GC_KEY_BACKSPACE ((GCKEY)42)
#define GC_KEY_TAB ((GCKEY)43)
#define GC_KEY_SPACE ((GCKEY)44)

#define GC_KEY_F1 ((GCKEY)58)
#define GC_KEY_F2 ((GCKEY)59)
#define GC_KEY_F3 ((GCKEY)60)
#define GC_KEY_F4 ((GCKEY)61)
#define GC_KEY_F5 ((GCKEY)62)
#define GC_KEY_F6 ((GCKEY)63)
#define GC_KEY_F7 ((GCKEY)64)
#define GC_KEY_F8 ((GCKEY)65)
#define GC_KEY_F9 ((GCKEY)66)
#define GC_KEY_F10 ((GCKEY)67)
#define GC_KEY_F11 ((GCKEY)68)
#define GC_KEY_F12 ((GCKEY)69)

#define GC_KEY_HOME ((GCKEY)74)
#define GC_KEY_PAGEUP ((GCKEY)75)
#define GC_KEY_DELETE ((GCKEY)76)
#define GC_KEY_END ((GCKEY)77)
#define GC_KEY_PAGEDOWN ((GCKEY)78)
#define GC_KEY_RIGHT ((GCKEY)79)
#define GC_KEY_LEFT ((GCKEY)80)
#define GC_KEY_DOWN ((GCKEY)81)
#define GC_KEY_UP ((GCKEY)82)

#define GC_KEY_LCTRL ((GCKEY)224)
#define GC_KEY_LSHIFT ((GCKEY)225)
#define GC_KEY_LALT ((GCKEY)226)
#define GC_KEY_LGUI ((GCKEY)227)
#define GC_KEY_RCTRL ((GCKEY)228)
#define GC_KEY_RSHIFT ((GCKEY)229)
#define GC_KEY_RALT ((GCKEY)230)
#define GC_KEY_RGUI ((GCKEY)231)

typedef struct {
  GCSTRING8 *title;
  GCVEC2U32 dimensions;
  GCVEC2U32 position;
  void *handle;
  void *renderer;
  GCB32 quitRequested;
  GCB32 currKeys[GC_KEY_COUNT];
  GCB32 pressedThisFrame[GC_KEY_COUNT];
  GCU64 perfFreq;
  GCU64 lastCounter;
  GCF32 dt;
  GCF32 elapsed;
  GCF32 mouseX;
  GCF32 mouseY;
  GCB32 mouseDown;
  GCB32 mousePressed;
  GCB32 mouseReleased;
  GCU8 textInput[128];
  GCUSIZE textLen;
  GCCOLOR clearColor;
} GCWINDOW;

static inline GCWINDOW *gc_window_create(GCARENA *arena, const char *title,
                                         GCU32 width, GCU32 height,
                                         GCB32 fullscreen) {
  GC_ASSERT(arena);
  GC_ASSERT(title);

  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
    printf("SDL_Init failed: %s\n", SDL_GetError());
    return NULL;
  }
  if (!TTF_Init()) {
    printf("TTF_Init failed: %s\n", SDL_GetError());
  }

  GCWINDOW *window = (GCWINDOW *)gc_arena_push(arena, sizeof(GCWINDOW));
  memset(window, 0, sizeof(*window));
  window->dimensions = (GCVEC2U32){width, height};
  window->position = (GCVEC2U32){0, 0};
  window->title = gc_str8_create(arena, title);
  window->clearColor = gc_color(24, 24, 27, 255);
  window->perfFreq = SDL_GetPerformanceFrequency();
  window->lastCounter = SDL_GetPerformanceCounter();

  SDL_WindowFlags flags = 0;

  if (fullscreen)
    flags |= SDL_WINDOW_FULLSCREEN;

  SDL_Window *handle = SDL_CreateWindow(title, (int)width, (int)height, flags);
  if (!handle) {
    printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
    return NULL;
  }
  window->handle = handle;
  SDL_ShowWindow(handle);
  SDL_RaiseWindow(handle);
  SDL_StartTextInput(handle);

  SDL_Renderer *renderer = SDL_CreateRenderer(handle, NULL);
  if (!renderer) {
    printf("SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(handle);
    window->handle = NULL;
    return NULL;
  }
  window->renderer = renderer;

  SDL_SetRenderDrawColor(renderer, window->clearColor.r, window->clearColor.g,
                         window->clearColor.b, window->clearColor.a);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  return window;
}

static inline void gc_window_begin(GCWINDOW *window) {
  GC_ASSERT(window);
  GC_ASSERT(window->handle);
  GC_ASSERT(window->renderer);

  GCU64 now = SDL_GetPerformanceCounter();
  if (window->perfFreq > 0) {
    GCF64 delta = (GCF64)(now - window->lastCounter) / (GCF64)window->perfFreq;
    window->dt = (GCF32)delta;
    if (window->dt > GC_DT_MAX)
      window->dt = GC_DT_MAX;
    if (window->dt < 0.0f)
      window->dt = 0.0f;
  } else {
    window->dt = 0.0f;
  }
  window->lastCounter = now;
  window->elapsed += window->dt;

  for (GCI32 i = 0; i < GC_KEY_COUNT; ++i)
    window->pressedThisFrame[i] = GC_FALSE;

  window->mousePressed = GC_FALSE;
  window->mouseReleased = GC_FALSE;
  window->textLen = 0;
  window->textInput[0] = 0;

  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      window->quitRequested = GC_TRUE;
    } else if (event.type == SDL_EVENT_KEY_DOWN) {
      SDL_Scancode sc = event.key.scancode;
      GCB32 nav = (sc == SDL_SCANCODE_BACKSPACE || sc == SDL_SCANCODE_DELETE ||
                   sc == SDL_SCANCODE_LEFT || sc == SDL_SCANCODE_RIGHT ||
                   sc == SDL_SCANCODE_HOME || sc == SDL_SCANCODE_END)
                      ? GC_TRUE
                      : GC_FALSE;
      if (sc >= 0 && sc < GC_KEY_COUNT && (!event.key.repeat || nav))
        window->pressedThisFrame[sc] = GC_TRUE;
    } else if (event.type == SDL_EVENT_TEXT_INPUT) {
      GCUSIZE n = strlen(event.text.text);
      GCUSIZE room = sizeof(window->textInput) - window->textLen - 1;
      if (n > room)
        n = room;
      memcpy(window->textInput + window->textLen, event.text.text, n);
      window->textLen += n;
      window->textInput[window->textLen] = 0;
    }
  }

  GCI32 keyCount = 0;
  const bool *state = SDL_GetKeyboardState((int *)&keyCount);
  if (state) {
    GCI32 n = keyCount < GC_KEY_COUNT ? keyCount : GC_KEY_COUNT;
    for (GCI32 i = 0; i < n; ++i)
      window->currKeys[i] = state[i] ? GC_TRUE : GC_FALSE;
  }

  GCF32 mx = 0.0f;
  GCF32 my = 0.0f;
  SDL_MouseButtonFlags buttons = SDL_GetMouseState((float *)&mx, (float *)&my);
  GCB32 down = (buttons & SDL_BUTTON_LMASK) ? GC_TRUE : GC_FALSE;
  window->mousePressed = (down && !window->mouseDown) ? GC_TRUE : GC_FALSE;
  window->mouseReleased = ((!down) && window->mouseDown) ? GC_TRUE : GC_FALSE;
  window->mouseDown = down;
  window->mouseX = (GCF32)mx;
  window->mouseY = (GCF32)my;

  SDL_Renderer *renderer = (SDL_Renderer *)window->renderer;
  SDL_SetRenderDrawColor(renderer, window->clearColor.r, window->clearColor.g,
                         window->clearColor.b, window->clearColor.a);
  SDL_RenderClear(renderer);
}

static inline void gc_window_end(GCWINDOW *window) {
  GC_ASSERT(window);
  GC_ASSERT(window->renderer);

  SDL_RenderPresent((SDL_Renderer *)window->renderer);
}

static inline void gc_window_update(GCWINDOW *window) {
  gc_window_begin(window);
  gc_window_end(window);
}

static inline GCB32 gc_window_should_quit(GCWINDOW *window) {
  GC_ASSERT(window);

  return window->quitRequested;
}

static inline GCB32 gc_window_key_currently_pressed(GCWINDOW *window,
                                                    GCKEY key) {
  GC_ASSERT(window);
  if (key < 0 || key >= GC_KEY_COUNT)
    return GC_FALSE;

  return window->currKeys[key];
}

static inline GCB32 gc_window_key_was_pressed(GCWINDOW *window, GCKEY key) {
  GC_ASSERT(window);
  if (key < 0 || key >= GC_KEY_COUNT)
    return GC_FALSE;

  return window->pressedThisFrame[key];
}

static inline GCF32 gc_window_dt(GCWINDOW *window) {
  GC_ASSERT(window);

  return window->dt;
}

static inline GCF32 gc_window_elapsed(GCWINDOW *window) {
  GC_ASSERT(window);

  return window->elapsed;
}

static inline void gc_window_set_clear(GCWINDOW *window, GCCOLOR color) {
  GC_ASSERT(window);

  window->clearColor = color;
}

static inline void gc_window_destroy(GCWINDOW *window) {
  if (!window)
    return;
  if (window->renderer) {
    SDL_DestroyRenderer((SDL_Renderer *)window->renderer);
    window->renderer = NULL;
  }
  if (window->handle) {
    SDL_StopTextInput((SDL_Window *)window->handle);
    SDL_DestroyWindow((SDL_Window *)window->handle);
    window->handle = NULL;
  }

  SDL_Quit();
  TTF_Quit();
}

static inline void gc_sleep_ms(GCU32 ms) { SDL_Delay((Uint32)ms); }

static inline GCB32 gc_rect_contains(GCRECT rect, GCF32 x, GCF32 y) {
  return (x >= rect.x && x < rect.x + rect.w && y >= rect.y &&
          y < rect.y + rect.h)
             ? GC_TRUE
             : GC_FALSE;
}

static inline void gc_draw_fill(GCWINDOW *window, GCRECT rect, GCCOLOR color) {
  GC_ASSERT(window);
  GC_ASSERT(window->renderer);

  SDL_Renderer *renderer = (SDL_Renderer *)window->renderer;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_FRect r = {rect.x, rect.y, rect.w, rect.h};
  SDL_RenderFillRect(renderer, &r);
}

static inline void gc_draw_outline(GCWINDOW *window, GCRECT rect,
                                   GCCOLOR color) {
  GC_ASSERT(window);
  GC_ASSERT(window->renderer);

  SDL_Renderer *renderer = (SDL_Renderer *)window->renderer;
  SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
  SDL_FRect r = {rect.x, rect.y, rect.w, rect.h};
  SDL_RenderRect(renderer, &r);
}

typedef struct {
  GCWINDOW *window;
  TTF_Font *font;
  GCF32 mouseX;
  GCF32 mouseY;
  GCB32 mouseDown;
  GCB32 mousePressed;
  GCB32 mouseReleased;
  GCF32 dt;
  GCF32 time;
  GCU32 hot;
  GCU32 active;
  GCU32 nextId;
  GCU32 focus;
  GCUSIZE cursor;
  GCU32 open;
  const char *input;
  GCUSIZE inputLen;
  GCB32 popupOpen;
  GCRECT popupList;
  const char **popupItems;
  GCI32 popupCount;
  GCI32 popupSelected;
  GCI32 popupHot;
  GCF32 popupRowH;
} GCUI;

static inline GCUI *gc_ui_create(GCARENA *arena, GCWINDOW *window) {
  ;
  GC_ASSERT(window);

  GCUI *result = (GCUI *)gc_arena_push(arena, sizeof(GCUI));
  memset(result, 0, sizeof(*result));
  result->window = window;

  return result;
}

static inline GCB32 gc_ui_set_font(GCUI *ui, const char *path, GCF32 size) {
  GC_ASSERT(ui);
  GC_ASSERT(path);

  if (ui->font) {
    TTF_CloseFont(ui->font);
    ui->font = NULL;
  }
  TTF_Font *font = TTF_OpenFont(path, (float)size);
  if (!font)
    return GC_FALSE;
  ui->font = font;
  return GC_TRUE;
}

static inline GCB32 gc_ui_load_default_font(GCUI *ui, GCF32 size) {
  GC_ASSERT(ui);

  const char *sysRoot = getenv("SystemRoot");
  if (!sysRoot)
    sysRoot = getenv("windir");
  if (sysRoot && sysRoot[0]) {
    static const char *winNames[] = {
        "segoeui.ttf", "arial.ttf", "calibri.ttf", "tahoma.ttf", "verdana.ttf",
    };
    for (GCUSIZE i = 0; i < sizeof(winNames) / sizeof(winNames[0]); ++i) {
      char winPath[512];
      snprintf(winPath, sizeof(winPath), "%s\\Fonts\\%s", sysRoot, winNames[i]);
      winPath[sizeof(winPath) - 1] = 0;
      if (gc_ui_set_font(ui, winPath, size))
        return GC_TRUE;
    }
  }

  static const char *paths[] = {
      "C:\\Windows\\Fonts\\segoeui.ttf",
      "C:\\Windows\\Fonts\\arial.ttf",
      "C:\\Windows\\Fonts\\calibri.ttf",
      "C:\\Windows\\Fonts\\tahoma.ttf",
      "C:\\Windows\\Fonts\\verdana.ttf",
      "/System/Library/Fonts/Supplemental/Arial.ttf",
      "/System/Library/Fonts/Supplemental/Verdana.ttf",
      "/System/Library/Fonts/Supplemental/Tahoma.ttf",
      "/Library/Fonts/Arial.ttf",
      "/System/Library/Fonts/Helvetica.ttc",
      "/usr/share/fonts/TTF/DejaVuSans.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/usr/share/fonts/Adwaita/AdwaitaSans-Regular.ttf",
      "/usr/share/fonts/noto/NotoSans-Regular.ttf",
  };
  for (GCUSIZE i = 0; i < sizeof(paths) / sizeof(paths[0]); ++i) {
    if (gc_ui_set_font(ui, paths[i], size))
      return GC_TRUE;
  }
  return GC_FALSE;
}

static inline void gc_ui_set_font_size(GCUI *ui, GCF32 size) {
  GC_ASSERT(ui);

  if (ui->font)
    TTF_SetFontSize(ui->font, (float)size);
}

static inline void gc_ui_begin(GCUI *ui) {
  GC_ASSERT(ui);
  GC_ASSERT(ui->window);

  GCWINDOW *window = ui->window;
  ui->mouseX = window->mouseX;
  ui->mouseY = window->mouseY;
  ui->mouseDown = window->mouseDown;
  ui->mousePressed = window->mousePressed;
  ui->mouseReleased = window->mouseReleased;
  ui->dt = window->dt;
  ui->time = window->elapsed;
  ui->input = (const char *)window->textInput;
  ui->inputLen = window->textLen;
  ui->nextId = 1;
  ui->hot = 0;
  ui->popupOpen = GC_FALSE;
  ui->popupHot = -1;
}

static inline void gc_popup_draw(GCUI *ui);

static inline void gc_ui_end(GCUI *ui) {
  GC_ASSERT(ui);

  if (!ui->mouseDown)
    ui->active = 0;
  if (!ui->focus)
    SDL_SetTextInputArea((SDL_Window *)ui->window->handle, NULL, 0);
  if (ui->popupOpen)
    gc_popup_draw(ui);
}

static inline void gc_ui_destroy(GCUI *ui) {
  if (!ui)
    return;
  if (ui->font) {
    TTF_CloseFont(ui->font);
    ui->font = NULL;
  }
}

static inline void gc_ui_text(GCUI *ui, const char *text, GCF32 x, GCF32 y,
                              GCCOLOR color) {
  GC_ASSERT(ui);
  if (!ui->font || !text || !text[0])
    return;

  SDL_Renderer *renderer = (SDL_Renderer *)ui->window->renderer;
  SDL_Color c = {color.r, color.g, color.b, color.a};
  SDL_Surface *surface = TTF_RenderText_Blended(ui->font, text, 0, c);
  if (!surface)
    return;
  GCI32 w = surface->w;
  GCI32 h = surface->h;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  if (!texture)
    return;
  SDL_FRect dst = {x, y, (GCF32)w, (GCF32)h};
  SDL_RenderTexture(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

static inline void gc_text_len(GCUI *ui, const char *text, GCUSIZE len, GCF32 x,
                               GCF32 y, GCCOLOR color) {
  GC_ASSERT(ui);
  if (!ui->font || !text || len == 0)
    return;

  SDL_Renderer *renderer = (SDL_Renderer *)ui->window->renderer;
  SDL_Color c = {color.r, color.g, color.b, color.a};
  SDL_Surface *surface = TTF_RenderText_Blended(ui->font, text, (size_t)len, c);
  if (!surface)
    return;
  GCI32 w = surface->w;
  GCI32 h = surface->h;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_DestroySurface(surface);
  if (!texture)
    return;
  SDL_FRect dst = {x, y, (GCF32)w, (GCF32)h};
  SDL_RenderTexture(renderer, texture, NULL, &dst);
  SDL_DestroyTexture(texture);
}

static inline GCI32 gc_text_width(GCUI *ui, const char *text, GCUSIZE len) {
  GC_ASSERT(ui);
  if (!ui->font || !text)
    return 0;

  GCI32 w = 0;
  GCI32 h = 0;
  if (len == 0)
    return 0;
  if (!TTF_GetStringSize(ui->font, text, (size_t)len, (int *)&w, (int *)&h))
    return 0;
  return w;
}

static inline GCUSIZE gc_text_fit_len(GCUI *ui, const char *text, GCUSIZE len,
                                      GCF32 maxW) {
  GC_ASSERT(ui);
  if ((GCF32)gc_text_width(ui, text, len) <= maxW)
    return len;

  GCUSIZE lo = 0;
  GCUSIZE hi = len;
  while (lo < hi) {
    GCUSIZE mid = (lo + hi + 1) / 2;
    if ((GCF32)gc_text_width(ui, text, mid) <= maxW)
      lo = mid;
    else
      hi = mid - 1;
  }
  while (lo > 0 && (((GCU8)text[lo] & 0xC0) == 0x80))
    lo -= 1;
  return lo;
}

static inline void gc_text_clip_rect(GCUI *ui, GCRECT rect) {
  GC_ASSERT(ui);

  GCI32 clipW = (int)rect.w - 2;
  GCI32 clipH = (int)rect.h - 2;
  if (clipW < 1)
    clipW = 1;
  if (clipH < 1)
    clipH = 1;
  SDL_Rect clip = {(int)rect.x + 1, (int)rect.y + 1, clipW, clipH};
  SDL_SetRenderClipRect((SDL_Renderer *)ui->window->renderer, &clip);
}

static inline void gc_text_clip_clear(GCUI *ui) {
  GC_ASSERT(ui);

  SDL_SetRenderClipRect((SDL_Renderer *)ui->window->renderer, NULL);
}

static inline void gc_text_centered(GCUI *ui, const char *text, GCRECT rect,
                                    GCCOLOR color) {
  GC_ASSERT(ui);
  if (!ui->font || !text || !text[0])
    return;

  GCI32 w = 0;
  GCI32 h = 0;
  if (!TTF_GetStringSize(ui->font, text, 0, (int *)&w, (int *)&h))
    return;

  GCUSIZE len = strlen(text);
  GCF32 dots = 0.0f;
  if ((GCF32)w > rect.w) {
    dots = (GCF32)gc_text_width(ui, "...", 3);
    if (rect.w <= dots)
      return;
    len = gc_text_fit_len(ui, text, len, rect.w - dots);
    w = gc_text_width(ui, text, len) + (GCI32)dots;
  }
  GCF32 x = rect.x + (rect.w - (GCF32)w) * 0.5f;
  GCF32 y = rect.y + (rect.h - (GCF32)h) * 0.5f;
  gc_text_clip_rect(ui, rect);
  gc_text_len(ui, text, len, x, y, color);
  if (dots > 0.0f)
    gc_ui_text(ui, "...", x + (GCF32)w - dots, y, color);
  gc_text_clip_clear(ui);
}

static inline void gc_popup_draw(GCUI *ui) {
  GC_ASSERT(ui);

  gc_draw_fill(ui->window, ui->popupList, gc_color(30, 30, 36, 255));
  gc_draw_outline(ui->window, ui->popupList, gc_color(140, 140, 150, 255));
  for (GCI32 i = 0; i < ui->popupCount; ++i) {
    GCRECT r = {ui->popupList.x, ui->popupList.y + ui->popupRowH * (GCF32)i,
                ui->popupList.w, ui->popupRowH};
    if (i == ui->popupHot)
      gc_draw_fill(ui->window, r, gc_color(50, 120, 220, 255));
    if (i == ui->popupSelected)
      gc_draw_outline(ui->window, r, gc_color(160, 200, 255, 255));
    if (ui->popupItems[i])
      gc_text_centered(ui, ui->popupItems[i],
                       (GCRECT){r.x, r.y, r.w - 8.0f, r.h},
                       gc_color(245, 245, 245, 255));
  }
}

static inline void gc_ui_panel(GCUI *ui, GCRECT rect, GCCOLOR color) {
  GC_ASSERT(ui);

  gc_draw_fill(ui->window, rect, color);
}

static inline void gc_ui_separator(GCUI *ui, GCRECT rect, GCCOLOR color) {
  GC_ASSERT(ui);

  if (rect.w <= 0.0f || rect.h <= 0.0f)
    return;
  if (rect.w >= rect.h) {
    GCF32 y = rect.y + (rect.h - 1.0f) * 0.5f;
    gc_draw_fill(ui->window, (GCRECT){rect.x, y, rect.w, 1.0f}, color);
  } else {
    GCF32 x = rect.x + (rect.w - 1.0f) * 0.5f;
    gc_draw_fill(ui->window, (GCRECT){x, rect.y, 1.0f, rect.h}, color);
  }
}

static inline void gc_ui_label(GCUI *ui, GCRECT rect, const char *text,
                               GCCOLOR color) {
  GC_ASSERT(ui);
  if (!ui->font || !text || !text[0])
    return;

  GCUSIZE len = strlen(text);
  GCF32 dots = 0.0f;
  if ((GCF32)gc_text_width(ui, text, len) > rect.w) {
    dots = (GCF32)gc_text_width(ui, "...", 3);
    if (rect.w <= dots)
      return;
    len = gc_text_fit_len(ui, text, len, rect.w - dots);
  }
  gc_text_clip_rect(ui, rect);
  gc_text_len(ui, text, len, rect.x, rect.y, color);
  if (dots > 0.0f)
    gc_ui_text(ui, "...", rect.x + (GCF32)gc_text_width(ui, text, len), rect.y,
               color);
  gc_text_clip_clear(ui);
}

static inline GCB32 gc_ui_button(GCUI *ui, GCRECT rect, const char *label) {
  GC_ASSERT(ui);

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (inside && ui->mousePressed)
    ui->active = id;

  GCB32 clicked = GC_FALSE;
  if (ui->active == id && ui->mouseReleased) {
    if (inside)
      clicked = GC_TRUE;
    ui->active = 0;
  }

  GCCOLOR fill = gc_color(60, 60, 68, 255);
  GCCOLOR line = gc_color(140, 140, 150, 255);
  if (ui->active == id && ui->mouseDown) {
    fill = gc_color(50, 120, 220, 255);
    line = gc_color(160, 200, 255, 255);
  } else if (ui->hot == id) {
    fill = gc_color(80, 80, 92, 255);
    line = gc_color(180, 180, 190, 255);
  }

  gc_draw_fill(ui->window, rect, fill);
  gc_draw_outline(ui->window, rect, line);
  if (label)
    gc_text_centered(ui, label, rect, gc_color(245, 245, 245, 255));

  return clicked;
}

static inline GCB32 gc_ui_checkbox(GCUI *ui, GCRECT box, const char *label,
                                   GCB32 *value) {
  GC_ASSERT(ui);
  GC_ASSERT(value);

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(box, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (inside && ui->mousePressed)
    ui->active = id;

  GCB32 changed = GC_FALSE;
  if (ui->active == id && ui->mouseReleased) {
    if (inside) {
      *value = *value ? GC_FALSE : GC_TRUE;
      changed = GC_TRUE;
    }
    ui->active = 0;
  }

  GCCOLOR fill = gc_color(30, 30, 35, 255);
  GCCOLOR line = gc_color(140, 140, 150, 255);
  if (ui->hot == id)
    line = gc_color(180, 180, 190, 255);
  gc_draw_fill(ui->window, box, fill);
  gc_draw_outline(ui->window, box, line);
  if (*value) {
    GCF32 pad = box.w < box.h ? box.w : box.h;
    pad *= 0.25f;
    GCRECT inner = {box.x + pad, box.y + pad, box.w - pad * 2.0f,
                    box.h - pad * 2.0f};
    gc_draw_fill(ui->window, inner, gc_color(50, 120, 220, 255));
  }
  if (label)
    gc_ui_text(ui, label, box.x + box.w + 8.0f, box.y,
               gc_color(245, 245, 245, 255));

  return changed;
}

static inline GCB32 gc_ui_slider(GCUI *ui, GCRECT rect, GCF32 min, GCF32 max,
                                 GCF32 *value) {
  GC_ASSERT(ui);
  GC_ASSERT(value);

  if (max < min) {
    GCF32 tmp = min;
    min = max;
    max = tmp;
  }
  if (*value < min)
    *value = min;
  if (*value > max)
    *value = max;

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (inside && ui->mousePressed)
    ui->active = id;

  GCB32 changed = GC_FALSE;
  if (ui->active == id && ui->mouseDown && max > min) {
    GCF32 t = (ui->mouseX - rect.x) / rect.w;
    if (t < 0.0f)
      t = 0.0f;
    if (t > 1.0f)
      t = 1.0f;
    GCF32 next = min + t * (max - min);
    if (next != *value) {
      *value = next;
      changed = GC_TRUE;
    }
  }

  GCF32 t = (max > min) ? (*value - min) / (max - min) : 0.0f;
  GCF32 barH = 6.0f;
  if (barH > rect.h)
    barH = rect.h;
  GCF32 barY = rect.y + (rect.h - barH) * 0.5f;
  gc_draw_fill(ui->window, (GCRECT){rect.x, barY, rect.w, barH},
               gc_color(30, 30, 35, 255));
  gc_draw_fill(ui->window, (GCRECT){rect.x, barY, rect.w * t, barH},
               gc_color(50, 120, 220, 255));
  GCF32 knobW = 12.0f;
  GCF32 knobX = rect.x + rect.w * t - knobW * 0.5f;
  if (knobX < rect.x)
    knobX = rect.x;
  if (knobX + knobW > rect.x + rect.w)
    knobX = rect.x + rect.w - knobW;
  gc_draw_fill(ui->window, (GCRECT){knobX, rect.y, knobW, rect.h},
               gc_color(230, 230, 235, 255));

  return changed;
}

static inline GCUSIZE gc_text_utf8_back(const char *s, GCUSIZE pos) {
  do {
    pos -= 1;
  } while (pos > 0 && (((GCU8)s[pos] & 0xC0) == 0x80));
  return pos;
}

static inline GCUSIZE gc_text_utf8_fwd(const char *s, GCUSIZE len,
                                       GCUSIZE pos) {
  if (pos < len) {
    pos += 1;
    while (pos < len && (((GCU8)s[pos] & 0xC0) == 0x80))
      pos += 1;
  }
  return pos;
}

static inline GCB32 gc_ui_textbox(GCUI *ui, GCRECT rect, char **buf,
                                  GCUSIZE *cap, GCARENA *arena) {
  GC_ASSERT(ui);
  GC_ASSERT(buf);
  GC_ASSERT(*buf);
  GC_ASSERT(cap);
  GC_ASSERT(*cap > 1);
  GC_ASSERT(arena);

  char *text = *buf;

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (ui->mousePressed) {
    if (inside) {
      ui->focus = id;
      ui->cursor = strlen(text);
    } else if (ui->focus == id) {
      ui->focus = 0;
    }
  }

  GCB32 changed = GC_FALSE;
  if (ui->focus == id) {
    GCUSIZE len = strlen(text);
    if (ui->cursor > len)
      ui->cursor = len;
    if (ui->inputLen > 0) {
      if (len + ui->inputLen >= *cap) {
        GCUSIZE next = *cap * 2;
        while (next <= len + ui->inputLen)
          next *= 2;
        char *grown = (char *)gc_arena_push(arena, next);
        memcpy(grown, text, len + 1);
        text = grown;
        *buf = grown;
        *cap = next;
      }
      memmove(text + ui->cursor + ui->inputLen, text + ui->cursor,
              len - ui->cursor + 1);
      memcpy(text + ui->cursor, ui->input, ui->inputLen);
      ui->cursor += ui->inputLen;
      changed = GC_TRUE;
      len = strlen(text);
    }
    if (gc_window_key_was_pressed(ui->window, GC_KEY_BACKSPACE) &&
        ui->cursor > 0) {
      GCUSIZE prev = gc_text_utf8_back(text, ui->cursor);
      memmove(text + prev, text + ui->cursor, len - ui->cursor + 1);
      ui->cursor = prev;
      changed = GC_TRUE;
      len = strlen(text);
    }
    if (gc_window_key_was_pressed(ui->window, GC_KEY_DELETE) &&
        ui->cursor < len) {
      GCUSIZE next = gc_text_utf8_fwd(text, len, ui->cursor);
      memmove(text + ui->cursor, text + next, len - next + 1);
      changed = GC_TRUE;
      len = strlen(text);
    }
    if (gc_window_key_was_pressed(ui->window, GC_KEY_LEFT))
      ui->cursor = gc_text_utf8_back(text, ui->cursor);
    if (gc_window_key_was_pressed(ui->window, GC_KEY_RIGHT))
      ui->cursor = gc_text_utf8_fwd(text, len, ui->cursor);
    if (gc_window_key_was_pressed(ui->window, GC_KEY_HOME))
      ui->cursor = 0;
    if (gc_window_key_was_pressed(ui->window, GC_KEY_END))
      ui->cursor = len;
    if (gc_window_key_was_pressed(ui->window, GC_KEY_RETURN))
      ui->focus = 0;
  }

  GCCOLOR line = gc_color(140, 140, 150, 255);
  if (ui->focus == id)
    line = gc_color(50, 120, 220, 255);
  else if (ui->hot == id)
    line = gc_color(180, 180, 190, 255);
  gc_draw_fill(ui->window, rect, gc_color(20, 20, 25, 255));
  gc_draw_outline(ui->window, rect, line);

  GCF32 tx = rect.x + 8.0f;
  GCI32 cw = 0;
  if (ui->font) {
    GCI32 tw = 0;
    GCI32 th = 0;
    TTF_GetStringSize(ui->font, text, 0, (int *)&tw, (int *)&th);
    GCF32 ty = rect.y + (rect.h - (GCF32)th) * 0.5f;
    GCI32 ch = 0;
    TTF_GetStringSize(ui->font, text, ui->cursor, (int *)&cw, (int *)&ch);
    if ((GCF32)tw > rect.w - 16.0f) {
      tx = rect.x + rect.w - 8.0f - (GCF32)cw;
      if (tx > rect.x + 8.0f)
        tx = rect.x + 8.0f;
    }
    gc_text_clip_rect(ui, rect);
    gc_ui_text(ui, text, tx, ty, gc_color(245, 245, 245, 255));
    gc_text_clip_clear(ui);
    if (ui->focus == id && rect.h > 14.0f &&
        (((GCI32)(ui->time * 2.0f) & 1) == 0)) {
      GCF32 chh = rect.h - 12.0f;
      gc_draw_fill(ui->window,
                   (GCRECT){tx + (GCF32)cw, rect.y + 6.0f, 2.0f, chh},
                   gc_color(245, 245, 245, 255));
    }
  }
  if (ui->focus == id) {
    SDL_Rect area = {(int)rect.x, (int)rect.y, (int)rect.w, (int)rect.h};
    SDL_SetTextInputArea((SDL_Window *)ui->window->handle, &area,
                         (int)(tx + (GCF32)cw - rect.x));
  }

  return changed;
}

static inline GCB32 gc_ui_combobox(GCUI *ui, GCRECT rect, const char **items,
                                   GCI32 count, GCI32 *selected) {
  GC_ASSERT(ui);
  GC_ASSERT(items);
  GC_ASSERT(selected);

  if (count < 1)
    return GC_FALSE;
  if (*selected < 0)
    *selected = 0;
  if (*selected >= count)
    *selected = count - 1;

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (inside && ui->mousePressed)
    ui->active = id;

  GCB32 clicked = GC_FALSE;
  if (ui->active == id && ui->mouseReleased) {
    if (inside)
      clicked = GC_TRUE;
    ui->active = 0;
  }
  if (clicked)
    ui->open = (ui->open == id) ? 0 : id;

  GCCOLOR fill = gc_color(60, 60, 68, 255);
  GCCOLOR line = gc_color(140, 140, 150, 255);
  if (ui->open == id) {
    fill = gc_color(50, 120, 220, 255);
    line = gc_color(160, 200, 255, 255);
  } else if (ui->hot == id) {
    fill = gc_color(80, 80, 92, 255);
    line = gc_color(180, 180, 190, 255);
  }
  gc_draw_fill(ui->window, rect, fill);
  gc_draw_outline(ui->window, rect, line);
  if (items[*selected])
    gc_text_centered(ui, items[*selected],
                     (GCRECT){rect.x, rect.y, rect.w - 28.0f, rect.h},
                     gc_color(245, 245, 245, 255));

  SDL_Renderer *renderer = (SDL_Renderer *)ui->window->renderer;
  SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
  GCF32 ax = rect.x + rect.w - 24.0f;
  GCF32 ay = rect.y + rect.h * 0.5f;
  SDL_RenderLine(renderer, ax, ay - 4.0f, ax + 7.0f, ay + 3.0f);
  SDL_RenderLine(renderer, ax + 7.0f, ay + 3.0f, ax + 14.0f, ay - 4.0f);

  GCB32 changed = GC_FALSE;
  if (ui->open == id) {
    GC_ASSERT(count < 1024);
    GCRECT list = {rect.x, rect.y + rect.h + 4.0f, rect.w,
                   rect.h * (GCF32)count};
    if (ui->mousePressed && !inside &&
        !gc_rect_contains(list, ui->mouseX, ui->mouseY))
      ui->open = 0;
  }
  if (ui->open == id) {
    GCRECT list = {rect.x, rect.y + rect.h + 4.0f, rect.w,
                   rect.h * (GCF32)count};
    GCU32 base = 0x01000000u + ((GCU32)id << 10);
    GCI32 hot = -1;
    for (GCI32 i = 0; i < count; ++i) {
      GCU32 row = base + (GCU32)i;
      GCRECT r = {rect.x, rect.y + rect.h + 4.0f + rect.h * (GCF32)i, rect.w,
                  rect.h};
      GCB32 in = gc_rect_contains(r, ui->mouseX, ui->mouseY);
      if (in) {
        ui->hot = row;
        hot = i;
      }
      if (in && ui->mousePressed)
        ui->active = row;
      if (ui->active == row && ui->mouseReleased) {
        if (in && *selected != i) {
          *selected = i;
          changed = GC_TRUE;
        }
        ui->active = 0;
        ui->open = 0;
      }
    }
    if (ui->open == id) {
      ui->popupOpen = GC_TRUE;
      ui->popupList = list;
      ui->popupItems = items;
      ui->popupCount = count;
      ui->popupSelected = *selected;
      ui->popupHot = hot;
      ui->popupRowH = rect.h;
    }
  }

  return changed;
}

static inline GCB32 gc_ui_toggle(GCUI *ui, GCRECT rect, const char *label,
                                 GCB32 *value) {
  GC_ASSERT(ui);
  GC_ASSERT(value);

  GCU32 id = ui->nextId++;
  GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
  if (inside)
    ui->hot = id;
  if (inside && ui->mousePressed)
    ui->active = id;

  GCB32 changed = GC_FALSE;
  if (ui->active == id && ui->mouseReleased) {
    if (inside) {
      *value = *value ? GC_FALSE : GC_TRUE;
      changed = GC_TRUE;
    }
    ui->active = 0;
  }

  GCCOLOR track =
      *value ? gc_color(50, 120, 220, 255) : gc_color(60, 60, 68, 255);
  gc_draw_fill(ui->window, rect, track);
  gc_draw_outline(ui->window, rect, gc_color(140, 140, 150, 255));
  GCF32 pad = 2.0f;
  GCF32 knob = rect.h - pad * 2.0f;
  GCF32 kx = *value ? rect.x + rect.w - knob - pad : rect.x + pad;
  gc_draw_fill(ui->window, (GCRECT){kx, rect.y + pad, knob, knob},
               gc_color(230, 230, 235, 255));
  if (label)
    gc_ui_text(ui, label, rect.x + rect.w + 8.0f, rect.y,
               gc_color(245, 245, 245, 255));

  return changed;
}

static inline void gc_ui_progress(GCUI *ui, GCRECT rect, GCF32 t) {
  GC_ASSERT(ui);

  if (t < 0.0f)
    t = 0.0f;
  if (t > 1.0f)
    t = 1.0f;
  gc_draw_fill(ui->window, rect, gc_color(30, 30, 35, 255));
  gc_draw_fill(ui->window, (GCRECT){rect.x, rect.y, rect.w * t, rect.h},
               gc_color(50, 120, 220, 255));
  gc_draw_outline(ui->window, rect, gc_color(140, 140, 150, 255));
}

#endif
