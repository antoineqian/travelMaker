#ifndef UTILS_H_
#define UTILS_H_
#include <iostream>
#include <vector>
#include <string>
#include <limits>
using std::cin;
using std::cout;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;

int getIntFromUser(int low, int high);

int getChoiceFromMenu(const vector<string> &choices, string title);

#endif /* UTILS_H_ */
