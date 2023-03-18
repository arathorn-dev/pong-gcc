#include "../includes/screen.h"
#include "../includes/theme.h"
#include "../includes/package.h"

extern Theme_t *$theme;
extern Package_t *$package;

extern int32_t playerScore;
extern int32_t enemyScore;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static float _counter = PONG_COUNTER_WINNER_PAGE;
static const char *_text;

//----------------------------------------------------------------------------------
// Static functions declaration.
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    PONG static void _draw_counter(void);
    PONG static void _draw_text(void);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions implementation.
//----------------------------------------------------------------------------------
PONG Screen_t *init_winner(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_ERROR, "[WINNER] Couldn't initialize Screen_t pointer.");
        return NULL;
    }
#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[WINNER]Screen_t structure created.");
#endif

    screen->type = WINNER_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;

    _counter = PONG_COUNTER_WINNER_PAGE;

    if (playerScore > enemyScore)
    {
        _text = "PLAYER";
    }
    else
    {
        _text = "ENEMY";
    }

    return screen;
}
PONG void update_winner(Screen_t *const screen)
{
    if (IsKeyPressed(KEY_ESCAPE))
    {
        screen->nextScreenType = MENU_SCREEN_E;
    }

    if (_counter > 1)
    {
        _counter -= (1.0f / PONG_FPS);
    }
    else
    {
        screen->nextScreenType = MENU_SCREEN_E;
    }
}
PONG void draw_winner(const Screen_t *const screen)
{
    ClearBackground($theme->color[2]);

    _draw_counter();
    _draw_text();
}
PONG void unload_winner(Screen_t **ptr)
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

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
PONG static void _draw_counter(void)
{
    const char *text = TextFormat("%1.0f", ceilf(_counter));
    Font font = $package->fonts[FONT_04B_03_E];
    int32_t fontSize = font.baseSize * 3;
    Vector2 measure = MeasureTextEx(font, text, fontSize, 1);

    DrawRectangleRec(
        (Rectangle){
            0,
            GetScreenHeight() / 2.35,
            GetScreenWidth(),
            fontSize},
        $theme->color[0]);

    DrawText(
        text,
        GetScreenWidth() / 2 - (measure.x / 3),
        GetScreenHeight() / 2 - (measure.y / 3),
        fontSize,
        $theme->color[3]);
}
PONG static void _draw_text(void)
{
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight() / 1.5;
    Font font = $package->fonts[FONT_04B_03_E];
    Vector2 position = {0};
    float fontSize = font.baseSize;
    Vector2 measure = MeasureTextEx(
        font,
        _text,
        fontSize,
        1);
    position.x = (width / 2) - (measure.x / 2.2);
    position.y = height;
    DrawTextEx(
        font,
        _text,
        position,
        fontSize,
        1,
        $theme->color[0]);
}