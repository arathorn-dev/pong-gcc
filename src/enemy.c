#include "includes/palette.h"
#include "includes/theme.h"

extern Theme_t *$theme;

//----------------------------------------------------------------------------------
// Static variables.
//----------------------------------------------------------------------------------
static float _SPEED = 6.8;

//----------------------------------------------------------------------------------
// Public functions.
//----------------------------------------------------------------------------------
PONG Palette_t *init_enemy(void)
{
    Palette_t *enemy = MemAlloc(sizeof(Palette_t));
    if (enemy == NULL)
    {
        TraceLog(LOG_ERROR, "[Enemy] Couldn't initialize Palette_t pointer.");
        return NULL;
    }

#if defined(PONG_DEBUG)
    TraceLog(LOG_INFO, "[Enemy] Palette_t structure created.");
#endif

    enemy->transform = (Rectangle){0};
    enemy->transform.x = GetScreenWidth() - PONG_WIDTH - PONG_PALETTE_SPACE;
    enemy->transform.y = (GetScreenHeight() / 2) - (PONG_HEIGHT / 2);
    enemy->transform.width = PONG_WIDTH;
    enemy->transform.height = PONG_HEIGHT;
    enemy->color = $theme->color[1];

    return enemy;
}
PONG void update_enemy(Palette_t *const enemy, Rectangle rect)
{
    if (rect.x > GetScreenWidth() / 2)
    {
        Vector2 position = (Vector2){0};
        position.y = enemy->transform.y;

        if (position.y > rect.y)
        {
            position.y += -_SPEED;
            enemy->transform.y = Clamp(position.y, PONG_GUI_HEIGHT, GetScreenHeight());
        }
        else if (position.y + enemy->transform.height < rect.y)
        {
            position.y += _SPEED;
            enemy->transform.y = Clamp(position.y, PONG_GUI_HEIGHT, GetScreenHeight() - enemy->transform.height);
        }
    }
}
PONG void draw_enemy(const Palette_t *const enemy)
{
    DrawRectangleRec(enemy->transform, enemy->color);
}
PONG void unload_enemy(Palette_t **ptr)
{
    if (*ptr != NULL)
    {
        MemFree(*ptr);
        (*ptr) = NULL;
#if defined(PONG_DEBUG)
        TraceLog(LOG_INFO, "[Enemy] Palette_t pointer destroyed.");
#endif
    }
}