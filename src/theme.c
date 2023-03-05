#include "includes/theme.h"

//----------------------------------------------------------------------------------
// Public functions implementation.
//----------------------------------------------------------------------------------
PONG Theme_t *init_theme(int32_t value)
{
    Theme_t *theme = MemAlloc(sizeof(Theme_t));
    if (theme == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Theme_t pointer.");
        return NULL;
    }
    if (!load_color_theme(theme, value))
    {
        TraceLog(LOG_ERROR, "Couldn't initialize color in Theme_t.");
        unload_theme(&theme);
        return NULL;
    }

    #if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "Theme_t structure created.");
    #endif
    return theme;
}

PONG void unload_theme(Theme_t **ptr)
{
    if(*ptr != NULL)
    {
        MemFree(*ptr);
        *ptr = NULL;
    #if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "Theme_t pointer destroyed.");
    #endif
    }
}

PONG bool load_color_theme(Theme_t *theme, int32_t value)
{
    bool result = true;
    theme->value = value;
    switch (value)
    {
    case 0:
        // GBP-NSO color.
        theme->color[0] = (Color){48, 56, 32, 255};
        theme->color[1] = (Color){99, 114, 81, 255};
        theme->color[2] = (Color){141, 156, 123, 255};
        theme->color[3] = (Color){181, 198, 156, 255};
        break;
    
    case 1:
        // Rustic GB
        theme->color[0] = (Color){44, 33, 55, 255};
        theme->color[1] = (Color){118, 68, 98, 255};
        theme->color[2] = (Color){169, 104, 104, 255};
        theme->color[3] = (Color){237, 180, 161, 255};
        break;
    
    case 2:
        // Mist GB
        theme->color[0] = (Color){45, 27, 0, 255};
        theme->color[1] = (Color){30, 96, 110, 255};
        theme->color[2] = (Color){90, 185, 168, 255};
        theme->color[3] = (Color){196, 240, 194, 255};
        break;
    
    case 3:
        // Gold GB
        theme->color[0] = (Color) {33, 11, 27, 255};
        theme->color[1] = (Color) {77, 34, 44, 255};
        theme->color[2] = (Color) {157, 101, 76, 255};
        theme->color[3] = (Color) {207, 171, 81, 255};
        break;
    
    default:
        result = false;
        theme->value = -1;
        break;
    }

    return result;
}