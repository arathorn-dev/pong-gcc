#include "includes/particle.h"
#include "includes/theme.h"

extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static Particle_t _particles[PONG_MAX_PARTICLES];
static float _gravity = 3.0f;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
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
    for (size_t i = 0; i < PONG_MAX_PARTICLES; ++i)
    {
        if (_particles[i].active)
        {
            _particles[i].position.y += _gravity / 2;
            _particles[i].position.x += _gravity / 2;
            _particles[i].alpha += -0.05;

            if (_particles[i].alpha < -2.0f)
                _particles[i].active = false;
            // particles[i].rotation += 2.0f;
        }
    }
}

PONG void draw_particle(Vector2 origin)
{
    for (size_t i = 0; i < PONG_MAX_PARTICLES; ++i)
    {
        if (_particles[i].active)
        {
            float rotation = _particles[i].rotation;
            Rectangle rec = (Rectangle){
                origin.x + (_particles[i].position.x * cosf(DEG2RAD * rotation)),
                origin.y + (_particles[i].position.y * sinf(DEG2RAD * rotation)),
                _particles[i].size,
                _particles[i].size,
            };
            DrawRectangleRec(
                rec,
                Fade(_particles[i].color, _particles[i].alpha));
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
    for (size_t i = 0; i < PONG_MAX_PARTICLES; ++i)
    {
        _particles[i].position.x = 0;
        _particles[i].position.y = 0;
        _particles[i].color = $theme->color[0];
        _particles[i].rotation = GetRandomValue(0, 360);
        _particles[i].size = GetRandomValue(5, 20);
        _particles[i].active = true;
        _particles[i].alpha = 1.0;
    }
}
