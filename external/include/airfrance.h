#include <vector>
#include <string>
using std::string;
using std::vector;

class AirFranceFlight
{
public:
    double price;
    string from;
    string to;
    string fromDate;
    string toDate;
};

/**
 * Dummy API that returns flights ignoring input parameters.
 * The point here is that we have to deal with different APIs from airline company to company.
 */
class AirFranceAPI
{
public:
    static vector<AirFranceFlight> getAvailableFlights(int nOfSeats, string from, string from_date, string to, string to_date);

    static bool bookFlight(const AirFranceFlight &flight);
};