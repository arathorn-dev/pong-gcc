#include "../includes/screen.h"

Screen_t *create_menu(void)
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
    screen->background = SKYBLUE;

    return screen;
}

void update_menu(Screen_t *const screen)
{
    // TODO
}

void draw_menu(const Screen_t *const screen)
{
    ClearBackground(screen->background);
    DrawText("Menu screen", 10, 10, 24, WHITE);
}

void close_menu(Screen_t **ptr)
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