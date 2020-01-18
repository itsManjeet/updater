#ifndef __UPDATER_HH__
#define __UPDATER_HH__

#include <releax/config.hh>
#include <releax/releax.hh>
#include <releax/notify.hh>

class Updater {
    std::string DOWNLOAD_LOC = "~/.local/download/";
    std::string UPDATE_FILE = "releax_os_file";

    Config      *cfg;
    std::string server;
    
    std::string get_response(std::string api);
    int download(std::string url);

    int do_update_patch(std::string file);
    int do_update_osimg(std::string file);

public:
    Updater(Config *cfg);

    float check_version();
    void notify_update(std::string string);
    int do_update();
    int Service();
};

#endif