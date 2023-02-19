#include "../includes/screen.h"

PONG Screen_t *init_option(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Screen_t pointer [OPTION].");
        return NULL;
    }
#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[OPTION]Screen_t structure created.");
#endif
    screen->type = OPTION_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;
    return screen;
}

PONG void  update_option(Screen_t *const screen)
{
    if (IsKeyPressed(KEY_BACKSPACE)) 
    {
        screen->nextScreenType = MENU_SCREEN_E;
    }
}

PONG void draw_option(const Screen_t *const screen)
{
    ClearBackground(GREEN);
}

PONG void unload_option(Screen_t **ptr)
{
    if ((*ptr) != NULL)
    {
        MemFree((*ptr));
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[OPTION] Screen_t pointer destroyed.");
#endif
    }
}