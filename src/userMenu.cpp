#include "userMenu.h"

UserMenu::UserMenu(shared_ptr<User> usr)
{
    this->user = usr;
}

void UserMenu::display()
{
    while (true)
    {
        int choice = getChoiceFromMenu(vector<string>{
                                           "User profile",
                                           "Make itinerary",
                                           "List my itineraries",
                                           "Log Out"},
                                       "User Menu");
        if (choice == 1)
            showUserProfile();
        else if (choice == 2)
            makeItinerary();
        else if (choice == 3)
            listItineraries();
        else if (choice == 4)
            break;
    }
}

void UserMenu::showUserProfile()
{
    cout << "Your username is " << this->user.lock()->getUsername() << '\n';
}

void UserMenu::makeItinerary()
{
    while (true)
    {
        int choice = getChoiceFromMenu(vector<string>{
                                           "Add flight",
                                           "Add hotel",
                                           "Done",
                                           "Cancel"},
                                       "Itinerary Menu");
        if (choice == 1)
            addFlight();
        else if (choice == 2)
        {
            addHotel();
        }
        else if (choice == 3)
        {
            confirmItinerary();
            break;
        }
        else if (choice == 4)
        {
            itinerary.clear();
            break;
        }
    }
}

void UserMenu::listItineraries()
{
    auto itineraries = this->user.lock()->getItineraries();
    if (itineraries.size() == 0)
    {
        cout << "You have not made any itineraries !\n";
    }
    cout << "You have made " << itineraries.size() << " itineraries.\n";
    cout << "*************************************************************\n";
    for (auto iti : itineraries)
    {
        cout << iti.toString() << '\n';
        cout << "*************************************************************\n";
    }
}

void UserMenu::addFlight()
{
    FlightRequest req = readFlightRequest();
    auto flights = Backend::findFlights(req);
    vector<string> flightsInfo;
    for (auto f : flights)
    {
        flightsInfo.push_back(f.toString());
    }
    int flightChoice = getChoiceFromMenu(flightsInfo, "Available Flights");

    Flight flight = flights[flightChoice - 1];

    auto reservation = make_shared<FlightReservation>(req, flight);
    itinerary.add(reservation);
}

const FlightRequest UserMenu::readFlightRequest()
{
    string from;
    cout << "Enter departure location: ";
    cin >> from;

    string to;
    cout << "Enter destination location: ";
    cin >> to;

    string fromDate;
    cout << "Enter departure date: ";
    cin >> fromDate;

    string toDate;
    cout << "Enter return date: ";
    cin >> toDate;

    int seats;
    cout << "Enter number of passengers: ";
    cin >> seats;

    return FlightRequest(fromDate, from, toDate, to, seats);
}

void UserMenu::addHotel()
{
    HotelRequest req = readHotelRequest();
    vector<HotelRoom> rooms = Backend::findRooms(req);
    vector<string> hotelsInfo;
    for (auto r : rooms)
    {
        hotelsInfo.push_back(r.toString());
    }
    int roomChoice = getChoiceFromMenu(hotelsInfo, "Available Rooms");

    HotelRoom chosenRoom = rooms[roomChoice - 1];

    auto reservation = make_shared<HotelReservation>(req, chosenRoom);
    itinerary.add(reservation);
}

const HotelRequest UserMenu::readHotelRequest()
{
    string city;
    cout << "Enter city: ";
    cin >> city;

    string fromDate;
    cout << "Enter start of stay: ";
    cin >> fromDate;

    string toDate;
    cout << "Enter end of stay: ";
    cin >> toDate;

    int guests;
    cout << "Enter number of guests: ";
    cin >> guests;

    return HotelRequest(fromDate, toDate, city, guests);
}

void UserMenu::confirmItinerary()
{
    Backend::confirmItinerary(itinerary);
    this->user.lock()->addItinerary(itinerary);
    itinerary.clear();
}