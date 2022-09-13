#include <iostream>
#include "user.h"
using namespace std;

int main()
{
    Session *session = new Session();
    session->getAccess();
    return 0;
}
