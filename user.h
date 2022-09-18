#ifndef USER_H_
#define USER_H_

#include <string>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "reservation.h"
#include "utils.h"
using std::cin;
using std::cout;
using std::make_shared;
using std::map;
using std::shared_ptr;
using std::string;
using std::vector;
class User
{
public:
    User(const User &) = delete;
    void operator=(const User &) = delete;
    explicit User(const string &username, const string &password)
    {
        this->username = username;
        this->password = password;
    };

    string getUsername() const { return username; }

    string getPassword() const { return password; }

    const vector<Itinerary> getItineraries() { return itineraries; };

    void addItinerary(const Itinerary &itinerary)
    {
        itineraries.push_back(itinerary);
    }

private:
    vector<Itinerary> itineraries;
    string username;
    string password;
};

class Session
{
public:
    ~Session()
    {
        userDB.clear();
        currentUser = nullptr;
    }

    shared_ptr<User> getCurrentUser() { return currentUser; }

    void getAccess()
    {
        int choice = getChoiceFromMenu(vector<string>{"Login", "SignUp"}, "Access menu");

        if (choice == 1)
            login();
        else if (choice == 2)
            signUp();

        cout << "Welcome " << currentUser->getUsername() << '\n';
    }

private:
    shared_ptr<User> currentUser = nullptr;
    void login()
    {
        loadDatabase();
        while (true)
        {
            cout << "Please enter your username and password: \n";
            string username, password;
            cin >> username >> password;
            if (!userDB.contains(username))
            {
                cout << "User does not exist\n";
                continue;
            }
            shared_ptr<User> user = userDB.find(username)->second;
            if (user->getPassword() != password)
            {
                cout << "Password does not match\n";
                continue;
            }
            currentUser = make_shared<User>(username, password);
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

            if (userDB.contains(username))
            {
                cout << "User already exists. Please try again\n";
                continue;
            }
            else
            {
                currentUser = make_shared<User>(username, password);
                break;
            }
        }
    };

    void loadDatabase()
    {
        // Dummy data is used for the database;
        shared_ptr<User> customer = make_shared<User>("antoineqian", "222");
        userDB[customer->getUsername()] = customer;
    }

    // Map of users for fast CRUD
    map<string, shared_ptr<User>> userDB;
};

#endif /** USER_H_ **/