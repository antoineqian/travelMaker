#include "utils.h"

int getIntFromUser(int low, int high)
{
    cout << "\nEnter number in range " << low << " - " << high << ": ";

    int choice;
    if (cin >> choice)
    {
        if (low <= choice && choice <= high)
            return choice;
        else
        {
            cout << "ERROR: number outside of range...Try again\n";
            return getIntFromUser(low, high);
        }
    }
    else
    {
        cout << "ERROR: invalid input...Try again\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return getIntFromUser(low, high);
    }
}

int getChoiceFromMenu(const vector<string> &choices, string title)
{
    cout << title << ":\n";
    for (int ch = 0; ch < (int)choices.size(); ++ch)
    {
        cout << "\t" << ch + 1 << ": " << choices[ch] << '\n';
    }
    return getIntFromUser(1, choices.size());
}
