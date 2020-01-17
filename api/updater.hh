#ifndef __UPDATER_HH__
#define __UPDATER_HH__

#include <releax/config.hh>

class Updater {

    Config *cfg;
public:
    Updater(Config *cfg);

    int Service();
};

#endif