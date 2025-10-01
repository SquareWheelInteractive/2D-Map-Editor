#include "editor.h"
#include "raylib.h"
#include "rlImGui.h"
#include "ui.h"

void editor_init(Editor* editor){
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(300, 300, "map editor");

    int curr_monitor_refresh_rate = GetMonitorRefreshRate(GetCurrentMonitor());
    SetTargetFPS(curr_monitor_refresh_rate);

    rlImGuiSetup(true);
}
void editor_update(Editor *editor){
    if(is_load_ui_active() || are_map_settings_choosed() == false)
        return;

    clear_map(editor->context.map_width, editor->context.map_height, editor->context.map_dimensions, KEY_C);
    change_to_next_tile_type(&editor->context, KEY_RIGHT, KEY_LEFT);
    paint(editor->scrn_size.x, editor->scrn_size.y, &editor->context);

    if(IsKeyPressed(KEY_ENTER)){
        send_to_txt(&editor->context);
    }
}
void editor_draw(Editor *editor){
    
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(editor->context.cam_2d);
        if(are_map_settings_choosed() == true)
            draw_editor(&editor->context);

    EndMode2D();
    draw_ui(&editor->context);
    DrawFPS(12, 12);
    EndDrawing();
}
void editor_unload(Editor *editor){
    unload_context(&editor->context);
    CloseWindow();
}
