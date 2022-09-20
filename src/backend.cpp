#include "backend.h"

const vector<Flight> Backend::findFlights(FlightRequest &req)
{
    vector<Flight> flights;
    for (auto m : AirlineManagerFactory::getManagers())
    {
        auto airlineFlights = m->queryFlights(req);
        flights.insert(flights.end(), airlineFlights.begin(), airlineFlights.end());
    }
    return flights;
}

const vector<HotelRoom> Backend::findRooms(HotelRequest &req)
{
    vector<HotelRoom> rooms;
    for (auto m : HotelManagerFactory::getManagers())
    {
        auto managerRooms = m->searchRooms(req);
        rooms.insert(rooms.end(), managerRooms.begin(), managerRooms.end());
    }
    return rooms;
}
void Backend::confirmItinerary(Itinerary itinerary)
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