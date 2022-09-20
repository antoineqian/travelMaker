#include "session.h"
#include "userMenu.h"

using namespace std;

int main()
{
    while (true)
    {
        Session *session = new Session();
        session->getAccess();
        UserMenu *menu = new UserMenu(session->getCurrentUser());
        menu->display();
    }
    return 0;
}
