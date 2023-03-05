#include "includes/app.h"

int main(void)
{
    App_t *const app = create_app();
    if (app != NULL)
    {
        run_app(app);
        close_app(&app);
    } else 
    {
        TraceLog(LOG_ERROR, "Error to init the game.");
    }
    return 0;
}
