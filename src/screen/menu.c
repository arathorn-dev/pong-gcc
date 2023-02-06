#include "../includes/screen.h"
#include "../includes/package.h"

extern Package_t *$package;

PONG Screen_t *create_menu(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Screen_t pointer [MENU].");
        return NULL;
    }

#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[MENU]Screen_t structure created.");
#endif

    screen->type = MENU_SCREEN_E;
    screen->background = PONG_COLOR_1;
    return screen;
}

PONG void update_menu(Screen_t *const screen)
{
    // TODO
}

PONG void draw_menu(const Screen_t *const screen)
{
    ClearBackground(screen->background);

    DrawTextEx(
        $package->fonts[FONT_04B_03_E],
        "New game",
        (Vector2){10, 10},
        $package->fonts[FONT_04B_03_E].baseSize,
        1,
        RAYWHITE);
}

PONG void close_menu(Screen_t **ptr)
{
    if ((*ptr) != NULL)
    {
        MemFree((*ptr));
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[MENU] Screen_t pointer destroyed.");
#endif
    }
}