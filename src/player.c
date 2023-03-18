#include "includes/palette.h"
#include "includes/theme.h"

extern Theme_t *$theme;

static float _SPEED = 8.8;

PONG Palette_t *init_player(void)
{
    Palette_t *player = MemAlloc(sizeof(Palette_t));
    if (player == NULL)
    {
        TraceLog(LOG_ERROR, "[Player] Couldn't initialize Palette_t pointer.");
        return NULL;
    }

#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[Player] Palette_t structure created.");
#endif

    player->transform = (Rectangle){0};
    player->transform.x = PONG_PALETTE_SPACE;
    player->transform.y = (GetScreenHeight() / 2) - (PONG_HEIGHT / 2);
    player->transform.width = PONG_WIDTH;
    player->transform.height = PONG_HEIGHT;
    player->color = $theme->color[1];

    return player;
}

PONG void update_player(Palette_t *const player)
{
    float positionY = player->transform.y;
    float height = player->transform.height;
    int32_t screenHeight = GetScreenHeight();

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))
    {
        positionY -= _SPEED;
        positionY = Clamp(positionY, PONG_GUI_HEIGHT, screenHeight);
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))
    {
        positionY += _SPEED;
        positionY = Clamp(positionY, PONG_GUI_HEIGHT, screenHeight - height);
    }
    player->transform.y = positionY;
}

PONG void draw_player(const Palette_t *const player)
{
    DrawRectangleRec(player->transform, player->color);
}

PONG void unload_player(Palette_t **ptr)
{
    if (*ptr != NULL)
    {
        MemFree(*ptr);
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[Player] Palette_t pointer destroyed.");
#endif
    }
}