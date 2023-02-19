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
    ScreenType_e nextScreenType;
} Screen_t;

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif
    
    PONG Screen_t *init_menu(void);
    PONG void update_menu(Screen_t *const);
    PONG void draw_menu(const Screen_t *const);
    PONG void unload_menu(Screen_t **);


    PONG Screen_t *init_option(void);
    PONG void  update_option(Screen_t *const);
    PONG void draw_option(const Screen_t *const);
    PONG void unload_option(Screen_t **);

    PONG Screen_t *init_game(void);
    PONG void  update_game(Screen_t *const);
    PONG void draw_game(const Screen_t *const);
    PONG void unload_game(Screen_t **);

#if defined(__cplusplus)
}
#endif

#endif //__SCREEN_H_
