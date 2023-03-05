#ifndef __PONG_THEME_H__
#define __PONG_THEME_H__
#include "../config.h"

PONG typedef struct 
{
    Color color[4];
    int32_t value;
} Theme_t;


#if defined(__cplusplus)
extern "C" {
#endif
    PONG Theme_t *init_theme(int32_t);
    PONG bool load_color_theme(Theme_t *, int32_t);
    PONG void unload_theme(Theme_t **);
#if defined(__cplusplus)
}
#endif

#endif //__PONG_THEME_H__