#include "includes/particle.h"
#include "includes/theme.h"

extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static Particle_t particles[PONG_MAX_PARTICLES];
static float gravity = 3.0f;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C" {
#endif

PONG void _init(void);

#if defined(__cplusplus)
}
#endif


//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
PONG void init_particle(void)
{
    _init();
}

PONG void update_particle(void)
{
    // for(size_t i=0; i < PONG_MAX_PARTICLES; ++i)
    // {
    //     if (!particles[i].active)
    //     {
    //         particles[i].active = true;
    //         particles[i].position.x = 0;  
    //         particles[i].position.y = 0;
    //         particles[i].alpha = 1.0f;
    //         particles[i].rotation = GetRandomValue(0, 360);
    //         break;
    //     }
    // }
    for(size_t i=0; i < PONG_MAX_PARTICLES; ++i)
    {
        if (particles[i].active)
        {
            particles[i].position.y += gravity / 2;
            particles[i].position.x += gravity / 2;
            particles[i].alpha += -0.05;

            if (particles[i].alpha < -2.0f)
                particles[i].active = false;
            // particles[i].rotation += 2.0f;
        }   
    }
}

PONG void draw_particle(Vector2 origin)
{   
    for(size_t i=0; i < PONG_MAX_PARTICLES; ++i)
    {
        if (particles[i].active)
        {
            float rotation = particles[i].rotation;
            Rectangle rec = (Rectangle){
                origin.x + (particles[i].position.x * cosf(DEG2RAD * rotation)),
                origin.y + (particles[i].position.y * sinf(DEG2RAD * rotation)),
                particles[i].size,
                particles[i].size,
            };
            DrawRectangleRec(
                rec,
                Fade(particles[i].color, particles[i].alpha)
            );
            // DrawRectanglePro(
            //     rec,
            //     (Vector2){0, 0},
            //     rotation,
            //     Fade(particles[i].color, particles[i].alpha)
            // ); 
        }
    }
}

PONG void reset_particle(void)
{
    _init();
}

PONG void unload_particle(void)
{
    // TODO
}

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
PONG void _init(void)
{
    for(size_t i=0; i < PONG_MAX_PARTICLES; ++i)
    {
        particles[i].position.x = 0;  
        particles[i].position.y = 0;
        particles[i].color = $theme->color[2];
        particles[i].rotation = GetRandomValue(0, 360);
        particles[i].size = GetRandomValue(5, 20);
        particles[i].active = true;
        particles[i].alpha = 1.0;
    }
}
