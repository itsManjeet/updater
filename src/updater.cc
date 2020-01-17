#include <updater.hh>
#include <releax/http.hh>

Updater::Updater(Config *cfg)
{
    this->cfg = cfg;
}

int
Updater::Service()
{
    std::string server = this->cfg->get("server");
    std::string url = server + "/check/alpha";
    
    Http http;
    std::cout << "Getting response " + url << std::endl;
    response resp = http.get(url);
    std::cout << "Data: " << resp.data << std::endl
              << "Header: " << resp.header << std::endl;

    return  0;
}