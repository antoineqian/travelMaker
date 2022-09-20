#include "session.h"

Session::~Session()
{
    userDB.clear();
}

shared_ptr<User> Session::getCurrentUser() { return currentUser; }

void Session::getAccess()
{
    int choice = getChoiceFromMenu(vector<string>{"Login", "SignUp"}, "Access menu");

    if (choice == 1)
        login();
    else if (choice == 2)
        signUp();

    cout << "Welcome " << currentUser->getUsername() << '\n';
}

void Session::login()
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
}

void Session::signUp()
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
}

void Session::loadDatabase()
{
    // Dummy data is used for the database;
    shared_ptr<User> customer = make_shared<User>("antoineqian", "222");
    userDB[customer->getUsername()] = customer;
}