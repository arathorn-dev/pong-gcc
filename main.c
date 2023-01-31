#include "src/includes/app.h"

int main(void)
{
    App_t *const app = init_app();

    run_app(app);
    end_app(&app);

    return 0;
}
