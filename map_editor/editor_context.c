#include <raylib/raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>

#include "editor_context.h"
#include "tile.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

void init_world_context(EditorContext* world_context){
    if(!world_context)return;
    for (int16_t i = 0; i< MAP_WIDTH; i++) {
        for (int16_t j= 0; j<MAP_HEIGHT; j++) {
            world_context->map_dimensions[i][j] = 0;
        }
    }
    world_context->curr_tile_inx = 0;
}

bool show_load_box = false;
#define PATH_MAX_CHAR_LENGTH 100
char path_text[PATH_MAX_CHAR_LENGTH];
void load_texture(EditorContext* context){
    if(IsKeyPressed(KEY_L))
        show_load_box = true;

    if(show_load_box){
        int result = GuiTextInputBox((Rectangle){12,12, 100, 200}, "TILE LOADER", "insert tile path", "LOAD", path_text, PATH_MAX_CHAR_LENGTH, 0);
        switch (result) {
            case 0:
                show_load_box = false;
            break;
            case 1:
                ;Texture tex = LoadTexture(path_text);
                if(tex.id == 0)
                    printf("texture path is invalid");
                context->tile_types_arr[context->curr_tile_inx].texture = tex;
                context->tile_types_arr[context->curr_tile_inx].id = context->curr_tile_inx + 1;
                context->curr_tile_inx++;
                show_load_box = false;
            break;
        }
    }
}
Vector2 get_screen_size(EditorContext* world_context, float world_scale){
    if(!world_context){
        return (Vector2){ 0, 0};
        printf("world context is null");
    }
    world_context->cam_2d.offset = (Vector2){0,0};
    world_context->cam_2d.target = (Vector2){0,0};
    world_context->cam_2d.zoom = world_scale;

    Vector2 scrn_width_height;
    scrn_width_height.x = MAP_WIDTH  * (TILE_SIZE * world_context->cam_2d.zoom);
    scrn_width_height.y = MAP_HEIGHT* (TILE_SIZE * world_context->cam_2d.zoom);

    return scrn_width_height;
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
void paint(int16_t scrn_width, int16_t scrn_height, EditorContext* context){
    if(!context)return;

    if(IsCursorOnScreen()){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            Vector2 mouse_pos = GetMousePosition();
            int col = floorf(mouse_pos.x / (TILE_SIZE*context->cam_2d.zoom));
            int row = floorf(mouse_pos.y / (TILE_SIZE*context->cam_2d.zoom));

            if(col < MAP_WIDTH && row < MAP_HEIGHT){
                context->map_dimensions[col][row] = context->tile_selector;
            }
        }
    }
}

void draw_editor(EditorContext* context){
    if(!context)return; 

    draw_tiles(context);

    if(context->tile_selector != 0){
        Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), context->cam_2d);
        DrawTexture(context->tile_types_arr[context->tile_selector - 1].texture, mouse_pos.x, mouse_pos.y, WHITE);
    }

    DrawLineV((Vector2){0, TILE_SIZE * MAP_HEIGHT}, (Vector2){TILE_SIZE*MAP_WIDTH, TILE_SIZE*MAP_HEIGHT}, GRAY);
}


void unload_context(EditorContext* context){
    if(!context)return;
    for (int16_t i = 0; i < context->curr_tile_inx; i++) {
        UnloadTexture(context->tile_types_arr[i].texture);
    }
}

void send_to_txt(EditorContext* context){
    if(!context)return;
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    // Write array to file
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            fprintf(file, "%d ", context->map_dimensions[col][row]);
        }
        fprintf(file, "\n");
    }

    fclose(file); 
    printf("Array written to output.txt successfully!\n");
}
