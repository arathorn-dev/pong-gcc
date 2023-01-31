#include "includes/app.h"

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

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
App_t *const init_app(void)
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
void end_app(App_t *const *ptr)
{
    if (*ptr != NULL)
    {
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
static void _init_app(App_t *const _)
{
    InitWindow(PONG_WIDTH, PONG_HEIGHT, PONG_TITLE);
}
//
static void _update_app(App_t *app)
{
    // TODO
}
//
static void _draw_app(const App_t *const app)
{
    BeginDrawing();
    ClearBackground(PONG_BACKGROUND);
    EndDrawing();
}