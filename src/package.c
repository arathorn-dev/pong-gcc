#include "includes/package.h"

//----------------------------------------------------------------------------------
// Private functions declaration.
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    PONG static void _load_fonts(Package_t *const);
    PONG static void _unload_fonts(Package_t *const);

    PONG static void _load_sounds(Package_t *const);
    PONG static void _unload_sounds(Package_t *const);
#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
PONG Package_t *create_package(void)
{
    Package_t *package = MemAlloc(sizeof(Package_t));
    if (package == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Package_t pointer.");
        return NULL;
    }
    _load_fonts(package);
    _load_sounds(package);
    return package;
}
PONG void close_package(Package_t **ptr)
{
    if ((*ptr) != NULL)
    {
        _unload_fonts((*ptr));
        _unload_sounds((*ptr));
        MemFree((*ptr));
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "Package_t pointer destroyed.");
#endif
    }
}

//----------------------------------------------------------------------------------
// Private functions implementation.
//----------------------------------------------------------------------------------
PONG static void _load_fonts(Package_t *const package)
{
    package->fonts[FONT_04B_03_E] = LoadFont("data/fonts/04b_03/04B_03__.TTF");
    package->fonts[FONT_BM_GERMAR] = LoadFont("data/fonts/BM_germar/BMgermar.TTF");
    package->fonts[FONT_ATARI] = LoadFont("data/fonts/Atari/AtariSmall.ttf");
}
PONG static void _unload_fonts(Package_t *const package)
{
    UnloadFont(package->fonts[FONT_04B_03_E]);
    UnloadFont(package->fonts[FONT_BM_GERMAR]);
    UnloadFont(package->fonts[FONT_ATARI]);
}

PONG static void _load_sounds(Package_t *const package) 
{
    package->sound[SELECT_SOUND] = LoadSound("data/sounds/select.wav");
}
PONG static void _unload_sounds(Package_t *const package) 
{
    UnloadSound(package->sound[SELECT_SOUND]);
}