#include "includes/ball.h"
#include "includes/theme.h"
#include "includes/raymath.h"
#include "includes/package.h"
#include "includes/particle.h"

extern Package_t *$package;
extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static int32_t _dirX = 1;
static int32_t _dirY = 1;

static float _SPEED = 8.5f;

static bool _isCollisionEnable = true;
static bool _isScreenCollision = false;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
#if defined(__cplusplus)
extern "C"
{
#endif

    PONG static Vector2 _check_collision(
        Ball_t *const ball,
        Vector2 position,
        Rectangle rect0,
        Rectangle rect1);

#if defined(__cplusplus)
}
#endif

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
PONG Ball_t *init_ball(void)
{
    Ball_t *ball = MemAlloc(sizeof(Ball_t));
    if (ball == NULL)
    {
        TraceLog(LOG_ERROR, "Couldn't initialize Ball_t* pointer.");
        return NULL;
    }

#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "Ball_t* structure created.");
#endif

    init_particle();
    reset_ball(ball);
    return ball;
}

PONG void update_ball(Ball_t *ball, Rectangle rect0, Rectangle rect1)
{
    if (_isScreenCollision)
    {
        update_particle();
    }
    else
    {
        Vector2 position = (Vector2){0};
        position.x = ball->transform.x;
        position.y = ball->transform.y;

        position.x += cosf(DEG2RAD * ball->angle) * _SPEED * _dirX;
        position.y += sinf(DEG2RAD * ball->angle) * _SPEED * _dirY;

        position = _check_collision(ball, position, rect0, rect1);

        if (!_isCollisionEnable)
        {
            float middle = GetScreenWidth() / 2;
            _isCollisionEnable = (_dirX > 0 && position.x > middle) || (_dirX < 0 && position.x < middle);
        }

        ball->transform.x = position.x;
        ball->transform.y = position.y;
    }
}

PONG void draw_ball(const Ball_t *const ball)
{
    if (_isScreenCollision)
    {
        draw_particle((Vector2){ball->transform.x, ball->transform.y});
    }
    else
    {
        DrawRectangleRec(ball->transform, ball->color);
    }
}

PONG void unload_ball(Ball_t **ptr)
{
    if (*ptr != NULL)
    {
        unload_particle();
        MemFree(*ptr);
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "Ball_t* pointer destroyed.");
#endif
    }
}

PONG void reset_ball(Ball_t *const ball)
{
    _isScreenCollision = false;
    _dirX = GetRandomValue(0, 1) ? -1 : 1;
    _dirY = 1;

    ball->transform = (Rectangle){0};
    ball->transform.x = (GetScreenWidth() / 2) - (PONG_WIDTH / 2);
    ball->transform.y = (GetScreenHeight() / 2) - (PONG_WIDTH / 2);
    ball->transform.width = PONG_WIDTH;
    ball->transform.height = PONG_WIDTH;

    ball->color = $theme->color[0];
    ball->angle = 0.0f;

    reset_particle();
}

PONG bool check_screen_collision_ball(void)
{
    return _isScreenCollision;
}

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
static Vector2 _check_collision(Ball_t *const ball, Vector2 position, Rectangle rect0, Rectangle rect1)
{
    int32_t screenWidth = GetScreenWidth();
    int32_t screenHeight = GetScreenHeight();

    Rectangle rectBall = (Rectangle){
        position.x,
        position.y,
        ball->transform.width,
        ball->transform.height};

    bool isPaletteCollision0 = CheckCollisionRecs(rectBall, rect0);
    bool isPaletteCollision1 = CheckCollisionRecs(rectBall, rect1);

    bool isHorizontalCollision = position.x < 0 || (position.x + ball->transform.width) > screenWidth;
    bool isVerticalCollision = position.y < PONG_GUI_HEIGHT || (position.y + ball->transform.width) > screenHeight;

    if (_isCollisionEnable && (isPaletteCollision0 || isPaletteCollision1))
    {
        _isCollisionEnable = false;
        _dirX *= -1;
        ball->angle = GetRandomValue(30, 60);
        PlaySound($package->sound[SELECT_SOUND]);
    }
    else if (isHorizontalCollision)
    {
        _isScreenCollision = true;
        PlaySound($package->sound[EXPLOSION_SOUND]);
    }
    else if (isVerticalCollision)
    {
        _dirY *= -1;
        PlaySound($package->sound[SELECT_SOUND]);
    }

    position.x = Clamp(position.x, 0, GetScreenWidth() - ball->transform.width);
    position.y = Clamp(position.y, 0, GetScreenHeight() - ball->transform.width);

    return position;
}
