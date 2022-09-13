#ifndef USER_H_
#define USER_H_

#include <string>
#include <iostream>
#include <map>
using std::cin;
using std::cout;
using std::map;
using std::string;

class User
{
public:
    void setUsername(const string &username) { this->username = username; }

    void setPassword(const string &password) { this->password = password; }

    string getUsername() const { return username; }

    string getPassword() const { return password; }

private:
    string username;
    string password;
};

class Session
{
public:
    ~Session()
    {
        for (auto pair : userDB)
        {
            delete pair.second;
        }
        userDB.clear();
        currentUser = nullptr;
    }

    const User *getCurrentUser() const { return currentUser; }

    void getAccess()
    {
        cout << "Menu \n";
        cout << "\t1: Login\n\t2: Signup\n";
        cout << "Enter number in range 1-2: ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            login();
        }
        else if (choice == 2)
        {
            signUp();
        }
        cout << "Welcome " << currentUser->getUsername() << '\n';
    }

private:
    User *currentUser = nullptr;
    void login()
    {
        loadDatabase();
        while (true)
        {
            // TODO: Dry up
            cout << "Please enter your username and password: \n";
            string username, password;
            cin >> username >> password;
            if (!userDB.count(username))
            {
                cout << "User does not exist\n";
                continue;
            }
            User *user = userDB.find(username)->second;
            if (user->getPassword() != password)
            {
                cout << "Password does not match\n";
                continue;
            }
            currentUser = user;
            break;
        }
    };

    void signUp()
    {
        loadDatabase();
        while (true)
        {
            cout << "Please enter your username and password: \n";
            string username, password;
            cin >> username >> password;

            if (userDB.count(username))
            {
                cout << "User already exists. Please try again\n";
                continue;
            }
            else
            {
                User *newUser = new User();
                newUser->setUsername(username);
                newUser->setPassword(password);
                currentUser = newUser;
                break;
            }
        }
    };

    void loadDatabase()
    {
        // cout << "Session: loadDatabase\n";
        User *customer = new User();
        customer->setUsername("antoineqian");
        customer->setPassword("222");
        userDB[customer->getUsername()] = customer;
    }

    // Map of users for fast CRUD
    map<string, User *> userDB;
};

#endif /** USER_H_ **/