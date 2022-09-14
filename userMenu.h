#ifndef USER_MENU_H_
#define USER_MENU_H_
#include <memory>
#include <vector>
#include "user.h"
#include "utils.h"
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
            int choice = getChoiceFromMenu(vector<string>{
                                               "User profile",
                                               "Make itinerary",
                                               "List my itineraries",
                                               "Log Out"},
                                           "User Menu");
            if (choice == 1)
                showUserProfile();
            else if (choice == 2)
                makeItinerary();
            else if (choice == 3)
                listItineraries();
            else if (choice == 4)
                break;
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
        auto itineraries = this->user.lock()->getItineraries();
        if (itineraries.size() == 0)
        {
            cout << "You have not made any itineraries !\n";
        }
        for (auto iti : itineraries)
        {
            iti.toString();
            cout << '\n';
        }
    }
};

#endif /** USER_MENU_H_ **/