#include <iostream>
#include "user.h"
using namespace std;

int main()
{
    UserManager *userManager = new UserManager();
    cout << "Menu \n";
    cout << "\t1: Login\n\t2: Signup\n";
    cout << "Enter number in range 1-2: ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        userManager->login();
    }
    else if (choice == 2)
    {
        userManager->signUp();
    }

    return 0;
}
