#pragma once

#include <raylib/raylib.h>
#include <stdint.h>

#define TILE_SIZE 12
#define MAX_TILE_TYPES 32
typedef struct Tile{
    int16_t id;
    Texture2D texture;
}Tile;

typedef struct EditorContext EditorContext;

void draw_tiles(EditorContext* context);
void change_to_next_tile_type(EditorContext* context, int next_key, int prev_key);

