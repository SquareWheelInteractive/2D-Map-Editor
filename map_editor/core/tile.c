#include "editor_context.h"
#include "tile.h"

void draw_tiles(EditorContext* context){
    if(!context || context->tile_amount_num <= 0) return; 

    for (int16_t col = 0; col < context->map_width; col++) {
        for (int16_t row = 0; row < context->map_height; row++) {
            int tile_id = context->map_dimensions[row * context->map_width+ col];
            for (int16_t t = 0; t < context->tile_amount_num; t++) {
                if(tile_id>0 && context->tile_types_arr[t].id == tile_id){
                    DrawTexture(context->tile_types_arr[t].texture, col*context->tile_size, row*context->tile_size, WHITE);
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

        if(context->tile_selector > context->tile_amount_num)
            context->tile_selector = 0;
    }
    if(IsKeyPressed(prev_key)){
        context->tile_selector--;

        if(context->tile_selector < 0)
            context->tile_selector = context->tile_amount_num;
    }
}
