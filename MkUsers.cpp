//
// Created by cenicol on 3/7/21.
//

#include "MkUsers.h"

#include <iostream>
#include <boost/filesystem.hpp>
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>

namespace fs = boost::filesystem;

using namespace std;
//using namespace soci;


MkUsers::MkUsers(std::string directory, bool force)
    : directory_(directory)
    , force_(force)
{}

void MkUsers::create() {

    fs::path p(directory_);
    cout << "Creating user file in directory " << p.c_str() << endl;
    p += "/users";
    cout << "User filename: " << p.c_str() << endl;
    if(exists(p)) {
        if (force_) {
            cout << "File " << p.c_str() << " will be overwritten." << endl;
            fs::remove(p);
            if(exists(p)) {
                throw runtime_error("File not removed.");
            }
        } else {
            cerr << "File " << p.c_str() << " exists. Use --force to overwrite it." << endl;
            return;
        }
    }
    //int rv = sqlite3_open(p.c_str(), &ppDb);
    soci::session sql(soci:: sqlite3, p.c_str());
    if(!exists(p)) {
        throw runtime_error("Unable to create database");
    }
}

/*

CREATE TABLE users (
  user_id INTEGER PRIMARY KEY,
  handle TEXT,
  password TEXT
  );

INSERT INTO users (handle, password) VALUES ('Cassie', 'password');

SELECT * FROM users;

 */
