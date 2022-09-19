#ifndef BACKEND_H_
#define BACKEND_H_
#include <vector>
#include "hotel.h"
#include "flight.h"

class Backend
{
public:
    static const vector<Flight> findFlights(FlightRequest &req)
    {
        vector<Flight> flights;
        for (auto m : AirlineManagerFactory::getManagers())
        {
            auto airlineFlights = m->queryFlights(req);
            flights.insert(flights.end(), airlineFlights.begin(), airlineFlights.end());
        }
        return flights;
    }

    static const vector<HotelRoom> findRooms(HotelRequest &req)
    {
        vector<HotelRoom> rooms;
        for (auto m : HotelManagerFactory::getManagers())
        {
            auto managerRooms = m->searchRooms(req);
            rooms.insert(rooms.end(), managerRooms.begin(), managerRooms.end());
        }
        return rooms;
    }
    static void confirmItinerary(Itinerary itinerary)
    {
        for (auto r : itinerary.getReservations())
        {
            shared_ptr<FlightReservation> flightRes;

            if ((flightRes = dynamic_pointer_cast<FlightReservation>(r)))
            {
                const string &name = flightRes->getFlight().getAirlineName();
                AirlineManagerFactory::getManager(name)->bookFlight(flightRes->getFlight());
            }
            shared_ptr<HotelReservation> hotelRes;

            if ((hotelRes = dynamic_pointer_cast<HotelReservation>(r)))
            {
                const string &name = hotelRes->getRoom().getHotelName();
                HotelManagerFactory::getManager(name)->bookRoom(*hotelRes);
            }
        }
    }
};

#endif /** BACKEND_H_ **/