#include "includes/ball.h"
#include "includes/theme.h"
#include "includes/raymath.h"
#include "includes/package.h"

extern Package_t *$package;
extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static int32_t dirX = -1; 
static int32_t dirY = 1; 
static float SPEED = 6.2;
static bool pause = false;

//----------------------------------------------------------------------------------
// Static functions definition.
//----------------------------------------------------------------------------------
static Vector2 _check_collision(Ball_t *const ball, Vector2 position, Rectangle rect);
static void _reset(Ball_t *const ball);

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

    float screenWidth = GetScreenWidth();
    float screenHeight = GetScreenHeight();

    ball->transform = (Rectangle){0};
    ball->transform.x = (screenWidth / 2) - (PONG_WIDTH / 2);
    ball->transform.y = (screenHeight / 2) - (PONG_WIDTH / 2);
    ball->transform.width = PONG_WIDTH;
    ball->transform.height = PONG_WIDTH;

    ball->color = $theme->color[2];
    ball->angle = 0.0f;

    return ball;
}

PONG void update_ball(Ball_t *ball, Rectangle rect)
{
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;
    }
    if (!pause) {
        Vector2 position = (Vector2){0};
        position.x = ball->transform.x;
        position.y = ball->transform.y;

        position.x += cosf(DEG2RAD * ball->angle) * SPEED * dirX;
        position.y += sinf(DEG2RAD * ball->angle) * SPEED * dirY;

        position = _check_collision(ball, position, rect);

        ball->transform.x = position.x;
        ball->transform.y = position.y;
    }
}

PONG void draw_ball(const Ball_t *const ball)
{
    DrawRectangleRec(ball->transform, ball->color);
}

PONG void unload_ball(Ball_t **ptr)
{
    if (*ptr != NULL)
    {
        MemFree(*ptr);
        (*ptr) = NULL;
        #if defined(PONG_DEBUG)
            TraceLog(LOG_INFO, "Ball_t* pointer destroyed.");
        #endif
    }
}

//----------------------------------------------------------------------------------
// Static functions implementation.
//----------------------------------------------------------------------------------
static Vector2 _check_collision(Ball_t *const ball, Vector2 position, Rectangle rect)
{
    int32_t screenWidth = GetScreenWidth(); 
    int32_t screenHeight = GetScreenHeight();

    Rectangle rectBall = (Rectangle){
        position.x,
        position.y,
        ball->transform.width,
        ball->transform.height
    };
    bool isPaletteCollision = CheckCollisionRecs(rectBall, rect);
    bool isHorizontalCollision = position.x < 0 || (position.x + ball->transform.width) > screenWidth;
    bool isVerticalCollision = position.y < 0 || (position.y + ball->transform.width) > screenHeight;

    if (isPaletteCollision) {
        dirX *= -1;
        ball->angle = GetRandomValue(30, 60);
        PlaySound($package->sound[0]);
    }
    else if (isHorizontalCollision)
    {
        dirX *= -1;
        ball->angle = GetRandomValue(30, 60);
        PlaySound($package->sound[0]);
    }
    else if (isVerticalCollision)
    {
        dirY *= -1;
        PlaySound($package->sound[0]);
    }

    position.x = Clamp(position.x, 0, GetScreenWidth() - ball->transform.width);
    position.y = Clamp(position.y, 0, GetScreenHeight() - ball->transform.width);

    return position;
}

static void _reset(Ball_t *const ball)
{
    ball->transform.x = (GetScreenWidth() / 2) - (PONG_WIDTH / 2);
    ball->transform.y = (GetScreenWidth() / 2) - (PONG_WIDTH / 2);
}