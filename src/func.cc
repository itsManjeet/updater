#include <func.hh>
#include <updater.hh>


int func_service(App *app)
{
    Updater updater(app->cfg);

    updater.Service();
    return 0;
}

int func_check(App *app)
{
    Updater updater(app->cfg);

    updater.Service();
    return 0;
}