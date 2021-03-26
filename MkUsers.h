//
// Created by cenicol on 3/7/21.
//

#ifndef CHATTOOLS_MKUSERS_H
#define CHATTOOLS_MKUSERS_H

#include <string>

//#include <sqlite3.h>

class MkUsers {
public:
    MkUsers(std::string dir, bool force = false);
    void create();

private:
    //sqlite3 *ppDb;
    std::string directory_;
    bool force_;

};


#endif //CHATTOOLS_MKUSERS_H
