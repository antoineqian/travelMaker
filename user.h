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

    string getUsername() { return username; }

    string getPassword() { return password; }

private:
    string username;
    string password;
};

class Admin : public User
{
};

class Customer : public User
{
};

class UserManager
{
public:
    void login()
    {
        LoadDatabase();
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
        }
    };

    void signUp()
    {
        LoadDatabase();
        while (true)
        {
            cout << "Please enter your username and password";
            string username, password;
            cin >> username >> password;

            if (userDB.count(username))
            {
                cout << "User already exists. Please try again\n";
                continue;
            }
            else
            {
                Customer *newUser = new Customer();
                newUser->setUsername(username);
                newUser->setPassword(password);
                break;
            }
        }
    };

    void LoadDatabase()
    {
        cout << "UsersManager: LoadDatabase\n";

        Admin *admin = new Admin();
        admin->setUsername("hsian");
        admin->setPassword("5321");
        userDB[admin->getUsername()] = admin;

        Customer *customer = new Customer();
        customer->setUsername("antoineqian");
        customer->setPassword("222");
        userDB[customer->getUsername()] = customer;
    }

    // Map of users for fast CRUD
    map<string, User *> userDB;
};