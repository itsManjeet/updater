#include <updater.hh>
#include <unistd.h>
#include <iostream>
#include <releax/http.hh>

Updater::Updater(Config *cfg)
{
    this->cfg = cfg;
    this->server = this->cfg->get("server");
}

float
Updater::check_version()
{

    return strtod(this->get_response("check").c_str(),0);    
}

std::string
Updater::get_response(std::string api)
{
    std::string rel_part;
    switch (osinfo::get_info().release) {
        case osinfo::alpha_release  : rel_part = "alpha"  ;     break;
        case osinfo::beta_release   : rel_part = "beta"   ;     break;
        case osinfo::stable_release : rel_part = "stable" ;     break;
        default:
            return "unknown";
    }

    std::string url = this->server + "/" + api + "/" + rel_part;

    Http http;
    response resp = http.get(url);

    return resp.data;
}
int
Updater::Service()
{
    auto osdata = osinfo::get_info();
    if ( osdata.release == osinfo::unknown_release) {
        std::cout << "Update not supported for unknow release" << std::endl;
        return -1;
    }
    while (true) {
        float web_ver = this->check_version();
        
        std::cout << web_ver << " " << osdata.version << std::endl;
        if (web_ver > osdata.version) {
            std::string message = "Version Update Found from current version '" + std::to_string(osdata.version).substr(0,4) + "' -> '" + std::to_string(web_ver).substr(0,4) + "'";
            Notification n(
                "Updater",
                "New Updates",
                message
            );

            n.send();
        } else if (web_ver < osdata.version) {
            std::string message = "Version Downgrade detected from current version '" + std::to_string(osdata.version).substr(0,4) + "' -> '" + std::to_string(web_ver).substr(0,4) + "'";
            Notification n(
                "Updater",
                "Downgrade Detected",
                message
            );

            n.send();
        }
        sleep(strtod(this->cfg->get("checktime","60").c_str(),0));
    }
    
    return  0;
}


int
Updater::do_update()
{
    auto osdata = osinfo::get_info();
    auto web_ver = this->check_version();
    if (web_ver != osdata.version) {
        std::cout << "Update Detected " + std::to_string(web_ver) + " => " + std::to_string(osdata.version) << std::endl;
        
        int st = this->download(this->get_response("url"));
        if (st != 0) {
            std::cout << "error while downloading data file";
            return -10;
        }
        std::string type_of_update = this->get_response("type");
        if (type_of_update == "patch") {
            return this->do_update_patch(this->DOWNLOAD_LOC + "/" + this->UPDATE_FILE);
        } else if (type_of_update == "osimg") {
            return this->do_update_osimg(this->DOWNLOAD_LOC + "/" + this->UPDATE_FILE);
        } else {
            std::cout << "Unknow type of update " + type_of_update << std::endl;
            return -20;
        }
    }
    std::cout << "System is already Upto date" << std::endl;
    return 0;
}

int
Updater::download(std::string url)
{
    Http http;

    if (!filesys::exist(this->DOWNLOAD_LOC)) {
        filesys::makedir(this->DOWNLOAD_LOC,0755);
    }
    if (http.status != 0) {
        return http.status;
    }
    http.download(url,this->DOWNLOAD_LOC + "/" + this->UPDATE_FILE);   
    return 0;
}

int
Updater::do_update_patch(std::string file)
{
    std::cout << "Updating Patch from " + file << std::endl;
    return 0;
}

int
Updater::do_update_osimg(std::string file)
{
    std::cout << "Updating OS image from " + file << std::endl;
    return 0;
}

