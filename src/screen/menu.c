#include "../includes/screen.h"
#include "../includes/package.h"
#include "../includes/utils.h"

extern Package_t *$package;
extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static int32_t _option = 0;

static const char *_optionList[3] = {
    "new game",
    "option",
    "exit",
};

static const char *_titleText = "pong";
static const char *_authorText = PONG_AUTHOR;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif
    PONG static void _update(Screen_t *);
    PONG static void _draw(void);
    PONG static void _draw_option_list(void);
    PONG static void _draw_author(void);
    PONG static void _draw_title(void);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
PONG Screen_t *init_menu(void)
{
    Screen_t *screen = MemAlloc(sizeof(Screen_t));
    if (screen == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Screen_t pointer [MENU].");
        return NULL;
    }
#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "Screen_t structure created.");
#endif
    screen->type = MENU_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;
    return screen;
}

PONG void update_menu(Screen_t *const screen)
{
    _update(screen);
}

PONG void draw_menu(const Screen_t *const screen)
{
    ClearBackground($theme->color[2]);
    _draw();
}

PONG void unload_menu(Screen_t **ptr)
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

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
PONG static void _update(Screen_t *screen)
{
    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP))
    {
        _option = Clamp(--_option, 0, 2);
        PlaySound(
            $package->sound[SELECT_SOUND]);
    }
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN))
    {
        _option = Clamp(++_option, 0, 2);
        PlaySound(
            $package->sound[SELECT_SOUND]);
    };

    if (IsKeyPressed(KEY_ENTER))
    {
        switch (_option)
        {
        case 0:
            TraceLog(LOG_INFO, "[GAME]");
            screen->nextScreenType = GAME_SCREEN_E;
            break;
        case 1:
            TraceLog(LOG_INFO, "[OPTION]");
            screen->nextScreenType = OPTION_SCREEN_E;
            break;
        case 2:
            TraceLog(LOG_INFO, "[EXIT]");
            screen->nextScreenType = EXIT_SCREEN_E;
            break;
        default:
            break;
        }
    }
}

PONG static void _draw(void)
{
    _draw_title();
    _draw_option_list();
    _draw_author();
}

PONG static void _draw_option_list(void)
{
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();
    height = height - (height / 3);
    Font font = $package->fonts[FONT_04B_03_E];
    for (size_t i = 0; i < 3; ++i)
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
            _option == i ? $theme->color[0] : $theme->color[1]);
    }
}

PONG static void _draw_author(void)
{
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();
    Font font = $package->fonts[FONT_BM_GERMAR];
    Vector2 position = {0};
    float fontSize = font.baseSize / 2;
    Vector2 measure = MeasureTextEx(
        font,
        _authorText,
        fontSize,
        1);
    position.x = (width / 2) - (measure.x / 2);
    position.y = height - measure.y;
    DrawTextEx(
        font,
        _authorText,
        position,
        fontSize,
        1,
        $theme->color[0]);
}

PONG static void _draw_title(void)
{
    int32_t width = GetScreenWidth();
    Font font = $package->fonts[FONT_ATARI];
    Vector2 position = {0};
    float fontSize = font.baseSize * 4;
    Vector2 measure = MeasureTextEx(
        font,
        _titleText,
        fontSize,
        1);
    position.x = (width / 2) - (measure.x / 2);
    position.y = 100;

    // --
    DrawRectangle(
        position.x + 7.5,
        position.y,
        measure.x,
        10,
        $theme->color[0]);
    DrawTextEx(
        font,
        _titleText,
        position,
        fontSize,
        1,
        $theme->color[3]);
    DrawRectangle(
        position.x + 7.5,
        12 + position.y + measure.y,
        measure.x,
        10,
        $theme->color[0]);
    // --
}