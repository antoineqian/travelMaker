#include "naebaprince.h";

vector<NaebaPrinceRoom> NaebaPrinceAPI::getAvailableRooms(int beds)
{
    vector<NaebaPrinceRoom> rooms;

    rooms.push_back({50});
    rooms.push_back({60});
    rooms.push_back({130});

    return rooms;
}