#ifndef __PONG_PALETTE_H__
#define __PONG_PALETTE_H__

#include "../config.h"

PONG typedef struct {
    Rectangle transform;
    Color color;
} Palette_t;

#if defined(__cplusplus)
extern "C" {
#endif

    PONG Palette_t *init_player(void);
    PONG void update_player(Palette_t *const);
    PONG void draw_player(const Palette_t *const);
    PONG void unload_player(Palette_t **);


#if defined(__cplusplus)
}
#endif


#endif //__PONG_PALETTE_H__