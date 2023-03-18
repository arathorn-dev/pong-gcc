#include "../includes/screen.h"
#include "../includes/theme.h"
#include "../includes/package.h"
#include "../includes/palette.h"
#include "../includes/ball.h"

extern Theme_t *$theme;
extern Package_t *$package;

extern int32_t playerScore;
extern int32_t enemyScore;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static Palette_t *_player = NULL;
static Palette_t *_enemy = NULL;
static Ball_t *_ball = NULL;

static bool _pause = false;
static bool _reset = false;

static float _counter = 3.0f;

typedef struct
{
    Vector2 position;
    Font font;
    Color color;
} Score_t;

static Score_t _scores[2];

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif
    PONG static void _draw_counter(void);
    PONG static void _draw_line(void);
    PONG static void _draw_score(void);
    PONG static void _init_score(void);
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

    _pause = false;
    _reset = false;

    _counter = 3.0f;

    playerScore = 0;
    enemyScore = 0;

    screen->type = GAME_SCREEN_E;
    screen->nextScreenType = UNKNOW_SCREEN_E;

    _player = init_player();
    _enemy = init_enemy();
    _ball = init_ball();

    _init_score();
    return screen;
}

PONG void update_game(Screen_t *const screen)
{

    if (IsKeyPressed(KEY_BACKSPACE))
    {
        screen->nextScreenType = MENU_SCREEN_E;
    }
    else if (IsKeyPressed(KEY_P))
    {
        _pause = !_pause;
    }

    if (!_pause)
    {
        update_player(_player);
        update_enemy(_enemy, _ball->transform);
    }

    update_ball(
        _ball,
        _player->transform,
        _enemy->transform);

    if (check_screen_collision_ball())
    {
        if (!_reset)
        {
            if (_ball->transform.x > GetScreenWidth() / 2)
                ++playerScore;
            else
                ++enemyScore;

            if (playerScore >= PONG_MAX_SCORE || enemyScore >= PONG_MAX_SCORE)
            {
                screen->nextScreenType = WINNER_SCREEN_E;
                return;
            }
        }

        _reset = true;
        _pause = true;
    }

    if (_reset)
    {
        _counter -= (1.0f / PONG_FPS);
        if (_counter < 0)
        {
            _counter = 3.0f;
            _reset = false;
            _pause = false;
            reset_ball(_ball);
        }
    }
}

PONG void draw_game(const Screen_t *const screen)
{
    ClearBackground($theme->color[2]);
    _draw_line();
    draw_ball(_ball);
    draw_player(_player);
    draw_enemy(_enemy);
    _draw_score();

    if (_reset)
        _draw_counter();
}

PONG void unload_game(Screen_t **ptr)
{
    if ((*ptr) != NULL)
    {
        unload_player(&_player);
        unload_enemy(&_enemy);
        unload_ball(&_ball);

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
PONG static void _init_score(void)
{
    _scores[0].font = $package->fonts[FONT_BM_GERMAR];
    _scores[0].position = (Vector2){PONG_SCORE_SPACE, 10.0f};
    _scores[0].color = $theme->color[3];

    _scores[1].font = $package->fonts[FONT_BM_GERMAR];
    int32_t width = MeasureText("000", _scores[1].font.baseSize);
    _scores[1].position = (Vector2){GetScreenWidth() - width - PONG_SCORE_SPACE, 10.0f};
    _scores[1].color = $theme->color[3];
}

PONG static void _draw_counter(void)
{
    const char *text = TextFormat("%1.0f", ceilf(_counter));
    Font font = $package->fonts[FONT_04B_03_E];
    int32_t fontSize = font.baseSize * 3;
    Vector2 measure = MeasureTextEx(font, text, fontSize, 1);

    DrawText(
        text,
        GetScreenWidth() / 2 - (measure.x / 3),
        GetScreenHeight() / 2 - (measure.y / 3),
        fontSize,
        $theme->color[0]);
}

PONG static void _draw_line(void)
{
    int32_t width = GetScreenWidth() / 2;
    DrawRectangle(
        width,
        0,
        5,
        GetScreenHeight(),
        $theme->color[1]);
}

PONG static void _draw_score(void)
{
    int score[2] = {playerScore, enemyScore};
    DrawRectangle(0, 0, GetScreenWidth(), PONG_GUI_HEIGHT, $theme->color[0]);
    for (size_t i = 0; i < 2; ++i)
    {
        DrawTextEx(
            _scores[i].font,
            TextFormat("%.3d", score[i]),
            _scores[i].position,
            _scores[i].font.baseSize,
            1,
            _scores[i].color);
    }
}