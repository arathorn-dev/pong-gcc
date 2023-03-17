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
static int32_t dirX = 1;
static int32_t dirY = 1;

static float SPEED = 7.0f;

static bool isCollisionEnable = true;
static bool isScreenCollision = false;

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
    if (isScreenCollision)
    {
        update_particle();
    }
    else
    {
        Vector2 position = (Vector2){0};
        position.x = ball->transform.x;
        position.y = ball->transform.y;

        position.x += cosf(DEG2RAD * ball->angle) * SPEED * dirX;
        position.y += sinf(DEG2RAD * ball->angle) * SPEED * dirY;

        position = _check_collision(ball, position, rect0, rect1);

        if (!isCollisionEnable)
        {
            float middle = GetScreenWidth() / 2;
            isCollisionEnable = (dirX > 0 && position.x > middle) || (dirX < 0 && position.x < middle);
        }

        ball->transform.x = position.x;
        ball->transform.y = position.y;
    }
}

PONG void draw_ball(const Ball_t *const ball)
{
    if (isScreenCollision)
    {
        draw_particle((Vector2){ball->transform.x, ball->transform.y});
    }
    else
    {
        DrawRectangleRec(ball->transform, ball->color);
        // if (isCollisionEnable)
        // {
        //     DrawRectangleLines(
        //         ball->transform.x,
        //         ball->transform.y,
        //         ball->transform.width,
        //         ball->transform.height,
        //         GREEN);
        // }
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
    isScreenCollision = false;
    dirX = GetRandomValue(0, 1) ? -1 : 1;
    dirY = 1;

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
    return isScreenCollision;
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

    if (isCollisionEnable && (isPaletteCollision0 || isPaletteCollision1))
    {
        isCollisionEnable = false;
        dirX *= -1;
        ball->angle = GetRandomValue(30, 60);
        PlaySound($package->sound[SELECT_SOUND]);
    }
    else if (isHorizontalCollision)
    {
        isScreenCollision = true;
        PlaySound($package->sound[EXPLOSION_SOUND]);
    }
    else if (isVerticalCollision)
    {
        dirY *= -1;
        PlaySound($package->sound[SELECT_SOUND]);
    }

    position.x = Clamp(position.x, 0, GetScreenWidth() - ball->transform.width);
    position.y = Clamp(position.y, 0, GetScreenHeight() - ball->transform.width);

    return position;
}
