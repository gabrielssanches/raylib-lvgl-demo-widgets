#include "raylib.h"
#include "lv_raylib.h"

#include "lvgl/demos/lv_demos.h"

#define DISPLAY_WIDTH   640
#define DISPLAY_HEIGHT  480
#define SCREEN_WIDTH    (50 + (2 * DISPLAY_WIDTH))
#define SCREEN_HEIGHT   (50 + DISPLAY_HEIGHT)

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static void UpdateDrawFrame(void) {
    lv_raylib_display_update();

    BeginDrawing();
    ClearBackground(RAYWHITE);

    lv_raylib_display_draw();

    DrawText(TextFormat("FPS:%i", GetFPS()), 30, 30, 30, RED);

    EndDrawing();
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib + lvgl demo widgets");

    lv_init();
    lv_raylib_window_create(SCREEN_WIDTH, SCREEN_HEIGHT);

    // first lvgl display with demo
    (void)lv_raylib_display_create(0, (SCREEN_HEIGHT -DISPLAY_HEIGHT)/2, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_demo_widgets();

    // second lvgl display with demo
    (void)lv_raylib_display_create(SCREEN_WIDTH/2, (SCREEN_HEIGHT -DISPLAY_HEIGHT)/2, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_demo_widgets();

#if defined(PLATFORM_WEB)
    EM_ASM({ window.onkeydown = function(e) { return !(e.keyCode == 32); }; });
    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
#else
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        UpdateDrawFrame();
    }
#endif

    lv_raylib_window_delete();

    CloseWindow();

    return 0;
}
