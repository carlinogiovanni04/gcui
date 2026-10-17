# gcui

Single-header immediate mode UI layer using SDL3.

## Build

```sh
make
./bin/gcui_test
```

Requires SDL3 and SDL3_ttf. One default font is picked from the system at runtime; `gc_ui_set_font` overrides it.

## Frame loop

```c
GCARENA *arena = gc_arena_create(GC_MB(2));
GCWINDOW *window = gc_window_create(arena, gc_str8_create(arena, "app"), 1280, 720, GC_FALSE);

GCUI ui;
gc_ui_init(&ui, window);
gc_ui_load_default_font(&ui, 20.0f);

while(!gc_window_should_quit(window)){
    gc_window_begin(window);
    gc_ui_begin(&ui);

    GCF32 dt = gc_window_dt(window);
    if(gc_ui_button(&ui, (GCRECT){32.0f, 32.0f, 200.0f, 48.0f}, "Click"))
        ...

    gc_ui_end(&ui);
    gc_window_end(window);
}

gc_ui_shutdown(&ui);
gc_window_destroy(window);
gc_window_quit();
gc_arena_destroy(arena);
```

`gc_window_begin` pumps events, snapshots input, and computes clamped deltatime. All drawing happens between begin and end. `gc_ui_end` draws deferred popups last so they land on top.

## Widgets

All widgets take explicit rects and return `GCB32` changed/clicked, except where noted.

| Call | Notes |
|---|---|
| `gc_ui_button(ui, rect, label)` | returns clicked |
| `gc_ui_checkbox(ui, box, label, *value)` | returns changed |
| `gc_ui_toggle(ui, rect, label, *value)` | switch, returns changed |
| `gc_ui_slider(ui, rect, min, max, *value)` | drag, returns changed |
| `gc_ui_textbox(ui, rect, &buf, &cap, arena)` | grows `buf` via arena, returns changed, Enter unfocuses |
| `gc_ui_combobox(ui, rect, items, count, *selected)` | returns true on new selection |
| `gc_ui_progress(ui, rect, t)` | `t` clamped to 0..1, no return |
| `gc_ui_label(ui, rect, text, color)` | ellipsizes with `...` past `rect.w` |
| `gc_ui_panel(ui, rect, color)` | fill rect |

## Helpers

- `gc_draw_fill(window, rect, color)` / `gc_draw_outline(window, rect, color)`
- `gc_rect_contains(rect, x, y)`
- `gc_color(r, g, b, a)`
- `gc_window_dt(window)` / `gc_window_elapsed(window)`
- `gc_window_key_was_pressed` (edge) / `gc_window_key_currently_pressed` (held)
- `gc_window_set_clear(window, color)`

Widget ids are positional: call widgets in the same order every frame. Combobox rows use a stable id range so opening one never shifts other widgets' ids.
