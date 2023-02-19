#include "../includes/screen.h"

PONG Screen_t *init_game(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Screen_t pointer [GAME].");
        return NULL;
    }
#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[GAME]Screen_t structure created.");
#endif
    screen->type = GAME_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;
    return screen;
}

PONG void  update_game(Screen_t *const screen)
{
    if (IsKeyPressed(KEY_BACKSPACE)) 
    {
        screen->nextScreenType = MENU_SCREEN_E;
    }
}

PONG void draw_game(const Screen_t *const screen)
{
    ClearBackground(SKYBLUE);
}

PONG void unload_game(Screen_t ** ptr)
{
    if ((*ptr) != NULL)
    {
        MemFree((*ptr));
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[GAME] Screen_t pointer destroyed.");
#endif
    }
}