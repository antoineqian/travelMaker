#include <vector>
using std::vector;

class NaebaPrinceRoom
{
public:
    double pricePerNight;
};

class NaebaPrinceAPI
{
public:
    static vector<NaebaPrinceRoom> getAvailableRooms(int beds);
};
