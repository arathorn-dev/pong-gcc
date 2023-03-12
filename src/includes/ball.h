#ifndef __PONG_BALL_H__
#define __PONG_BALL_H__

#include "../config.h"

PONG typedef struct {
    Rectangle transform;
    Color color;
    float angle;
} Ball_t;

#if defined(__cplusplus)
extern "C" {
#endif

    PONG Ball_t *init_ball(void);
    PONG void update_ball(Ball_t *, Rectangle, Rectangle);
    PONG void draw_ball(const Ball_t *const);
    PONG void unload_ball(Ball_t **);

    PONG bool check_collision_ball(void);
    PONG void reset_ball(Ball_t *const);

#if defined(__cplusplus)
}
#endif


#endif // __PONG_BALL_H__