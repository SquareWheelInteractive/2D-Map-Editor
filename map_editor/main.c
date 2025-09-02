#include <raylib/raylib.h>
#include <stdint.h>
#include "editor_context.c"

int main(){
    world_context context;
    Vector2 scrn_size = get_screen_size(&context, 5.0f);

    InitWindow(scrn_size.x, scrn_size.y, "map editor");

    int curr_monitor_refresh_rate = GetMonitorRefreshRate(GetCurrentMonitor());
    SetTargetFPS(curr_monitor_refresh_rate);

    char* textures[TILE_TYPES] = {"Art/grass_tile_01.png", "Art/grass_tile_02.png", "Art/tree_tile_01.png"};
    init_world_context(&context,textures);

    while (!WindowShouldClose()) {

        clear_map(MAP_WIDTH, MAP_HEIGHT, context.map_dimensions, KEY_C);
        change_to_next_tile_type(&context, KEY_RIGHT, KEY_LEFT);

        if(IsKeyPressed(KEY_ENTER)){
            send_to_txt(&context);
        }

        paint(scrn_size.x,scrn_size.y,&context);

        BeginDrawing();
        ClearBackground(BLACK);
        BeginMode2D(context.cam_2d);

            draw_editor(&context);

        EndMode2D();
        EndDrawing();
    }

    unload_context(&context);

    CloseWindow();
    return -1;
}
