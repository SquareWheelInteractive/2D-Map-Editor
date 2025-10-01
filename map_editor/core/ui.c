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
    if(!editor_context)return; 

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
            if(editor_context->tile_amount_num < MAX_TILE_TYPES){
                Texture tex = LoadTexture(path_text);
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
        }

        ImGui::End();
    }
}
bool is_load_ui_active(){
    return show_load_box;
}

bool settings_choosed = false;
int m_w = 0;
int m_h = 0;
int w_scale = 0;
int tile_size = 0;
void map_settings_ui(EditorContext* editor_context){
    if(!editor_context)return;

    if(!settings_choosed){
        ImGui::Begin("Map settings", nullptr,
                     ImGuiWindowFlags_AlwaysAutoResize |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoCollapse); // Create a window
        ImGui::InputInt("map width", &m_w);
        ImGui::InputInt("map height", &m_h);
        ImGui::InputInt("tile size", &tile_size);
        ImGui::InputInt("world scale", &w_scale);
        if(ImGui::Button("set")){
            if(w_scale <= 0 || m_w <= 0 || m_h <= 0 || m_w * m_h > MAX_MAP_SIZE * MAX_MAP_SIZE || tile_size <= 0){
                ImGui::End();
                return;
            }
            editor_context->tile_size = tile_size;
            Vector2 scn_size = set_screen_size(editor_context, m_w, m_h, (float)w_scale);
            SetWindowSize((int)scn_size.x, (int)scn_size.y);
            init_world_context(editor_context);
            settings_choosed = true;
        }
        ImGui::End();
    }
}
bool are_map_settings_choosed(){
    return settings_choosed;
}

void draw_ui(EditorContext* editor_context){
    if(!editor_context) return;

    rlImGuiBegin();

    map_settings_ui(editor_context);
    if(settings_choosed)
        ui_load_texture(editor_context);

    rlImGuiEnd();
}
