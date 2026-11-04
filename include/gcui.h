#ifndef GCUI_H
#define GCUI_H


#if defined(_MSC_VER)
#pragma warning(disable : 4244)
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib")
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h> //@TODO Linux
#include <timeapi.h>

typedef uint8_t  GCU8;
typedef uint16_t GCU16;
typedef uint32_t GCU32;
typedef uint64_t GCU64;

typedef int8_t  GCI8;
typedef int16_t GCI16;
typedef int32_t GCI32;
typedef int64_t GCI64;

typedef float  GCF32;
typedef double GCF64;

typedef size_t    GCUSIZE;
typedef uintptr_t GCUPTR;

typedef GCI32 GCB32;

#define GC_TRUE  (GCB32)1
#define GC_FALSE (GCB32)0
#define GC_ASSERT(c)                                                                               \
if (!(c)) {                                                                                    \
printf("ASSERTION FAILED - %s:%d", __FILE__, __LINE__);                                    \
exit(1);                                                                                   \
}
#define GC_KB(n) ((GCUSIZE)(n) * 1024u)
#define GC_MB(n) ((GCUSIZE)(n) * 1024u * 1024u)
#define GC_GB(n) ((GCUSIZE)(n) * 1024u * 1024u * 1024u)

#define GC_DT_MAX (GCF32)0.1f

typedef struct {
    void  *base;
    GCUPTR capacity;
    GCUPTR used;
} GCARENA;

static inline GCARENA *gc_arena_create(GCUPTR size)
{
    GCARENA *result  = (GCARENA *)malloc(sizeof(GCARENA));
    result->base     = malloc(size);
    result->capacity = size;
    result->used     = 0;
    return result;
}

static inline void *gc_arena_push(GCARENA *arena, GCUPTR size)
{
    GC_ASSERT(arena);
    GC_ASSERT(size <= arena->capacity - arena->used);
    
    void *result = (char *)arena->base + arena->used;
    arena->used += size;
    return result;
}

static inline void gc_arena_pop(GCARENA *arena, GCUPTR size)
{
    GC_ASSERT(arena);
    GC_ASSERT(size <= arena->used);
    
    arena->used -= size;
}

static inline void gc_arena_clear(GCARENA *arena)
{
    GC_ASSERT(arena);
    
    arena->used = 0;
}

static inline void gc_arena_destroy(GCARENA *arena)
{
    free(arena->base);
    free(arena);
}

typedef struct {
    GCU8   *data;
    GCUSIZE size;
} GCSTRING8;

static inline GCSTRING8 *gc_str8_create(GCARENA *arena, const char *cStr)
{
    GC_ASSERT(arena);
    GC_ASSERT(cStr);
    
    GCUSIZE    len    = strlen(cStr);
    GCSTRING8 *result = (GCSTRING8 *)gc_arena_push(arena, sizeof(GCSTRING8));
    result->size      = len;
    result->data      = (GCU8 *)gc_arena_push(arena, len + 1);
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

static inline GCCOLOR gc_color(GCU8 r, GCU8 g, GCU8 b, GCU8 a)
{
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

#define GC_KEY_RETURN    ((GCKEY)40)
#define GC_KEY_ESCAPE    ((GCKEY)41)
#define GC_KEY_BACKSPACE ((GCKEY)42)
#define GC_KEY_TAB       ((GCKEY)43)
#define GC_KEY_SPACE     ((GCKEY)44)

#define GC_KEY_F1  ((GCKEY)58)
#define GC_KEY_F2  ((GCKEY)59)
#define GC_KEY_F3  ((GCKEY)60)
#define GC_KEY_F4  ((GCKEY)61)
#define GC_KEY_F5  ((GCKEY)62)
#define GC_KEY_F6  ((GCKEY)63)
#define GC_KEY_F7  ((GCKEY)64)
#define GC_KEY_F8  ((GCKEY)65)
#define GC_KEY_F9  ((GCKEY)66)
#define GC_KEY_F10 ((GCKEY)67)
#define GC_KEY_F11 ((GCKEY)68)
#define GC_KEY_F12 ((GCKEY)69)

#define GC_KEY_HOME     ((GCKEY)74)
#define GC_KEY_PAGEUP   ((GCKEY)75)
#define GC_KEY_DELETE   ((GCKEY)76)
#define GC_KEY_END      ((GCKEY)77)
#define GC_KEY_PAGEDOWN ((GCKEY)78)
#define GC_KEY_RIGHT    ((GCKEY)79)
#define GC_KEY_LEFT     ((GCKEY)80)
#define GC_KEY_DOWN     ((GCKEY)81)
#define GC_KEY_UP       ((GCKEY)82)

#define GC_KEY_LCTRL  ((GCKEY)224)
#define GC_KEY_LSHIFT ((GCKEY)225)
#define GC_KEY_LALT   ((GCKEY)226)
#define GC_KEY_LGUI   ((GCKEY)227)
#define GC_KEY_RCTRL  ((GCKEY)228)
#define GC_KEY_RSHIFT ((GCKEY)229)
#define GC_KEY_RALT   ((GCKEY)230)
#define GC_KEY_RGUI   ((GCKEY)231)

typedef struct {
    GCSTRING8 *title;
    GCVEC2U32  dimensions;
    GCVEC2U32  position;
    void *handle;
    void *deviceContext;
    void *backBuffer;
    GCB32      quitRequested;
    GCB32      currKeys[GC_KEY_COUNT];
    GCB32      pressedThisFrame[GC_KEY_COUNT];
    GCU64      perfFreq;
    GCU64      lastCounter;
    GCF32      dt;
    GCF32      elapsed;
    GCU32      mouseX;
    GCU32      mouseY;
    GCF32      mouseScrollX;
    GCF32      mouseScrollY;
    GCB32      mouseDown;
    GCB32      mousePressed;
    GCB32      mouseReleased;
    GCU8       textInput[128];
    GCUSIZE    textLen;
    GCCOLOR    clearColor;
} GCWINDOW;

GCB32 g_mDown = GC_FALSE;

static inline GCKEY gc_vk_to_gckey(WPARAM vk)
{
    if (vk >= 'A' && vk <= 'Z') return GC_KEY_A + (GCKEY)(vk - 'A');
    if (vk >= '0' && vk <= '9') return (vk == '0') ? GC_KEY_0 : (GC_KEY_1 + (GCKEY)(vk - '1'));
    if (vk >= VK_F1 && vk <= VK_F12) return GC_KEY_F1 + (GCKEY)(vk - VK_F1);
    
    switch (vk) {
        case VK_RETURN:   return GC_KEY_RETURN;
        case VK_ESCAPE:   return GC_KEY_ESCAPE;
        case VK_BACK:     return GC_KEY_BACKSPACE;
        case VK_TAB:      return GC_KEY_TAB;
        case VK_SPACE:    return GC_KEY_SPACE;
        case VK_HOME:     return GC_KEY_HOME;
        case VK_PRIOR:    return GC_KEY_PAGEUP;
        case VK_DELETE:   return GC_KEY_DELETE;
        case VK_END:      return GC_KEY_END;
        case VK_NEXT:     return GC_KEY_PAGEDOWN;
        case VK_RIGHT:    return GC_KEY_RIGHT;
        case VK_LEFT:     return GC_KEY_LEFT;
        case VK_DOWN:     return GC_KEY_DOWN;
        case VK_UP:       return GC_KEY_UP;
        case VK_LCONTROL: return GC_KEY_LCTRL;
        case VK_RCONTROL: return GC_KEY_RCTRL;
        case VK_LSHIFT:   return GC_KEY_LSHIFT;
        case VK_RSHIFT:   return GC_KEY_RSHIFT;
        case VK_LMENU:    return GC_KEY_LALT;
        case VK_RMENU:    return GC_KEY_RALT;
        default:          return -1;
    }
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{ 
    GCWINDOW *window = (GCWINDOW *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    
    switch (uMsg) 
    { 
        case WM_CLOSE:
        case WM_DESTROY: {
            if (window) window->quitRequested = GC_TRUE;
            PostQuitMessage(0);
            return 0;
        }
        case WM_MOUSEWHEEL: {
            if (window) {
                
                short delta = (short)HIWORD(wParam);
                // 1 notch = 120 -> +1.0f (up) or -1.0f (down)
                window->mouseScrollY += (GCF32)delta / (GCF32)WHEEL_DELTA;
            }
            return 0;
        }
        
        case WM_MOUSEHWHEEL: {
            if (window) {
                short delta = (short)HIWORD(wParam);
                // 1 notch = 120 -> +1.0f (right) or -1.0f (left)
                window->mouseScrollX += (GCF32)delta / (GCF32)WHEEL_DELTA;
            }
            return 0;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN: {
            g_mDown = GC_TRUE;
            return 0;
        }
        
        case WM_LBUTTONUP:
        case WM_RBUTTONUP: {
            g_mDown = GC_FALSE;
            return 0;
        }
        
        case WM_KEYDOWN: {
            if (window) {
                GCKEY key = gc_vk_to_gckey(wParam);
                if (key >= 0 && key < GC_KEY_COUNT) {
                    window->currKeys[key] = GC_TRUE;
                    window->pressedThisFrame[key] = GC_TRUE;
                }
            }
            return 0;
        }
        
        case WM_KEYUP: {
            if (window) {
                GCKEY key = gc_vk_to_gckey(wParam);
                if (key >= 0 && key < GC_KEY_COUNT) {
                    window->currKeys[key] = GC_FALSE;
                }
            }
            return 0;
        }
        
        case WM_CHAR: {
            if (window) {
                
                if (wParam >= 32 && wParam != 127) {
                    
                    wchar_t wch = (wchar_t)wParam;
                    char utf8[4];
                    int len = WideCharToMultiByte(CP_UTF8, 0, &wch, 1, utf8, sizeof(utf8), NULL, NULL);
                    if (len > 0 && window->textLen + (GCUSIZE)len < sizeof(window->textInput) - 1) {
                        memcpy(window->textInput + window->textLen, utf8, len);
                        window->textLen += len;
                        window->textInput[window->textLen] = '\0';
                    }
                }
            }
            return 0;
        }
        
        default: 
        return DefWindowProc(hwnd, uMsg, wParam, lParam); 
    } 
}
static inline GCWINDOW *gc_window_create(GCARENA *arena, const char *title, GCU32 width,
                                         GCU32 height, GCB32 fullscreen)
{
    (void)fullscreen; //@TODO
    GC_ASSERT(arena);
    GC_ASSERT(title);
    
    GCWINDOW *window = (GCWINDOW *)gc_arena_push(arena, sizeof(GCWINDOW));
    memset(window, 0, sizeof(*window));
    RECT clientRect;
    window->dimensions  = (GCVEC2U32){width, height};
    
    window->title       = gc_str8_create(arena, title);
    window->clearColor  = gc_color(24, 24, 27, 255);
    
    LARGE_INTEGER perfFreq, perfCounter;
    QueryPerformanceFrequency(&perfFreq);
    QueryPerformanceCounter(&perfCounter);
    
    window->perfFreq    = perfFreq.QuadPart;
    window->lastCounter = perfCounter.QuadPart;
    DWORD flags = WS_OVERLAPPEDWINDOW;
    
    HINSTANCE instance = GetModuleHandle(0);
    const char * className = "GcUiWndClass";
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProcedure;
    wc.hInstance     = instance;
    wc.lpszClassName = className;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    
    RegisterClass(&wc);
    
    HWND handle = CreateWindowA(className,
                                title,
                                flags,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                width,
                                height,
                                NULL,
                                NULL,
                                instance,
                                NULL);
    
    if (!handle) {
        printf("CreateWindow failed: %d\n", GetLastError());
        return NULL;
    }
    window->handle = handle;
    
    SetWindowLongPtr(handle, GWLP_USERDATA, (LONG_PTR)window);
    GetClientRect(handle, &clientRect);
    window->dimensions.x = clientRect.right - clientRect.left;
    window->dimensions.y = clientRect.bottom - clientRect.top;
    
    ShowWindow(handle, SW_SHOW);
    
    HDC screenDC = GetDC(handle);
    window->deviceContext = CreateCompatibleDC(screenDC);
    window->backBuffer    = CreateCompatibleBitmap(screenDC, window->dimensions.x, window->dimensions.y);
    SelectObject(window->deviceContext, window->backBuffer);
    ReleaseDC(handle, screenDC);
    
    PatBlt(window->deviceContext, 0, 0, window->dimensions.x, window->dimensions.y, BLACKNESS);
    
    return window;
}

static inline void gc_window_begin(GCWINDOW *window)
{
    GC_ASSERT(window);
    GC_ASSERT(window->handle);
    
    LARGE_INTEGER nowLi;
    QueryPerformanceCounter(&nowLi);
    
    GCU64 now = nowLi.QuadPart;
    if (window->perfFreq > 0) {
        GCF64 delta = (GCF64)(now - window->lastCounter) / (GCF64)window->perfFreq;
        window->dt  = (GCF32)delta;
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
    
    window->mousePressed  = GC_FALSE;
    window->mouseReleased = GC_FALSE;
    window->textLen       = 0;
    window->textInput[0]  = 0;
    window->mouseScrollX  = 0.0f;
    window->mouseScrollY  = 0.0f;
    
    // Message loop
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            window->quitRequested = GC_TRUE;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    POINT cPoint = {0};
    GetCursorPos(&cPoint);
    ScreenToClient((HWND)window->handle, &cPoint);
    
    window->mousePressed  = (g_mDown && !window->mouseDown) ? GC_TRUE : GC_FALSE;
    window->mouseReleased = ((!g_mDown) && window->mouseDown) ? GC_TRUE : GC_FALSE;
    window->mouseDown     = g_mDown;
    window->mouseX        = (cPoint.x < 0) ? 0 : (GCU32)cPoint.x;
    window->mouseY        = (cPoint.y < 0) ? 0 : (GCU32)cPoint.y;
    
    RECT clientRect;
    GetClientRect((HWND)window->handle, &clientRect);
    GCU32 newWidth  = (GCU32)(clientRect.right - clientRect.left);
    GCU32 newHeight = (GCU32)(clientRect.bottom - clientRect.top);
    
    if (newWidth > 0 && newHeight > 0 && 
        (newWidth != window->dimensions.x || newHeight != window->dimensions.y)) 
    {
        window->dimensions.x = newWidth;
        window->dimensions.y = newHeight;
        
        HDC screenDC = GetDC((HWND)window->handle);
        HBITMAP newBitmap = CreateCompatibleBitmap(screenDC, newWidth, newHeight);
        
        SelectObject((HDC)window->deviceContext, newBitmap);
        if (window->backBuffer) {
            DeleteObject((HBITMAP)window->backBuffer);
        }
        window->backBuffer = newBitmap;
        ReleaseDC((HWND)window->handle, screenDC);
    }
    
    // Clear screen
    RECT bufferRect = { 0, 0, (LONG)window->dimensions.x, (LONG)window->dimensions.y };
    HBRUSH brush = CreateSolidBrush(RGB(window->clearColor.r, 
                                        window->clearColor.g, 
                                        window->clearColor.b));
    FillRect((HDC)window->deviceContext, &bufferRect, brush);
    DeleteObject(brush);
    
    timeBeginPeriod(1);
}

static inline void gc_window_end(GCWINDOW *window)
{
    GC_ASSERT(window);
    GC_ASSERT(window->backBuffer);
    GC_ASSERT(window->deviceContext);
    
    HDC hdcWindow = GetDC((HWND)window->handle);
    BitBlt(hdcWindow, 0, 0, window->dimensions.x, window->dimensions.y, 
           (HDC)window->deviceContext, 0, 0, SRCCOPY);
    ReleaseDC((HWND)window->handle, hdcWindow);
    
    timeEndPeriod(1);
}

static inline void gc_window_update(GCWINDOW *window)
{
    gc_window_begin(window);
    gc_window_end(window);
}

static inline GCB32 gc_window_should_quit(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return window->quitRequested;
}

static inline GCB32 gc_window_key_currently_pressed(GCWINDOW *window, GCKEY key)
{
    GC_ASSERT(window);
    if (key < 0 || key >= GC_KEY_COUNT)
        return GC_FALSE;
    
    return window->currKeys[key];
}

static inline GCB32 gc_window_key_was_pressed(GCWINDOW *window, GCKEY key)
{
    GC_ASSERT(window);
    if (key < 0 || key >= GC_KEY_COUNT)
        return GC_FALSE;
    
    return window->pressedThisFrame[key];
}

static inline GCF32 gc_window_dt(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return window->dt;
}

static inline GCF32 gc_window_elapsed(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return window->elapsed;
}

static inline GCVEC2U32 gc_window_size(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return window->dimensions;
}

static inline GCF32 gc_window_width(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return (GCF32)window->dimensions.x;
}

static inline GCF32 gc_window_height(GCWINDOW *window)
{
    GC_ASSERT(window);
    
    return (GCF32)window->dimensions.y;
}

static inline void gc_window_set_clear(GCWINDOW *window, GCCOLOR color)
{
    GC_ASSERT(window);
    
    window->clearColor = color;
}

static inline void gc_window_destroy(GCWINDOW *window)
{
    if (!window)
        return;
    
    if (window->handle) {
        DestroyWindow(window->handle);
        window->handle = NULL;
    }
    
}

static inline void gc_sleep_ms(GCU32 ms)
{
    Sleep((DWORD)ms);
}

static inline GCB32 gc_rect_contains(GCRECT rect, GCF32 x, GCF32 y)
{
    return (x >= rect.x && x < rect.x + rect.w && y >= rect.y && y < rect.y + rect.h) ? GC_TRUE
        : GC_FALSE;
}


static inline void gc_draw_fill(GCWINDOW *window, GCRECT rect, GCCOLOR color)
{
    GC_ASSERT(window);
    GC_ASSERT(window->deviceContext); 
    
    HDC hdc = (HDC)window->deviceContext;
    
    
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    
    
    RECT win_rect = {
        .left   = (LONG)rect.x,
        .top    = (LONG)rect.y,
        .right  = (LONG)(rect.x + rect.w),
        .bottom = (LONG)(rect.y + rect.h)
    };
    
    
    FillRect(hdc, &win_rect, brush);
    
    
    DeleteObject(brush);
}


static inline void gc_draw_outline(GCWINDOW *window, GCRECT rect, GCCOLOR color)
{
    GC_ASSERT(window);
    GC_ASSERT(window->deviceContext);
    
    
    RECT win_rect = { 
        (LONG)rect.x, 
        (LONG)rect.y, 
        (LONG)(rect.x + rect.w), 
        (LONG)(rect.y + rect.h) 
    };
    
    HBRUSH brush = CreateSolidBrush(RGB(color.r, color.g, color.b));
    FrameRect(window->deviceContext, &win_rect, brush);
    
    DeleteObject(brush);
}

typedef struct {
    GCWINDOW    *window;
    void *font;
    GCU32        mouseX;
    GCU32        mouseY;
    GCF32        mouseScrollX;
    GCF32        mouseScrollY;
    GCB32        mouseDown;
    GCB32        mousePressed;
    GCB32        mouseReleased;
    GCF32        dt;
    GCF32        time;
    GCU32        hot;
    GCU32        active;
    GCU32        nextId;
    GCU32        focus;
    GCUSIZE      cursor;
    GCU32        open;
    const char  *input;
    GCUSIZE      inputLen;
    GCB32        popupOpen;
    GCRECT       popupList;
    const char **popupItems;
    GCI32        popupCount;
    GCI32        popupSelected;
    GCI32        popupHot;
    GCF32        popupRowH;
    GCRECT       clipStack[8];
    GCI32        clipDepth;
} GCUI;

typedef struct {
    GCF32  offset;
    GCF32  content;
    GCRECT view;
} GCUISCROLL;

static inline GCUI *gc_ui_create(GCARENA *arena, GCWINDOW *window)
{
    GC_ASSERT(window);
    
    GCUI *result = (GCUI *)gc_arena_push(arena, sizeof(GCUI));
    memset(result, 0, sizeof(*result));
    result->window = window;
    
    return result;
}

static inline GCB32 gc_ui_set_font(GCUI *ui, const char *path, GCF32 size)
{
    GC_ASSERT(ui);
    GC_ASSERT(path);
    
    if (ui->font) {
        DeleteObject((HFONT)ui->font);
        ui->font = NULL;
    }
    
    HFONT font = CreateFont(
                            -(int)size,                     // Height
                            0,                              // Width (0 = auto-match aspect ratio)
                            0,                              // Escapement
                            0,                              // Orientation
                            FW_NORMAL,                      // Weight (e.g., FW_NORMAL, FW_BOLD)
                            FALSE,                          // Italic
                            FALSE,                          // Underline
                            FALSE,                          // StrikeOut
                            DEFAULT_CHARSET,                // Character set
                            OUT_OUTLINE_PRECIS,             // Output precision
                            CLIP_DEFAULT_PRECIS,            // Clip precision
                            CLEARTYPE_QUALITY,              // Quality (ClearType for smooth text)
                            DEFAULT_PITCH | FF_DONTCARE,    // Pitch and family
                            path                            // Face name (e.g., "Arial")
                            );
    
    if (!font)
        return GC_FALSE;
    
    ui->font = font;
    return GC_TRUE;
}

static inline GCB32 gc_ui_load_default_font(GCUI *ui, GCF32 size)
{
    GC_ASSERT(ui);
    
#if defined(_WIN32)
    char  *sysRootOwned = NULL;
    size_t sysRootSize  = 0;
    _dupenv_s(&sysRootOwned, &sysRootSize, "SystemRoot");
    const char *sysRoot = sysRootOwned;
    if (!sysRoot || !sysRoot[0]) {
        free(sysRootOwned);
        sysRootOwned = NULL;
        _dupenv_s(&sysRootOwned, &sysRootSize, "windir");
        sysRoot = sysRootOwned;
    }
#else
    const char *sysRoot = getenv("SystemRoot");
    if (!sysRoot)
        sysRoot = getenv("windir");
#endif
    if (sysRoot && sysRoot[0]) {
        static const char *winNames[] = {
            "segoeui.ttf", "arial.ttf", "calibri.ttf", "tahoma.ttf", "verdana.ttf",
        };
        for (GCUSIZE i = 0; i < sizeof(winNames) / sizeof(winNames[0]); ++i) {
            char winPath[512];
            snprintf(winPath, sizeof(winPath), "%s\\Fonts\\%s", sysRoot, winNames[i]);
            winPath[sizeof(winPath) - 1] = 0;
            if (gc_ui_set_font(ui, winPath, size)) {
#if defined(_WIN32)
                free(sysRootOwned);
#endif
                return GC_TRUE;
            }
        }
    }
#if defined(_WIN32)
    free(sysRootOwned);
#endif
    
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

static inline void gc_ui_set_font_size(GCUI *ui, GCF32 size)
{
    GC_ASSERT(ui);
    
    if (ui->font) {
        LOGFONT lf;
        
        if (GetObject((HFONT)ui->font, sizeof(LOGFONT), &lf)) {
            lf.lfHeight = -(int)size;
            HFONT new_font = CreateFontIndirect(&lf);
            if (new_font) {
                DeleteObject((HFONT)ui->font);
                ui->font = new_font;
            }
        }
    }
}
static inline void gc_ui_reset_clip_rect(GCUI *ui)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    SelectClipRgn(ui->window->deviceContext, NULL);
}
static inline void gc_ui_begin(GCUI *ui)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    
    GCWINDOW *window  = ui->window;
    ui->mouseX        = window->mouseX;
    ui->mouseY        = window->mouseY;
    ui->mouseScrollX  = window->mouseScrollX;
    ui->mouseScrollY  = window->mouseScrollY;
    ui->mouseDown     = window->mouseDown;
    ui->mousePressed  = window->mousePressed;
    ui->mouseReleased = window->mouseReleased;
    ui->dt            = window->dt;
    ui->time          = window->elapsed;
    ui->input         = (const char *)window->textInput;
    ui->inputLen      = window->textLen;
    ui->nextId        = 1;
    ui->hot           = 0;
    ui->popupOpen     = GC_FALSE;
    ui->popupHot      = -1;
    ui->clipDepth     = 0;
    gc_ui_reset_clip_rect(ui);
}

static inline void gc_popup_draw(GCUI *ui);

static inline void gc_ui_reset_text_input_area(GCUI *ui)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->handle);
    
    HWND hwnd = (HWND)ui->window->handle;
    HIMC himc = ImmGetContext(hwnd);
    if (himc) {
        COMPOSITIONFORM cf;
        cf.dwStyle = CFS_DEFAULT; 
        ImmSetCompositionWindow(himc, &cf);
        ImmReleaseContext(hwnd, himc);
    }
}

static inline void gc_ui_end(GCUI *ui)
{
    GC_ASSERT(ui);
    
    if (!ui->mouseDown)
        ui->active = 0;
    if (!ui->focus)
        gc_ui_reset_text_input_area(ui);
    if (ui->popupOpen)
        gc_popup_draw(ui);
}

static inline void gc_ui_destroy(GCUI *ui)
{
    if (!ui)
        return;
    if (ui->font) {
        CloseHandle(ui->font);
        ui->font = NULL;
    }
}

static inline void gc_ui_text(GCUI *ui, const char *text, GCF32 x, GCF32 y, GCCOLOR color)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (!ui->font || !text || !text[0])
        return;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    HFONT oldFont = (HFONT)SelectObject(hdc, (HFONT)ui->font);
    
    COLORREF oldColor = SetTextColor(hdc, RGB(color.r, color.g, color.b));
    int oldMode = SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, (int)x, (int)y, text, (int)strlen(text));
    
    SetBkMode(hdc, oldMode);
    SetTextColor(hdc, oldColor);
    SelectObject(hdc, oldFont);
}

static inline void gc_text_len(GCUI *ui, const char *text, GCUSIZE len, GCF32 x, GCF32 y,
                               GCCOLOR color)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (!ui->font || !text || len == 0)
        return;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    HFONT old_font = (HFONT)SelectObject(hdc, (HFONT)ui->font);
    
    COLORREF old_color = SetTextColor(hdc, RGB(color.r, color.g, color.b));
    int old_mode = SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, (int)x, (int)y, text, (int)len);
    
    SetBkMode(hdc, old_mode);
    SetTextColor(hdc, old_color);
    SelectObject(hdc, old_font);
}

static inline GCI32 gc_text_width(GCUI *ui, const char *text, GCUSIZE len)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (!ui->font || !text || len == 0)
        return 0;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    HFONT old_font = (HFONT)SelectObject(hdc, (HFONT)ui->font);
    
    SIZE size = {0};
    GetTextExtentPoint32A(hdc, text, (int)len, &size);
    
    SelectObject(hdc, old_font);
    
    return (GCI32)size.cx;
}
static inline GCUSIZE gc_text_fit_len(GCUI *ui, const char *text, GCUSIZE len, GCF32 maxW)
{
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

static inline void gc_text_clip_rect(GCUI *ui, GCRECT rect)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (ui->clipDepth < (GCI32)(sizeof(ui->clipStack) / sizeof(ui->clipStack[0]))) {
        if (ui->clipDepth > 0) {
            GCRECT parent = ui->clipStack[ui->clipDepth - 1];
            GCF32 right      = parent.x + parent.w;
            GCF32 bottom     = parent.y + parent.h;
            GCF32 nextRight  = rect.x + rect.w;
            GCF32 nextBottom = rect.y + rect.h;
            if (rect.x < parent.x)
                rect.x = parent.x;
            if (rect.y < parent.y)
                rect.y = parent.y;
            if (nextRight > right)
                nextRight = right;
            if (nextBottom > bottom)
                nextBottom = bottom;
            rect.w = nextRight - rect.x;
            rect.h = nextBottom - rect.y;
        }
        ui->clipStack[ui->clipDepth] = rect;
        ui->clipDepth += 1;
    }
    
    GCI32 clipW = (int)rect.w - 2;
    GCI32 clipH = (int)rect.h - 2;
    if (clipW < 1)
        clipW = 1;
    if (clipH < 1)
        clipH = 1;
    
    int left   = (int)rect.x + 1;
    int top    = (int)rect.y + 1;
    int right  = left + clipW;
    int bottom = top + clipH;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    HRGN hrgn = CreateRectRgn(left, top, right, bottom);
    SelectClipRgn(hdc, hrgn);
    
    DeleteObject(hrgn);
}
static inline void gc_text_clip_clear(GCUI *ui)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (ui->clipDepth > 0)
        ui->clipDepth -= 1;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    if (ui->clipDepth > 0) {
        GCRECT rect = ui->clipStack[ui->clipDepth - 1];
        
        HRGN hrgn = CreateRectRgn(
                                  (int)rect.x, 
                                  (int)rect.y, 
                                  (int)(rect.x + rect.w), 
                                  (int)(rect.y + rect.h)
                                  );
        SelectClipRgn(hdc, hrgn);
        DeleteObject(hrgn);
    } else {
        SelectClipRgn(hdc, NULL);
    }
}
static inline void gc_text_centered(GCUI *ui, const char *text, GCRECT rect, GCCOLOR color)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    
    if (!ui->font || !text || !text[0])
        return;
    
    HDC hdc = (HDC)ui->window->deviceContext;
    
    HFONT old_font = (HFONT)SelectObject(hdc, (HFONT)ui->font);
    
    SIZE size = {0};
    int text_len = (int)strlen(text);
    GetTextExtentPoint32A(hdc, text, text_len, &size);
    
    GCI32 w = (GCI32)size.cx;
    GCI32 h = (GCI32)size.cy;
    
    SelectObject(hdc, old_font);
    
    GCUSIZE len  = (GCUSIZE)text_len;
    GCF32   dots = 0.0f;
    if ((GCF32)w > rect.w) {
        dots = (GCF32)gc_text_width(ui, "...", 3);
        if (rect.w <= dots)
            return;
        len = gc_text_fit_len(ui, text, len, rect.w - dots);
        w   = gc_text_width(ui, text, len) + (GCI32)dots;
    }
    
    GCF32 x = rect.x + (rect.w - (GCF32)w) * 0.5f;
    GCF32 y = rect.y + (rect.h - (GCF32)h) * 0.5f;
    
    gc_text_clip_rect(ui, rect);
    gc_text_len(ui, text, len, x, y, color);
    if (dots > 0.0f)
        gc_ui_text(ui, "...", x + (GCF32)w - dots, y, color);
    gc_text_clip_clear(ui);
}

static inline void gc_popup_draw(GCUI *ui)
{
    GC_ASSERT(ui);
    
    gc_draw_fill(ui->window, ui->popupList, gc_color(30, 30, 36, 255));
    gc_draw_outline(ui->window, ui->popupList, gc_color(140, 140, 150, 255));
    for (GCI32 i = 0; i < ui->popupCount; ++i) {
        GCRECT r = {ui->popupList.x, ui->popupList.y + ui->popupRowH * (GCF32)i, ui->popupList.w,
            ui->popupRowH};
        if (i == ui->popupHot)
            gc_draw_fill(ui->window, r, gc_color(50, 120, 220, 255));
        if (i == ui->popupSelected)
            gc_draw_outline(ui->window, r, gc_color(160, 200, 255, 255));
        if (ui->popupItems[i])
            gc_text_centered(ui, ui->popupItems[i], (GCRECT){r.x, r.y, r.w - 8.0f, r.h},
                             gc_color(245, 245, 245, 255));
    }
}

static inline void gc_ui_panel(GCUI *ui, GCRECT rect, GCCOLOR color)
{
    GC_ASSERT(ui);
    
    gc_draw_fill(ui->window, rect, color);
}

static inline void gc_ui_separator(GCUI *ui, GCRECT rect, GCCOLOR color)
{
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

static inline void gc_ui_label(GCUI *ui, GCRECT rect, const char *text, GCCOLOR color)
{
    GC_ASSERT(ui);
    if (!ui->font || !text || !text[0])
        return;
    
    GCUSIZE len  = strlen(text);
    GCF32   dots = 0.0f;
    if ((GCF32)gc_text_width(ui, text, len) > rect.w) {
        dots = (GCF32)gc_text_width(ui, "...", 3);
        if (rect.w <= dots)
            return;
        len = gc_text_fit_len(ui, text, len, rect.w - dots);
    }
    gc_text_clip_rect(ui, rect);
    gc_text_len(ui, text, len, rect.x, rect.y, color);
    if (dots > 0.0f)
        gc_ui_text(ui, "...", rect.x + (GCF32)gc_text_width(ui, text, len), rect.y, color);
    gc_text_clip_clear(ui);
}

static inline GCB32 gc_ui_button(GCUI *ui, GCRECT rect, const char *label)
{
    GC_ASSERT(ui);
    
    GCU32 id     = ui->nextId++;
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

static inline GCB32 gc_ui_checkbox(GCUI *ui, GCRECT box, const char *label, GCB32 *value)
{
    GC_ASSERT(ui);
    GC_ASSERT(value);
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(box, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (inside && ui->mousePressed)
        ui->active = id;
    
    GCB32 changed = GC_FALSE;
    if (ui->active == id && ui->mouseReleased) {
        if (inside) {
            *value  = *value ? GC_FALSE : GC_TRUE;
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
        GCRECT inner = {box.x + pad, box.y + pad, box.w - pad * 2.0f, box.h - pad * 2.0f};
        gc_draw_fill(ui->window, inner, gc_color(50, 120, 220, 255));
    }
    if (label)
        gc_ui_text(ui, label, box.x + box.w + 8.0f, box.y, gc_color(245, 245, 245, 255));
    
    return changed;
}

static inline GCB32 gc_ui_slider_horizontal(GCUI *ui, GCRECT rect, GCF32 min, GCF32 max,
                                            GCF32 *value)
{
    GC_ASSERT(ui);
    GC_ASSERT(value);
    
    if (max < min) {
        GCF32 tmp = min;
        min       = max;
        max       = tmp;
    }
    if (*value < min)
        *value = min;
    if (*value > max)
        *value = max;
    
    GCU32 id     = ui->nextId++;
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
            *value  = next;
            changed = GC_TRUE;
        }
    }
    
    GCF32 t    = (max > min) ? (*value - min) / (max - min) : 0.0f;
    GCF32 barH = 6.0f;
    if (barH > rect.h)
        barH = rect.h;
    GCF32 barY = rect.y + (rect.h - barH) * 0.5f;
    gc_draw_fill(ui->window, (GCRECT){rect.x, barY, rect.w, barH}, gc_color(30, 30, 35, 255));
    gc_draw_fill(ui->window, (GCRECT){rect.x, barY, rect.w * t, barH}, gc_color(50, 120, 220, 255));
    GCF32 knobW = 12.0f;
    GCF32 knobX = rect.x + rect.w * t - knobW * 0.5f;
    if (knobX < rect.x)
        knobX = rect.x;
    if (knobX + knobW > rect.x + rect.w)
        knobX = rect.x + rect.w - knobW;
    gc_draw_fill(ui->window, (GCRECT){knobX, rect.y, knobW, rect.h}, gc_color(230, 230, 235, 255));
    
    return changed;
}

static inline GCB32 gc_ui_slider_vertical(GCUI *ui, GCRECT rect, GCF32 min, GCF32 max, GCF32 *value)
{
    GC_ASSERT(ui);
    GC_ASSERT(value);
    
    if (max < min) {
        GCF32 tmp = min;
        min       = max;
        max       = tmp;
    }
    if (*value < min)
        *value = min;
    if (*value > max)
        *value = max;
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (inside && ui->mousePressed)
        ui->active = id;
    
    GCB32 changed = GC_FALSE;
    if (ui->active == id && ui->mouseDown && max > min) {
        
        GCF32 t = 1.0f - ((ui->mouseY - rect.y) / rect.h);
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;
        
        GCF32 next = min + t * (max - min);
        if (next != *value) {
            *value  = next;
            changed = GC_TRUE;
        }
    }
    
    GCF32 t    = (max > min) ? (*value - min) / (max - min) : 0.0f;
    GCF32 barW = 6.0f;
    if (barW > rect.w)
        barW = rect.w;
    GCF32 barX = rect.x + (rect.w - barW) * 0.5f;
    
    gc_draw_fill(ui->window, (GCRECT){barX, rect.y, barW, rect.h}, gc_color(30, 30, 35, 255));
    
    GCF32 fillH = rect.h * t;
    GCF32 fillY = rect.y + rect.h - fillH;
    gc_draw_fill(ui->window, (GCRECT){barX, fillY, barW, fillH}, gc_color(50, 120, 220, 255));
    
    GCF32 knobH = 12.0f;
    if (knobH > rect.h)
        knobH = rect.h;
    
    GCF32 knobY = rect.y + rect.h - (rect.h * t) - (knobH * 0.5f);
    
    if (knobY < rect.y)
        knobY = rect.y;
    if (knobY + knobH > rect.y + rect.h)
        knobY = rect.y + rect.h - knobH;
    
    gc_draw_fill(ui->window, (GCRECT){rect.x, knobY, rect.w, knobH}, gc_color(230, 230, 235, 255));
    
    return changed;
}

static inline GCUSIZE gc_text_utf8_back(const char *s, GCUSIZE pos)
{
    do {
        pos -= 1;
    } while (pos > 0 && (((GCU8)s[pos] & 0xC0) == 0x80));
    return pos;
}

static inline GCB32 gc_ui_handle_scrollwheel(GCUI *ui, GCRECT rect, GCF32 viewSize, GCF32 totalSize,
                                             GCF32 *scrollOffset, GCF32 scrollSpeed)
{
    GC_ASSERT(ui);
    GC_ASSERT(scrollOffset);
    
    if (totalSize <= viewSize || ui->mouseScrollY == 0.0f) {
        return GC_FALSE;
    }
    
    if (!gc_rect_contains(rect, ui->mouseX, ui->mouseY)) {
        return GC_FALSE;
    }
    
    GCF32 min  = 0.0f;
    GCF32 max  = totalSize - viewSize;
    GCF32 next = *scrollOffset - (ui->mouseScrollY * scrollSpeed);
    
    if (next < min)
        next = min;
    if (next > max)
        next = max;
    
    if (next != *scrollOffset) {
        *scrollOffset = next;
        return GC_TRUE;
    }
    
    return GC_FALSE;
}

static inline GCB32 gc_ui_scrollbar_vertical(GCUI *ui, GCRECT rect, GCF32 viewSize, GCF32 totalSize,
                                             GCF32 *scrollOffset)
{
    GC_ASSERT(ui);
    GC_ASSERT(scrollOffset);
    
    if (totalSize <= viewSize) {
        *scrollOffset = 0.0f;
        return GC_FALSE;
    }
    
    GCF32 min = 0.0f;
    GCF32 max = totalSize - viewSize;
    
    if (*scrollOffset < min)
        *scrollOffset = min;
    if (*scrollOffset > max)
        *scrollOffset = max;
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (inside && ui->mousePressed)
        ui->active = id;
    
    GCF32 thumbH = (viewSize / totalSize) * rect.h;
    if (thumbH < 16.0f)
        thumbH = 16.0f;
    if (thumbH > rect.h)
        thumbH = rect.h;
    
    GCF32 travelH = rect.h - thumbH;
    GCB32 changed = GC_FALSE;
    
    if (ui->active == id && ui->mouseDown && travelH > 0.0f) {
        GCF32 mouseRelY = ui->mouseY - rect.y - (thumbH * 0.5f);
        GCF32 t         = mouseRelY / travelH;
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;
        
        GCF32 next = min + t * (max - min);
        if (next != *scrollOffset) {
            *scrollOffset = next;
            changed       = GC_TRUE;
        }
    }
    
    gc_draw_fill(ui->window, rect, gc_color(25, 25, 25, 255));
    
    GCF32 t      = (max > min) ? (*scrollOffset - min) / (max - min) : 0.0f;
    GCF32 thumbY = rect.y + (t * travelH);
    
    GCCOLOR thumbColor = gc_color(100, 100, 105, 255);
    if (ui->active == id) {
        thumbColor = gc_color(160, 160, 165, 255);
    } else if (ui->hot == id) {
        thumbColor = gc_color(130, 130, 135, 255);
    }
    
    gc_draw_fill(ui->window, (GCRECT){rect.x, thumbY, rect.w, thumbH}, thumbColor);
    
    return changed;
}
static inline GCB32 gc_ui_scrollbar_horizontal(GCUI *ui, GCRECT rect, GCF32 viewSize,
                                               GCF32 totalSize, GCF32 *scrollOffset)
{
    GC_ASSERT(ui);
    GC_ASSERT(scrollOffset);
    
    if (totalSize <= viewSize) {
        *scrollOffset = 0.0f;
        return GC_FALSE;
    }
    
    GCF32 min = 0.0f;
    GCF32 max = totalSize - viewSize;
    
    if (*scrollOffset < min)
        *scrollOffset = min;
    if (*scrollOffset > max)
        *scrollOffset = max;
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (inside && ui->mousePressed)
        ui->active = id;
    
    GCF32 thumbW = (viewSize / totalSize) * rect.w;
    if (thumbW < 16.0f)
        thumbW = 16.0f;
    if (thumbW > rect.w)
        thumbW = rect.w;
    
    GCF32 travelW = rect.w - thumbW;
    GCB32 changed = GC_FALSE;
    
    if (ui->active == id && ui->mouseDown && travelW > 0.0f) {
        GCF32 mouseRelX = ui->mouseX - rect.x - (thumbW * 0.5f);
        GCF32 t         = mouseRelX / travelW;
        if (t < 0.0f)
            t = 0.0f;
        if (t > 1.0f)
            t = 1.0f;
        
        GCF32 next = min + t * (max - min);
        if (next != *scrollOffset) {
            *scrollOffset = next;
            changed       = GC_TRUE;
        }
    }
    
    gc_draw_fill(ui->window, rect, gc_color(25, 25, 25, 255));
    
    GCF32 t      = (max > min) ? (*scrollOffset - min) / (max - min) : 0.0f;
    GCF32 thumbX = rect.x + (t * travelW);
    
    GCCOLOR thumbColor = gc_color(100, 100, 105, 255);
    if (ui->active == id) {
        thumbColor = gc_color(160, 160, 165, 255);
    } else if (ui->hot == id) {
        thumbColor = gc_color(130, 130, 135, 255);
    }
    
    gc_draw_fill(ui->window, (GCRECT){thumbX, rect.y, thumbW, rect.h}, thumbColor);
    
    return changed;
}

static inline void gc_ui_scroll_begin(GCUI *ui, GCUISCROLL *scroll, GCRECT view, GCF32 content,
                                      GCF32 wheelSpeed)
{
    GC_ASSERT(ui);
    GC_ASSERT(scroll);
    
    scroll->view    = view;
    scroll->content = content;
    
    GCF32 max = content - view.h;
    if (max < 0.0f)
        max = 0.0f;
    if (scroll->offset < 0.0f)
        scroll->offset = 0.0f;
    if (scroll->offset > max)
        scroll->offset = max;
    
    gc_ui_handle_scrollwheel(ui, view, view.h, content, &scroll->offset, wheelSpeed);
    gc_text_clip_rect(ui, view);
}

static inline GCB32 gc_ui_scroll_end(GCUI *ui, GCUISCROLL *scroll)
{
    GC_ASSERT(ui);
    GC_ASSERT(scroll);
    
    gc_text_clip_clear(ui);
    
    GCF32  barW = 10.0f;
    GCRECT bar  = {scroll->view.x + scroll->view.w - barW, scroll->view.y + 2.0f, barW,
        scroll->view.h - 4.0f};
    
    return gc_ui_scrollbar_vertical(ui, bar, scroll->view.h, scroll->content, &scroll->offset);
}

static inline GCUSIZE gc_text_utf8_fwd(const char *s, GCUSIZE len, GCUSIZE pos)
{
    if (pos < len) {
        pos += 1;
        while (pos < len && (((GCU8)s[pos] & 0xC0) == 0x80))
            pos += 1;
    }
    return pos;
}

static inline GCB32 gc_ui_textbox(GCUI *ui, GCRECT rect, char **buf, GCUSIZE *cap, GCARENA *arena)
{
    GC_ASSERT(ui);
    GC_ASSERT(buf);
    GC_ASSERT(*buf);
    GC_ASSERT(cap);
    GC_ASSERT(*cap > 1);
    GC_ASSERT(arena);
    
    char *text = *buf;
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (ui->mousePressed) {
        if (inside) {
            ui->focus  = id;
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
            memmove(text + ui->cursor + ui->inputLen, text + ui->cursor, len - ui->cursor + 1);
            memcpy(text + ui->cursor, ui->input, ui->inputLen);
            ui->cursor += ui->inputLen;
            changed = GC_TRUE;
            len     = strlen(text);
        }
        if (gc_window_key_was_pressed(ui->window, GC_KEY_BACKSPACE) && ui->cursor > 0) {
            GCUSIZE prev = gc_text_utf8_back(text, ui->cursor);
            memmove(text + prev, text + ui->cursor, len - ui->cursor + 1);
            ui->cursor = prev;
            changed    = GC_TRUE;
            len        = strlen(text);
        }
        if (gc_window_key_was_pressed(ui->window, GC_KEY_DELETE) && ui->cursor < len) {
            GCUSIZE next = gc_text_utf8_fwd(text, len, ui->cursor);
            memmove(text + ui->cursor, text + next, len - next + 1);
            changed = GC_TRUE;
            len     = strlen(text);
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
        HDC hdc = (HDC)ui->window->deviceContext;
        HFONT old_font = (HFONT)SelectObject(hdc, (HFONT)ui->font);
        
        SIZE total_size = {0};
        SIZE cursor_size = {0};
        int text_len = (int)strlen(text);
        
        GetTextExtentPoint32A(hdc, text, text_len, &total_size);
        GetTextExtentPoint32A(hdc, text, (int)ui->cursor, &cursor_size);
        
        SelectObject(hdc, old_font);
        
        GCI32 tw = (GCI32)total_size.cx;
        GCI32 th = (GCI32)total_size.cy;
        cw = (GCI32)cursor_size.cx;
        
        GCF32 ty = rect.y + (rect.h - (GCF32)th) * 0.5f;
        if ((GCF32)tw > rect.w - 16.0f) {
            tx = rect.x + rect.w - 8.0f - (GCF32)cw;
            if (tx > rect.x + 8.0f)
                tx = rect.x + 8.0f;
        }
        
        gc_text_clip_rect(ui, rect);
        gc_ui_text(ui, text, tx, ty, gc_color(245, 245, 245, 255));
        gc_text_clip_clear(ui);
        
        if (ui->focus == id && rect.h > 14.0f && (((GCI32)(ui->time * 2.0f) & 1) == 0)) {
            GCF32 chh = rect.h - 12.0f;
            gc_draw_fill(ui->window, (GCRECT){tx + (GCF32)cw, rect.y + 6.0f, 2.0f, chh},
                         gc_color(245, 245, 245, 255));
        }
    }
    
    if (ui->focus == id) {
        HWND hwnd = (HWND)ui->window->handle;
        HIMC himc = ImmGetContext(hwnd);
        if (himc) {
            COMPOSITIONFORM cf;
            cf.dwStyle = CFS_RECT;
            cf.ptCurrentPos.x = (LONG)rect.x;
            cf.ptCurrentPos.y = (LONG)rect.y;
            cf.rcArea.left = (LONG)rect.x;
            cf.rcArea.top = (LONG)rect.y;
            cf.rcArea.right = (LONG)(rect.x + rect.w);
            cf.rcArea.bottom = (LONG)(rect.y + rect.h);
            ImmSetCompositionWindow(himc, &cf);
            ImmReleaseContext(hwnd, himc);
        }
    }
    
    return changed;
}

static inline GCB32 gc_ui_combobox(GCUI *ui, GCRECT rect, const char **items, GCI32 count,
                                   GCI32 *selected)
{
    GC_ASSERT(ui);
    GC_ASSERT(ui->window);
    GC_ASSERT(ui->window->deviceContext);
    GC_ASSERT(items);
    GC_ASSERT(selected);
    
    if (count < 1)
        return GC_FALSE;
    if (*selected < 0)
        *selected = 0;
    if (*selected >= count)
        *selected = count - 1;
    
    GCU32 id     = ui->nextId++;
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
        gc_text_centered(ui, items[*selected], (GCRECT){rect.x, rect.y, rect.w - 28.0f, rect.h},
                         gc_color(245, 245, 245, 255));
    
    HDC hdc = (HDC)ui->window->deviceContext;
    HPEN arrow_pen = CreatePen(PS_SOLID, 1, RGB(245, 245, 245));
    HPEN old_pen = (HPEN)SelectObject(hdc, arrow_pen);
    
    GCF32 ax = rect.x + rect.w - 24.0f;
    GCF32 ay = rect.y + rect.h * 0.5f;
    
    POINT pt;
    MoveToEx(hdc, (int)ax, (int)(ay - 4.0f), &pt);
    LineTo(hdc, (int)(ax + 7.0f), (int)(ay + 3.0f));
    LineTo(hdc, (int)(ax + 14.0f), (int)(ay - 4.0f));
    
    SelectObject(hdc, old_pen);
    DeleteObject(arrow_pen);
    
    GCB32 changed = GC_FALSE;
    if (ui->open == id) {
        GC_ASSERT(count < 1024);
        GCRECT list = {rect.x, rect.y + rect.h + 4.0f, rect.w, rect.h * (GCF32)count};
        if (ui->mousePressed && !inside && !gc_rect_contains(list, ui->mouseX, ui->mouseY))
            ui->open = 0;
    }
    
    if (ui->open == id) {
        GCRECT list = {rect.x, rect.y + rect.h + 4.0f, rect.w, rect.h * (GCF32)count};
        GCU32  base = 0x01000000u + ((GCU32)id << 10);
        GCI32  hot  = -1;
        for (GCI32 i = 0; i < count; ++i) {
            GCU32  row = base + (GCU32)i;
            GCRECT r   = {rect.x, rect.y + rect.h + 4.0f + rect.h * (GCF32)i, rect.w, rect.h};
            GCB32  in  = gc_rect_contains(r, ui->mouseX, ui->mouseY);
            if (in) {
                ui->hot = row;
                hot     = i;
            }
            if (in && ui->mousePressed)
                ui->active = row;
            if (ui->active == row && ui->mouseReleased) {
                if (in && *selected != i) {
                    *selected = i;
                    changed   = GC_TRUE;
                }
                ui->active = 0;
                ui->open   = 0;
            }
        }
        if (ui->open == id) {
            ui->popupOpen     = GC_TRUE;
            ui->popupList     = list;
            ui->popupItems    = items;
            ui->popupCount    = count;
            ui->popupSelected = *selected;
            ui->popupHot      = hot;
            ui->popupRowH     = rect.h;
        }
    }
    
    return changed;
}

static inline GCB32 gc_ui_toggle(GCUI *ui, GCRECT rect, const char *label, GCB32 *value)
{
    GC_ASSERT(ui);
    GC_ASSERT(value);
    
    GCU32 id     = ui->nextId++;
    GCB32 inside = gc_rect_contains(rect, ui->mouseX, ui->mouseY);
    if (inside)
        ui->hot = id;
    if (inside && ui->mousePressed)
        ui->active = id;
    
    GCB32 changed = GC_FALSE;
    if (ui->active == id && ui->mouseReleased) {
        if (inside) {
            *value  = *value ? GC_FALSE : GC_TRUE;
            changed = GC_TRUE;
        }
        ui->active = 0;
    }
    
    GCCOLOR track = *value ? gc_color(50, 120, 220, 255) : gc_color(60, 60, 68, 255);
    gc_draw_fill(ui->window, rect, track);
    gc_draw_outline(ui->window, rect, gc_color(140, 140, 150, 255));
    GCF32 pad  = 2.0f;
    GCF32 knob = rect.h - pad * 2.0f;
    GCF32 kx   = *value ? rect.x + rect.w - knob - pad : rect.x + pad;
    gc_draw_fill(ui->window, (GCRECT){kx, rect.y + pad, knob, knob}, gc_color(230, 230, 235, 255));
    if (label)
        gc_ui_text(ui, label, rect.x + rect.w + 8.0f, rect.y, gc_color(245, 245, 245, 255));
    
    return changed;
}

static inline void gc_ui_progress(GCUI *ui, GCRECT rect, GCF32 t)
{
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
