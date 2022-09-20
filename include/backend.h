#ifndef BACKEND_H_
#define BACKEND_H_
#include <vector>
#include "hotel.h"
#include "flight.h"
#include "itinerary.h"

class Backend
{
public:
    static const vector<Flight> findFlights(FlightRequest &req);

    static const vector<HotelRoom> findRooms(HotelRequest &req);

    static void confirmItinerary(Itinerary itinerary);
};

#endif /** BACKEND_H_ **/