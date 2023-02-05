#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "../config.h"

typedef enum
{
    SCREEN_MENU_E,
    SCREEN_GAME_E,
} ScreenType;

PONG typedef struct
{

} Screen_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    Screen_t *create_screen(void);

#if defined(__cplusplus)
}
#endif

#endif //__SCREEN_H_