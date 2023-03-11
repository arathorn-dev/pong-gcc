#ifndef __PONG_PARTICLE_H__
#define __PONG_PARTICLE_H__

#include "../config.h"


PONG typedef struct
{
    Vector2 position;
    Color color;
    float alpha;
    float size;
    float rotation;
    bool active;
} Particle_t;

#if defined(__cplusplus)
extern "C" {
#endif

PONG void init_particle(void);
PONG void update_particle(void);
PONG void draw_particle(Vector2);
PONG void reset_particle(void);
PONG void unload_particle(void);

#if defined(__cplusplus)
}
#endif

#endif