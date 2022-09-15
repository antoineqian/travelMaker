#include <string>
#include <vector>
#include <iostream>
#include "reservation.h"
using std::ostringstream;
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
    static vector<AirJapanFlight> fetchFlights(string from, string from_date, string to, string to_date, int persons)
    {
        vector<AirJapanFlight> flights;

        flights.push_back({200, "25-01-2022", "10-02-2022", "Paris", "Tokyo"});
        flights.push_back({250, "29-01-2022", "10-02-2022", "Paris", "Osaka"});
        return flights;
    }
    static bool reserveFlight(const AirJapanFlight &flight)
    {
        return true;
    }
};

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
    static vector<AirFranceFlight> getAvailableFlights(int nOfSeats, string from, string from_date, string to, string to_date)
    {
        vector<AirFranceFlight> flights;

        flights.push_back({200, "Paris", "Tokyo", "25-01-2022", "10-02-2022"});
        flights.push_back({250, "Paris", "Tokyo", "29-01-2022", "10-02-2022"});
        return flights;
    }

    static bool bookFlight(const AirFranceFlight &flight)
    {
        return true;
    }
};

////////////////////////

class Flight
{
private:
    string airlineName;
    double cost;
    string from;
    string to;
    string dateFrom;
    string dateTo;

public:
    Flight(const string &airlineName, double cost, string &dateFrom, string &dateTo, string &from, string &to) : airlineName(airlineName), cost(cost), dateFrom(dateFrom), dateTo(dateTo), from(from), to(to){};
    string toString() const
    {
        ostringstream oss;
        oss << "Airline: " << airlineName << " Cost: " << cost << " Departure Date " << dateFrom << " Arrival date " << dateTo;
        return oss.str();
    }
    double getCost() const { return cost; }
    const string &getAirlineName() const { return airlineName; }
};
class FlightRequest
{
private:
    string dateFrom;
    string from;
    string dateTo;
    string to;
    int seats;

public:
    FlightRequest(string dateFrom, string from, string dateTo, string to, int seats) : dateFrom(dateFrom), from(from), dateTo(dateTo), to(to), seats(seats){};

    const string &getDateFrom() const { return dateFrom; }

    const string &getDateTo() const { return dateTo; }

    int getSeats() const { return seats; }

    void setSeats(int seats) { this->seats = seats; }

    const string &getFrom() const { return from; }

    const string &getTo() const { return to; }
};

class FlightReservation : public Reservation
{
public:
    FlightReservation(FlightRequest req, Flight flight) : request(req), flight(flight){};

    virtual double totalCost() const override { return flight.getCost(); }

    virtual string toString() const override
    {
        ostringstream oss;
        oss << "Airline reservation with " << flight.getAirlineName() << ": From " << request.getFrom() << " on " << request.getDateFrom() << "\n";
        oss << "to " << request.getTo() << " on " << request.getDateTo() << "\n";
        oss << "\tSeats: " << request.getSeats() << '\n';
        oss << "\tTotal Cost:" << totalCost() << '\n';

        return oss.str();
    }
    const FlightRequest &getRequest() const { return request; }
    const Flight &getFlight() const { return flight; }

private:
    FlightRequest request;
    Flight flight;
};

class IAirlineManager
{
public:
    virtual string getName() const = 0;
    virtual vector<Flight> queryFlights(const FlightRequest &req) const = 0;
    virtual void bookFlight(Flight flight) const = 0;
};

class AirJapanManager : public IAirlineManager
{
    virtual string getName() const override { return "Air Japan"; }

    virtual vector<Flight> queryFlights(const FlightRequest &req) const override
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

    virtual void bookFlight(Flight flight) const override
    {
        // Dummy call to API instead of using flight info`
        // Always succeed
        AirJapanAPI::reserveFlight(AirJapanFlight());
    }
};

class AirFranceManager : public IAirlineManager
{
    virtual string getName() const override { return "Air France"; }

    virtual vector<Flight> queryFlights(const FlightRequest &req) const override
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
    virtual void bookFlight(Flight flight) const override
    {
        // Dummy call to API instead of using flight info
        // Always succeeed
        AirFranceAPI::bookFlight(AirFranceFlight());
    }
};

/*
 * Factory to encapsulate how communications are made with the different airline APIs
 */
class AirlineManagerFactory
{
public:
    static vector<IAirlineManager *> getManagers()
    {
        return vector<IAirlineManager *>{new AirFranceManager(), new AirJapanManager()};
    }

    static IAirlineManager *getManager(const string &name)
    {
        for (IAirlineManager *m : AirlineManagerFactory::getManagers())
        {
            if (m->getName() == name)
                return m;
        }
        return nullptr;
    }
};