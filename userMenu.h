#ifndef USER_MENU_H_
#define USER_MENU_H_
#include <memory>
#include <vector>
#include "flight.h"
#include "user.h"
#include "utils.h"
using std::shared_ptr;
using std::weak_ptr;
class UserMenu
{
private:
    weak_ptr<User> user;
    Itinerary itinerary;

public:
    ~UserMenu();
    UserMenu(shared_ptr<User> usr)
    {
        this->user = usr;
    }
    void display()
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

    void showUserProfile()
    {
        cout << "Your username is " << this->user.lock()->getUsername() << '\n';
    }

    void makeItinerary()
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

    void listItineraries()
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

    void addFlight()
    {
        FlightRequest req = readRequestFromUser();
        vector<Flight> flights;
        vector<string> flightsInfo;
        for (auto m : AirlineManagerFactory::getManagers())
        {
            auto airlineFlights = m->queryFlights(req);
            for (auto f : airlineFlights)
            {
                flightsInfo.push_back(f.toString());
            }
            flights.insert(flights.end(), airlineFlights.begin(), airlineFlights.end());
        }
        int flightChoice = getChoiceFromMenu(flightsInfo, "Available Flights");

        Flight flight = flights[flightChoice - 1];

        auto reservation = make_shared<FlightReservation>(req, flight);
        itinerary.add(reservation);
    }

    const FlightRequest readRequestFromUser()
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

    void confirmItinerary()
    {
        for (auto r : itinerary.getReservations())
        {
            shared_ptr<FlightReservation> flightRes;

            if ((flightRes = dynamic_pointer_cast<FlightReservation>(r)))
            {
                const string &name = flightRes->getFlight().getAirlineName();
                AirlineManagerFactory::getManager(name)->bookFlight(flightRes->getFlight());
            }
        }
        this->user.lock()->addItinerary(itinerary);
        itinerary.clear();
    }
};

#endif /** USER_MENU_H_ **/