#include "../includes/screen.h"
#include "../includes/package.h"

extern Package_t *$package;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static size_t option = 0;

typedef struct {
    const char *text;
    Vector2 position;
    Color color;
}Word_t;

static Word_t newGameOption = {0};
static Word_t exitOption = {0};

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
    screen->background = PONG_COLOR_0;

    int32_t width = GetScreenWidth();
    int32_t height = GetScreenHeight();

    float heightDiff = height / 1.5;

    newGameOption.text = "New game";
    Vector2 data = MeasureTextEx(
        $package->fonts[FONT_04B_03_E],
        newGameOption.text,
        $package->fonts[FONT_04B_03_E].baseSize,
        1
    );
    newGameOption.position = (Vector2){
        (width / 2) - data.x/2,
        heightDiff
    };
    newGameOption.color = PONG_COLOR_3;

    exitOption.text = "Exit";
    Vector2 data1 = MeasureTextEx(
        $package->fonts[FONT_04B_03_E],
        exitOption.text,    
        $package->fonts[FONT_04B_03_E].baseSize,
        1
    );
    exitOption.position = (Vector2){
        (width / 2) - data1.x/2,
        heightDiff + data.y
    };
    exitOption.color = PONG_COLOR_3;

    return screen;
}

PONG void update_menu(Screen_t *const screen)
{
    if(IsKeyPressed(KEY_W) || IsKeyPressed(KEY_S))
    {
        option = (option == 0) ? 1 : 0;
    }
}

PONG void draw_menu(const Screen_t *const screen)
{
    ClearBackground(screen->background);

    DrawTextEx(
        $package->fonts[FONT_04B_03_E],
        newGameOption.text,
        newGameOption.position,
        $package->fonts[FONT_04B_03_E].baseSize,
        1,
        option == 0 ? newGameOption.color : PONG_COLOR_2);
    
     DrawTextEx(
        $package->fonts[FONT_04B_03_E],
        exitOption.text,
        exitOption.position,
        $package->fonts[FONT_04B_03_E].baseSize,
        1,
        option == 1 ? exitOption.color : PONG_COLOR_2);
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
