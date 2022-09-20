#include "flight.h"

/**
 *
 *  Flight
 *
 */

Flight::Flight(const string &airlineName, double cost, string &dateFrom, string &dateTo, string &from, string &to)
    : airlineName(airlineName), cost(cost), dateFrom(dateFrom), dateTo(dateTo), from(from), to(to){};

string Flight::toString() const
{
    ostringstream oss;
    oss << "Airline: " << airlineName << " Cost: " << cost << " Departure Date " << dateFrom << " Arrival date " << dateTo;
    return oss.str();
}

double Flight::getCost() const { return cost; }

const string &Flight::getAirlineName() const { return airlineName; }

/**
 *
 * FlightRequest
 *
 */
FlightRequest::FlightRequest(string dateFrom, string from, string dateTo, string to, int seats)
    : dateFrom(dateFrom), from(from), dateTo(dateTo), to(to), seats(seats){};

const string &FlightRequest::getDateFrom() const { return dateFrom; }

const string &FlightRequest::getDateTo() const { return dateTo; }

int FlightRequest::getSeats() const { return seats; }

void FlightRequest::setSeats(int seats) { this->seats = seats; }

const string &FlightRequest::getFrom() const { return from; }

const string &FlightRequest::getTo() const { return to; }

/**
 *
 * FlightReservation
 *
 */
FlightReservation::FlightReservation(FlightRequest req, Flight flight) : request(req), flight(flight){};

double FlightReservation::totalCost() const { return flight.getCost(); }

string FlightReservation::toString() const
{
    ostringstream oss;
    oss << "Airline reservation with " << flight.getAirlineName() << ": From " << request.getFrom() << " on " << request.getDateFrom() << '\n';
    oss << "to " << request.getTo() << " on " << request.getDateTo() << '\n';
    oss << "\tSeats: " << request.getSeats() << '\n';
    oss << "\tTotal Cost: " << totalCost() << '\n';

    return oss.str();
}
const FlightRequest &FlightReservation::getRequest() const { return request; }

const Flight &FlightReservation::getFlight() const { return flight; }

/**
 *
 * AirJapanManager
 *
 */
string AirJapanManager::getName() const { return "Air Japan"; }

vector<Flight> AirJapanManager::queryFlights(const FlightRequest &req) const
{
    vector<AirJapanFlight> airJapanflights = AirJapanAPI::fetchFlights(
        req.getFrom(),
        req.getDateFrom(),
        req.getTo(),
        req.getDateTo(),
        req.getSeats());

    vector<Flight> flights;

    for (auto &japanFlight : airJapanflights)
    {
        Flight flight = Flight(getName(), japanFlight.cost, japanFlight.date_from, japanFlight.date_to, japanFlight.departure_location, japanFlight.arrival_location);
        flights.push_back(flight);
    }
    return flights;
}

void AirJapanManager::bookFlight(Flight flight) const
{
    // Dummy call to API instead of using flight info`
    // Always succeed
    AirJapanAPI::reserveFlight(AirJapanFlight());
}

/**
 *
 * AirFranceManager
 *
 */
string AirFranceManager::getName() const { return "Air France"; }

vector<Flight> AirFranceManager::queryFlights(const FlightRequest &req) const
{
    vector<AirFranceFlight> airFranceflights = AirFranceAPI::getAvailableFlights(
        req.getSeats(),
        req.getFrom(),
        req.getDateFrom(),
        req.getTo(),
        req.getDateTo());

    vector<Flight> flights;

    for (auto &afFlight : airFranceflights)
    {
        Flight flight = Flight(getName(), afFlight.price, afFlight.fromDate, afFlight.toDate, afFlight.from, afFlight.to);
        flights.push_back(flight);
    }
    return flights;
}
void AirFranceManager::bookFlight(Flight flight) const
{
    // Dummy call to API instead of using flight info
    // Always succeeed
    AirFranceAPI::bookFlight(AirFranceFlight());
}

/**
 *
 * AirlineManagerFactory
 *
 */
vector<IAirlineManager *> AirlineManagerFactory::getManagers()
{
    return vector<IAirlineManager *>{new AirFranceManager(), new AirJapanManager()};
}

IAirlineManager *AirlineManagerFactory::getManager(const string &name)
{
    for (IAirlineManager *m : AirlineManagerFactory::getManagers())
    {
        if (m->getName() == name)
            return m;
    }
    return nullptr;
}
