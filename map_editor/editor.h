#pragma once

#include "editor_context.h"
#include <raylib/raylib.h>

typedef struct Editor{
    EditorContext context;
    Vector2 scrn_size;
}Editor;

void editor_init(Editor* editor);
void editor_update(Editor* editor);
void editor_draw(Editor* editor);
void editor_unload(Editor* editor);
