#include "editor_context.h"
#include "tile.h"

void draw_tiles(EditorContext* context){
    if(!context || context->curr_tile_inx <= 0) return; 

    for (int16_t col = 0; col < MAP_WIDTH; col++) {
        for (int16_t row = 0; row < MAP_HEIGHT; row++) {
            int tile_id = context->map_dimensions[col][row];
            for (int16_t t = 0; t < context->curr_tile_inx; t++) {
                if(tile_id>0 && context->tile_types_arr[t].id == tile_id){
                    DrawTexture(context->tile_types_arr[t].texture, col*TILE_SIZE, row*TILE_SIZE, WHITE);
                    break;
                }
            }
        }
    }
}

void change_to_next_tile_type(EditorContext* context, int next_key, int prev_key){
    if(!context)return;

    if(IsKeyPressed(next_key)){
        context->tile_selector++;

        if(context->tile_selector > context->curr_tile_inx)
            context->tile_selector = 0;
    }
    if(IsKeyPressed(prev_key)){
        context->tile_selector--;

        if(context->tile_selector < 0)
            context->tile_selector = context->curr_tile_inx;
    }
}
