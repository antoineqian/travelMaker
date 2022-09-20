#include "airfrance.h"

vector<AirFranceFlight> AirFranceAPI::getAvailableFlights(int nOfSeats, string from, string from_date, string to, string to_date)
{
    vector<AirFranceFlight> flights;

    flights.push_back({200, "Paris", "Tokyo", "25-01-2022", "10-02-2022"});
    flights.push_back({250, "Paris", "Tokyo", "29-01-2022", "10-02-2022"});
    return flights;
}

bool AirFranceAPI::bookFlight(const AirFranceFlight &flight)
{
    return true;
}