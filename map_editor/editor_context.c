#include <raylib/raylib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#include "editor_context.h"
#include "tile.h"

void init_world_context(EditorContext* editor_context){
    if(!editor_context)return;
    for (int16_t i = 0; i< MAP_WIDTH; i++) {
        for (int16_t j= 0; j<MAP_HEIGHT; j++) {
            editor_context->map_dimensions[i][j] = 0;
        }
    }
    editor_context->curr_tile_inx = 0;
}
Vector2 set_screen_size(EditorContext* editor_context, float world_scale){
    if(!editor_context){
        return (Vector2){ 0, 0};
        printf("world context is null\n");
    }
    editor_context->cam_2d.offset = (Vector2){0,0};
    editor_context->cam_2d.target = (Vector2){0,0};
    editor_context->cam_2d.zoom = world_scale;

    Vector2 scrn_width_height;
    scrn_width_height.x = MAP_WIDTH  * (TILE_SIZE * editor_context->cam_2d.zoom);
    scrn_width_height.y = MAP_HEIGHT * (TILE_SIZE * editor_context->cam_2d.zoom);

    return scrn_width_height;
}
void paint(int16_t scrn_width, int16_t scrn_height, EditorContext* editor_context){
    if(!editor_context)return;

    if(IsCursorOnScreen()){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mouse_pos = GetMousePosition();
            int col = floorf(mouse_pos.x / (TILE_SIZE*editor_context->cam_2d.zoom));
            int row = floorf(mouse_pos.y / (TILE_SIZE*editor_context->cam_2d.zoom));

            if(col < MAP_WIDTH && row < MAP_HEIGHT){
                editor_context->map_dimensions[col][row] = editor_context->tile_selector;
            }
        }
    }
}
void clear_map(int16_t map_width, int16_t map_height, int16_t map[map_width][map_height], int key){
    if(IsKeyDown(key)){
        for (int16_t i =0; i < map_width; i++) {
            for (int16_t j =0; j < map_height; j++) {
                map[i][j] = 0;
            }
        }    
    }
}
void draw_editor(EditorContext* editor_context){
    if(!editor_context)return; 

    draw_tiles(editor_context);

    if(editor_context->tile_selector != 0){
        Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), editor_context->cam_2d);
        DrawTexture(editor_context->tile_types_arr[editor_context->tile_selector - 1].texture, mouse_pos.x, mouse_pos.y, WHITE);
    }

    DrawLineV((Vector2){0, TILE_SIZE * MAP_HEIGHT}, (Vector2){TILE_SIZE*MAP_WIDTH, TILE_SIZE*MAP_HEIGHT}, GRAY);
}
void unload_context(EditorContext* editor_context){
    if(!editor_context)return;
    for (int16_t i = 0; i < editor_context->curr_tile_inx; i++) {
        UnloadTexture(editor_context->tile_types_arr[i].texture);
    }
}
void send_to_txt(EditorContext* editor_context){
    if(!editor_context)return;
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write array to file
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            fprintf(file, "%d ", editor_context->map_dimensions[col][row]);
        }
        fprintf(file, "\n");
    }

    fclose(file); 
    printf("Array written to output.txt successfully!\n");
}
