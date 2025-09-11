#include <raylib/raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <raylib/raygui.h>
#include "ui.h"

bool show_load_box = false;
#define PATH_MAX_CHAR_LENGTH 100
char path_text[PATH_MAX_CHAR_LENGTH];
void ui_load_texture(EditorContext* editor_context){
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
                editor_context->tile_types_arr[editor_context->curr_tile_inx].texture = tex;
                editor_context->tile_types_arr[editor_context->curr_tile_inx].id = editor_context->curr_tile_inx + 1;
                editor_context->curr_tile_inx++;
                show_load_box = false;
            break;
        }
    }
}
