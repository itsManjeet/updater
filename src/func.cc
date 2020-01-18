#include <func.hh>
#include <updater.hh>
#include <releax/io.hh>


int func_service(App *app)
{
    Updater updater(app->cfg);

    updater.Service();
    return 0;
}

int func_check(App *app)
{
    Updater updater(app->cfg);  
    auto osdata = osinfo::get_info();
    auto webver = updater.check_version();
    if (webver > osdata.version) {
        std::cout << io::msg() << "System Update found " + std::to_string(webver) + " => " + std::to_string(osdata.version) << io::end();
    } else {
        std::cout << io::msg() << "Sytem is already upto date" << io::end();
    }
    return 0;
}

int func_do_update(App *app)
{
    Updater updater(app->cfg);
    updater.do_update();

    return 0;
}