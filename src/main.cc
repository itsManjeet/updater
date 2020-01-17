#include <func.hh>

#define CONF_FILE "updater.conf"

int
main(int    ac,
     char** av)
{

    auto app = new App();

    app->name("updater")
       ->version(0.1)
       ->release('a')
       ->desc("Update manager for releax os")

       ->author("Manjeet Saini","itsmanjeet1998@gmail.com","-")
       ->config_file(CONF_FILE)
       
    /* start Service if no args */
       ->main_func(func_service)

       ->sub("check",
             "check for new updates",
             "",
             func_check);


    int status = app->execute(ac, av);
    delete app;

    return status;
}