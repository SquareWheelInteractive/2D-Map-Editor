#include <raylib/raylib.h>
#include "editor.h"

int main(){
    Editor editor;
    editor_init(&editor);

    while (!WindowShouldClose()) {

        editor_update(&editor);

        editor_draw(&editor);
    }
    return 0;
}
