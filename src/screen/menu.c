#include "../includes/screen.h"
#include "../includes/package.h"

extern Package_t *$package;

typedef struct {
    const char *text;
    float fontSize; 
    Font * font;
    Color color;
    Vector2 position;
    Vector2 measure;
}Word_t;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static ScreenType_e nextScreen = UNKNOW_SCREEN_E;

static const char *pongText = "pong";
static const char *newGameText = "new game";
static const char *optionText = "option";
static const char *exitText = "exit";
static const char *authorText = "Created by Arathorn 2023";

static int32_t option = 0;
static Word_t pongWord = {0};
static Word_t newGameWord = {0};
static Word_t optionWord = {0};
static Word_t exitWord = {0};
static Word_t authorWord = {0};

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif
    PONG static void _init_word(void);
    PONG static void _update_word(void);
    PONG static void _draw_word(void);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
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
    _init_word();
    return screen;
}

PONG void update_menu(Screen_t *const screen)
{
    _update_word();
}

PONG void draw_menu(const Screen_t *const screen)
{
    ClearBackground(screen->background);
    _draw_word();
}

PONG ScreenType_e unload_menu(const Screen_t *const screen)
{
   //TODO 
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

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
PONG static void _init_word(void)
{
    //TODO: improve load method.
    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();
    float heightDiff = height / 1.5;
    // --
    pongWord.text = pongText;
    pongWord.font = &$package->fonts[FONT_ATARI];
    pongWord.fontSize = pongWord.font->baseSize * 4;
    pongWord.measure = MeasureTextEx(
        (*pongWord.font),
        pongWord.text,
        pongWord.fontSize,
        1
    );
    pongWord.position = (Vector2){
        (width / 2) - pongWord.measure.x/2,
        100
    };
    pongWord.color = PONG_COLOR_3;
    // --
    newGameWord.text = newGameText;
    newGameWord.font = &$package->fonts[FONT_04B_03_E];
    newGameWord.fontSize = newGameWord.font->baseSize;
    newGameWord.measure = MeasureTextEx(
        (*newGameWord.font),
        newGameWord.text,
        newGameWord.fontSize,
        1
    );
    newGameWord.position = (Vector2){
        (width / 2) - newGameWord.measure.x/2,
        heightDiff
    };
    newGameWord.color = PONG_COLOR_3;
    // --
    optionWord.text = optionText;
    optionWord.font = &$package->fonts[FONT_04B_03_E];
    optionWord.fontSize = optionWord.font->baseSize;
    optionWord.measure = MeasureTextEx(
        (*optionWord.font),
        optionWord.text,
        optionWord.fontSize,
        1
    );
    optionWord.position = (Vector2){
        (width / 2) - optionWord.measure.x/2,
        heightDiff + optionWord.measure.y
    };
    optionWord.color = PONG_COLOR_3;
    // --
    exitWord.text = exitText;
    exitWord.font = &$package->fonts[FONT_04B_03_E];
    exitWord.fontSize = exitWord.font->baseSize;
    exitWord.measure = MeasureTextEx(
        (*exitWord.font),
        exitWord.text,    
        exitWord.fontSize,
        1
    );
    exitWord.position = (Vector2){
        (width / 2) - exitWord.measure.x/2,
        heightDiff + (exitWord.measure.y * 2),
    };
    exitWord.color = PONG_COLOR_3;
    // --
    authorWord.text = authorText;
    authorWord.font = &$package->fonts[FONT_BM_GERMAR];
    authorWord.fontSize = authorWord.font->baseSize / 2;
    authorWord.measure = MeasureTextEx(
        (*authorWord.font),
        authorWord.text,    
        authorWord.fontSize,
        1
    );
    authorWord.position = (Vector2){
        (width / 2) - authorWord.measure.x/2,
        height - authorWord.measure.y,
    };
    authorWord.color = PONG_COLOR_3;
}

PONG static void _update_word(void)
{
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        option = Clamp(--option, 0, 2);
        PlaySound(
            $package->sound[SELECT_SOUND]
        );
    }
    else if(IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        option = Clamp(++option, 0, 2);
        PlaySound(
            $package->sound[SELECT_SOUND]
        );
    };
    
    if (IsKeyPressed(KEY_ENTER)) {
        switch (option)
        {
        case 0:
            TraceLog(LOG_INFO, "[GAME]");
            nextScreen = GAME_SCREEN_E;
            break;
        case 1:
            TraceLog(LOG_INFO, "[OPTION]");
            nextScreen = OPTION_SCREEN_E;
            break;
        case 2:
            TraceLog(LOG_INFO, "[EXIT]");
            nextScreen = EXIT_SCREEN_E;
            break;
        default:
            break;
        }
    }
}

PONG static void _draw_word(void)
{
    // --
    DrawRectangle(
        pongWord.position.x + 7.5,
        pongWord.position.y,
        pongWord.measure.x,
        10,
        PONG_COLOR_2
    );
    // --
    DrawTextEx(
        (*pongWord.font),
        pongWord.text,
        pongWord.position,
        pongWord.fontSize,
        1,
        pongWord.color
    );

    // --
    DrawRectangle(
        pongWord.position.x + 7.5,
        12 + pongWord.position.y + pongWord.measure.y,
        pongWord.measure.x,
        10,
        PONG_COLOR_2
    );
    // --

    DrawTextEx(
        (*newGameWord.font),
        newGameWord.text,
        newGameWord.position,
        newGameWord.fontSize,
        1,
        option == 0 ? newGameWord.color : PONG_COLOR_2
    );
    
    DrawTextEx(
        (*optionWord.font),
        optionWord.text,
        optionWord.position,
        optionWord.fontSize,
        1,
        option == 1 ? optionWord.color : PONG_COLOR_2
    );
    
     DrawTextEx(
        (*exitWord.font),
        exitWord.text,
        exitWord.position,
        exitWord.fontSize,
        1,
        option == 2 ? exitWord.color : PONG_COLOR_2
    );

    DrawTextEx(
        (*authorWord.font),
        authorWord.text,
        authorWord.position,
        authorWord.fontSize,
        1,
        authorWord.color
    );
}