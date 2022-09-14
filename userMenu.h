#ifndef USER_MENU_H_
#define USER_MENU_H_
#include <memory>
#include "user.h"
using std::shared_ptr;
using std::weak_ptr;
class UserMenu
{
private:
    weak_ptr<User> user;

public:
    ~UserMenu();
    UserMenu(shared_ptr<User> usr)
    {
        this->user = usr;
    }
    void display()
    {
        while (true)
        {
            cout << "User menu \n";
            cout << "\t1: User profile\n\t2: Make itinerary\n\t3: List my itineraries\n\t4: Logout\n";
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                showUserProfile();
            }
            else if (choice == 2)
            {
                makeItinerary();
            }
            else if (choice == 3)
            {
                listItineraries();
            }
            else if (choice == 4)
            {
                break;
            }
        }
    }

    void showUserProfile()
    {
        cout << "Your username is " << this->user.lock()->getUsername() << '\n';
    }

    void makeItinerary()
    {
    }
    void listItineraries()
    {
    }
};

#endif /** USER_MENU_H_ **/