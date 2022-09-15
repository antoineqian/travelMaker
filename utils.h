#ifndef UTILS_H_
#define UTILS_H_
#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::string;
using std::vector;

int getIntFromUser(int low, int high)
{
    cout << "\nEnter number in range " << low << " - " << high << ": ";

    int choice;
    cin >> choice;
    if (low <= choice && choice <= high)
        return choice;

    cout << "ERROR: invalid number...Try again\n";
    return getIntFromUser(low, high);
}

int getChoiceFromMenu(const vector<string> &choices, string title)
{
    cout << title << ":\n";
    for (int ch = 0; ch < (int)choices.size(); ++ch)
    {
        cout << "\t" << ch + 1 << ": " << choices[ch] << "\n";
    }
    return getIntFromUser(1, choices.size());
}

#endif /* UTILS_H_ */
