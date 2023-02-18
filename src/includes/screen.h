#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "../config.h"

PONG typedef enum {
    UNKNOW_SCREEN_E = -1,
    EXIT_SCREEN_E = 0,
    MENU_SCREEN_E,
    OPTION_SCREEN_E,
    GAME_SCREEN_E,
} ScreenType_e;

PONG typedef struct
{
    ScreenType_e type;
    Color background;
} Screen_t;

#if defined(__cplusplus)
extern "C"
{
#endif
    //----------------------------------------------------------------------------------
    // Public functions.
    //----------------------------------------------------------------------------------
    PONG Screen_t *create_menu(void);
    PONG void update_menu(Screen_t *const);
    PONG void draw_menu(const Screen_t *const);
    PONG ScreenType_e unload_menu(const Screen_t *const);
    PONG void close_menu(Screen_t **);

#if defined(__cplusplus)
}
#endif

#endif //__SCREEN_H_
