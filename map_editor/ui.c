#include <raylib/raylib.h>
#include "ui.h"
#include "editor_context.h"
#include "imgui.h"
#include "rlImGui.h"
#include <stdio.h>

bool show_load_box = false;
#define PATH_MAX_CHAR_LENGTH 100
char path_text[PATH_MAX_CHAR_LENGTH] = "";

void ui_load_texture(EditorContext* editor_context){
    if(IsKeyPressed(KEY_L))
        show_load_box = true;

    if(show_load_box){
        ImGui::Begin("Tile Loader", &show_load_box,
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse); // Create a window

        ImGui::Text("Enter tile path:");
        ImGui::InputText("path", path_text, IM_ARRAYSIZE(path_text));

        if(ImGui::Button("LOAD")){
            ;Texture tex = LoadTexture(path_text);
            if(tex.id == 0){
                printf("texture path is invalid\n");
                ImGui::End();
                return;
            }
            editor_context->tile_types_arr[editor_context->tile_amount_num].texture = tex;
            editor_context->tile_types_arr[editor_context->tile_amount_num].id = editor_context->tile_amount_num + 1;
            editor_context->tile_amount_num++;
            path_text[0] = '\0';
            show_load_box = false;
        }

        ImGui::End();
    }
}

void draw_ui(EditorContext* editor_context){
    rlImGuiBegin();

    ui_load_texture(editor_context);

    rlImGuiEnd();
}
