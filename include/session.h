#ifndef SESSION_H_
#define SESSION_H_
#include <memory>
#include <iostream>
#include <map>
#include "user.h"
using std::make_shared;
using std::map;
using std::shared_ptr;

class Session
{
public:
    ~Session();

    shared_ptr<User> getCurrentUser();

    void getAccess();

private:
    shared_ptr<User> currentUser = nullptr;

    // Map of users for fast CRUD
    map<string, shared_ptr<User>> userDB;

    void login();

    void signUp();

    void loadDatabase();
};

#endif /** SESSION_H_ **/