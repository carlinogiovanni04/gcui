#include "../include/gcui.h"

int main(void){
    GCARENA *arena = gc_arena_create(GC_MB(2));

    GCSTRING8 *windowTitle = gc_str8_create(arena, "gcui");
    GCWINDOW *window = gc_window_create(arena, windowTitle, 1280, 720, GC_FALSE);
    if(!window){
        printf("failed to create window\n");
        gc_arena_destroy(arena);
        return 1;
    }

    GCUI *ui = gc_ui_init(arena, window);
    gc_ui_load_default_font(ui, 20.0f);


    GCB32 showBox = GC_TRUE;
    GCB32 fast = GC_FALSE;
    GCF32 speed = 240.0f;
    GCF32 boxX = 0.0f;
    GCI32 clicks = 0;
    char *name = (char *)gc_arena_push(arena, 128);
    memset(name, 0, 128);
    GCUSIZE nameCap = 128;
    char line[96];
    const char *modes[] = {"Chill", "Normal", "Spicy"};
    GCCOLOR cols[] = {gc_color(50, 120, 220, 255), gc_color(80, 200, 120, 255), gc_color(220, 80, 80, 255)};
    GCI32 mode = 0;

    while(!gc_window_should_quit(window)){
        gc_window_begin(window);
        gc_ui_begin(ui);

        GCF32 dt = gc_window_dt(window);

        if(gc_window_key_was_pressed(window, GC_KEY_ESCAPE))
            break;

        if(showBox){
            GCF32 eff = fast ? speed * 2.0f : speed;
            boxX += eff * dt;
            if(boxX > 1280.0f)
                boxX -= 1280.0f;
            gc_draw_fill(window, (GCRECT){boxX, 400.0f, 64.0f, 64.0f}, cols[mode]);
        }

        gc_ui_panel(ui, (GCRECT){16.0f, 16.0f, 344.0f, 544.0f}, gc_color(36, 36, 42, 255));

        if(gc_ui_button(ui, (GCRECT){32.0f, 32.0f, 312.0f, 48.0f}, "Click me"))
            clicks += 1;

        snprintf(line, sizeof(line), "clicks: %d", clicks);
        gc_ui_label(ui, (GCRECT){32.0f, 92.0f, 312.0f, 28.0f}, line, gc_color(245, 245, 245, 255));

        snprintf(line, sizeof(line), "dt: %.3f ms  fps: %.0f", (GCF64)(dt * 1000.0f), dt > 0.0f ? (GCF64)(1.0f / dt) : 0.0);
        gc_ui_label(ui, (GCRECT){32.0f, 124.0f, 312.0f, 28.0f}, line, gc_color(180, 180, 190, 255));

        gc_ui_checkbox(ui, (GCRECT){32.0f, 160.0f, 24.0f, 24.0f}, "Show box", &showBox);
        gc_ui_label(ui, (GCRECT){32.0f, 192.0f, 312.0f, 28.0f}, "Speed", gc_color(245, 245, 245, 255));
        gc_ui_slider(ui, (GCRECT){32.0f, 224.0f, 312.0f, 24.0f}, 0.0f, 600.0f, &speed);

        gc_ui_label(ui, (GCRECT){32.0f, 260.0f, 312.0f, 28.0f}, "Name", gc_color(245, 245, 245, 255));
        gc_ui_textbox(ui, (GCRECT){32.0f, 292.0f, 312.0f, 36.0f}, &name, &nameCap, arena);
        snprintf(line, sizeof(line), "Hello, %s", name);
        gc_ui_label(ui, (GCRECT){32.0f, 336.0f, 312.0f, 28.0f}, line, gc_color(180, 180, 190, 255));

        gc_ui_label(ui, (GCRECT){32.0f, 372.0f, 312.0f, 28.0f}, "Box color", gc_color(245, 245, 245, 255));
        gc_ui_combobox(ui, (GCRECT){32.0f, 404.0f, 312.0f, 40.0f}, modes, 3, &mode);

        gc_ui_toggle(ui, (GCRECT){32.0f, 456.0f, 56.0f, 28.0f}, "Fast", &fast);

        gc_ui_label(ui, (GCRECT){32.0f, 496.0f, 312.0f, 28.0f}, "Progress", gc_color(245, 245, 245, 255));
        gc_ui_progress(ui, (GCRECT){32.0f, 528.0f, 312.0f, 16.0f}, boxX / 1280.0f);

        gc_ui_end(ui);
        gc_window_end(window);
    }

    gc_ui_destroy(ui);
    gc_window_destroy(window);
    gc_arena_destroy(arena);

    return 0;
}
