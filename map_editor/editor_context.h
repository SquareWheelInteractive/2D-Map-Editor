#pragma once

#include <raylib/raylib.h>
#include <stdint.h>
#include "tile.h"

#define MAX_MAP_SIZE 32

typedef struct EditorContext{
    Camera2D cam_2d;
    Tile tile_types_arr[MAX_TILE_TYPES];
    int16_t map_dimensions[MAX_MAP_SIZE * MAX_MAP_SIZE];
    int16_t tile_selector;
    int8_t tile_amount_num;
    int16_t map_width;
    int16_t map_height;
} EditorContext;

void init_world_context(EditorContext* world_context);
void load_texture(EditorContext* context);
Vector2 set_screen_size(EditorContext* world_context, int16_t map_width, int16_t map_height, float world_scale);
void clear_map(int16_t map_width, int16_t map_height, int16_t* map, int key);
void paint(int16_t scrn_width, int16_t scrn_height, EditorContext* context);
void draw_editor(EditorContext* context);
void unload_context(EditorContext* context);
void send_to_txt(EditorContext* context);
