#include "includes/package.h"

//----------------------------------------------------------------------------------
// Private functions declaration.
//----------------------------------------------------------------------------------

#if defined(__cplusplus)
extern "C"
{
#endif
    static void _load_fonts(Package_t *const);
    static void _unload_fonts(Package_t *const);

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
    return package;
}
PONG void close_package(Package_t **ptr)
{
    if ((*ptr) != NULL)
    {
        _unload_fonts((*ptr));
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
static void _load_fonts(Package_t *const package)
{
    package->fonts[FONT_04B_03_E] = LoadFont("data/fonts/04b_03/04B_03__.TTF");
}
static void _unload_fonts(Package_t *const package)
{
    UnloadFont(package->fonts[FONT_04B_03_E]);
}