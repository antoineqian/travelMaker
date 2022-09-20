#ifndef FLIGHT_H_
#define FLIGHT_H_
#include "itinerary.h"
#include "airjapan.h"
#include "airfrance.h"

class Flight
{
private:
    double cost;
    string airlineName, from, to, dateFrom, dateTo;

public:
    explicit Flight(const string &airlineName, double cost, string &dateFrom, string &dateTo, string &from, string &to);

    string toString() const;

    double getCost() const;

    const string &getAirlineName() const;
};

class FlightRequest
{
private:
    string dateFrom, from, dateTo, to;
    int seats;

public:
    explicit FlightRequest(string dateFrom, string from, string dateTo, string to, int seats);

    const string &getDateFrom() const;

    const string &getDateTo() const;

    int getSeats() const;

    void setSeats(int seats);

    const string &getFrom() const;

    const string &getTo() const;
};

class FlightReservation : public Reservation
{
private:
    FlightRequest request;
    Flight flight;

public:
    explicit FlightReservation(FlightRequest req, Flight flight);

    virtual double totalCost() const override;

    virtual string toString() const override;

    const FlightRequest &getRequest() const;

    const Flight &getFlight() const;
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
    virtual string getName() const override;

    virtual vector<Flight> queryFlights(const FlightRequest &req) const override;

    virtual void bookFlight(Flight flight) const override;
};

class AirFranceManager : public IAirlineManager
{
    virtual string getName() const override;

    virtual vector<Flight> queryFlights(const FlightRequest &req) const override;

    virtual void bookFlight(Flight flight) const override;
};

/*
 * Factory to encapsulate how communications are made with the different airline APIs
 */
class AirlineManagerFactory
{
public:
    static vector<IAirlineManager *> getManagers();

    static IAirlineManager *getManager(const string &name);
};

#endif /** FLIGHT_H_ **/