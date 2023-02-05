#include "includes/app.h"

int main(void)
{
    App_t *const app = create_app();

    run_app(app);
    close_app(&app);

    return 0;
}
