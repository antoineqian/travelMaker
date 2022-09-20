#ifndef USER_MENU_H_
#define USER_MENU_H_
#include <memory>
#include <iostream>
#include <vector>
#include "flight.h"
#include "hotel.h"
#include "user.h"
#include "utils.h"
#include "backend.h"
#include "itinerary.h"
using std::cin;
using std::cout;
using std::make_shared;
using std::weak_ptr;

class UserMenu
{
private:
    weak_ptr<User> user;
    Itinerary itinerary;

    void showUserProfile();

    void makeItinerary();

    void listItineraries();

    void addFlight();

    const FlightRequest readFlightRequest();

    void addHotel();

    const HotelRequest readHotelRequest();

    void confirmItinerary();

public:
    ~UserMenu();
    explicit UserMenu(shared_ptr<User> usr);

    void display();
};

#endif /** USER_MENU_H_ **/