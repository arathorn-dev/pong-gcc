#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "../config.h"

typedef enum
{
    MENU_SCREEN_E,
} ScreenType;

PONG typedef struct
{
    ScreenType type;
    Color background;
} Screen_t;

#if defined(__cplusplus)
extern "C"
{
#endif
//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
    Screen_t *create_menu(void);
    void update_menu(Screen_t *const);
    void draw_menu(const Screen_t *const);
    void close_menu(Screen_t **);


#if defined(__cplusplus)
}
#endif

#endif //__SCREEN_H_