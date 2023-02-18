#include "includes/app.h"
#include "includes/package.h"

//----------------------------------------------------------------------------------
// Shared variables definition(global)
//----------------------------------------------------------------------------------
Package_t *$package = NULL;


//----------------------------------------------------------------------------------
// Private functions declaration.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif
    static void _init_app(App_t *const);
    static void _update_app(App_t *const);
    static void _draw_app(const App_t *const);
    static void _close_screen_app(App_t *const);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
App_t *const create_app(void)
{
    App_t *app = MemAlloc(sizeof(App_t));
    if (app == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize App_t pointer.");
        return NULL;
    }

#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "App_t structure created.");
#endif

    _init_app(app);
    return app;
}
//
void run_app(App_t *const app)
{
    while (!WindowShouldClose())
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
        close_package(&$package);
        MemFree(*ptr);
        ptr = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "App_t pointer destroyed.");
#endif
    }

    CloseWindow();
}

//----------------------------------------------------------------------------------
// Private functions implementation.
//----------------------------------------------------------------------------------
static void _init_app(App_t *const app)
{
    InitWindow(PONG_WIDTH, PONG_HEIGHT, PONG_TITLE);

    // Load screens.
    app->screens = MemAlloc(sizeof(Screen_t *));
    app->screenIndex = 0;

    $package = create_package();

    app->screens[app->screenIndex] = create_menu();
}
//
static void _update_app(App_t *app)
{
    const size_t index = app->screenIndex;
    Screen_t *screen = app->screens[index];

    switch (screen->type)
    {
    case MENU_SCREEN_E:
        update_menu(screen);
        break;

    default:
        break;
    }
}
//
static void _draw_app(const App_t *const app)
{
    BeginDrawing();
    const size_t index = app->screenIndex;
    const Screen_t *const screen = app->screens[index];

    switch (screen->type)
    {
    case MENU_SCREEN_E:
        draw_menu(screen);
        break;

    default:
        break;
    }
    EndDrawing();
}

static void _close_screen_app(App_t *const app)
{
    if (app != NULL)
    {
        const size_t index = app->screenIndex;
        Screen_t *screen = app->screens[index];
        switch (screen->type)
        {
        case MENU_SCREEN_E:
            close_menu(&screen);
            break;

        default:
            break;
        }
    }
}