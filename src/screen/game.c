#include "../includes/screen.h"
#include "../includes/theme.h"
#include "../includes/package.h"
#include "../includes/palette.h"
#include "../includes/ball.h"

extern Theme_t *$theme;
extern Package_t *$package;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static Palette_t *player = NULL;
static Ball_t *ball = NULL;

static float counter = 3.0f;

static bool pause = false;
static bool reset = false;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif
PONG static void _draw_counter(void);
#if defined(__cplusplus)
}
#endif
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

    pause = false;
    reset = false;

    counter = 3.0f;

    screen->type = GAME_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;

    player = init_player();
    ball = init_ball();

    return screen;
}

PONG void  update_game(Screen_t *const screen)
{

    if (IsKeyPressed(KEY_BACKSPACE)) 
        screen->nextScreenType = MENU_SCREEN_E;
    
    if (IsKeyPressed(KEY_P))
        pause = !pause;

    if (!pause)
    {
        update_player(player);
        update_ball(ball, player->transform);
    }

    if (check_collision_ball())
    {
        reset = true;
        pause = true;
    }

    if (reset) {
        counter -= (1.0f / PONG_FPS);
        if (counter < 0) {
            counter = 3.0f;
            reset = false;
            pause = false;
            reset_ball(ball);
        }
    }
}

PONG void draw_game(const Screen_t *const screen)
{
    ClearBackground($theme->color[1]);
    draw_player(player);
    draw_ball(ball);

    if (reset)
        _draw_counter();
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
static void _draw_counter(void)
{
    const char *text = TextFormat("%1.0f", ceilf(counter));
    Font font = $package->fonts[FONT_ATARI];

    DrawText(
        text,
        GetScreenWidth() / 2,
        GetScreenHeight() / 2,
        font.baseSize,
        $theme->color[3]
    );
}