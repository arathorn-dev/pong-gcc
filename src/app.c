#include <string.h>
#include <stdio.h>
#include "includes/app.h"
#include "includes/package.h"
#include "includes/theme.h"

//----------------------------------------------------------------------------------
// Shared variables definition(global)
//----------------------------------------------------------------------------------
Package_t *$package = NULL;
Theme_t *$theme = NULL;

//----------------------------------------------------------------------------------
// Local variables definition.
//----------------------------------------------------------------------------------
static float alpha = 0.0f;
static bool isTransition = false;
static bool isFadeOut;
static ScreenType_e fromScreen = UNKNOW_SCREEN_E;
static ScreenType_e toScreen = UNKNOW_SCREEN_E;


//----------------------------------------------------------------------------------
// Local functions declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif
    PONG static void _init_app(App_t *const);
    PONG static void _update_app(App_t *const);
    PONG static void _draw_app(const App_t *const);
    PONG static void _close_screen_app(App_t *const);

    PONG static void _transitionToScreen(App_t *const, ScreenType_e screen);
    PONG static void _updateTransition(App_t *const app);
    PONG static void _drawTransition(void);

    // Read & write data.
    PONG static bool _read_file_init(void);
    PONG static bool _write_file_init(void);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
App_t *const create_app(void)
{
    App_t *app = NULL;
    if (_read_file_init())
    {
        app = MemAlloc(sizeof(App_t));
        if (app == NULL)
        {
            TraceLog(LOG_ERROR, "Couldn't initialize App_t pointer.");
            return NULL;
        }

        #if defined(PONG_DEBUG)
            TraceLog(LOG_INFO, "App_t structure created.");
        #endif

        _init_app(app);
    }
    return app;
}
//
void run_app(App_t *const app)
{
    while (app->isRunning)
    {
        _update_app(app);
        _draw_app(app);
    }
}
//
void close_app(App_t *const *ptr)
{
    if (*ptr != NULL)
    {
        _close_screen_app((*ptr));
        _write_file_init();
        close_package(&$package);
        unload_theme(&$theme);
        MemFree(*ptr);
        ptr = NULL;
        #if defined(PONG_DEBUG)
            TraceLog(LOG_INFO, "App_t pointer destroyed.");
        #endif
    }
    CloseAudioDevice();
    CloseWindow();
}

//----------------------------------------------------------------------------------
// Private functions implementation.
//----------------------------------------------------------------------------------
static void _init_app(App_t *const app)
{
    InitWindow(PONG_SCREEN_WIDTH, PONG_SCREEN_HEIGHT, PONG_SCREEN_TITLE);
    InitAudioDevice();
    HideCursor();
    SetTargetFPS(PONG_FPS);
    // Load screen.
    $package = create_package();
    SetSoundVolume($package->sound[0], PONG_VOLUME);
    app->currentScreen = init_menu();
    app->isRunning = true;
}
//
static void _update_app(App_t *app)
{
    Screen_t *const screen = app->currentScreen;
    if (isTransition) {
        _updateTransition(app);
    } else {
        switch (screen->type)
        {
        case MENU_SCREEN_E:
            update_menu(screen);
            if (screen->nextScreenType != UNKNOW_SCREEN_E) 
            {
                if (screen->nextScreenType == EXIT_SCREEN_E)
                 {
                    app->isRunning = false;
                 } else
                 {
                    _transitionToScreen(app, screen->nextScreenType);
                 }
            }
                
            break;
        case OPTION_SCREEN_E:
            update_option(screen);
            if (screen->nextScreenType != UNKNOW_SCREEN_E) 
                _transitionToScreen(app, screen->nextScreenType);
            break;
        case GAME_SCREEN_E:
            update_game(screen);
            if (screen->nextScreenType != UNKNOW_SCREEN_E) 
                _transitionToScreen(app, screen->nextScreenType);
            break;
        default:
            break;
        }
    }
}
//
static void _draw_app(const App_t *const app)
{
    BeginDrawing();
    const Screen_t *const screen = app->currentScreen;

    switch (screen->type)
    {
    case MENU_SCREEN_E:
        draw_menu(screen);
        break;
    case OPTION_SCREEN_E:
        draw_option(screen);
        break;
    case GAME_SCREEN_E:
        draw_game(screen);
        break;
    default:
        break;
    }

    if (isTransition) _drawTransition();
    EndDrawing();
}

static void _close_screen_app(App_t *const app)
{
    if (app != NULL)
    {
        Screen_t *screen = app->currentScreen;
        switch (screen->type)
        {
        case MENU_SCREEN_E:
            unload_menu(&screen);
            break;
        case OPTION_SCREEN_E:
            unload_option(&screen);
        break;
        case GAME_SCREEN_E:
            unload_game(&screen);
        break;
        default:break;
        }
    }
}

PONG static void _transitionToScreen(App_t *const app, ScreenType_e screen)
{
    alpha = 0.0f;
    isTransition = true;
    isFadeOut = false;
    fromScreen = app->currentScreen->type;
    toScreen = screen;
}

PONG static void _updateTransition(App_t *const app)
{
    if (isFadeOut)
    {
        alpha -= 0.05f;
        if (alpha < -0.01f) 
        {
            alpha = 0.0f;
            isTransition = false;
            isFadeOut = false;
            fromScreen = UNKNOW_SCREEN_E;
            toScreen = UNKNOW_SCREEN_E;
        }
    } else 
    {
        alpha += 0.08f;
        if (alpha > 1.01f) 
        {
            switch(fromScreen)
            {
                case MENU_SCREEN_E:
                    unload_menu(&app->currentScreen);
                    break;
                case OPTION_SCREEN_E:
                    unload_option(&app->currentScreen);
                    break;
                case GAME_SCREEN_E:
                    unload_game(&app->currentScreen);
                    break;
                default: break;
            }

            switch(toScreen)
            {
                case MENU_SCREEN_E:
                    app->currentScreen = init_menu();
                    break;
                case OPTION_SCREEN_E:
                    app->currentScreen = init_option();
                    break;
                case GAME_SCREEN_E:
                    app->currentScreen = init_game();
                    break;
                default: break;
            }

            isFadeOut = true;
        } 
    }
}

PONG static void _drawTransition(void)
{
    DrawRectangle(
        0,
        0,
        GetScreenWidth(),
        GetScreenHeight(),
        Fade(BLACK, alpha)     
    );
}

PONG static bool _read_file_init(void)
{
    int32_t result = false;
    if(FileExists(PONG_INIT_FILE))
    {
        char *data = LoadFileText(PONG_INIT_FILE);
        char *aux = data;
        char *nextLine;

        char *line = strtok_s(aux, "\n", &nextLine);
        while (line != NULL)
        {
            int32_t index = TextFindIndex(line, PONG_TOKEN_THEME);
            if (index >= 0)
            {
                char *nextToken;
                char *auxToken = line;
                char *token = strtok_s(auxToken, PONG_TOKEN_EQUAL, &nextToken);
                if (token != NULL) 
                {
                    int32_t value = TextToInteger(nextToken);
                    $theme = init_theme(value);   
                    if ($theme != NULL) {
                        result = true;
                    }                   
                }
            }
            line = strtok_s(NULL, "\n", &nextLine);
        }
        UnloadFileText(data);
    }
    return result;
}

PONG static bool _write_file_init(void)
{   
    int32_t value = $theme->value;
    char strValue[2];
    sprintf(strValue, "%d", value);

    char *base = "[CONFIG]\nTHEME=";
    size_t length = TextLength(base);
    char *data = MemAlloc(sizeof(char) * length + 2);
    memcpy(data, base, length + 1);
    memset(data + length, *strValue, sizeof(char));

    SaveFileText(PONG_INIT_FILE, data);

    MemFree(data);
    data = NULL;

    return true;
}