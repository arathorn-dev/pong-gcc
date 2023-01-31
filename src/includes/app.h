#ifndef __PONG_APP_H__
#define __PONG_APP_H__

#include "../../config.h"

PONG typedef struct
{
} App_t;

#if defined(__cplusplus)
extern "C"
{
#endif

    App_t *const init_app(void);

    void run_app(App_t *const);

    void end_app(App_t *const *);

#if defined(__cplusplus)
}
#endif

#endif //__PONG_APP_H__