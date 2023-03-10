#include "../includes/screen.h"
#include "../includes/theme.h"
#include "../includes/palette.h"
#include "../includes/ball.h"

extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static Palette_t *player = NULL;
static Ball_t *ball = NULL;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
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

    player = init_player();
    ball = init_ball();

    return screen;
}

PONG void  update_game(Screen_t *const screen)
{
    update_player(player);
    update_ball(ball, player->transform);
    if (IsKeyPressed(KEY_BACKSPACE)) 
        screen->nextScreenType = MENU_SCREEN_E;
}

PONG void draw_game(const Screen_t *const screen)
{
    ClearBackground($theme->color[1]);
    draw_player(player);
    draw_ball(ball);
}

PONG void unload_game(Screen_t ** ptr)
{
    if ((*ptr) != NULL)
    {
        unload_player(&player);
        unload_ball(&ball);

        MemFree((*ptr));
        (*ptr) = NULL;
        #if defined(PONG_DEBUG)
            TraceLog(LOG_INFO, "[GAME] Screen_t pointer destroyed.");
        #endif
    }
}

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------