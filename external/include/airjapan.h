#include <vector>
#include <string>
using std::string;
using std::vector;

class AirJapanFlight
{
public:
    double cost;
    string date_from;
    string date_to;
    string departure_location;
    string arrival_location;
};

/**
 * Dummy API that returns flights ignoring input parameters.
 * The point here is that we have to deal with different APIs from airline company to company.
 */
class AirJapanAPI
{
public:
    static vector<AirJapanFlight> fetchFlights(string from, string from_date, string to, string to_date, int persons);

    static bool reserveFlight(const AirJapanFlight &flight);
};