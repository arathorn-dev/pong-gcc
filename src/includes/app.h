#ifndef __PONG_APP_H__
#define __PONG_APP_H__

#include "../config.h"
#include "screen.h"

PONG typedef struct
{
    Screen_t *currentScreen;
    bool isRunning;

} App_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    App_t *const create_app(void);

    void run_app(App_t *const);

    void close_app(App_t *const *);

#if defined(__cplusplus)
}
#endif

#endif //__PONG_APP_H__