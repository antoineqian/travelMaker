#ifndef FLIGHT_H_
#define FLIGHT_H_
#include "itinerary.h"
#include "airjapan.h"
#include "airfrance.h"

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
    explicit Flight(const string &airlineName, double cost, string &dateFrom, string &dateTo, string &from, string &to) : airlineName(airlineName), cost(cost), dateFrom(dateFrom), dateTo(dateTo), from(from), to(to){};
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
    explicit FlightRequest(string dateFrom, string from, string dateTo, string to, int seats) : dateFrom(dateFrom), from(from), dateTo(dateTo), to(to), seats(seats){};

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
    explicit FlightReservation(FlightRequest req, Flight flight) : request(req), flight(flight){};

    virtual double totalCost() const override { return flight.getCost(); }

    virtual string toString() const override
    {
        ostringstream oss;
        oss << "Airline reservation with " << flight.getAirlineName() << ": From " << request.getFrom() << " on " << request.getDateFrom() << '\n';
        oss << "to " << request.getTo() << " on " << request.getDateTo() << '\n';
        oss << "\tSeats: " << request.getSeats() << '\n';
        oss << "\tTotal Cost: " << totalCost() << '\n';

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

#endif /** FLIGHT_H_ **/