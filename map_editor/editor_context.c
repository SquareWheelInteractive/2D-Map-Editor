#include <math.h>
#include <stdint.h>
#include <raylib/raylib.h>
#include <stdio.h>

#define TILE_SIZE 12
#define MAP_WIDTH 15
#define MAP_HEIGHT 15
#define TILE_TYPES 3

typedef struct Tile{
    int16_t id;
    Texture2D texture;
}Tile;

typedef struct world_context{
    Camera2D cam_2d;
    Tile tile_types_arr[TILE_TYPES];
    int16_t map_dimensions[MAP_WIDTH][MAP_HEIGHT];
    int16_t tile_selector;
} world_context;

void init_world_context(world_context* world_context, char* textures[]){
    for (int16_t i = 0; i< MAP_WIDTH; i++) {
        for (int16_t j= 0; j<MAP_HEIGHT; j++) {
            world_context->map_dimensions[i][j] = 0;
        }
    }

    for (int16_t i=0; i<TILE_TYPES; i++) {
        world_context->tile_types_arr[i].id = i+1;
        world_context->tile_types_arr[i].texture = LoadTexture(textures[i]);
    }
}
Vector2 get_screen_size(world_context* world_context, float world_scale){
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
void paint(int16_t scrn_width, int16_t scrn_height, world_context* context){
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

void draw_tiles(world_context* context){
    for (int16_t col = 0; col < MAP_WIDTH; col++) {
        for (int16_t row = 0; row < MAP_HEIGHT; row++) {
            int tile_id = context->map_dimensions[col][row];
            for (int16_t t = 0; t < TILE_TYPES; t++) {
                if(tile_id>0 && context->tile_types_arr[t].id == tile_id){
                    DrawTexture(context->tile_types_arr[t].texture, col*TILE_SIZE, row*TILE_SIZE, WHITE);
                    break;
                }
            }
        }
    }
}
void draw_editor(world_context* context){
    draw_tiles(context);

    if(context->tile_selector != 0){
        Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), context->cam_2d);
        DrawTexture(context->tile_types_arr[context->tile_selector - 1].texture, mouse_pos.x, mouse_pos.y, WHITE);
    }

    DrawLineV((Vector2){0, TILE_SIZE * MAP_HEIGHT}, (Vector2){TILE_SIZE*MAP_WIDTH, TILE_SIZE*MAP_HEIGHT}, GRAY);
}

void change_to_next_tile_type(world_context* context, int next_key, int prev_key){
    if(IsKeyPressed(next_key)){
        context->tile_selector++;

        if(context->tile_selector > TILE_TYPES)
            context->tile_selector = 0;
    }
    if(IsKeyPressed(prev_key)){
        context->tile_selector--;

        if(context->tile_selector < 0)
            context->tile_selector = TILE_TYPES;
    }
}

void unload_context(world_context* context){
    for (int16_t i = 0; i < TILE_TYPES; i++) {
        UnloadTexture(context->tile_types_arr[i].texture);
    }
}

void send_to_txt(world_context* context){
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
