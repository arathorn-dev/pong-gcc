#include "../includes/screen.h"
#include "../includes/utils.h"
#include "../includes/package.h"

extern Package_t *$package;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------

static uint8_t _option;
static const char *_optionList[4] = {
    "GBP-NSO color",
    "Rustic GB",
    "Mist GB",
    "Gold GB",
};

static const char *_authorText = PONG_AUTHOR;

//----------------------------------------------------------------------------------
// Static functions declaration.
//----------------------------------------------------------------------------------

#if defined(_cplusplus)
extern "C" {
#endif
    PONG static void _update_text(void);
    PONG static void _draw_option_list(void);
    PONG static void _draw_author(void);
    PONG static void _reset(void);
#if defined(_cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions implementation.
//----------------------------------------------------------------------------------
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
    _update_text();
}

PONG void draw_option(const Screen_t *const screen)
{
    ClearBackground(PONG_COLOR_1);
    _draw_option_list();
    _draw_author();
}

PONG void unload_option(Screen_t **ptr)
{
    if ((*ptr) != NULL)
    {
        _reset();
        MemFree((*ptr));
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[OPTION] Screen_t pointer destroyed.");
#endif
    }
}

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------

PONG static void _update_text(void)
{
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        _option = Clamp(--_option, 0, 4 - 1);
        PlaySound(
            $package->sound[SELECT_SOUND]
        );
    }
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        _option = Clamp(++_option, 0, 4 - 1);
        PlaySound(
            $package->sound[SELECT_SOUND]
        );
    }
}

PONG static void _draw_option_list(void)
{
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();
    height = height - (height / 2);

    // Draw options.
    Font font = $package->fonts[FONT_04B_03_E];
    for (size_t i=0; i < 4; ++i)
    {
        const char *text = _optionList[i];
        int32_t fontSize = font.baseSize;
        Vector2 position = {0};

        position.x = (width / 2) - (MeasureText(text, fontSize) / 2); 
        position.y = height + (i * fontSize);

        DrawTextEx(
            font,
            text,
            position,
            fontSize,
            1,
            _option == i ? PONG_COLOR_3 : PONG_COLOR_2
        );
    }
}

PONG static void _draw_author(void)
{
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();
    // Draw info author.
    Font font = $package->fonts[FONT_BM_GERMAR];
    Vector2 position = {0};
    float fontSize = font.baseSize / 2;
    Vector2 measure = MeasureTextEx(
        font,
        _authorText,
        fontSize,
        1
    );
    position.x = (width / 2) - (measure.x / 2);
    position.y = height - measure.y;
    DrawTextEx(
        font,
        _authorText,
        position,
        fontSize,
        1,
        PONG_COLOR_3
    );
}

PONG static void _reset(void)
{
    _option = 0;
}