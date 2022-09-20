#include "airjapan.h"

vector<AirJapanFlight> AirJapanAPI::fetchFlights(string from, string from_date, string to, string to_date, int persons)
{
    vector<AirJapanFlight> flights;

    flights.push_back({200, "25-01-2022", "10-02-2022", "Paris", "Tokyo"});
    flights.push_back({250, "29-01-2022", "10-02-2022", "Paris", "Osaka"});
    return flights;
}

bool AirJapanAPI::reserveFlight(const AirJapanFlight &flight)
{
    return true;
}